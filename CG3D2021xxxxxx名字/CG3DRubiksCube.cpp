#include "pch.h"
#include "CG3DRubiksCube.h"

IMPLEMENT_SERIAL(CG3DRubiksCube, CG3DRenderable, 1)

CG3DRubiksCube::CG3DRubiksCube()
	:CG3DRenderable(CString("CG3DRubiksCube")), mSize(600) {
	CG3DRubiksCube(600);
}

CG3DRubiksCube::CG3DRubiksCube(double size)
	:CG3DRenderable(CString("CG3DRubiksCube")), mSize(size) {
	mName.Format(_T("魔方-%ld"), sID);
	size += 3*(6+1);  //加上边框宽度
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
			{
				m_pCubes[i][j][k] = new CG3DCube(mSize / 3);
				m_pCubes[i][j][k]->Translate((i - 1) * size / 3, (j - 1) * size / 3, (k - 1) * size / 3);
			}

}

CG3DRubiksCube::CG3DRubiksCube(const CG3DRubiksCube& other)
	: CG3DRenderable(CString("CG3DRubiksCube")), mSize(other.mSize)
{
	mName.Format(_T("魔方-%ld"), sID);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
			{
				m_pCubes[i][j][k] = other.m_pCubes[i][j][k];
			}
}

CG3DRubiksCube::~CG3DRubiksCube() {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				if (m_pCubes[i][j][k] != nullptr)
					delete m_pCubes[i][j][k];
}

//序列化 
void CG3DRubiksCube::Serialize(CArchive& ar) {
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
void CG3DRubiksCube::Render(CG3DRenderContext* pRC, CG3DCamera* pCamera) {
	if (pRC == nullptr || pCamera == nullptr)
		return;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				if (m_pCubes[i][j][k] != nullptr)
				{
					m_pCubes[i][j][k]->Render(pRC, pCamera, mMat);
				}

}

//计算包围盒（重写基类虚函数） 
void CG3DRubiksCube::computeBoundingBox() {
	mABox.setNull();  //先清空 
	//根据参数和矩阵计算包围盒 
	mABox = ABox3d(Vector3<double>(-mSize / 2, -mSize / 2, -mSize / 2), Vector3<double>(mSize / 2, mSize / 2, mSize / 2));
	setBoundsDirty(false);
}
