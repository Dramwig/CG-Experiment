#include "pch.h"
#include "CG3DClosedFoldedLine.h"
#include "CG3DRenderContext.h" 
#include "CG3DCamera.h" 

IMPLEMENT_SERIAL(CG3DClosedFoldedLine, CG3DRenderable, 1)

CG3DClosedFoldedLine::CG3DClosedFoldedLine()
	: CG3DRenderable(CString("CG3DClosedFoldedLine"))
{
	mName.Format(_T("封闭折线-%ld"), sID);
}

CG3DClosedFoldedLine::CG3DClosedFoldedLine(const CString& name): CG3DRenderable(name){}

CG3DClosedFoldedLine::CG3DClosedFoldedLine(const CG3DClosedFoldedLine& other)
	: CG3DRenderable(CString("CG3DClosedFoldedLine"))
{
	mName.Format(_T("封闭折线-%ld"), sID);
}

CG3DClosedFoldedLine::~CG3DClosedFoldedLine()
{
}

//序列化 
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

//绘制 
void CG3DClosedFoldedLine::Render(CG3DRenderContext* pRC, CG3DCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return;
	
	glLineWidth(penWidth());// 设置线宽
	glPointSize(penWidth());// 设置点大小
	// 设置线型
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

	// 设置填充样式
	if (penFill() == 0) // 无填充
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // 使用线框模式
	}
	else if (penFill() == 1) // 实体填充
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 使用线框模式
	}
	else if (penFill() == 2) // 点填充
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); // 使用线框模式
	}

	glPushMatrix(); //保存当前的坐标系 
	glMultMatrixd(mMat.ptr()); //图形变换（如果之前不保存坐标系，该变换会影响坐标系） 

	glBegin(GL_LINE_LOOP);
	float red = GetRValue(penColor()) / 255.0f;
	float green = GetGValue(penColor()) / 255.0f;
	float blue = GetBValue(penColor()) / 255.0f;
	glColor3f(red, green, blue); // 使用OpenGL的颜色表示方式设置颜色
	for(Vec3f point: mPoints)
	{
		glVertex3f(point.x(), point.y(), point.z());
	}
	glEnd();
	glPopMatrix(); //恢复原有坐标系 
}


void CG3DClosedFoldedLine::computeBoundingBox() //计算包围盒 
{
	mABox.setNull();  //先清空 
	//根据参数和矩阵计算包围盒 

	setBoundsDirty(false);
}
