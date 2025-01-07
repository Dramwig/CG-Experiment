#include "pch.h"
#include "CG2DPolygon.h"
#include "CG2DRenderContext.h"
#include "CG2DCamera.h"

IMPLEMENT_SERIAL(CG2DPolygon, CG2DRenderable, 1)

CG2DPolygon::CG2DPolygon(){
    mName.Format(_T("�����-%ld"), sID);
}

CG2DPolygon::CG2DPolygon(const std::vector<Vec2d>& vertices) : mPoints(vertices) {
    mName.Format(_T("�����-%ld"), sID);
}

CG2DPolygon::CG2DPolygon(const CG2DPolygon& other) : mPoints(other.mPoints) {
    mName.Format(_T("�����-%ld"), sID);
}

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
        // �����㷨
        int algorithm = pRC->LineAlgorithm();
        if (algorithm == (int)LineAlgorithm::CDC) {
            // ʹ��GDI��������ֱ��
            CPen pen(penStyle(), penWidth(), penColor());
            HPEN hOldPen = (HPEN)::SelectObject(hDC, pen.GetSafeHandle());
            Vec3d s = mMat * Vec3d(mPoints.front()); //����ʵ�����
            Vec2i v1 = pCamera->WorldtoViewPort(Vec2d(s.x(), s.y()));
            ::MoveToEx(hDC, v1.x(), v1.y(), nullptr);
            for (size_t i = 1; i < mPoints.size(); ++i) {
                Vec3d e = mMat * Vec3d(mPoints[i]); //����ʵ���յ�
                Vec2i v2 = pCamera->WorldtoViewPort(Vec2d(e.x(), e.y()));
                ::LineTo(hDC, v2.x(), v2.y());
            }
            Vec3d e = mMat * Vec3d(mPoints[0]); //����ʵ���յ�
            Vec2i v2 = pCamera->WorldtoViewPort(Vec2d(e.x(), e.y()));
            ::LineTo(hDC, v2.x(), v2.y());
            ::SelectObject(hDC, hOldPen);
        }
        else if (algorithm == (int)LineAlgorithm::DDA) {
            // ʹ��DDA�㷨����ֱ��
            for (size_t i = 1; i < mPoints.size(); ++i) {
                Vec3d s = mMat * Vec3d(mPoints[i - 1]); //����ʵ�����
                Vec3d e = mMat * Vec3d(mPoints[i]); //����ʵ���յ�
                Vec2i v1 = pCamera->WorldtoViewPort(Vec2d(s.x(), s.y()));
                Vec2i v2 = pCamera->WorldtoViewPort(Vec2d(e.x(), e.y()));
                if (algorithm == (int)LineAlgorithm::DDA)
                    pRC->DDALine(v1.x(), v1.y(), v2.x(), v2.y(), penColor());
                else if (algorithm == (int)LineAlgorithm::MidPoint)
					pRC->MidPointLine(v1.x(), v1.y(), v2.x(), v2.y(), penColor());
				else if (algorithm == (int)LineAlgorithm::Bresenham)
					pRC->BresenhamLine(v1.x(), v1.y(), v2.x(), v2.y(), penColor());
            }
            Vec3d s = mMat * Vec3d(mPoints[mPoints.size() - 1]); //����ʵ�����
            Vec3d e = mMat * Vec3d(mPoints[0]); //����ʵ���յ�
            Vec2i v1 = pCamera->WorldtoViewPort(Vec2d(s.x(), s.y()));
            Vec2i v2 = pCamera->WorldtoViewPort(Vec2d(e.x(), e.y()));
            if (algorithm == (int)LineAlgorithm::DDA)
                pRC->DDALine(v1.x(), v1.y(), v2.x(), v2.y(), penColor());
            else if (algorithm == (int)LineAlgorithm::MidPoint)
                pRC->MidPointLine(v1.x(), v1.y(), v2.x(), v2.y(), penColor());
            else if (algorithm == (int)LineAlgorithm::Bresenham)
                pRC->BresenhamLine(v1.x(), v1.y(), v2.x(), v2.y(), penColor());
        }
       
    }
    //�˴����Ի��ƶ����Χ�еķ�ʽ��ʾ����ѡ�У�Ҳ��������ȷ��ѡ����ʾ��ʽ
    DrawSelectedBoundingBoxi(hDC, this, pCamera);
}

void CG2DPolygon::computeBoundingBox() {
    mABox.setNull();
    for (const auto& vertex : mPoints) {
        Vec3d s = mMat * Vec3d(vertex);
        mABox.addPoint(Vec2d(s.x(), s.y()));
    }
    setBoundsDirty(false);
}

void CG2DPolygon::addPoint(const Vec2d& point) {
    mPoints.push_back(point);
    setBoundsDirty(true);
}

void CG2DPolygon::addPoint(const CPoint& point) {
    mPoints.push_back(Vec2d(point));
    setBoundsDirty(true);
}

int CG2DPolygon::size() {
    return int(mPoints.size());
}

void CG2DPolygon::clear() {
    mPoints.clear();
}

bool CG2DPolygon::empty() {
    return mPoints.empty();
}

CPoint CG2DPolygon::back() {
    return CPoint(int(mPoints.back().x()), int(mPoints.back().y()));
}

void CG2DPolygon::pop() {
    mPoints.pop_back();
}

// ��ȡ���ӿ��ڵİ�Χ��(�����ڻ��ƶ���İ�Χ�У�
ABox2i CG2DPolygon::BoundingABoxi(CG2DCamera* pCamera)
{
    ABox2i abox;
    for (const auto& vertex : mPoints) {
        Vec3d s = mMat * Vec3d(vertex);
        Vec2i v = pCamera->WorldtoViewPort(Vec2d(s.x(), s.y()));
        abox.addPoint(v);
    }
    return abox;
}
