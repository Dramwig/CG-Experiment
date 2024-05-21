#include "pch.h"
#include "CG3DBaseDrawTest.h"
#include "CG3DRenderContext.h" 
#include "CG3DCamera.h" 

IMPLEMENT_SERIAL(CG3DBaseDrawTest, CG3DRenderable, 1)

CG3DBaseDrawTest::CG3DBaseDrawTest()
	: CG3DRenderable(CString("CG3DBaseDrawTest"))
{
	mName.Format(_T("测试-%ld"), sID);
}

CG3DBaseDrawTest::CG3DBaseDrawTest(const CG3DBaseDrawTest& other)
	: CG3DRenderable(CString("CG3DTriStrip"))
{
	mName.Format(_T("测试-%ld"), sID);
}

CG3DBaseDrawTest::~CG3DBaseDrawTest()
{
}

//序列化 
void CG3DBaseDrawTest::Serialize(CArchive& ar)
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
void CG3DBaseDrawTest::Render(CG3DRenderContext* pRC, CG3DCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return;

	//// 设置线宽
	//glLineWidth(20.0f);

	//// 设置点大小
	//glPointSize(5.0f);

	//// 设置线型
	//glEnable(GL_LINE_STIPPLE);
	//glLineStipple(1, 0x00FF);

	//// 设置填充样式
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // 使用线框模式

	glPushMatrix(); //保存当前的坐标系 
	glMultMatrixd(mMat.ptr()); //图形变换（如果之前不保存坐标系，该变换会影响坐标系） 


	//glBegin(GL_QUADS); // 开始绘制立方体，共6个面，绘制时注意顶点顺序逆时针方向（从体外向体内看时） 
	//glColor3f(0.0f, 1.0f, 0.0f); // 颜色改为蓝色 
	//glVertex3f(300, 300, -300); // 四边形的右上顶点 (顶面) 
	//glVertex3f(-300, 300, -300); // 四边形的左上顶点 (顶面) 
	//glVertex3f(-300, 300, 300); // 四边形的左下顶点 (顶面) 
	//glVertex3f(300, 300, 300); // 四边形的右下顶点 (顶面) 
	//glEnd();
	LineSegmentsRender();

	glPopMatrix(); //恢复原有坐标系 
}

void CG3DBaseDrawTest::PointRender() //点
{
	glPointSize(10.0f); // 设置点的大小
	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.0f, 0.0f); // 红色
	glVertex3f(0.0f, 0.0f, 0.0f); // 在原点位置绘制一个点
	glEnd();
}
void CG3DBaseDrawTest::LineSegmentsRender() //线段
{
	glLineWidth(20.0f); // 设置线宽
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f); // 绿色
	glVertex3f(-1000.0f, 0.0f, 0.0f); // 线段起点
	glVertex3f(1000.0f, 0.0f, 0.0f); // 线段终点
	glEnd();
}
void CG3DBaseDrawTest::FoldedLineRender() //折线
{
	glLineWidth(2.0f);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 1.0f); // 蓝色
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();
}
void CG3DBaseDrawTest::ClosedFoldedLineRender() // 闭合折线
{
	glLineWidth(2.0f);
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1.0f, 0.0f); // 黄色
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();
}
void CG3DBaseDrawTest::PolygonRender() //多边形
{
	glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.0f, 0.5f); // 紫色
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(1.0f, 0.5f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 0.5f, 0.0f);
	glEnd();
}

void CG3DBaseDrawTest::TriangleRender() //三角形
{
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.5f, 0.2f); // 橙色
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();
}
void CG3DBaseDrawTest::QuadRender() //四边形
{
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.7f, 0.7f); // 青色
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glEnd();
}
void CG3DBaseDrawTest::TriangularFanRender() //三角扇
{
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.5f, 0.0f, 0.5f); // 紫色
	glVertex3f(0.0f, 0.0f, 0.0f);  // 中心点
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(-0.5f, 1.0f, 0.0f);
	glVertex3f(0.5f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f); // 重复第一个顶点来关闭扇形
	glEnd();
}
void CG3DBaseDrawTest::TriangularStripRender() //三角条带
{
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.0f, 1.0f, 0.5f); // 浅绿色
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();
}
void CG3DBaseDrawTest::QuadStripRender() //四边形条带
{
	glBegin(GL_QUAD_STRIP);
	glColor3f(1.0f, 0.3f, 0.3f); // 淡红色
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();
}

void CG3DBaseDrawTest::computeBoundingBox() //计算包围盒 
{
	mABox.setNull();  //先清空 
	//根据参数和矩阵计算包围盒 

	setBoundsDirty(false);
}