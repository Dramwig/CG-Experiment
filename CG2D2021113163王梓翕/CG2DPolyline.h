#ifndef _CG2DPOLYLINE_H_INCLUDED
#define _CG2DPOLYLINE_H_INCLUDED

#include "Vector2.h"
#include "CG2DRenderable.h"

class CG2DPolyline : public CG2DRenderable {\
    DECLARE_SERIAL(CG2DPolyline)
public:
    CG2DPolyline();
    CG2DPolyline(const std::vector<Vec2d>& points);
    CG2DPolyline(const CG2DPolyline& other);
    virtual ~CG2DPolyline();

    // 序列化
    virtual void Serialize(CArchive& ar) override;

    // 绘制
    virtual void Render(CG2DRenderContext* pRC, CG2DCamera* pCamera) override;

    // 包围盒与拾取相关
    virtual void computeBoundingBox() override;

    // 添加点
    void addPoint(const Vec2d& point);

protected:
    std::vector<Vec2d> mPoints; // 折线上的点集合
};

#endif // _CG2DPOLYLINE_H_INCLUDED
