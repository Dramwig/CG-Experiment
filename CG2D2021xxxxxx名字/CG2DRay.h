#ifndef _CG2DRay_H_INCLUDED
#define _CG2DRay_H_INCLUDED

#include "Vector2.h"
#include "CG2DRenderable.h"

class CG2DRay : public CG2DRenderable {
	DECLARE_SERIAL(CG2DRay)
public:
    CG2DRay();
    CG2DRay(const Vec2d& start, const Vec2d& direction); // �������ͷ���������
    CG2DRay(const CG2DRay& other);
    virtual ~CG2DRay();

public:
	//���л�
	virtual void Serialize(CArchive& ar) override;
	//���ƣ�ʹ��CGDI2DRenderContext��CGDI2DCamera
	virtual void Render(CG2DRenderContext* pRC, CG2DCamera* pCamera) override; //���ƶ���ʹ��ָ�����
	//��Χ����ʰȡ���
	virtual void computeBoundingBox(); //�����Χ��

protected:
    Vec2d mStart;       // ���
    Vec2d mDirection;   // ����
};

#endif // _CG2DRay_H_INCLUDED
