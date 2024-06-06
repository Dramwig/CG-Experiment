#pragma once
#include "CG3DRenderable.h" 

class CG3DCone : public CG3DRenderable
{
	DECLARE_SERIAL(CG3DCone)
public:
	CG3DCone();
	CG3DCone(double r, double h);
	CG3DCone(const CString& name);
	CG3DCone(const CG3DCone& other);
	virtual ~CG3DCone();

	//序列化 
	virtual void Serialize(CArchive& ar);
	//绘制 
	virtual void Render(CG3DRenderContext* pRC, CG3DCamera* pCamera);

	//计算包围盒（重写基类虚函数） 
	virtual void computeBoundingBox();

	void setRadius(double r) { radius = r; }
	double getRadius() { return radius; }
	void setHeight(double h) { height = h; }
	double getHeight() { return height; }
	void setSlices(int s) { slices = s; }
	int getSlices() { return slices; }
	void setStacks(int s) { stacks = s; }
	int getStacks() { return stacks; }

protected:
	double radius = 500;
	double height = 500;
	int slices = 50;
	int stacks = 10;
};
