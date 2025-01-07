#include "pch.h"
#include "CG3DCone.h"
#include "CG3DRenderContext.h" 
#include "CG3DCamera.h" 
#include <vector>
#include "vector3.h"

IMPLEMENT_SERIAL(CG3DCone, CG3DRenderable, 1)

CG3DCone::CG3DCone()
	: CG3DRenderable(CString("CG3DCone"))
{
	mName.Format(_T("Բ׶��-%ld"), sID);
}

CG3DCone::CG3DCone(double r, double h)
	: CG3DRenderable(CString("CG3DCone")), radius(r), height(h)
{
	mName.Format(_T("Բ׶��-%ld"), sID);
}

CG3DCone::CG3DCone(const CString& name) : CG3DRenderable(name) {}

CG3DCone::CG3DCone(const CG3DCone& other)
	: CG3DRenderable(CString("CG3DCone"))
{
	mName.Format(_T("Բ׶��-%ld"), sID);
}

CG3DCone::~CG3DCone()
{
}

//���л� 
void CG3DCone::Serialize(CArchive& ar)
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
void CG3DCone::Render(CG3DRenderContext* pRC, CG3DCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return;

	//����������� 
	mAppearance.apply(0, pCamera, pRC); //Ӧ����� 
	mPolygonMode.apply(0, pCamera, pRC); //Ӧ�ö����ģʽ 

	glPushMatrix();
	glMultMatrixd(mMat.ptr()); // Ӧ�ñ任����

	GLUquadricObj* objCone = gluNewQuadric(); // ����һ���µĶ����������
	gluQuadricDrawStyle(objCone, GLU_FILL); // ���û�����ʽΪ���

	// ����Բ׶
	gluCylinder(objCone, radius, 0.0, height, slices, stacks); // ���װ뾶������뾶��0��ʾԲ׶�����߶ȣ���Ƭ���Ͷѵ���

	gluDeleteQuadric(objCone); // ɾ�������������
	glPopMatrix();
}


void CG3DCone::computeBoundingBox() //�����Χ�� 
{
	mABox.setNull();  //����� 
	//���ݲ����;�������Χ�� 

	setBoundsDirty(false);
}
