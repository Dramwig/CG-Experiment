#include "pch.h"
#include "CG2DCameraMoveCommand.h"
#include "CG2D2021xxxxxx名字Doc.h" //包含View之前要包含Doc
#include "CG2D2021xxxxxx名字View.h" //用户交互绘制，并将图形对象通过Doc添加到场景
#include "CG2DLineSegment.h" //将创建的图形对象：直线段
#include <cstring>

CG2DCameraMoveCommand::CG2DCameraMoveCommand(CView* pview/* = nullptr*/)
	:UIEventListener(pview), mStart(0, 0), mEnd(0, 0)
{
	mStep = 0;
}
int CG2DCameraMoveCommand::GetType() //命令类型
{
	return static_cast<int>(CommandType::cmd2dCameraMove); //UIEventListener.h中定义，要根据不同的命令对象进行修改，此处是绘制直线段
}
int CG2DCameraMoveCommand::OnLButtonDown(UINT nFlags, CPoint pos)//
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
		view->Prompt(_T("选择移动的终点")); //通过处理事件的View显示到状态栏
	}
	else if (mStep == 2) //第二次单击鼠标左键，记录鼠标点击位置作为将创建线段的终点
	{
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
		view->Prompt(_T("请选择参考移动起点")); //状态栏显示
		mStep = 0; //操作结束，重置步骤
	}
	else
	{
	}
	return 0;
}

int CG2DCameraMoveCommand::OnMouseMove(UINT nFlags, CPoint pos)
{
	if (mView == nullptr)
		return -1;
	CCG2D2021xxxxxx名字View* view = dynamic_cast<CCG2D2021xxxxxx名字View*>(mView);
	if (view == nullptr)
		return -1;
	if (mStep == 0) //还没点击第一个点（获取线段起点）
	{
		view->Prompt(_T("请选择参考移动起点")); //状态栏显示
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
		Vec2d start = view->ViewPorttoWorld(Vec2i(prePos.x, prePos.y));
		Vec2d end = view->ViewPorttoWorld(Vec2i(curPos.x, curPos.y));
		view->CameraMoveOffset(end.x() - start.x(), end.y() - start.y()); //移动相机（视口）（二维）（相机移动，视口移动）
		mEnd = curPos; //记录最新位置，作为终点
	}
	else
	{
	}
	return 0;
}
int CG2DCameraMoveCommand::Cancel()
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
