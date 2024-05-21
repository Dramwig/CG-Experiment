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