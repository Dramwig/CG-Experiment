#pragma once
#include "CG3DRenderable.h" 

class CG3DBaseDrawTest : public CG3DRenderable
{
	DECLARE_SERIAL(CG3DBaseDrawTest)
public:
	CG3DBaseDrawTest();
	CG3DBaseDrawTest(const CG3DBaseDrawTest& other);
	virtual ~CG3DBaseDrawTest();

	//序列化 
	virtual void Serialize(CArchive& ar);
	//绘制 
	virtual void Render(CG3DRenderContext* pRC, CG3DCamera* pCamera);
	void PointRender(); //点
	void LineSegmentsRender(); //线段
	void FoldedLineRender(); //折线
	void ClosedFoldedLineRender(); // 闭合折线
	void PolygonRender(); //多边形
	void TriangleRender(); //三角形
	void QuadRender(); //四边形
	void TriangularFanRender(); //三角扇
	void TriangularStripRender(); //三角条带
	void QuadStripRender(); //四边形条带

	//计算包围盒（重写基类虚函数） 
	virtual void computeBoundingBox();

	//void setSlices(int slices) { mSlices = slices; } 
	//void setStacks(int stacks) { mStacks = stacks; } 

protected:
	//立方体坐标系（坐标原点在中心，坐标轴方向沿边） 
	//double mSize = 1; //边长 
	//绘制时需要的参数：经度、纬度方向的细分数 
	//int mSlices = 16; //z 轴周围的细分(经度线) 。 
	//int mStacks = 16; //沿z轴的细分数 (纬度线) 。 
};
