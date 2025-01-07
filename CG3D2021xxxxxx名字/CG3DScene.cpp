#include "pch.h" 
#include "CG3DScene.h" 
#include "CG3DRenderable.h" 
#include "CG3DCamera.h" 
#include "CG3DRenderContext.h" 

IMPLEMENT_SERIAL(CG3DScene, CGObject, 1)

CG3DScene::CG3DScene() :CGObject(CString("CG3DScene"))
{
}

CG3DScene::~CG3DScene()
{
	removeAllRenderable();

	//+ 
	RemoveAllLights();
}
//���л� 
void CG3DScene::Serialize(CArchive& ar)
{
	CGObject::Serialize(ar); //�ȵ��û�������л� 

	mRenderables.Serialize(ar); //����ͼ�ζ������л� 
	if (ar.IsStoring())
	{
	}
	else //��ȡͼ���ļ����ڴ�ʱҪ����ͼ�γ��������Ĺ���������ͼ�ζ����Ҳ������� 
	{
		int cnt = mRenderables.GetCount();
		for (int i = 0; i < cnt; i++)
		{
			mRenderables.GetAt(i)->addToScene(this); //�����볡���Ĺ��� 
		}
	}
}
//ͼ�ζ�����ӵ���������������֮���˫����� 
bool CG3DScene::addRenderable(CG3DRenderable* pr)
{
	if (pr == nullptr || !pr->IsKindOf(RUNTIME_CLASS(CG3DRenderable)))
		return false;
	mRenderables.Add(pr);
	pr->addToScene(this);
	return true;
}

CG3DRenderable* CG3DScene::detachRenderable(CG3DRenderable* r)
{
	if (r)
	{
		r->addToScene(nullptr);
		size_t i = 0, cnt = mRenderables.GetSize();
		while (i < cnt)
		{
			if (mRenderables.GetAt(i) == r) {
				mRenderables.RemoveAt(i);
			}
			i++;
		}
	}
	return r;
}

bool CG3DScene::delRenderable(CG3DRenderable* pr)
{
	if (pr == nullptr)
		return false;
	size_t i = 0, cnt = mRenderables.GetSize();
	while (i < cnt)
	{
		if (mRenderables.GetAt(i) == pr) {
			delete mRenderables.GetAt(i);
			mRenderables.RemoveAt(i);
			return true;
		}
		i++;
	}
	return false;
}

void CG3DScene::removeAllRenderable()
{
	size_t i = 0, cnt = mRenderables.GetSize();
	while (i < cnt)
	{
		if (mRenderables.GetAt(i))
			delete mRenderables.GetAt(i);
		i++;
	}
	mRenderables.RemoveAll();
}

CG3DRenderable* CG3DScene::getRenderable(unsigned int index)
{
	if (index >= (unsigned int)mRenderables.GetSize())
		return nullptr;
	return mRenderables.GetAt(index);
}
//��Ⱦ���� 
bool CG3DScene::Render(CG3DRenderContext* pRC, CG3DCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return false;

	//�������ݣ���Դ���˴�����ʵ��ͬʱ�����8����Դ 
	int lights = 0;
	for (INT_PTR idx = 0; idx < mLights.GetSize(); idx++)
	{
		mLights.GetAt(idx)->apply(lights, pCamera, pRC, false);
		lights++;
		if (!mLights.GetAt(idx)->enabled())
		{
			deleteLight(idx);
			idx--;
		}
	}
	for (INT_PTR idx = 0; idx < std::min(mLights.GetSize(), INT_PTR(7)); idx++)
	{
		mLights.GetAt(idx)->apply(idx, pCamera, pRC);
	}
	mLightModel.apply(0, pCamera, pRC); //����ģ�� 
	mShadeModel.apply(0, pCamera, pRC); //��ɫģʽ 

	pCamera->Projection(pCamera->ProjectionMode()); //�˴��ٶ�CG3DCamera�ɳ�Ա��������ͶӰģʽ 
	//ͼ�ζ���Ļ��� 
	size_t i = 0, cnt = mRenderables.GetSize();
	while (i < cnt)
	{
		CG3DRenderable* r = mRenderables.GetAt(i);
		if (r != nullptr)
		{
			r->Render(pRC, pCamera);
		}
		i++;
	}
	return true;
}

//��ά������Χ�м��� 
ABox3d CG3DScene::BoundingABox()
{
	ABox3d box;
	size_t i = 0, cnt = mRenderables.GetSize();
	while (i < cnt)
	{
		CG3DRenderable* r = mRenderables.GetAt(i);
		if (r)
		{
			box.extend(r->BoundingABox());
		}
	}
	return box;
}

//��ʱ�ص� 
bool CG3DScene::TimerCallback()
{
	size_t i = 0, cnt = mRenderables.GetSize();
	if (cnt == 0)
		return false;
	int lights = 0;
	for (INT_PTR idx = 0; idx < mLights.GetSize(); idx++)
	{
		if (mLights.GetAt(idx)->Callback() != nullptr)
		{
			mLights.GetAt(idx)->Callback()(mLights.GetAt(idx)); //���ù�Դ�Ļص� 
			lights++;
		}
	}

	bool changed = false;
	while (i < cnt) //���ó�����ÿ��ͼ�ζ���Ļص�����״̬���� 
	{
		CG3DRenderable* s = mRenderables.GetAt(i);
		if (s && s->TimerCallbackEnabled()) //һ����Ļص� 
		{
			if (s->TimerCallback())
				changed = true;
		}
		if (s && s->Callback()) //�ض�����Ļص� 
		{
			if (s->Callback()(s))
				changed = true;
		}
		i++;
	}
	return changed;
}
bool CG3DScene::AddLight(CGLight * light)
{
	mLights.Add(light);
	return true;
}
bool CG3DScene::deleteLight(int index)
{
	if (index >= mLights.GetSize())
		return false;

	// ��ɾ�������ٴ��������Ƴ�ָ��
	delete mLights[index]; // ȷ�����ָ��ָ��Ķ�����ͨ��new�����
	mLights.RemoveAt(index);
	return true;
}

void CG3DScene::RemoveLastLight()
{
	if(mLights.GetSize() == 0)
		return;
	CGLight* pLight = mLights.GetAt(mLights.GetSize()-1);
	if (pLight != nullptr)
	{
		pLight->setEnabled(false);
	}
}
void CG3DScene::RemoveAllLights()
{
	for (int i = 0; i < mLights.GetSize(); i++)
	{
		CGLight* pLight = mLights.GetAt(i);
		if (pLight != nullptr)
		{
			pLight->setEnabled(false);
		}
	}
}
