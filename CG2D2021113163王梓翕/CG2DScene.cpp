#include "pch.h"
#include "CG2DScene.h"
#include "CG2DRenderable.h"
#include "CG2DCamera.h"
#include "CG2DRenderContext.h"
IMPLEMENT_SERIAL(CG2DScene, CGObject, 1)
CG2DScene::CG2DScene()
	:CGObject(CString("CG2DScene"))
{
}
CG2DScene::~CG2DScene()
{
	removeAllRenderable();
}
//序列化
void CG2DScene::Serialize(CArchive& ar)
{
	CGObject::Serialize(ar); //先调用基类的序列化
	mRenderables.Serialize(ar); //所用图形对象序列化
	if (ar.IsStoring())
	{
	}
	else //读取图形文件到内存时要建立图形场景与对象的关联，否则图形对象找不到场景
	{
		size_t cnt = mRenderables.GetCount();
		for (size_t i = 0; i < cnt; i++)
		{
			mRenderables.GetAt(i)->addToScene(this); //建立与场景的关联
		}
	}
}
//图形对象添加到场景，建立两者之间的双向关联
bool CG2DScene::addRenderable(CG2DRenderable* pr)
{
	if (pr == nullptr || !pr->IsKindOf(RUNTIME_CLASS(CG2DRenderable)))
		return false;
	mRenderables.Add(pr);
	pr->addToScene(this);
	return true;
}
CG2DRenderable* CG2DScene::detachRenderable(CG2DRenderable* r)
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
bool CG2DScene::delRenderable(CG2DRenderable* pr)
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
void CG2DScene::removeAllRenderable()
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
CG2DRenderable* CG2DScene::getRenderable(unsigned int index)
{
	if (index >= (unsigned int)mRenderables.GetSize())
		return nullptr;
	return mRenderables.GetAt(index);
}
//渲染场景到指定客户区（客户区包含若干视口），每个视口对应一个相机。
bool CG2DScene::Render(CG2DRenderContext* pRC, CG2DCamera* pCamera)
{
	//在派生类中具体实现
	if (pRC == nullptr || pCamera == nullptr)
		return false;
	//绘制场景中的所有图形对象
	size_t i = 0, cnt = mRenderables.GetSize();
	while (i < cnt)
	{
		CG2DRenderable* r = mRenderables.GetAt(i);
		if (r != nullptr)
		{
			r->Render(pRC, pCamera);
		}
		i++;
	}
	//绘制世界坐标系示意（给定范围）
	Vec2d wxs(-200, 0), wxe(200, 0), wys(0, -200), wye(0, 200); //X轴、Y轴
	//转换到视口
	Vec2i vxs = pCamera->WorldtoViewPort(wxs);
	Vec2i vxe = pCamera->WorldtoViewPort(wxe);
	Vec2i vys = pCamera->WorldtoViewPort(wys);
	Vec2i vye = pCamera->WorldtoViewPort(wye);
	//绘制x轴
	HDC hDC = pRC->GetMemHDC();
	CPen penr(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN hOldPen = (HPEN)::SelectObject(hDC, penr.GetSafeHandle());
	::MoveToEx(hDC, vxs.x(), vxs.y(), nullptr);
	::LineTo(hDC, vxe.x(), vxe.y());
	::SelectObject(hDC, hOldPen);
	//绘制y轴
	CPen penb(PS_SOLID, 1, RGB(0, 0, 255));
	hOldPen = (HPEN)::SelectObject(hDC, penb.GetSafeHandle());
	::MoveToEx(hDC, vys.x(), vys.y(), nullptr);
	::LineTo(hDC, vye.x(), vye.y());
	::SelectObject(hDC, hOldPen);
	return true;
}
//二维场景包围盒计算
ABox2d CG2DScene::BoundingABox()
{
	ABox2d box;
	size_t i = 0, cnt = mRenderables.GetSize();
	while (i < cnt)
	{
		CG2DRenderable* r = mRenderables.GetAt(i);
		if (r != nullptr)
		{
			box.extend(((CG2DRenderable*)r)->BoundingABox());
		}
		i++;
	}
	return box;
}