#pragma once
#include "CG3DRenderable.h" 

class CG3DSphere : public CG3DRenderable
{
	DECLARE_SERIAL(CG3DSphere)
public:
	CG3DSphere();
	CG3DSphere(double r);
	CG3DSphere(const CString& name);
	CG3DSphere(const CG3DSphere& other);
	virtual ~CG3DSphere();

	//���л� 
	virtual void Serialize(CArchive& ar);
	//���� 
	virtual void Render(CG3DRenderContext* pRC, CG3DCamera* pCamera);

	//�����Χ�У���д�����麯���� 
	virtual void computeBoundingBox();

	void setRadius(double r) { radius = r; }
	double getRadius() { return radius; }
	void setSlices(int s) { slices = s; }
	int getSlices() { return slices; }
	void setStacks(int s) { stacks = s; }
	int getStacks() { return stacks; }

protected:
	double radius=500;
	int slices=50;
	int stacks=10;
};
