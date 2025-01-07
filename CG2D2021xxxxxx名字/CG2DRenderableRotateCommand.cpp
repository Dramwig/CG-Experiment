#include "pch.h"
#include "CG2D2021xxxxxx名字Doc.h"
#include "CG2D2021xxxxxx名字View.h"
#include "CG2DRenderableRotateCommand.h"

CG2DRenderableRotateCommand::CG2DRenderableRotateCommand(CView* pview, CCG2D2021xxxxxx名字Doc* pDoc)
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
    CCG2D2021xxxxxx名字View* view = dynamic_cast<CCG2D2021xxxxxx名字View*>(mView);
    if (view == nullptr)
        return -1;

    mStep++;
    if (mStep == 1)
    {
        view->Prompt(_T("选择旋转中心点"));
        mCenter = pos;  // Set rotation center
    }
    else if (mStep == 2)
    {
        view->Prompt(_T("选择旋转角度参考点"));
        mStartPos = mEndPos = pos;  // Set start position to calculate angle
    }
    else if (mStep == 3)
    {
        view->Prompt(_T("转动完成"));
        mStep = 0;
        mCenter = mStartPos = mEndPos = CPoint(0, 0);
        
    }
    return 0;
}

int CG2DRenderableRotateCommand::OnMouseMove(UINT nFlags, CPoint pos)
{
    if (mView == nullptr || mStep < 1)
        return -1;
    CCG2D2021xxxxxx名字View* view = dynamic_cast<CCG2D2021xxxxxx名字View*>(mView);
    if (view == nullptr)
        return -1;
    if (mStep == 0)
    {
        view->Prompt(_T("选择旋转中心点"));
    }
    else if (mStep == 1)
    {
        view->Prompt(_T("选择旋转角度参考点"));
    }
    else if (mStep == 2)
    {
        view->Prompt(_T("旋转中，鼠标按下选择选旋转终点"));

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
    CCG2D2021xxxxxx名字View* view = dynamic_cast<CCG2D2021xxxxxx名字View*>(mView);
    if (view == nullptr)
        return -1;
    mStep = 0;
    view->Prompt(_T("就绪"));
    return 0;
}
