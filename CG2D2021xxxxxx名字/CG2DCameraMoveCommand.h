#pragma once
#include "UIEventListener.h"
class CG2DCameraMoveCommand : public UIEventListener
{
public:
	CG2DCameraMoveCommand(CView* pview = nullptr);
	~CG2DCameraMoveCommand() = default;
	virtual int GetType() override; //命令类型
	//假定鼠标左键单击拾取线段起点、终点，移动鼠标时画橡皮筋线
	virtual int OnLButtonDown(UINT nFlags, CPoint pos) override;
	virtual int OnMouseMove(UINT nFlags, CPoint pos) override;
	//取消正在执行的命令（如按ESC键）
	virtual int Cancel() override;
protected:
	CPoint mStart; //点击的第一点作为线段起点
	CPoint mEnd; //点击的第二点作为线段终点
};
