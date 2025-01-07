#pragma once
#include "UIEventListener.h"
class CG2DWindowBoxCommand : public UIEventListener
{
public:
	CG2DWindowBoxCommand(CView* pview = nullptr);
	~CG2DWindowBoxCommand() = default;
	virtual int GetType() override; //命令类型
	virtual void DrawRect(CView* mView, CPoint start, CPoint end);
	//鼠标事件（鼠标左键单击用于拾取）
	virtual int OnLButtonDown(UINT nFlags, CPoint pos) override;
	virtual int OnLButtonUp(UINT nFlags, CPoint pos) override;
	virtual int OnMouseMove(UINT nFlags, CPoint pos) override;
	//取消Esc
	virtual int Cancel() override;
private:
	CPoint mStartPos, prePos; // 鼠标按下时的位置
	bool mIsLongPress; // 是否处于长按状态
};
