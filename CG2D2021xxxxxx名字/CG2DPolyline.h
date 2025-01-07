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

    // ���л�
    virtual void Serialize(CArchive& ar) override;

    // ����
    virtual void Render(CG2DRenderContext* pRC, CG2DCamera* pCamera) override;

    // ��Χ����ʰȡ���
    virtual void computeBoundingBox() override;

    // ��ӵ�
    void addPoint(const Vec2d& point);
    void addPoint(const CPoint& point);
    int size();
    void clear();
    bool empty();
    CPoint back();
    void pop();
    // ���ض�mPoints�����ã������д����
    std::vector<Vec2d>& getPoints() {
        return mPoints;
    }
    virtual ABox2i BoundingABoxi(CG2DCamera* pCamera); //��ȡ���ӿ��ڵİ�Χ��(�����ڻ��ƶ���İ�Χ�У�
    
protected:
    std::vector<Vec2d> mPoints; // �����ϵĵ㼯��
};

