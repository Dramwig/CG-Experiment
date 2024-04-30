#include "pch.h"
#include "CG2DPolygon.h"
#include "CG2DRenderContext.h"
#include "CG2DCamera.h"

IMPLEMENT_SERIAL(CG2DPolygon, CG2DRenderable, 1)

CG2DPolygon::CG2DPolygon() : CG2DRenderable(CString("CG2DPolygon")) {}

CG2DPolygon::CG2DPolygon(const std::vector<Vec2d>& vertices) : CG2DRenderable(CString("CG2DPolygon")), mPoints(vertices) {}

CG2DPolygon::CG2DPolygon(const CG2DPolygon& other) : CG2DRenderable(CString("CG2DPolygon")), mPoints(other.mPoints) {}

CG2DPolygon::~CG2DPolygon() {}

void CG2DPolygon::Serialize(CArchive& ar) {
    CG2DRenderable::Serialize(ar);
    if (ar.IsStoring()) {
        int size = int(mPoints.size());
        ar << size;
        for (const auto& vertex : mPoints) {
            ar << vertex.x() << vertex.y();
        }
    }
    else {
        int size;
        ar >> size;
        mPoints.clear();
        for (int i = 0; i < size; ++i) {
            double x, y;
            ar >> x >> y;
            mPoints.push_back(Vec2d(x, y));
        }
    }
}

void CG2DPolygon::Render(CG2DRenderContext* pRC, CG2DCamera* pCamera) 
{
    if (pRC == nullptr || pCamera == nullptr || mPoints.empty()) {
        return;
    }
    HDC hDC = pRC->GetMemHDC();
    if (hDC != 0) {
        // 测试算法
        int algorithm = pRC->LineAlgorithm();
        if (algorithm == (int)LineAlgorithm::CDC) {
            // 使用GDI函数绘制直线
            CPen pen(penStyle(), penWidth(), penColor());
            HPEN hOldPen = (HPEN)::SelectObject(hDC, pen.GetSafeHandle());
            Vec2i startPoint = pCamera->WorldtoViewPort(mPoints.front());
            ::MoveToEx(hDC, startPoint.x(), startPoint.y(), nullptr);
            for (size_t i = 1; i < mPoints.size(); ++i) {
                Vec2i endPoint = pCamera->WorldtoViewPort(mPoints[i]);
                ::LineTo(hDC, endPoint.x(), endPoint.y());
            }
            Vec2i endPoint = pCamera->WorldtoViewPort(mPoints[0]);
            ::LineTo(hDC, endPoint.x(), endPoint.y());
            ::SelectObject(hDC, hOldPen);
        }
        else if (algorithm == (int)LineAlgorithm::DDA) {
            // 使用DDA算法绘制直线
            for (size_t i = 1; i < mPoints.size(); ++i) {
                Vec2i startPoint = pCamera->WorldtoViewPort(mPoints[i - 1]);
                Vec2i endPoint = pCamera->WorldtoViewPort(mPoints[i]);
                pRC->DDALine(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y(), penColor());
            }
            Vec2i startPoint = pCamera->WorldtoViewPort(mPoints[mPoints.size()-1]);
            Vec2i endPoint = pCamera->WorldtoViewPort(mPoints[0]);
            pRC->DDALine(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y(), penColor());
        }
        else if (algorithm == (int)LineAlgorithm::MidPoint) {
            // 使用中点算法绘制直线
            for (size_t i = 1; i < mPoints.size(); ++i) {
                Vec2i startPoint = pCamera->WorldtoViewPort(mPoints[i - 1]);
                Vec2i endPoint = pCamera->WorldtoViewPort(mPoints[i]);
                pRC->MidPointLine(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y(), penColor());
            }
            Vec2i startPoint = pCamera->WorldtoViewPort(mPoints[mPoints.size() - 1]);
            Vec2i endPoint = pCamera->WorldtoViewPort(mPoints[0]);
            pRC->MidPointLine(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y(), penColor());
        }
        else if (algorithm == (int)LineAlgorithm::Bresenham) {
            // 使用Bresenham算法绘制直线
            for (size_t i = 1; i < mPoints.size(); ++i) {
                Vec2i startPoint = pCamera->WorldtoViewPort(mPoints[i - 1]);
                Vec2i endPoint = pCamera->WorldtoViewPort(mPoints[i]);
                pRC->BresenhamLine(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y(), penColor());
            }
            Vec2i startPoint = pCamera->WorldtoViewPort(mPoints[mPoints.size() - 1]);
            Vec2i endPoint = pCamera->WorldtoViewPort(mPoints[0]);
            pRC->BresenhamLine(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y(), penColor());
        }
    }
}

void CG2DPolygon::computeBoundingBox() {
    if (mPoints.size() < 3) {
        mABox.setNull();
        return;
    }
    mABox.setNull();
    for (const auto& vertex : mPoints) {
        mABox.addPoint(vertex);
    }
    setBoundsDirty(false);
}

void CG2DPolygon::addPoint(const Vec2d& vertex) {
    mPoints.push_back(vertex);
    setBoundsDirty(true);
}
