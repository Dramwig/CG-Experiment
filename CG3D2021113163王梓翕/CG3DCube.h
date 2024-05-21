#ifndef _CG3DCube_H_INCLUDED 
#define _CG3DCube_H_INCLUDED 

#include "CG3DRenderable.h" 

class CG3DCube : public CG3DRenderable
{
	DECLARE_SERIAL(CG3DCube)
public:
	CG3DCube();
	CG3DCube(double size); //给定边长 
	CG3DCube(const CG3DCube& other);
	virtual ~CG3DCube();

	//序列化 
	virtual void Serialize(CArchive& ar);
	//绘制 
	virtual void Render(CG3DRenderContext* pRC, CG3DCamera* pCamera);

	//计算包围盒（重写基类虚函数） 
	virtual void computeBoundingBox();

	//void setSlices(int slices) { mSlices = slices; } 
	//void setStacks(int stacks) { mStacks = stacks; } 

protected:
	//立方体坐标系（坐标原点在中心，坐标轴方向沿边） 
	double mSize = 1; //边长 
	//绘制时需要的参数：经度、纬度方向的细分数 
	//int mSlices = 16; //z 轴周围的细分(经度线) 。 
	//int mStacks = 16; //沿z轴的细分数 (纬度线) 。 
};

#endif //_CG3DCube_H_INCLUDED