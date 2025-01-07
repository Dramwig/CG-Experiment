#pragma once
#include "Vector2.h"
#include "CG2DRenderable.h"
#include <vector>

class CG2DPolyline : public CG2DRenderable {
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
    void addPoint(const CPoint& point);
    int size();
    void clear();
    bool empty();
    CPoint back();
    void pop();
    // 返回对mPoints的引用，允许读写操作
    std::vector<Vec2d>& getPoints() {
        return mPoints;
    }
    virtual ABox2i BoundingABoxi(CG2DCamera* pCamera); //获取在视口内的包围盒(仅用于绘制对象的包围盒）
    
protected:
    std::vector<Vec2d> mPoints; // 折线上的点集合
};

