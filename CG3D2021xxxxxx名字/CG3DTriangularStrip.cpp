#include "pch.h"
#include "CG3DTriangularStrip.h"
#include "CG3DRenderContext.h" 
#include "CG3DCamera.h" 

IMPLEMENT_SERIAL(CG3DTriangularStrip, CG3DRenderable, 1)

CG3DTriangularStrip::CG3DTriangularStrip()
	: CG3DClosedFoldedLine(CString("CG3DTriangularStrip"))
{
	mName.Format(_T("��������-%ld"), sID);
}

CG3DTriangularStrip::CG3DTriangularStrip(const CG3DTriangularStrip& other)
	: CG3DClosedFoldedLine(CString("CG3DTriangularStrip"))
{
	mName.Format(_T("��������-%ld"), sID);
}

CG3DTriangularStrip::~CG3DTriangularStrip()
{
}

//���� 
void CG3DTriangularStrip::Render(CG3DRenderContext* pRC, CG3DCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return;

	glLineWidth(penWidth());// �����߿�
	glPointSize(penWidth());// ���õ��С
	// ��������
	if (penStyle() == PS_SOLID)
	{
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(penWidth(), 0xFFFF);
	}
	else if (penStyle() == PS_DASH)
	{
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(penWidth(), 0xF0F0);
	}
	else if (penStyle() == PS_DOT)
	{
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(penWidth(), 0xAAAA);
	}

	// ���������ʽ
	if (penFill() == 0) // �����
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // ʹ���߿�ģʽ
	}
	else if (penFill() == 1) // ʵ�����
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // ʹ���߿�ģʽ
	}
	else if (penFill() == 2) // �����
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); // ʹ���߿�ģʽ
	}

	glPushMatrix(); //���浱ǰ������ϵ 
	glMultMatrixd(mMat.ptr()); //ͼ�α任�����֮ǰ����������ϵ���ñ任��Ӱ������ϵ�� 

	glBegin(GL_TRIANGLE_STRIP);
	float red = GetRValue(penColor()) / 255.0f;
	float green = GetGValue(penColor()) / 255.0f;
	float blue = GetBValue(penColor()) / 255.0f;
	glColor3f(red, green, blue); // ʹ��OpenGL����ɫ��ʾ��ʽ������ɫ
	for (Vec3f point : mPoints)
	{
		glVertex3f(point.x(), point.y(), point.z());
	}
	glEnd();
	glPopMatrix(); //�ָ�ԭ������ϵ 
}


