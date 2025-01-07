#include "pch.h"
#include "CG2DRenderContext.h"
#include "CG2DCamera.h"
#include "CG2DCircle.h"

IMPLEMENT_SERIAL(CG2DCircle, CG2DRenderable, 1)

CG2DCircle::CG2DCircle() : mCenter(0, 0), mRadius(0) {}

CG2DCircle::CG2DCircle(const Vec2d& center, double radius)
    : CG2DRenderable(CString("CG2DCircle")), mCenter(center), mRadius(radius)
{
    mName.Format(_T("Բ-%ld"), sID);
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
    if (hDC == nullptr) {
        return;
    }
    Vec3d s = mMat * Vec3d(mCenter); //����ʵ�����
    Vec2i v1 = pCamera->WorldtoViewPort(Vec2d(s.x(), s.y()));
    double r1 = mRadius* mMat.scalex(); //����ʵ�ʰ뾶
    double r2 = mRadius * mMat.scaley();
    CPen pen(penStyle(), penWidth(), penColor());
    if (hDC != 0) // Using Windows' Graphics Device Interface API (GDI functions) to draw
    {
        HPEN hOldPen = (HPEN)::SelectObject(hDC, pen.GetSafeHandle());
        // Draw the circle
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH)); // ѡ��͸����ˢ
        Ellipse(hDC, int(v1.x()- r1), int(v1.y()- r2), int(v1.x()+ r1), int(v1.y()+ r2));
        SelectObject(hDC, hOldBrush); // �ָ��ɱ�ˢ
        SelectObject(hDC, hOldPen); // Restore the original drawing environment's pen
    }
    //�˴����Ի��ƶ����Χ�еķ�ʽ��ʾ����ѡ�У�Ҳ��������ȷ��ѡ����ʾ��ʽ
    DrawSelectedBoundingBox(hDC, this, pCamera);
}

void CG2DCircle::computeBoundingBox() {
    mABox.setNull();
    Vec3d s = mMat * Vec3d(mCenter); //����ʵ�����
    double r1 = mRadius * mMat.scalex(); //����ʵ�ʰ뾶
    double r2 = mRadius * mMat.scaley();
    mABox.addPoint(Vec2d(int(s.x() - r1), int(s.y() - r2)));	//���
    mABox.addPoint(Vec2d(int(s.x() + r1), int(s.y() + r2)));	//�յ�
    setBoundsDirty(false);
}
