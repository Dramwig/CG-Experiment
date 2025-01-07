#ifndef _CG3DCube_H_INCLUDED 
#define _CG3DCube_H_INCLUDED 

#include "CG3DRenderable.h" 
#include "AABBox3.h"

class CG3DCube : public CG3DRenderable
{
	DECLARE_SERIAL(CG3DCube) //����Ϊ�����л���
public:
	CG3DCube();
	CG3DCube(double size); //�����߳� 
	CG3DCube(const CG3DCube& other);
	virtual ~CG3DCube();

	//���л� 
	virtual void Serialize(CArchive& ar);
	//���� 
	void Draw(bool outline = false);
	virtual void Render(CG3DRenderContext* pRC, CG3DCamera* pCamera);
	void Render(CG3DRenderContext* pRC, CG3DCamera* pCamera, Mat4d pMat);

	//�����Χ�У���д�����麯���� 
	virtual void computeBoundingBox();

	//void setSlices(int slices) { mSlices = slices; } 
	//void setStacks(int stacks) { mStacks = stacks; } 

protected:
	//����������ϵ������ԭ�������ģ������᷽���رߣ� 
	double mSize = 1; //�߳� 
	//����ʱ��Ҫ�Ĳ��������ȡ�γ�ȷ����ϸ���� 
	//int mSlices = 16; //z ����Χ��ϸ��(������) �� 
	//int mStacks = 16; //��z���ϸ���� (γ����) �� 
};

#endif //_CG3DCube_H_INCLUDED
