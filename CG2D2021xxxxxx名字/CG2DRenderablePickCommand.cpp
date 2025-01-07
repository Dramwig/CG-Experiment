#include "pch.h"
#include "CG2D2021xxxxxx名字Doc.h" //包含View之前要包含Doc
#include "CG2D2021xxxxxx名字View.h" //用户交互绘制，并将图形对象通过Doc添加到场景
#include "CG2DRenderablePickCommand.h"
CG2DRenderablePickCommand::CG2DRenderablePickCommand(CView* pview/* = nullptr*/)
	:UIEventListener(pview)
{
	mStep = 0;
}
int CG2DRenderablePickCommand::GetType() //命令类型
{
	return static_cast<int>(CommandType::cmd2dPickRenderable); //UIEventListener.h中定义，要根据不同的命令对象进行修改，此处是绘制直线段
}
//鼠标事件（鼠标左键单击用于拾取）
int CG2DRenderablePickCommand::OnLButtonDown(UINT nFlags, CPoint pos)
{
	if (mView == nullptr)
		return -1;
	CCG2D2021xxxxxx名字View* view = dynamic_cast<CCG2D2021xxxxxx名字View*>(mView);
	if (view == nullptr)
		return -1;
	mStep++; //每次单击鼠标左键时操作步骤计数加一
	if (mStep == 1)
	{
		Vec2d p = view->ViewPorttoWorld(Vec2i(pos.x, pos.y));
		if (nFlags & MK_CONTROL)  //Ctrl键按下
			view->AppendPicked(p, 5); //假定pick半径5，需要单独定义
		else
			view->UpdatePicked(p, 5);
		mStep = 0;
	}
	return 0;
}
int CG2DRenderablePickCommand::OnMouseMove(UINT nFlags, CPoint pos)
{
	if (mView == nullptr)
		return -1;
	CCG2D2021xxxxxx名字View* view = dynamic_cast<CCG2D2021xxxxxx名字View*>(mView);
	if (view == nullptr)
		return -1;
	if (mStep == 0)
	{
		view->Prompt(_T("鼠标点击图形对象"));
	}
	return 0;
}
//取消Esc
int CG2DRenderablePickCommand::Cancel()
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
