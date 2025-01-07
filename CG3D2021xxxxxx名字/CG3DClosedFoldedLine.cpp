#include "pch.h"
#include "CG3DClosedFoldedLine.h"
#include "CG3DRenderContext.h" 
#include "CG3DCamera.h" 

IMPLEMENT_SERIAL(CG3DClosedFoldedLine, CG3DRenderable, 1)

CG3DClosedFoldedLine::CG3DClosedFoldedLine()
	: CG3DRenderable(CString("CG3DClosedFoldedLine"))
{
	mName.Format(_T("�������-%ld"), sID);
}

CG3DClosedFoldedLine::CG3DClosedFoldedLine(const CString& name): CG3DRenderable(name){}

CG3DClosedFoldedLine::CG3DClosedFoldedLine(const CG3DClosedFoldedLine& other)
	: CG3DRenderable(CString("CG3DClosedFoldedLine"))
{
	mName.Format(_T("�������-%ld"), sID);
}

CG3DClosedFoldedLine::~CG3DClosedFoldedLine()
{
}

//���л� 
void CG3DClosedFoldedLine::Serialize(CArchive& ar)
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
void CG3DClosedFoldedLine::Render(CG3DRenderContext* pRC, CG3DCamera* pCamera)
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

	glBegin(GL_LINE_LOOP);
	float red = GetRValue(penColor()) / 255.0f;
	float green = GetGValue(penColor()) / 255.0f;
	float blue = GetBValue(penColor()) / 255.0f;
	glColor3f(red, green, blue); // ʹ��OpenGL����ɫ��ʾ��ʽ������ɫ
	for(Vec3f point: mPoints)
	{
		glVertex3f(point.x(), point.y(), point.z());
	}
	glEnd();
	glPopMatrix(); //�ָ�ԭ������ϵ 
}


void CG3DClosedFoldedLine::computeBoundingBox() //�����Χ�� 
{
	mABox.setNull();  //����� 
	//���ݲ����;�������Χ�� 

	setBoundsDirty(false);
}
