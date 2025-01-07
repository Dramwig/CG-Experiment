#pragma once
#include "Vector2.h"
#include "CG2DRenderable.h"

class CG2DCircle : public CG2DRenderable
{
    DECLARE_SERIAL(CG2DCircle)
public:
    CG2DCircle();
    CG2DCircle(const Vec2d& center, double radius);
    CG2DCircle(const CG2DCircle& other);
    virtual ~CG2DCircle();

    void Serialize(CArchive& ar) override;
    void Render(CG2DRenderContext* pRC, CG2DCamera* pCamera) override;
    void computeBoundingBox() override;

protected:
    Vec2d mCenter;
    double mRadius;
};
