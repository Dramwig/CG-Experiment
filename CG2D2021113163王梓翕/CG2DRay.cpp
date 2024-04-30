#include "pch.h"
#include "CG2DRay.h"
#include "CG2DRenderContext.h"
#include "CG2DCamera.h"

IMPLEMENT_SERIAL(CG2DRay, CG2DRenderable, 1)

CG2DRay::CG2DRay() : mStart(Vec2d(0, 0)), mDirection(Vec2d(1, 0)) {
    mName.Format(_T("射线-%ld"), sID);
}

CG2DRay::CG2DRay(const Vec2d& start, const Vec2d& direction) : mStart(start), mDirection(direction) {
    mName.Format(_T("射线-%ld"), sID);
}

CG2DRay::CG2DRay(const CG2DRay& other) : mStart(other.mStart), mDirection(other.mDirection) {
    mName.Format(_T("射线-%ld"), sID);
}

CG2DRay::~CG2DRay() {}

void CG2DRay::Serialize(CArchive& ar) {
    CG2DRenderable::Serialize(ar);
    if (ar.IsStoring()) {
        ar << mStart.x() << mStart.y() << mDirection.x() << mDirection.y();
    }
    else {
        ar >> mStart.x() >> mStart.y() >> mDirection.x() >> mDirection.y();
    }
}

void CG2DRay::Render(CG2DRenderContext* pRC, CG2DCamera* pCamera) {
    if (pRC == nullptr || pCamera == nullptr) {
        return;
    }
    HDC hDC = pRC->GetMemHDC();
    // 转换起点和方向到设备坐标系
    Vec2i v1 = pCamera->WorldtoViewPort(mStart);
    Vec2i v2 = pCamera->WorldtoViewPort(mStart + mDirection * 1000); // 假设射线长度为1000
    //测试算法
    int algrithm = pRC->LineAlgorithm(); //通过绘制环境对应的View获取Ribbon面板中选中的直线段绘制算法
    if (algrithm == (int)LineAlgorithm::CDC)
    { //根据线段的线型、线宽、颜色属性创建画笔
        CPen pen(penStyle(), penWidth(), penColor());
        if (hDC != 0) //使用Windows的图形设备接口API（GDI函数）绘制
        { //画笔选入绘制环境
            HPEN hOldPen = (HPEN)::SelectObject(hDC, pen.GetSafeHandle());
            ::MoveToEx(hDC, v1.x(), v1.y(), nullptr);
            ::LineTo(hDC, v2.x(), v2.y());
            ::SelectObject(hDC, hOldPen); //恢复原绘制环境的画笔
        }
    }
    else if (algrithm == (int)LineAlgorithm::DDA)
        pRC->DDALine(v1.x(), v1.y(), v2.x(), v2.y(), penColor());
    else if (algrithm == (int)LineAlgorithm::MidPoint)
        pRC->MidPointLine(v1.x(), v1.y(), v2.x(), v2.y(), penColor());
    else if (algrithm == (int)LineAlgorithm::Bresenham)
        pRC->BresenhamLine(v1.x(), v1.y(), v2.x(), v2.y(), penColor());
}

void CG2DRay::computeBoundingBox() {
    mABox.setNull(); // 清空包围盒
    // 射线的包围盒只考虑起点，因为方向可以无限延伸
    mABox.addPoint(mStart);
    setBoundsDirty(false);
}
