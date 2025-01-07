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
	mName.Format(_T("圆柱体-%ld"), sID);
}

CG3DCylinder::CG3DCylinder(double r, double h)
	: CG3DRenderable(CString("CG3DCylinder")), radius(r), height(h)
{
	mName.Format(_T("圆柱体-%ld"), sID);
}

CG3DCylinder::CG3DCylinder(const CString& name) : CG3DRenderable(name) {}

CG3DCylinder::CG3DCylinder(const CG3DCylinder& other)
	: CG3DRenderable(CString("CG3DCylinder"))
{
	mName.Format(_T("圆柱体-%ld"), sID);
}

CG3DCylinder::~CG3DCylinder()
{
}

//序列化 
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

//绘制 
void CG3DCylinder::Render(CG3DRenderContext* pRC, CG3DCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return;

	//相关属性设置 
	mAppearance.apply(0, pCamera, pRC); //应用外观 
	mPolygonMode.apply(0, pCamera, pRC); //应用多边形模式 

	glPushMatrix();
	glMultMatrixd(mMat.ptr()); // 应用变换矩阵

	GLUquadricObj* objCylinder = gluNewQuadric(); // 创建一个新的二次曲面对象
	gluQuadricDrawStyle(objCylinder, GLU_FILL); // 设置绘制样式为填充

	// 绘制圆锥
	gluCylinder(objCylinder, radius, radius, height, slices, stacks);// 基底半径，顶点半径（与基底半径相同表示圆柱），高度，切片数和堆叠数

	gluDeleteQuadric(objCylinder); // 删除二次曲面对象
	glPopMatrix();
}


void CG3DCylinder::computeBoundingBox() //计算包围盒 
{
	mABox.setNull();  //先清空 
	//根据参数和矩阵计算包围盒 

	setBoundsDirty(false);
}
