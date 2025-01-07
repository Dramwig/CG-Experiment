#ifndef _UIEventListener_H_INCLUDED
#define _UIEventListener_H_INCLUDED
#include "CGObject.h"
enum class CommandType //操作命令类型，参考如下定义，可根据需要修改
{
	cmdNone = 0, //无，显示鼠标指针，不交互画图
	cmd2dLineSegment = 1, //利用起点、终点绘制直线段
	cmd2dLine = 2, //启用两点绘制无限长直线
	cmd2dRay = 3, //利用起点、方向（第二点确定）绘制射线
	cmd2dPolyline = 4, //折线连续相连的直线段形成
	cmd2dCircleCenterRadius = 10, //圆心和半径（第二点确定）绘制整圆
	cmd2dCricle2PDiameter = 11, //利用两点形成圆直径绘制整圆
	cmd2dCircle2PSemi = 12, //利用两点形成半圆弧（圆弧方向由第二点确定，逆时针方向）
	cmd2dCricle3PCircum = 13, //输入三点形成外接整圆
	cmd2dCircle3PArc = 14, //利用三点形成圆弧（第一点是圆心，第二点是弧起点，第三点弧终点，逆时针方向）
	cmd2dCircle3PFan = 15, //利用三点形成扇形（第一点是圆心，第二点是弧起点，第三点弧终点，逆时针方向）
	cmd2dCircle3PExArc = 16, //利用三点形成外接圆弧
	cmd2dCircle3PExFan = 17, //利用三点形成外接扇形
	cmd2dEllipse = 30, //通过包围矩形绘制椭圆
	cmd2dEllipseArc = 31, //绘制椭圆弧
	cmd2dRectangle = 40,
	cmd2dPolygon = 41,
	cmd2dRegularPolygon = 42,
	cmd2dSeedFill = 43,
	cmd2dTranslateRenderable = 100,
	cmd2dRotateRenderable = 101,
	cmd2dScaleRenderable = 102,
	cmd2dMirrorRenderable = 103,
	cmd2dShearRenderable = 104,
	cmd2dMoveRenderable = 105,
	cmd2dMoveCamera = 110,
	cmd2dRotateCamera = 111,
	cmd2dZoomCamera = 112,
	cmd2dPickRenderable = 115,
	cmd2dPickInBoxRenderable = 117,
	cmd2dRectClip = 121,
	cmd2dPolyClip = 122,
	cmd2dCameraMove = 130,
	cmd2dWindowBox = 131,
	cmdUnknown = 1000
};
//与绘图客户区的交互，使用命令模式，简化CView派生类中键盘、鼠标事件的处理
class UIEventListener : public CGObject
{
public:
	UIEventListener(CView* pview = nullptr) :mStep(0), mView(pview) { }
	~UIEventListener() = default;
	//命令类型，必须在派生类中重写
	virtual int GetType() = 0;
	//取消命令（按ESC键中断当前命令的执行），必须在派生类中重写
	virtual int Cancel() = 0;
	//鼠标事件（都只给出默认实现，派生类根据需要重写相应的函数）
	virtual int OnLButtonUp(UINT nFlags, CPoint point) { return 0; }
	virtual int OnLButtonDown(UINT nFlags, CPoint point) { return 0; }
	virtual int OnLButtonDblClk(UINT nFlags, CPoint point) { return 0; }
	virtual int OnMouseMove(UINT nFlags, CPoint point) { return 0; }
	virtual int OnMouseWheel(UINT nFlags, short zDelta, CPoint point) { return 0; }
	virtual int OnMButtonUp(UINT nFlags, CPoint point) { return 0; }
	virtual int OnMButtonDown(UINT nFlags, CPoint point) { return 0; }
	virtual int OnMButtonDblClk(UINT nFlags, CPoint point) { return 0; }
	virtual int OnRButtonUp(UINT nFlags, CPoint point) { return 0; }
	virtual int OnRButtonDown(UINT nFlags, CPoint point) { return 0; }
	virtual int OnRButtonDblClk(UINT nFlags, CPoint point) { return 0; }
	//键盘事件（都只给出默认实现，派生类根据需要重写相应的函数）
	virtual int OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) { return 0; }
	virtual int OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) { return 0; }
	virtual int OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) { return 0; }
	virtual int OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) { return 0; }
	virtual int OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) { return 0; }
protected:
	int mStep = 0; // 命令操作计数
	CView* mView = nullptr; // 处理事件的窗口
};
#endif //_UIEventListener_H_INCLUDED
