#include "pch.h"
#include "CG2D2021xxxxxx����Doc.h"
#include "CG2D2021xxxxxx����View.h"
#include "CG2DRenderableRotateCommand.h"

CG2DRenderableRotateCommand::CG2DRenderableRotateCommand(CView* pview, CCG2D2021xxxxxx����Doc* pDoc)
    : UIEventListener(pview), mDoc(pDoc)
{
    mStep = 0;
    mCenter = mStartPos = mEndPos = CPoint(0, 0);
}

int CG2DRenderableRotateCommand::GetType()
{
    return static_cast<int>(CommandType::cmd2dRotateRenderable);
}

int CG2DRenderableRotateCommand::OnLButtonDown(UINT nFlags, CPoint pos)
{
    if (mView == nullptr)
        return -1;
    CCG2D2021xxxxxx����View* view = dynamic_cast<CCG2D2021xxxxxx����View*>(mView);
    if (view == nullptr)
        return -1;

    mStep++;
    if (mStep == 1)
    {
        view->Prompt(_T("ѡ����ת���ĵ�"));
        mCenter = pos;  // Set rotation center
    }
    else if (mStep == 2)
    {
        view->Prompt(_T("ѡ����ת�ǶȲο���"));
        mStartPos = mEndPos = pos;  // Set start position to calculate angle
    }
    else if (mStep == 3)
    {
        view->Prompt(_T("ת�����"));
        mStep = 0;
        mCenter = mStartPos = mEndPos = CPoint(0, 0);
        
    }
    return 0;
}

int CG2DRenderableRotateCommand::OnMouseMove(UINT nFlags, CPoint pos)
{
    if (mView == nullptr || mStep < 1)
        return -1;
    CCG2D2021xxxxxx����View* view = dynamic_cast<CCG2D2021xxxxxx����View*>(mView);
    if (view == nullptr)
        return -1;
    if (mStep == 0)
    {
        view->Prompt(_T("ѡ����ת���ĵ�"));
    }
    else if (mStep == 1)
    {
        view->Prompt(_T("ѡ����ת�ǶȲο���"));
    }
    else if (mStep == 2)
    {
        view->Prompt(_T("��ת�У���갴��ѡ��ѡ��ת�յ�"));

        if (mDoc)
        { 
            Vec2d center = view->ViewPorttoWorld(Vec2i(mCenter.x, mCenter.y));
            Vec2d start = view->ViewPorttoWorld(Vec2i(mEndPos.x, mEndPos.y));
            Vec2d current = view->ViewPorttoWorld(Vec2i(pos.x, pos.y));

            double angle = atan2(current.y() - center.y(), current.x() - center.x()) -
                atan2(start.y() - center.y(), start.x() - center.x());
            angle = angle * 180 / PI;
            mDoc->Rotate(angle, center.x(), center.y());
            mEndPos = pos;

            if (mView) {
                mView->Invalidate(true);
                mView->UpdateWindow();
            }
        }
        
    }
    return 0;
}

int CG2DRenderableRotateCommand::Cancel()
{
    if (mView == nullptr)
        return -1;
    CCG2D2021xxxxxx����View* view = dynamic_cast<CCG2D2021xxxxxx����View*>(mView);
    if (view == nullptr)
        return -1;
    mStep = 0;
    view->Prompt(_T("����"));
    return 0;
}
