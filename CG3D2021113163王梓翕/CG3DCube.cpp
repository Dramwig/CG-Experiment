#include "pch.h" 
#include "CG3DCube.h" 
#include "CG3DRenderContext.h" 
#include "CG3DCamera.h" 

IMPLEMENT_SERIAL(CG3DCube, CG3DRenderable, 1)

CG3DCube::CG3DCube()
	: CG3DRenderable(CString("CG3DCube")), mSize(1)
{
	mName.Format(_T("立方体-%ld"), sID);
}
CG3DCube::CG3DCube(double size) //给定边长 
	: CG3DRenderable(CString("CG3DCube")), mSize(size)
{
	mName.Format(_T("立方体-%ld"), sID);
}

CG3DCube::CG3DCube(const CG3DCube& other)
	: CG3DRenderable(CString("CG3DCube")), mSize(other.mSize)
{
	mName.Format(_T("立方体-%ld"), sID);
}

CG3DCube::~CG3DCube()
{
}

//序列化 
void CG3DCube::Serialize(CArchive& ar)
{
	CG3DRenderable::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << mSize;
	}
	else
	{
		ar >> mSize;
	}
}

//绘制 
void CG3DCube::Render(CG3DRenderContext* pRC, CG3DCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return;
	double half = mSize / 2; //模型坐标系在正方体中心，边（面）与坐标轴平行 

	glPushMatrix(); //保存当前的坐标系 
	glMultMatrixd(mMat.ptr()); //图形变换（如果之前不保存坐标系，该变换会影响坐标系） 

	//// 设置线宽
	//glLineWidth(20.0f);

	//// 设置点大小
	//glPointSize(5.0f);

	//// 设置线型
	//glEnable(GL_LINE_STIPPLE);
	//glLineStipple(1, 0x00FF);

	// 设置填充样式
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // 使用线框模式

	glBegin(GL_QUADS); // 开始绘制立方体，共6个面，绘制时注意顶点顺序逆时针方向（从体外向体内看时） 
	//GL_QUADS 模式下，每四个顶点被视为一个四边形

	glColor3f(0.0f, 1.0f, 0.0f); // 颜色改为蓝色 
	glVertex3f(half, half, -half); // 四边形的右上顶点 (顶面) 
	glVertex3f(-half, half, -half); // 四边形的左上顶点 (顶面) 
	glVertex3f(-half, half, half); // 四边形的左下顶点 (顶面) 
	glVertex3f(half, half, half); // 四边形的右下顶点 (顶面) 

	glColor3f(1.0f, 0.5f, 0.0f); // 颜色改成橙色 
	glVertex3f(half, -half, half); // 四边形的右上顶点(底面) 
	glVertex3f(-half, -half, half); // 四边形的左上顶点(底面) 
	glVertex3f(-half, -half, -half); // 四边形的左下顶点(底面) 
	glVertex3f(half, -half, -half); // 四边形的右下顶点(底面) 

	glColor3f(1.0f, 0.0f, 0.0f); // 颜色改成红色 
	glVertex3f(half, half, half); // 四边形的右上顶点(前面) 
	glVertex3f(-half, half, half); // 四边形的左上顶点(前面) 
	glVertex3f(-half, -half, half); // 四边形的左下顶点(前面) 
	glVertex3f(half, -half, half); // 四边形的右下顶点(前面) 

	glColor3f(1.0f, 1.0f, 0.0f); // 颜色改成黄色 
	glVertex3f(half, -half, -half); // 四边形的右上顶点(后面) 
	glVertex3f(-half, -half, -half); // 四边形的左上顶点(后面) 
	glVertex3f(-half, half, -half); // 四边形的左下顶点(后面) 
	glVertex3f(half, half, -half); // 四边形的右下顶点(后面) 

	glColor3f(0.0f, 0.0f, 1.0f); // 颜色改成蓝色 
	glVertex3f(-half, half, half); // 四边形的右上顶点(左面) 
	glVertex3f(-half, half, -half); // 四边形的左上顶点(左面) 
	glVertex3f(-half, -half, -half); // 四边形的左下顶点(左面)
	glVertex3f(-half, -half, half); // 四边形的右下顶点(左面) 

	glColor3f(1.0f, 0.0f, 1.0f); // 颜色改成紫罗兰色 
	glVertex3f(half, half, -half); // 四边形的右上顶点(右面) 
	glVertex3f(half, half, half); // 四边形的左上顶点(右面) 
	glVertex3f(half, -half, half); // 四边形的左下顶点(右面) 
	glVertex3f(half, -half, -half); // 四边形的右下顶点(右面) 

	glEnd(); // 立方体绘制结束 

	//使用glut库方式（glBegin与glEnd范围替换为如下代码） 
	//glutSolidCube(mSize); 

	glPopMatrix(); //恢复原有坐标系 

	//以上是使用gl核心库的实现。以下给出glu库、glut库的调用方式 
	//仅用于其他类中或以后实现复杂场景可直接使用glu库或glut库时的调用方式。 
	//使用glu库绘制球体示意（假定存在CG3DSphere球体类） 
	//GLUquadricObj* objSphere = gluNewQuadric(); 
	//gluSphere(objSphere, mRadius, mSlices, mStacks); //半径、经度方向细分数、维度方向细分数 
	//gluDeleteQuadric(objSphere); 
	//或者使用glut库方式。三种方式使用其中一种。 
	//glutSolidSphere(mRadius, mSlices, mStacks); //半径、经度方向细分数、维度方向细分数 
}

void CG3DCube::computeBoundingBox() //计算包围盒 
{
	mABox.setNull();  //先清空 
	//根据参数和矩阵计算包围盒 

	setBoundsDirty(false);
}