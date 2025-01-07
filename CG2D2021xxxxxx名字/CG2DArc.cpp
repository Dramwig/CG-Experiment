#include "pch.h"
#include "CG2DArc.h"
#include "CG2DRenderContext.h"
#include "CG2DCamera.h"


IMPLEMENT_SERIAL(CG2DArc, CG2DRenderable, 1)

CG2DArc::CG2DArc() : mCenter(Vec2d(0, 0)), mRadius(0), mStartAngle(0), mSweepAngle(0) {}

CG2DArc::CG2DArc(const Vec2d& center, double radius, double startAngle, double sweepAngle)
    : mCenter(center), mRadius(radius), mStartAngle(startAngle), mSweepAngle(sweepAngle)
{
    mName.Format(_T("Բ��-%ld"), sID);
}

CG2DArc::CG2DArc(const CG2DArc& other)
    : mCenter(other.mCenter), mRadius(other.mRadius), mStartAngle(other.mStartAngle), mSweepAngle(other.mSweepAngle) {}

CG2DArc::~CG2DArc() {}

void CG2DArc::Serialize(CArchive& ar) {
    CG2DRenderable::Serialize(ar);
    if (ar.IsStoring()) {
        ar << mCenter.x() << mCenter.y() << mRadius << mStartAngle << mSweepAngle;
    }
    else {
        ar >> mCenter.x() >> mCenter.y() >> mRadius >> mStartAngle >> mSweepAngle;
    }
}

void CG2DArc::Render(CG2DRenderContext* pRC, CG2DCamera* pCamera) {
    if (pRC == nullptr || pCamera == nullptr) {
        return;
    }

    // ��ȡ�����豸������
    HDC hDC = pRC->GetMemHDC();
    if (hDC == nullptr) {
        return;
    }

    Vec2i center = pCamera->WorldtoViewPort(mCenter);

    // ʹ�� GDI ��������Բ��
    pRC->MidPointCircleArc(center.x(), center.y(), (int)mRadius, penColor(), (float)mStartAngle, (float)mSweepAngle);
}

void CG2DArc::computeBoundingBox() {

    // ����Բ�������յ����ӿ��е�����
    Vec2d startPoint = mCenter + Vec2d(mRadius * cos(mStartAngle), mRadius * sin(mStartAngle));
    Vec2d endPoint = mCenter + Vec2d(mRadius * cos(mStartAngle + mSweepAngle), mRadius * sin(mStartAngle + mSweepAngle));

    mABox.addPoint(startPoint); //���
    mABox.addPoint(endPoint); //�յ�
    for (double angle = 0; angle <= 2 * PI + 0.01; angle += PI / 2) {
        Vec2d point = mCenter + Vec2d(mRadius * cos(angle), mRadius * sin(angle));
        if (angle >= mStartAngle && angle <= mStartAngle + mSweepAngle)
            mABox.addPoint(point);
    }
}
