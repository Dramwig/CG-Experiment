#include "pch.h"
#include "CG2DLine.h"
#include "CG2DRenderContext.h"
#include "CG2DCamera.h"

IMPLEMENT_SERIAL(CG2DLine, CG2DRenderable, 1)

CG2DLine::CG2DLine() : CG2DRenderable(CString("CG2DLine")), mStart(Vec2d(0, 0)), mEnd(Vec2d(1, 1)) {
    mName.Format(_T("ֱ��-%ld"), sID);
}

CG2DLine::CG2DLine(const Vec2d& s, const Vec2d& e) : CG2DRenderable(CString("CG2DLine")), mStart(s), mEnd(e) {
    mName.Format(_T("ֱ��-%ld"), sID);
}

CG2DLine::CG2DLine(const CG2DLine& other) : CG2DRenderable(CString("CG2DLine")), mStart(other.mStart), mEnd(other.mEnd) {
    mName.Format(_T("ֱ��-%ld"), sID);
}

CG2DLine::~CG2DLine() {}

void CG2DLine::Serialize(CArchive& ar) {
    CG2DRenderable::Serialize(ar);
    if (ar.IsStoring()) {
        ar << mStart.x() << mStart.y() << mEnd.x() << mEnd.y();
    }
    else {
        ar >> mStart.x() >> mStart.y() >> mEnd.x() >> mEnd.y();
    }
}

void CG2DLine::Render(CG2DRenderContext* pRC, CG2DCamera* pCamera) {
    if (pRC == nullptr || pCamera == nullptr) {
        return;
    }
    HDC hDC = pRC->GetMemHDC();
    // ת�������յ㵽�豸����ϵ
    Vec2i startPoint = pCamera->WorldtoViewPort(mStart + (mStart - mEnd) * 1000);
    Vec2i endPoint = pCamera->WorldtoViewPort(mEnd + (mEnd - mStart) * 1000);
    //�����㷨
    int algrithm = pRC->LineAlgorithm(); //ͨ�����ƻ�����Ӧ��View��ȡRibbon�����ѡ�е�ֱ�߶λ����㷨
    if (algrithm == (int)LineAlgorithm::CDC)
    { //�����߶ε����͡��߿���ɫ���Դ�������
        CPen pen(penStyle(), penWidth(), penColor());
        if (hDC != 0) //ʹ��Windows��ͼ���豸�ӿ�API��GDI����������
        { //����ѡ����ƻ���
            HPEN hOldPen = (HPEN)::SelectObject(hDC, pen.GetSafeHandle());
            ::MoveToEx(hDC, startPoint.x(), startPoint.y(), nullptr);
            ::LineTo(hDC, endPoint.x(), endPoint.y());
            ::SelectObject(hDC, hOldPen); //�ָ�ԭ���ƻ����Ļ���
        }
    }
    else if (algrithm == (int)LineAlgorithm::DDA)
        pRC->DDALine(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y(), penColor());
    else if (algrithm == (int)LineAlgorithm::MidPoint)
        pRC->MidPointLine(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y(), penColor());
    else if (algrithm == (int)LineAlgorithm::Bresenham)
        pRC->BresenhamLine(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y(), penColor());
}

void CG2DLine::computeBoundingBox() {
    mABox.setNull(); // ��հ�Χ��
    // ֱ�ߵİ�Χ��ֻ���������յ�
    mABox.addPoint(mStart);
    mABox.addPoint(mEnd);
    setBoundsDirty(false);
}
