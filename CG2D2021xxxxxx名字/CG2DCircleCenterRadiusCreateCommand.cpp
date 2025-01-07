#include "pch.h"
#include "CG2DCircleCenterRadiusCreateCommand.h"
#include "CG2D2021xxxxxx名字Doc.h" //包含View之前要包含Doc
#include "CG2D2021xxxxxx名字View.h" //用户交互绘制，并将图形对象通过Doc添加到场景
#include "CG2DLineSegment.h"
#include "CG2DCircle.h"
#include "CG2DPolygon.h"

CG2DCircleCenterRadiusCreateCommand::CG2DCircleCenterRadiusCreateCommand(CView* pview/* = nullptr*/)
	:UIEventListener(pview), mCenter(0, 0), mEdgePoint(0, 0)
{
	mStep = 0;
}
int CG2DCircleCenterRadiusCreateCommand::GetType() //命令类型
{
	return static_cast<int>(CommandType::cmd2dCircleCenterRadius); //UIEventListener.h中定义，要根据不同的命令对象进行修改，此处是绘制直线段
}
int CG2DCircleCenterRadiusCreateCommand::OnLButtonDown(UINT nFlags, CPoint pos)
{
	if (mView == nullptr)
		return -1;
	CCG2D2021xxxxxx名字View* view = dynamic_cast<CCG2D2021xxxxxx名字View*>(mView);
	if (view == nullptr)
		return -1;
	mStep++; //每次单击鼠标左键时操作步骤计数加一
	mEdgePoint = pos;
	if (mStep == 1) //第一次单击鼠标左键，记录鼠标点击位置作为将创建线段的起点
	{
		mCenter = pos;
		view->Prompt(_T("请选择圆形的半径")); //通过处理事件的View显示到状态栏
	}
	else if (mStep == 2) //第二次单击鼠标左键，记录鼠标点击位置作为将创建线段的终点
	{
		if (pos == mCenter)
		{
			mStep = 1;
			view->Prompt(_T("与圆心重合，请重新选择半径"));
			return -1;
		}
		//擦除最后橡皮线
		CClientDC dc(mView);
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = dc.SelectObject(&pen);
		int mode = dc.SetROP2(R2_NOTXORPEN); //R2_NOT
		dc.MoveTo(CPoint(mCenter.x, mCenter.y));
		dc.LineTo(CPoint(mEdgePoint.x, mEdgePoint.y));
		dc.SelectObject(pOldPen);
		dc.SetROP2(mode);
		
		//鼠标左键第二次单击，直线段创建的起点、终点已获取。
		//创建对象要注意坐标转换到场景，并设置相应的属性
		//获取起点、终点对应的场景坐标用于创建直线段对象

		int Radius = static_cast<int>(sqrt(pow(mCenter.x - mEdgePoint.x, 2) 
			+ pow(mCenter.y - mEdgePoint.y, 2)));
		CG2DPolygon* polygon = new CG2DPolygon();
		polygon->setPenColor(view->PenColor());
		polygon->setPenWidth(view->PenWidth());
		polygon->setPenStyle(view->PenStyle());
		for(double theta = 0; theta < 2*PI; theta += 2*PI  / 100) {
			Vec2d p = Vec2d(mCenter.x + Radius * cos(theta), mCenter.y + Radius * sin(theta));
			p = view->ViewPorttoWorld(Vec2d(p.x(), p.y()));
			polygon->addPoint(p);
		}
		view->addRenderable(polygon); //创建成功，添加到场景
		view->Invalidate(); //客户区需要重绘
		view->UpdateWindow(); //客户区执行重绘
		mStep = 0; //设为0可重写开始绘制线段而不用点击命令面板上的线段按钮
		mCenter.x = mCenter.y = mEdgePoint.x = mEdgePoint.y = 0;
		view->Prompt(_T("请输入圆形的圆心")); //状态栏显示
	}
	else
	{
	}
	return 0;
}

int CG2DCircleCenterRadiusCreateCommand::OnMouseMove(UINT nFlags, CPoint pos)
{
	if (mView == nullptr)
		return -1;
	CCG2D2021xxxxxx名字View* view = dynamic_cast<CCG2D2021xxxxxx名字View*>(mView);
	if (view == nullptr)
		return -1;
	if (mStep == 0) //还没点击第一个点（获取线段起点）
	{
		view->Prompt(_T("请输入圆形的圆心")); //状态栏显示
	}
	else if (mStep == 1) //已经输入了起点后，当前鼠标移动的位置与起点形成橡皮线
	{
		if (pos == mCenter)
		{
			return -1; //两点重合，不做处理
		}
		CPoint prePos;
		prePos = mEdgePoint;
		//绘制新橡皮线时先擦除上次的橡皮线
		CClientDC dc(mView);
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = dc.SelectObject(&pen);
		int mode = dc.SetROP2(R2_NOTXORPEN); //R2_NOT
		dc.MoveTo(CPoint(mCenter.x, mCenter.y));
		dc.LineTo(CPoint(prePos.x, prePos.y));
		int preRadius = static_cast<int>(sqrt(pow(prePos.x - mCenter.x, 2) + pow(prePos.y - mCenter.y, 2)));
		dc.Ellipse(mCenter.x - preRadius, mCenter.y - preRadius, mCenter.x + preRadius, mCenter.y + preRadius);
		//绘制新的橡皮线
		int radius = static_cast<int>(sqrt(pow(pos.x - mCenter.x, 2) + pow(pos.y - mCenter.y, 2)));
		dc.Ellipse(mCenter.x - radius, mCenter.y - radius, mCenter.x + radius, mCenter.y + radius);
		dc.MoveTo(CPoint(mCenter.x, mCenter.y));
		dc.LineTo(CPoint(pos.x, pos.y));
		dc.SelectObject(pOldPen);
		dc.SetROP2(mode);
		mEdgePoint = pos; //记录最新位置，作为终点
	}
	else
	{
	}
	return 0;
}
int CG2DCircleCenterRadiusCreateCommand::Cancel()
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
		dc.MoveTo(CPoint(mCenter.x, mCenter.y));
		dc.LineTo(CPoint(mEdgePoint.x, mEdgePoint.y));
		dc.SelectObject(pOldPen);
		dc.SetROP2(mode);
	}
	mStep = 0;
	mCenter.x = mCenter.y = mEdgePoint.x = mEdgePoint.y = 0;
	view->Prompt(_T("就绪")); //状态栏显示
	return 0;
}
