#include "pch.h"
#include "CG2DRenderContext.h"
#include "CG2DCamera.h"
#include "CG2DCircle.h"

IMPLEMENT_SERIAL(CG2DCircle, CG2DRenderable, 1)

CG2DCircle::CG2DCircle() : mCenter(0, 0), mRadius(0) {}

CG2DCircle::CG2DCircle(const Vec2d& center, double radius)
    : CG2DRenderable(CString("CG2DCircle")), mCenter(center), mRadius(radius)
{
    mName.Format(_T("圆-%ld"), sID);
}

CG2DCircle::CG2DCircle(const CG2DCircle& other)
    : CG2DCircle(other.mCenter, other.mRadius)
{}

CG2DCircle::~CG2DCircle() {}

void CG2DCircle::Serialize(CArchive& ar) {
    CG2DRenderable::Serialize(ar);
    if (ar.IsStoring()) {
        ar << mCenter.x() << mCenter.y() << mRadius;
    }
    else {
        ar >> mCenter.x() >> mCenter.y() >> mRadius;
    }
}

void CG2DCircle::Render(CG2DRenderContext* pRC, CG2DCamera* pCamera) {
    if (pRC == nullptr || pCamera == nullptr) {
        return;
    }

    HDC hDC = pRC->GetMemHDC();
    Vec2i center = pCamera->WorldtoViewPort(mCenter);

    if (hDC == nullptr) {
        return;
    }

    // 使用 GDI 函数绘制圆
    pRC->MidPointCircle(center.x(), center.y(), (int)mRadius, penColor());

}

void CG2DCircle::computeBoundingBox() {
    mABox.setNull();
    Vec2d topLeft = mCenter - Vec2d(mRadius, mRadius);
    Vec2d bottomRight = mCenter + Vec2d(mRadius, mRadius);
    mABox.addPoint(topLeft);
    mABox.addPoint(bottomRight);
    setBoundsDirty(false);
}
