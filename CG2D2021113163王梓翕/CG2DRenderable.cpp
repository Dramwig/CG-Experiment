#include "pch.h"
#include "CG2DRenderable.h"
IMPLEMENT_SERIAL(CG2DRenderable, CGObject, 1)
CG2DRenderable::CG2DRenderable()
	:CGObject(CString("CG2DRenderable"))
{
}
CG2DRenderable::CG2DRenderable(const CString& name)
	: CGObject(CString(name))
{
}
//序列化
void CG2DRenderable::Serialize(CArchive& ar)
{
	CGObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << mPenColor << mPenWidth << mPenStyle << mBrushColor << mBrushStyle << mHatchStyle;
	}
	else
	{
		ar >> mPenColor >> mPenWidth >> mPenStyle >> mBrushColor >> mBrushStyle >> mHatchStyle;
	}
}
//绘制
void CG2DRenderable::Render(CG2DRenderContext* pRC, CG2DCamera* pCamera) //绘制对象，使用指定相机
{
	//派生类中实现
}
ABox2d& CG2DRenderable::BoundingABox() //AABB包围盒，可用于设置
{
	if (boundsDirty())
	{
		computeBoundingBox();
	}
	return mABox;
}
void CG2DRenderable::computeBoundingBox() //计算包围盒，需要在派生类中实现
{
	//派生类中实现，然后要调用如下函数
	setBoundsDirty(false);
}