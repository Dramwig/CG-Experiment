#include "pch.h"
#include "CG2DPolylineCreateCommand.h"
#include "CG2D2021xxxxxx名字Doc.h" //包含View之前要包含Doc
#include "CG2D2021xxxxxx名字View.h" //用户交互绘制，并将图形对象通过Doc添加到场景
#include "CG2DPolyline.h"
#include "CG2DLineSegment.h"

CG2DPolylineCreateCommand::CG2DPolylineCreateCommand(CView* pview /*= nullptr*/)
    : UIEventListener(pview), mLastPoint(0,0){
    mStep = 0;
}

int CG2DPolylineCreateCommand::GetType() {
    return static_cast<int>(CommandType::cmd2dPolyline);
}

void CG2DPolylineCreateCommand::DrawR2NOTLine(CPoint& mStart, CPoint& prePos)const{
    CClientDC dc(mView);
    CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
    CPen* pOldPen = dc.SelectObject(&pen);
    int mode = dc.SetROP2(R2_NOTXORPEN); //R2_NOT
    dc.MoveTo(CPoint(mStart.x, mStart.y));
    dc.LineTo(CPoint(prePos.x, prePos.y));
    dc.SelectObject(pOldPen);
    dc.SetROP2(mode);
}

int CG2DPolylineCreateCommand::OnLButtonDown(UINT nFlags, CPoint pos) {
    if (mView == nullptr)
        return -1;

    CCG2D2021xxxxxx名字View* view = dynamic_cast<CCG2D2021xxxxxx名字View*>(mView);
    if (view == nullptr)
        return -1;

    if (!polyline.empty() && pos == polyline.back())
    {
        mStep = 1;
        view->Prompt(_T("与上一点重合，请输入直线段的终点"));
        return -1;
    }

    // 点击开始捕捉点
    mStep++;
    mLastPoint = pos;
    polyline.addPoint(pos);
    view->Prompt(_T("请选择下一个点或中键完成多边线"));

    return 0;
}

int CG2DPolylineCreateCommand::OnRButtonDown(UINT /* nFlags */, CPoint /* pos */) {
    // 右键完成绘制
    if (mView == nullptr || mStep < 2)
        return -1;

    CCG2D2021xxxxxx名字View* view = dynamic_cast<CCG2D2021xxxxxx名字View*>(mView);
    if (view == nullptr)
        return -1;

    std::vector<Vec2d> mPoints = polyline.getPoints();
    for (Vec2d& point : mPoints)
        point = view->ViewPorttoWorld(Vec2i(point));
    CG2DPolyline *ewPolyline = new CG2DPolyline(mPoints);
    ewPolyline->setPenColor(view->PenColor());
    ewPolyline->setPenWidth(view->PenWidth());
    ewPolyline->setPenStyle(view->PenStyle());

    view->addRenderable(ewPolyline);

    // 完成后重置
    view->Invalidate(); //客户区需要重绘
    view->UpdateWindow(); //客户区执行重绘
    mStep = 0; //设为0可重写开始绘制线段而不用点击命令面板上的线段按钮
    polyline.clear();
    mLastPoint = CPoint(0, 0);
    view->Prompt(_T("多边线创建完成"));
    return 0;
}

int CG2DPolylineCreateCommand::OnMButtonDown(UINT /* nFlags */, CPoint /* pos */) {
    return OnRButtonDown(0, CPoint(0, 0));
}

int CG2DPolylineCreateCommand::OnMouseMove(UINT nFlags, CPoint pos) {
    // 鼠标移动时绘制橡皮线
    if (mView == nullptr || polyline.empty())
        return -1;

    CCG2D2021xxxxxx名字View* view = dynamic_cast<CCG2D2021xxxxxx名字View*>(mView);
    if (view == nullptr)
        return -1;
    if (mStep == 0) //还没点击第一个点（获取线段起点）
    {
        view->Prompt(_T("请输入折线的起点")); //状态栏显示
    }else if (mStep > 0) {
        CPoint lastPoint = polyline.back();
        DrawR2NOTLine(lastPoint, mLastPoint);
        DrawR2NOTLine(lastPoint, pos);
        mLastPoint = pos;
    }
    return 0;
}

int CG2DPolylineCreateCommand::Cancel() {
    // 取消操作，清除已捕捉的点
    if (mView == nullptr)
        return -1;

    CCG2D2021xxxxxx名字View * view = dynamic_cast<CCG2D2021xxxxxx名字View*>(mView);
    if (view == nullptr)
        return -1;


    if (!polyline.empty()) {
        // 擦除从最后一个点到当前鼠标位置的橡皮线
        CPoint lastPoint = polyline.back();
        DrawR2NOTLine(lastPoint, mLastPoint);
        mLastPoint = lastPoint;
        polyline.pop();
    }

    // 清除所有已捕捉的点
    polyline.clear();
    mLastPoint = CPoint(0, 0);
    mStep = 0;

    // 通知视图更新
    view->Invalidate();
    view->UpdateWindow();
    view->Prompt(_T("就绪"));

    return 0;
}

