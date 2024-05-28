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

	float red = GetRValue(penColor()) / 255.0f;
	float green = GetGValue(penColor()) / 255.0f;
	float blue = GetBValue(penColor()) / 255.0f;
	glColor3f(red, green, blue); // 使用OpenGL的颜色表示方式设置颜色
	
	glBegin(GL_QUADS);

	std::vector<std::vector<Vec3d>> points(stacks+2, std::vector<Vec3d>(slices));
	double M_PI = 3.14159265358979323846;
	for (int index1 = 0; index1 < stacks+2; ++index1) {
		double j = -90 + index1 * (180.0 / (stacks + 1)); // Adjust for inclusive end points
		double phi = j * M_PI / 180; // Convert degrees to radians
		for (int index2 = 0; index2 < slices; ++index2) {
			double i = index2 * (360.0 / slices); // Slices cover the full 360 degrees
			double theta = i * M_PI / 180; // Convert degrees to radians
			double x = radius * cos(theta) * cos(phi);
			double y = radius * sin(theta) * cos(phi);
			double z = radius * sin(phi);
			points[index1][index2] = Vec3d(x, y, z);
		}
	}
	Vec3d point;
	for (int index1 = 0; index1 < stacks+1; ++index1) {
		for (int index2 = 0; index2 < slices; ++index2) {
			point = points[index1][(index2 + 1) % slices];
			glVertex3f(point.x(), point.y(), point.z());
			point = points[index1][index2];
			glVertex3f(point.x(), point.y(), point.z());
			point = points[index1 + 1][index2];
			glVertex3f(point.x(), point.y(), point.z());
			point = points[index1 + 1][(index2 + 1) % slices];
			glVertex3f(point.x(), point.y(), point.z());
		}
	}

	glEnd();
	glPopMatrix(); //恢复原有坐标系 
}


void CG3DSphere::computeBoundingBox() //计算包围盒 
{
	mABox.setNull();  //先清空 
	//根据参数和矩阵计算包围盒 

	setBoundsDirty(false);
}