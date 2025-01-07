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

//���л� 
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

//���ƶ���������������д�� 
void CG3DRenderable::Render(CG3DRenderContext * pRC, CG3DCamera * pCamera) //���ƶ���ʹ��ָ����� 
{
	//��������ʵ�� 
	if (pRC == nullptr || pCamera == nullptr)
		return;
	//����OpenGL�Ļ��� 
}

//ͼ�ζ����Χ�У�AABB��Χ�� 
ABox3d& CG3DRenderable::BoundingABox()
{
	if (boundsDirty())
	{
		computeBoundingBox();
	}
	return mABox;
}

//�������İ�Χ�У���������ʵ�֣� 
void CG3DRenderable::computeBoundingBox()
{
	//��������ʵ�� 
	setBoundsDirty(false);
}

void CG3DRenderable::Translate(double tx, double ty, double tz) //ƽ�ƣ���ά�� 
{
	//ʹ�þ�������ʾ���� 
	mMat.preMultiply(Mat4d::getTranslation(tx, ty, tz));
	setBoundsDirty(true);
}

void CG3DRenderable::Rotate(double angle, double cx, double cy, double cz) //��ת����ά�� 
{
	//ʹ�þ������� 
	mMat.preMultiply(Mat4d::getRotation(angle, Vec3d(cx, cy, cz)));
	setBoundsDirty(true);
}

void CG3DRenderable::Scale(double sx, double sy, double sz) //���ţ���ά�� 
{
	//ʹ�þ������� 
	mMat.preMultiply(Mat4d::getScaling(sx, sy, sz));
	setBoundsDirty(true);
}

bool CG3DRenderable::TimerCallback()
{
	if (mAppearance.Material().Callback() != nullptr) //���ò��ʻص� 
		return mAppearance.Material().Callback()(&mAppearance.Material());

	return false;
}
