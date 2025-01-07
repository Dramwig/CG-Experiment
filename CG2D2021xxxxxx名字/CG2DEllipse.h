#pragma once

#include "Vector2.h"
#include "CG2DRenderable.h"

class CG2DEllipse : public CG2DRenderable {
    DECLARE_SERIAL(CG2DEllipse)
public:
    CG2DEllipse();
    CG2DEllipse(const Vec2d& center, double semiMajorAxis, double semiMinorAxis);
    CG2DEllipse(const CG2DEllipse& other);
    virtual ~CG2DEllipse();

    void Serialize(CArchive& ar) override;
    void Render(CG2DRenderContext* pRC, CG2DCamera* pCamera) override;
    void computeBoundingBox() override;

private:
    Vec2d mCenter;
    double mSemiMajorAxis;
    double mSemiMinorAxis;
};
