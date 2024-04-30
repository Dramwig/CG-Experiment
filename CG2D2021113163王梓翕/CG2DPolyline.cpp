#include "pch.h"
#include "CG2DPolyline.h"
#include "CG2DRenderContext.h"
#include "CG2DCamera.h"

IMPLEMENT_SERIAL(CG2DPolyline, CG2DRenderable, 1)

CG2DPolyline::CG2DPolyline() : CG2DRenderable(CString("CG2DPolyline")) {}

CG2DPolyline::CG2DPolyline(const std::vector<Vec2d>& points) : CG2DRenderable(CString("CG2DPolyline")), mPoints(points) {}

CG2DPolyline::CG2DPolyline(const CG2DPolyline& other) : CG2DRenderable(CString("CG2DPolyline")), mPoints(other.mPoints) {}

CG2DPolyline::~CG2DPolyline() {}

void CG2DPolyline::Serialize(CArchive& ar) {
    CG2DRenderable::Serialize(ar);
    if (ar.IsStoring()) {
        int size = int(mPoints.size());
        ar << size;
        for (const auto& point : mPoints) {
            ar << point.x() << point.y();
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

void CG2DPolyline::Render(CG2DRenderContext* pRC, CG2DCamera* pCamera) {
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
            ::SelectObject(hDC, hOldPen);
        }
        else if (algorithm == (int)LineAlgorithm::DDA) {
            // 使用DDA算法绘制直线
            for (size_t i = 1; i < mPoints.size(); ++i) {
                Vec2i startPoint = pCamera->WorldtoViewPort(mPoints[i - 1]);
                Vec2i endPoint = pCamera->WorldtoViewPort(mPoints[i]);
                pRC->DDALine(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y(), penColor());
            }
        }
        else if (algorithm == (int)LineAlgorithm::MidPoint) {
            // 使用中点算法绘制直线
            for (size_t i = 1; i < mPoints.size(); ++i) {
                Vec2i startPoint = pCamera->WorldtoViewPort(mPoints[i - 1]);
                Vec2i endPoint = pCamera->WorldtoViewPort(mPoints[i]);
                pRC->MidPointLine(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y(), penColor());
            }
        }
        else if (algorithm == (int)LineAlgorithm::Bresenham) {
            // 使用Bresenham算法绘制直线
            for (size_t i = 1; i < mPoints.size(); ++i) {
                Vec2i startPoint = pCamera->WorldtoViewPort(mPoints[i - 1]);
                Vec2i endPoint = pCamera->WorldtoViewPort(mPoints[i]);
                pRC->BresenhamLine(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y(), penColor());
            }
        }
    }
}

void CG2DPolyline::computeBoundingBox() {
    if (mPoints.empty()) {
        mABox.setNull();
        return;
    }
    mABox.setNull();
    for (const auto& point : mPoints) {
        mABox.addPoint(point);
    }
    setBoundsDirty(false);
}

void CG2DPolyline::addPoint(const Vec2d& point) {
    mPoints.push_back(point);
    setBoundsDirty(true);
}
