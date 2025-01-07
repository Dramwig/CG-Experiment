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
//序列化 
void CG3DScene::Serialize(CArchive& ar)
{
	CGObject::Serialize(ar); //先调用基类的序列化 

	mRenderables.Serialize(ar); //所用图形对象序列化 
	if (ar.IsStoring())
	{
	}
	else //读取图形文件到内存时要建立图形场景与对象的关联，否则图形对象找不到场景 
	{
		int cnt = mRenderables.GetCount();
		for (int i = 0; i < cnt; i++)
		{
			mRenderables.GetAt(i)->addToScene(this); //建立与场景的关联 
		}
	}
}
//图形对象添加到场景，建立两者之间的双向关联 
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
//渲染场景 
bool CG3DScene::Render(CG3DRenderContext* pRC, CG3DCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return false;

	//补充内容：光源，此处仅简单实现同时打开最多8个光源 
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
	mLightModel.apply(0, pCamera, pRC); //光照模型 
	mShadeModel.apply(0, pCamera, pRC); //着色模式 

	pCamera->Projection(pCamera->ProjectionMode()); //此处假定CG3DCamera由成员函数返回投影模式 
	//图形对象的绘制 
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

//三维场景包围盒计算 
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

//定时回调 
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
			mLights.GetAt(idx)->Callback()(mLights.GetAt(idx)); //调用光源的回调 
			lights++;
		}
	}

	bool changed = false;
	while (i < cnt) //调用场景中每个图形对象的回调进行状态更新 
	{
		CG3DRenderable* s = mRenderables.GetAt(i);
		if (s && s->TimerCallbackEnabled()) //一个类的回调 
		{
			if (s->TimerCallback())
				changed = true;
		}
		if (s && s->Callback()) //特定对象的回调 
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

	// 先删除对象，再从数组中移除指针
	delete mLights[index]; // 确保这个指针指向的对象是通过new分配的
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
