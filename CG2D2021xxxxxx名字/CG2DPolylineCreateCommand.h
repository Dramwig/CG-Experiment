#pragma once
#include "UIEventListener.h"
#include "CG2DPolyline.h"
class CG2DPolylineCreateCommand : public UIEventListener
{
public:
	CG2DPolylineCreateCommand(CView* pview = nullptr);
	~CG2DPolylineCreateCommand() = default;
	virtual int GetType() override; //命令类型
	//假定鼠标左键单击拾取线段起点、终点，移动鼠标时画橡皮筋线
	virtual int OnLButtonDown(UINT nFlags, CPoint pos) override;
	virtual int OnRButtonDown(UINT nFlags, CPoint pos) override;
	virtual int OnMButtonDown(UINT nFlags, CPoint pos) override;
	virtual int OnMouseMove(UINT nFlags, CPoint pos) override;
	//取消正在执行的命令（如按ESC键）
	virtual int Cancel() override;
	virtual void DrawR2NOTLine(CPoint& mStart, CPoint& prePos)const;
protected:
	CG2DPolyline polyline;
	CPoint mLastPoint;
};
