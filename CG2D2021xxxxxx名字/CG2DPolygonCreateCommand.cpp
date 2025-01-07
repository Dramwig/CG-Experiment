#include "pch.h"
#include "CG2DPolygonCreateCommand.h"
#include "CG2D2021xxxxxx����Doc.h" //����View֮ǰҪ����Doc
#include "CG2D2021xxxxxx����View.h" //�û��������ƣ�����ͼ�ζ���ͨ��Doc��ӵ�����
#include "CG2DPolygon.h"

CG2DPolygonCreateCommand::CG2DPolygonCreateCommand(CView* pview /*= nullptr*/)
    : UIEventListener(pview), mLastPoint(0, 0) {
    mStep = 0;
}

int CG2DPolygonCreateCommand::GetType() {
    return static_cast<int>(CommandType::cmd2dPolygon);
}

void CG2DPolygonCreateCommand::DrawR2NOTLine(CPoint& mStart, CPoint& prePos)const {
    CClientDC dc(mView);
    CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
    CPen* pOldPen = dc.SelectObject(&pen);
    int mode = dc.SetROP2(R2_NOTXORPEN); //R2_NOT
    dc.MoveTo(CPoint(mStart.x, mStart.y));
    dc.LineTo(CPoint(prePos.x, prePos.y));
    dc.SelectObject(pOldPen);
    dc.SetROP2(mode);
}

int CG2DPolygonCreateCommand::OnLButtonDown(UINT nFlags, CPoint pos) {
    if (mView == nullptr)
        return -1;

    CCG2D2021xxxxxx����View* view = dynamic_cast<CCG2D2021xxxxxx����View*>(mView);
    if (view == nullptr)
        return -1;

    if (!polygon.empty() && pos == polygon.back())
    {
        mStep = 1;
        view->Prompt(_T("����һ���غϣ�������ֱ�߶ε��յ�"));
        return -1;
    }

    // �����ʼ��׽��
    mStep++;
    mLastPoint = pos;
    polygon.addPoint(pos);
    view->Prompt(_T("��ѡ����һ������м���ɶ����"));

    return 0;
}

int CG2DPolygonCreateCommand::OnRButtonDown(UINT /* nFlags */, CPoint /* pos */) {
    // �Ҽ���ɻ���
    if (mView == nullptr || mStep < 2)
        return -1;

    CCG2D2021xxxxxx����View* view = dynamic_cast<CCG2D2021xxxxxx����View*>(mView);
    if (view == nullptr)
        return -1;

    std::vector<Vec2d> mPoints = polygon.getPoints();
    for (Vec2d& point : mPoints)
        point = view->ViewPorttoWorld(Vec2i(point));
    CG2DPolygon* ewPolygon = new CG2DPolygon(mPoints);
    ewPolygon->setPenColor(view->PenColor());
    ewPolygon->setPenWidth(view->PenWidth());
    ewPolygon->setPenStyle(view->PenStyle());

    view->addRenderable(ewPolygon);

    // ��ɺ�����
    view->Invalidate(); //�ͻ�����Ҫ�ػ�
    view->UpdateWindow(); //�ͻ���ִ���ػ�
    mStep = 0; //��Ϊ0����д��ʼ�����߶ζ����õ����������ϵ��߶ΰ�ť
    polygon.clear();
    mLastPoint = CPoint(0, 0);
    view->Prompt(_T("����ߴ������"));
    return 0;
}

int CG2DPolygonCreateCommand::OnMButtonDown(UINT /* nFlags */, CPoint /* pos */) {
    return OnRButtonDown(0, CPoint(0, 0));
}

int CG2DPolygonCreateCommand::OnMouseMove(UINT nFlags, CPoint pos) {
    // ����ƶ�ʱ������Ƥ��
    if (mView == nullptr || polygon.empty())
        return -1;

    CCG2D2021xxxxxx����View* view = dynamic_cast<CCG2D2021xxxxxx����View*>(mView);
    if (view == nullptr)
        return -1;
    if (mStep == 0) //��û�����һ���㣨��ȡ�߶���㣩
    {
        view->Prompt(_T("���������ߵ����")); //״̬����ʾ
    }
    else if (mStep > 0) {
        CPoint lastPoint = polygon.back();
        DrawR2NOTLine(lastPoint, mLastPoint);
        DrawR2NOTLine(lastPoint, pos);
        mLastPoint = pos;
    }
    return 0;
}

int CG2DPolygonCreateCommand::Cancel() {
    // ȡ������������Ѳ�׽�ĵ�
    if (mView == nullptr)
        return -1;

    CCG2D2021xxxxxx����View* view = dynamic_cast<CCG2D2021xxxxxx����View*>(mView);
    if (view == nullptr)
        return -1;


    if (!polygon.empty()) {
        // ���������һ���㵽��ǰ���λ�õ���Ƥ��
        CPoint lastPoint = polygon.back();
        DrawR2NOTLine(lastPoint, mLastPoint);
        mLastPoint = lastPoint;
        polygon.pop();
    }

    // ��������Ѳ�׽�ĵ�
    polygon.clear();
    mLastPoint = CPoint(0, 0);
    mStep = 0;

    // ֪ͨ��ͼ����
    view->Invalidate();
    view->UpdateWindow();
    view->Prompt(_T("����"));

    return 0;
}

