#include "pch.h"
#include "CG2DLineSegmentCreateCommand.h"
#include "CG2D2021xxxxxx名字Doc.h" //包含View之前要包含Doc
#include "CG2D2021xxxxxx名字View.h" //用户交互绘制，并将图形对象通过Doc添加到场景
#include "CG2DLineSegment.h" //将创建的图形对象：直线段
#include <cstring>

CG2DLineSegmentCreateCommand::CG2DLineSegmentCreateCommand(CView* pview/* = nullptr*/)
	:UIEventListener(pview), mStart(0, 0), mEnd(0, 0)
{
	mStep = 0;
}
int CG2DLineSegmentCreateCommand::GetType() //命令类型
{
	return static_cast<int>(CommandType::cmd2dLineSegment); //UIEventListener.h中定义，要根据不同的命令对象进行修改，此处是绘制直线段
}
int CG2DLineSegmentCreateCommand::OnLButtonDown(UINT nFlags, CPoint pos)//
{
	if (mView == nullptr)
		return -1;
	CCG2D2021xxxxxx名字View* view = dynamic_cast<CCG2D2021xxxxxx名字View*>(mView);
	if (view == nullptr)
		return -1;
	mStep++; //每次单击鼠标左键时操作步骤计数加一

	if (mStep == 1) //第一次单击鼠标左键，记录鼠标点击位置作为将创建线段的起点
	{
		mStart = mEnd = pos;
		view->Prompt(_T("请输入直线段的终点")); //通过处理事件的View显示到状态栏
	}
	else if (mStep == 2) //第二次单击鼠标左键，记录鼠标点击位置作为将创建线段的终点
	{
		if (pos == mStart)
		{
			mStep = 1;
			view->Prompt(_T("与第一点重合，请输入直线段的终点"));
			return -1;
		}
		//擦除最后橡皮线
		CClientDC dc(mView);
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = dc.SelectObject(&pen);
		int mode = dc.SetROP2(R2_NOTXORPEN); //R2_NOT
		dc.MoveTo(CPoint(mStart.x, mStart.y));
		dc.LineTo(CPoint(mEnd.x, mEnd.y));
		dc.SelectObject(pOldPen);
		dc.SetROP2(mode);
		//判断是否按下SHIFT键，如果是，则根据X、Y方向的增量大小决定绘制水平线或垂直线
		if (nFlags & MK_SHIFT)//按下了MK_SHIFT键
		{
			if (abs(pos.x - mStart.x) <= abs(pos.y - mStart.y)) //x方向变化小，垂直线
			{
				mEnd.x = mStart.x; //X保持不变
				mEnd.y = pos.y;
			}
			else //x方向变化大，水平线
			{
				mEnd.x = pos.x;
				mEnd.y = mStart.y; //Y保持不变
			}
		}
		else //一般直线段（非水平、垂直），记录终点。
		{
			mEnd = pos;
		}
		//鼠标左键第二次单击，直线段创建的起点、终点已获取。
		//创建对象要注意坐标转换到场景，并设置相应的属性
		//获取起点、终点对应的场景坐标用于创建直线段对象
		Vec2d start = view->ViewPorttoWorld(Vec2i(mStart.x, mStart.y));
		Vec2d end = view->ViewPorttoWorld(Vec2i(mEnd.x, mEnd.y));
		//创建线段并添加到场景
		CG2DLineSegment* pLine = new CG2DLineSegment(start, end);
		pLine->setPenColor(view->PenColor());
		pLine->setPenWidth(view->PenWidth());
		pLine->setPenStyle(view->PenStyle());
		view->addRenderable(pLine); //创建成功，添加到场景
		view->Invalidate(); //客户区需要重绘
		view->UpdateWindow(); //客户区执行重绘
		mStep = 0; //设为0可重写开始绘制线段而不用点击命令面板上的线段按钮
		mStart.x = mStart.y = mEnd.x = mEnd.y = 0;
		view->Prompt(_T("请输入直线段的起点")); //状态栏显示
	}
	else
	{
	}
	return 0;
}

int CG2DLineSegmentCreateCommand::OnMouseMove(UINT nFlags, CPoint pos)
{ 
	if (mView == nullptr)
		return -1;
	CCG2D2021xxxxxx名字View* view = dynamic_cast<CCG2D2021xxxxxx名字View*>(mView);
	if (view == nullptr)
		return -1;
	if (mStep == 0) //还没点击第一个点（获取线段起点）
	{
		view->Prompt(_T("请输入直线段的起点")); //状态栏显示
		//CString strPrompt; // 创建一个CString对象来存储格式化的提示信息
		//strPrompt.Format(_T("请输入直线段的起点，当前：(%d, %d)"), pos.x, pos.y);
		//view->Prompt(strPrompt);  // 显示提示信息
	}
	else if (mStep == 1) //已经输入了起点后，当前鼠标移动的位置与起点形成橡皮线
	{
		if (pos == mStart)
		{
			return -1; //两点重合，不做处理
		}
		CPoint prePos, curPos;
		prePos = mEnd;
		//判断是否按下SHIFT键，绘制水平线或垂直线
		if (nFlags & MK_SHIFT)
		{
			if (abs(pos.x - mStart.x) <= abs(pos.y - mStart.y)) //x方向变化小，垂直线
			{
				curPos.x = mStart.x;
				curPos.y = pos.y;
			}
			else
			{
				curPos.x = pos.x;
				curPos.y = mStart.y;
			}
		}
		else
		{
			curPos = pos;
		}
		//CString strPrompt; // 创建一个CString对象来存储格式化的提示信息
		//strPrompt.Format(_T("请输入直线段的终点，当前：(%d, %d)"), curPos.x, curPos.y);
		//view->Prompt(strPrompt);  // 显示提示信息
		//绘制新橡皮线时先擦除上次的橡皮线
		CClientDC dc(mView);
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = dc.SelectObject(&pen);
		int mode = dc.SetROP2(R2_NOTXORPEN); //R2_NOT
		dc.MoveTo(CPoint(mStart.x, mStart.y));
		dc.LineTo(CPoint(prePos.x, prePos.y));
		//绘制新的橡皮线
		dc.MoveTo(CPoint(mStart.x, mStart.y));
		dc.LineTo(CPoint(curPos.x, curPos.y));
		dc.SelectObject(pOldPen);
		dc.SetROP2(mode);
		mEnd = curPos; //记录最新位置，作为终点
	}
	else
	{
	}
	return 0;
}
int CG2DLineSegmentCreateCommand::Cancel()
{
	if (mView == nullptr)
		return -1;
	CCG2D2021xxxxxx名字View* view = dynamic_cast<CCG2D2021xxxxxx名字View*>(mView);
	if (view == nullptr)
		return -1;
	if (mStep == 1) //如果已经单击左键一次，则结束操作前删除橡皮线
	{
		CClientDC dc(mView);
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = dc.SelectObject(&pen);
		int mode = dc.SetROP2(R2_NOTXORPEN); //R2_NOT
		dc.MoveTo(CPoint(mStart.x, mStart.y));
		dc.LineTo(CPoint(mEnd.x, mEnd.y));
		dc.SelectObject(pOldPen);
		dc.SetROP2(mode);
	}
	mStep = 0;
	mStart.x = mStart.y = mEnd.x = mEnd.y = 0;
	view->Prompt(_T("就绪")); //状态栏显示
	return 0;
}
