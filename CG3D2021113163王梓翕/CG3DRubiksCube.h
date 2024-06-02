#pragma once
#include"CG3DCube.h"

class CG3DRubiksCube : public CG3DRenderable
{
	DECLARE_SERIAL(CG3DRubiksCube) //声明为可序列化类
public:
	CG3DRubiksCube();
	CG3DRubiksCube(double size); //给定边长 
	CG3DRubiksCube(const CG3DRubiksCube& other);
	virtual ~CG3DRubiksCube();

	//序列化 
	virtual void Serialize(CArchive& ar);
	//绘制 
	virtual void Render(CG3DRenderContext* pRC, CG3DCamera* pCamera);

	//计算包围盒（重写基类虚函数） 
	virtual void computeBoundingBox();

	void UpRotate(bool R) {
		int y = 2;
		CG3DCube* tmpCubes[3][3];
		for (int x = 0; x < 3; x++)
			for (int z = 0; z < 3; z++) {
				tmpCubes[x][z] = m_pCubes[x][y][z];
				if (!R) {
					m_pCubes[x][y][z]->Rotate(90, 0, 1, 0);
				}
				else {
					m_pCubes[x][y][z]->Rotate(-90, 0, 1, 0);
				}
			}
		for (int x = 0; x < 3; x++)
			for (int z = 0; z < 3; z++)
				if (!R)
					m_pCubes[x][y][z] = tmpCubes[2 - z][x];
				else
					m_pCubes[x][y][z] = tmpCubes[z][2 - x];
					
	}
	void DownRotate(bool R) {
		int y = 0;
		CG3DCube* tmpCubes[3][3];
		for (int x = 0; x < 3; x++)
			for (int z = 0; z < 3; z++) {
				tmpCubes[x][z] = m_pCubes[x][y][z];
				if (!R) {
					m_pCubes[x][y][z]->Rotate(90, 0, 1, 0);
				}
				else {
					m_pCubes[x][y][z]->Rotate(-90, 0, 1, 0);
				}
			}
		for (int x = 0; x < 3; x++)
			for (int z = 0; z < 3; z++)
				if (!R)
					m_pCubes[x][y][z] = tmpCubes[2 - z][x];
				else
					m_pCubes[x][y][z] = tmpCubes[z][2 - x];
	}
	void LeftRotate(bool R) {
		int x = 0;
		CG3DCube* tmpCubes[3][3];
		for (int y = 0; y < 3; y++)
			for (int z = 0; z < 3; z++) {
				tmpCubes[y][z] = m_pCubes[x][y][z];
				if (!R) {
					m_pCubes[x][y][z]->Rotate(90, 1, 0, 0);
				}
				else {
					m_pCubes[x][y][z]->Rotate(-90, 1, 0, 0);
				}
			}
		for (int y = 0; y < 3; y++)
			for (int z = 0; z < 3; z++)
				if (!R)
					m_pCubes[x][y][z] = tmpCubes[z][2 - y];
				else
					m_pCubes[x][y][z] = tmpCubes[2 - z][y];
	}
	void RightRotate(bool R) {
		int x = 2;
		CG3DCube* tmpCubes[3][3];
		for (int y = 0; y < 3; y++)
			for (int z = 0; z < 3; z++) {
				tmpCubes[y][z] = m_pCubes[x][y][z];
				if (!R) {
					m_pCubes[x][y][z]->Rotate(90, 1, 0, 0);
				}
				else {
					m_pCubes[x][y][z]->Rotate(-90, 1, 0, 0);
				}
			}
		for (int y = 0; y < 3; y++)
			for (int z = 0; z < 3; z++)
				if (!R)
					m_pCubes[x][y][z] = tmpCubes[z][2 - y];
				else
					m_pCubes[x][y][z] = tmpCubes[2 - z][y];
	}
	void FrontRotate(bool R) {
		int z = 2;
		CG3DCube* tmpCubes[3][3];
		for (int x = 0; x < 3; x++)
			for (int y = 0; y < 3; y++) {
				tmpCubes[x][y] = m_pCubes[x][y][z];
				if (!R) {
					m_pCubes[x][y][z]->Rotate(90, 0, 0, 1);
				}
				else {
					m_pCubes[x][y][z]->Rotate(-90, 0, 0, 1);
				}
			}
		for (int x = 0; x < 3; x++)
			for (int y = 0; y < 3; y++)
				if (!R)
					m_pCubes[x][y][z] = tmpCubes[y][2 - x];
				else
					m_pCubes[x][y][z] = tmpCubes[2 - y][x];
	}
	void BackRotate(bool R) {
		int z = 0;
		CG3DCube* tmpCubes[3][3];
		for (int x = 0; x < 3; x++)
			for (int y = 0; y < 3; y++) {
				tmpCubes[x][y] = m_pCubes[x][y][z];
				if (!R) 
					m_pCubes[x][y][z]->Rotate(90, 0, 0, 1);
				else 
					m_pCubes[x][y][z]->Rotate(-90, 0, 0, 1);
			}
		for (int x = 0; x < 3; x++)
			for (int y = 0; y < 3; y++) 
				if(!R)
					m_pCubes[x][y][z] = tmpCubes[y][2-x];
				else
					m_pCubes[x][y][z] = tmpCubes[2-y][x];
	}

protected:
	CG3DCube* m_pCubes[3][3][3];
	double mSize; //边长 
};

