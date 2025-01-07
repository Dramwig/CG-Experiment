#include "pch.h"
#include "CG2DRay.h"
#include "CG2DRenderContext.h"
#include "CG2DCamera.h"

IMPLEMENT_SERIAL(CG2DRay, CG2DRenderable, 1)

CG2DRay::CG2DRay() : mStart(Vec2d(0, 0)), mDirection(Vec2d(1, 0)) {
    mName.Format(_T("����-%ld"), sID);
}

CG2DRay::CG2DRay(const Vec2d& start, const Vec2d& direction) : mStart(start), mDirection(direction) {
    mName.Format(_T("����-%ld"), sID);
}

CG2DRay::CG2DRay(const CG2DRay& other) : mStart(other.mStart), mDirection(other.mDirection) {
    mName.Format(_T("����-%ld"), sID);
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
    // ת�����ͷ����豸����ϵ
    Vec2i v1 = pCamera->WorldtoViewPort(mStart);
    Vec2i v2 = pCamera->WorldtoViewPort(mStart + mDirection * 1000); // �������߳���Ϊ1000
    //�����㷨
    int algrithm = pRC->LineAlgorithm(); //ͨ�����ƻ�����Ӧ��View��ȡRibbon�����ѡ�е�ֱ�߶λ����㷨
    if (algrithm == (int)LineAlgorithm::CDC)
    { //�����߶ε����͡��߿���ɫ���Դ�������
        CPen pen(penStyle(), penWidth(), penColor());
        if (hDC != 0) //ʹ��Windows��ͼ���豸�ӿ�API��GDI����������
        { //����ѡ����ƻ���
            HPEN hOldPen = (HPEN)::SelectObject(hDC, pen.GetSafeHandle());
            ::MoveToEx(hDC, v1.x(), v1.y(), nullptr);
            ::LineTo(hDC, v2.x(), v2.y());
            ::SelectObject(hDC, hOldPen); //�ָ�ԭ���ƻ����Ļ���
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
    mABox.setNull(); // ��հ�Χ��
    // ���ߵİ�Χ��ֻ������㣬��Ϊ���������������
    mABox.addPoint(mStart);
    setBoundsDirty(false);
}
