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
    // 序列化
    virtual void Serialize(CArchive& ar) override;
    // 绘制，使用CGDI2DRenderContext、CGDI2DCamera
    virtual void Render(CG2DRenderContext* pRC, CG2DCamera* pCamera) override;
    // 包围盒与拾取相关
    virtual void computeBoundingBox() override;

protected:
    Vec2d mCenter;          // 圆心
    double mRadius;         // 半径
    double mStartAngle;     // 开始角度
    double mSweepAngle;     // 扫描角度
};

#endif // _CG2DArc_H_INCLUDED
