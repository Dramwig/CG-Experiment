#include "pch.h"
#include "CG3DCylinder.h"
#include "CG3DRenderContext.h" 
#include "CG3DCamera.h" 
#include <vector>
#include "vector3.h"

IMPLEMENT_SERIAL(CG3DCylinder, CG3DRenderable, 1)

CG3DCylinder::CG3DCylinder()
	: CG3DRenderable(CString("CG3DCylinder"))
{
	mName.Format(_T("Բ����-%ld"), sID);
}

CG3DCylinder::CG3DCylinder(double r, double h)
	: CG3DRenderable(CString("CG3DCylinder")), radius(r), height(h)
{
	mName.Format(_T("Բ����-%ld"), sID);
}

CG3DCylinder::CG3DCylinder(const CString& name) : CG3DRenderable(name) {}

CG3DCylinder::CG3DCylinder(const CG3DCylinder& other)
	: CG3DRenderable(CString("CG3DCylinder"))
{
	mName.Format(_T("Բ����-%ld"), sID);
}

CG3DCylinder::~CG3DCylinder()
{
}

//���л� 
void CG3DCylinder::Serialize(CArchive& ar)
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
void CG3DCylinder::Render(CG3DRenderContext* pRC, CG3DCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return;

	//����������� 
	mAppearance.apply(0, pCamera, pRC); //Ӧ����� 
	mPolygonMode.apply(0, pCamera, pRC); //Ӧ�ö����ģʽ 

	glPushMatrix();
	glMultMatrixd(mMat.ptr()); // Ӧ�ñ任����

	GLUquadricObj* objCylinder = gluNewQuadric(); // ����һ���µĶ����������
	gluQuadricDrawStyle(objCylinder, GLU_FILL); // ���û�����ʽΪ���

	// ����Բ׶
	gluCylinder(objCylinder, radius, radius, height, slices, stacks);// ���װ뾶������뾶������װ뾶��ͬ��ʾԲ�������߶ȣ���Ƭ���Ͷѵ���

	gluDeleteQuadric(objCylinder); // ɾ�������������
	glPopMatrix();
}


void CG3DCylinder::computeBoundingBox() //�����Χ�� 
{
	mABox.setNull();  //����� 
	//���ݲ����;�������Χ�� 

	setBoundsDirty(false);
}
