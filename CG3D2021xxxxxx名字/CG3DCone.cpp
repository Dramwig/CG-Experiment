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
	mName.Format(_T("圆锥体-%ld"), sID);
}

CG3DCone::CG3DCone(double r, double h)
	: CG3DRenderable(CString("CG3DCone")), radius(r), height(h)
{
	mName.Format(_T("圆锥体-%ld"), sID);
}

CG3DCone::CG3DCone(const CString& name) : CG3DRenderable(name) {}

CG3DCone::CG3DCone(const CG3DCone& other)
	: CG3DRenderable(CString("CG3DCone"))
{
	mName.Format(_T("圆锥体-%ld"), sID);
}

CG3DCone::~CG3DCone()
{
}

//序列化 
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

//绘制 
void CG3DCone::Render(CG3DRenderContext* pRC, CG3DCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return;

	//相关属性设置 
	mAppearance.apply(0, pCamera, pRC); //应用外观 
	mPolygonMode.apply(0, pCamera, pRC); //应用多边形模式 

	glPushMatrix();
	glMultMatrixd(mMat.ptr()); // 应用变换矩阵

	GLUquadricObj* objCone = gluNewQuadric(); // 创建一个新的二次曲面对象
	gluQuadricDrawStyle(objCone, GLU_FILL); // 设置绘制样式为填充

	// 绘制圆锥
	gluCylinder(objCone, radius, 0.0, height, slices, stacks); // 基底半径，顶点半径（0表示圆锥），高度，切片数和堆叠数

	gluDeleteQuadric(objCone); // 删除二次曲面对象
	glPopMatrix();
}


void CG3DCone::computeBoundingBox() //计算包围盒 
{
	mABox.setNull();  //先清空 
	//根据参数和矩阵计算包围盒 

	setBoundsDirty(false);
}
