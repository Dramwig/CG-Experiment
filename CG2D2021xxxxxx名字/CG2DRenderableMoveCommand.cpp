#include "pch.h"
#include "CG2D2021xxxxxx名字Doc.h" //包含View之前要包含Doc
#include "CG2D2021xxxxxx名字View.h" //用户交互绘制，并将图形对象通过Doc添加到场景
#include "CG2DRenderableMoveCommand.h"

CG2DRenderableMoveCommand::CG2DRenderableMoveCommand(CView* pview/* = nullptr*/, CCG2D2021xxxxxx名字Doc* pDoc/* = nullptr*/)
	:UIEventListener(pview), mDoc(pDoc)
{
	mStep = 0;
	mStartPos = CPoint(0, 0);
	prePos = CPoint(0, 0);
}

int CG2DRenderableMoveCommand::GetType() //命令类型
{
	return static_cast<int>(CommandType::cmd2dMoveRenderable); //UIEventListener.h中定义，要根据不同的命令对象进行修改，此处是绘制直线段
}

//鼠标事件（鼠标左键单击用于拾取）
int CG2DRenderableMoveCommand::OnLButtonDown(UINT nFlags, CPoint pos)
{
	if (mView == nullptr)
		return -1;
	CCG2D2021xxxxxx名字View* view = dynamic_cast<CCG2D2021xxxxxx名字View*>(mView);
	if (view == nullptr)
		return -1;

	mStep++; //每次单击鼠标左键时操作步骤计数加一
	if (mStep == 1)
	{
		view->Prompt(_T("拖动鼠标选择图形对象"));
		mStartPos = pos;
		prePos = pos;
	}
	else if (mStep == 2)
	{
		view->Prompt(_T("移动完成"));
		mStep = 0;
		mStartPos = CPoint(0, 0);
		prePos = CPoint(0, 0);
	}
	return 0;
}

int CG2DRenderableMoveCommand::OnMouseMove(UINT nFlags, CPoint pos)
{
	if (mView == nullptr)
		return -1;
	CCG2D2021xxxxxx名字View* view = dynamic_cast<CCG2D2021xxxxxx名字View*>(mView);
	if (view == nullptr)
		return -1;
	if (mStep == 0)
	{
		view->Prompt(_T("鼠标按下选择参考点"));
	}
	else if (mStep == 1)
	{
		view->Prompt(_T("鼠标按下选择移动终点"));
		if (mDoc)
		{
			Vec2d s = view->ViewPorttoWorld(Vec2i(prePos.x, prePos.y));
			Vec2d t = view->ViewPorttoWorld(Vec2i(pos.x, pos.y));
			mDoc->Translate(t.x() - s.x(), t.y() - s.y());
			prePos = pos;
			if (mView) {
				mView->Invalidate(true);
				mView->UpdateWindow();
			}
		}
	}
	return 0;
}

//取消Esc
int CG2DRenderableMoveCommand::Cancel()
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

