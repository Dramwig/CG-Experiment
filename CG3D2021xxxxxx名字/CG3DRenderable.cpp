#include "pch.h" 
#include "CG3DRenderable.h" 

IMPLEMENT_SERIAL(CG3DRenderable, CGObject, 1)

CG3DRenderable::CG3DRenderable()
	:CGObject(CString("CG3DRenderable"))
{
}
CG3DRenderable::CG3DRenderable(const CString& name)
	: CGObject(CString(name))
{}

CG3DRenderable::~CG3DRenderable()
{
}

//序列化 
void CG3DRenderable::Serialize(CArchive & ar)
{
	CGObject::Serialize(ar);
	if (ar.IsStoring())
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				ar << mMat.e(i, j);
	}
	else
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				ar >> mMat.e(i, j);
	}
}

//绘制对象（在派生类中重写） 
void CG3DRenderable::Render(CG3DRenderContext * pRC, CG3DCamera * pCamera) //绘制对象，使用指定相机 
{
	//派生类中实现 
	if (pRC == nullptr || pCamera == nullptr)
		return;
	//基于OpenGL的绘制 
}

//图形对象包围盒，AABB包围盒 
ABox3d& CG3DRenderable::BoundingABox()
{
	if (boundsDirty())
	{
		computeBoundingBox();
	}
	return mABox;
}

//计算对象的包围盒（派生类中实现） 
void CG3DRenderable::computeBoundingBox()
{
	//派生类中实现 
	setBoundsDirty(false);
}

void CG3DRenderable::Translate(double tx, double ty, double tz) //平移（三维） 
{
	//使用矩阵运算示例： 
	mMat.preMultiply(Mat4d::getTranslation(tx, ty, tz));
	setBoundsDirty(true);
}

void CG3DRenderable::Rotate(double angle, double cx, double cy, double cz) //旋转（三维） 
{
	//使用矩阵运算 
	mMat.preMultiply(Mat4d::getRotation(angle, Vec3d(cx, cy, cz)));
	setBoundsDirty(true);
}

void CG3DRenderable::Scale(double sx, double sy, double sz) //缩放（三维） 
{
	//使用矩阵运算 
	mMat.preMultiply(Mat4d::getScaling(sx, sy, sz));
	setBoundsDirty(true);
}

bool CG3DRenderable::TimerCallback()
{
	if (mAppearance.Material().Callback() != nullptr) //调用材质回调 
		return mAppearance.Material().Callback()(&mAppearance.Material());

	return false;
}
