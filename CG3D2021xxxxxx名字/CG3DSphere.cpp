#include "pch.h"
#include "CG3DSphere.h"
#include "CG3DRenderContext.h" 
#include "CG3DCamera.h" 
#include <vector>
#include "vector3.h"

IMPLEMENT_SERIAL(CG3DSphere, CG3DRenderable, 1)

CG3DSphere::CG3DSphere()
	: CG3DRenderable(CString("CG3DSphere"))
{
	mName.Format(_T("����-%ld"), sID);
}

CG3DSphere::CG3DSphere(double r)
	: CG3DRenderable(CString("CG3DSphere")), radius(r)
{
	mName.Format(_T("����-%ld"), sID);
}

CG3DSphere::CG3DSphere(const CString& name) : CG3DRenderable(name) {}

CG3DSphere::CG3DSphere(const CG3DSphere& other)
	: CG3DRenderable(CString("CG3DSphere"))
{
	mName.Format(_T("����-%ld"), sID);
}

CG3DSphere::~CG3DSphere()
{
}

//���л� 
void CG3DSphere::Serialize(CArchive& ar)
{
	CG3DRenderable::Serialize(ar);
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

//���� 
void CG3DSphere::Render(CG3DRenderContext* pRC, CG3DCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return;

	//����������� 
	mAppearance.apply(0, pCamera, pRC); //Ӧ����� 
	mPolygonMode.apply(0, pCamera, pRC); //Ӧ�ö����ģʽ 

	glPushMatrix();
	glMultMatrixd(mMat.ptr());
	GLUquadricObj* objSphere = gluNewQuadric();
	gluSphere(objSphere, radius, slices, stacks);
	gluDeleteQuadric(objSphere);
	glPopMatrix();
}


void CG3DSphere::computeBoundingBox() //�����Χ�� 
{
	mABox.setNull();  //����� 
	//���ݲ����;�������Χ�� 

	setBoundsDirty(false);
}
