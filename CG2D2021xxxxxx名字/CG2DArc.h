#ifndef _CG2DArc_H_INCLUDED
#define _CG2DArc_H_INCLUDED

#include "Vector2.h"
#include "CG2DRenderable.h"

class CG2DArc : public CG2DRenderable {
    DECLARE_SERIAL(CG2DArc)
public:
    CG2DArc();
    CG2DArc(const Vec2d& center, double radius, double startAngle, double sweepAngle);
    CG2DArc(const CG2DArc& other);
    virtual ~CG2DArc();

public:
    // ���л�
    virtual void Serialize(CArchive& ar) override;
    // ���ƣ�ʹ��CGDI2DRenderContext��CGDI2DCamera
    virtual void Render(CG2DRenderContext* pRC, CG2DCamera* pCamera) override;
    // ��Χ����ʰȡ���
    virtual void computeBoundingBox() override;

protected:
    Vec2d mCenter;          // Բ��
    double mRadius;         // �뾶
    double mStartAngle;     // ��ʼ�Ƕ�
    double mSweepAngle;     // ɨ��Ƕ�
};

#endif // _CG2DArc_H_INCLUDED
