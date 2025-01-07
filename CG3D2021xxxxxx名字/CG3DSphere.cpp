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
	mName.Format(_T("球体-%ld"), sID);
}

CG3DSphere::CG3DSphere(double r)
	: CG3DRenderable(CString("CG3DSphere")), radius(r)
{
	mName.Format(_T("球体-%ld"), sID);
}

CG3DSphere::CG3DSphere(const CString& name) : CG3DRenderable(name) {}

CG3DSphere::CG3DSphere(const CG3DSphere& other)
	: CG3DRenderable(CString("CG3DSphere"))
{
	mName.Format(_T("球体-%ld"), sID);
}

CG3DSphere::~CG3DSphere()
{
}

//序列化 
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

//绘制 
void CG3DSphere::Render(CG3DRenderContext* pRC, CG3DCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return;

	//相关属性设置 
	mAppearance.apply(0, pCamera, pRC); //应用外观 
	mPolygonMode.apply(0, pCamera, pRC); //应用多边形模式 

	glPushMatrix();
	glMultMatrixd(mMat.ptr());
	GLUquadricObj* objSphere = gluNewQuadric();
	gluSphere(objSphere, radius, slices, stacks);
	gluDeleteQuadric(objSphere);
	glPopMatrix();
}


void CG3DSphere::computeBoundingBox() //计算包围盒 
{
	mABox.setNull();  //先清空 
	//根据参数和矩阵计算包围盒 

	setBoundsDirty(false);
}
