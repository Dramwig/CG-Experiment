#include "pch.h"
#include "CG2DEllipse.h"
#include "CG2DRenderContext.h"
#include "CG2DCamera.h"

IMPLEMENT_SERIAL(CG2DEllipse, CG2DRenderable, 1)

CG2DEllipse::CG2DEllipse() : CG2DEllipse(Vec2d(0, 0), 0, 0) {}

CG2DEllipse::CG2DEllipse(const Vec2d& center, double semiMajorAxis, double semiMinorAxis)
    : CG2DRenderable(CString("CG2DEllipse")), mCenter(center), mSemiMajorAxis(semiMajorAxis), mSemiMinorAxis(semiMinorAxis)
{
    mName.Format(_T("椭圆-%ld"), sID);
}

CG2DEllipse::CG2DEllipse(const CG2DEllipse& other)
    : CG2DEllipse(other.mCenter, other.mSemiMajorAxis, other.mSemiMinorAxis)
{}

CG2DEllipse::~CG2DEllipse() {}

void CG2DEllipse::Serialize(CArchive& ar) {
    CG2DRenderable::Serialize(ar);
    if (ar.IsStoring()) {
        ar << mCenter.x() << mCenter.y() << mSemiMajorAxis << mSemiMinorAxis;
    }
    else {
        ar >> mCenter.x() >> mCenter.y() >> mSemiMajorAxis >> mSemiMinorAxis;
    }
}

void CG2DEllipse::Render(CG2DRenderContext* pRC, CG2DCamera* pCamera) {
    if (pRC == nullptr || pCamera == nullptr) {
        return;
    }

    HDC hDC = pRC->GetMemHDC();
    Vec2i center = pCamera->WorldtoViewPort(mCenter);

    if (hDC == nullptr) {
        return;
    }

    // 计算椭圆的外接矩形
    Vec2i topLeft(center.x() - (int)mSemiMajorAxis, center.y() - (int)mSemiMinorAxis);
    Vec2i bottomRight(center.x() + (int)mSemiMajorAxis, center.y() + (int)mSemiMinorAxis);

    // 使用 GDI 函数绘制椭圆轮廓线
    ::Arc(hDC, topLeft.x(), topLeft.y(), bottomRight.x(), bottomRight.y(), 0, 0, 0, 0);
}

void CG2DEllipse::computeBoundingBox() {
    mABox.setNull();
    Vec2d topLeft = mCenter - Vec2d(mSemiMajorAxis, mSemiMinorAxis);
    Vec2d bottomRight = mCenter + Vec2d(mSemiMajorAxis, mSemiMinorAxis);
    mABox.addPoint(topLeft);
    mABox.addPoint(bottomRight);
    setBoundsDirty(false);
}
