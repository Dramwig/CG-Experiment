#pragma once
#include "CG3DRenderable.h" 

class CG3DCylinder : public CG3DRenderable
{
	DECLARE_SERIAL(CG3DCylinder)
public:
	CG3DCylinder();
	CG3DCylinder(double r, double h);
	CG3DCylinder(const CString& name);
	CG3DCylinder(const CG3DCylinder& other);
	virtual ~CG3DCylinder();

	//���л� 
	virtual void Serialize(CArchive& ar);
	//���� 
	virtual void Render(CG3DRenderContext* pRC, CG3DCamera* pCamera);

	//�����Χ�У���д�����麯���� 
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
