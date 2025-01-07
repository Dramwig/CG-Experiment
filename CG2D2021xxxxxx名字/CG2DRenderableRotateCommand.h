#pragma once
#include "UIEventListener.h"
class CG2DRenderableRotateCommand : public UIEventListener
{
public:
	CG2DRenderableRotateCommand(CView* pview = nullptr, CCG2D2021xxxxxx名字Doc* pDoc = nullptr);
	~CG2DRenderableRotateCommand() = default;
	virtual int GetType() override; //命令类型
	//鼠标事件（鼠标左键单击用于拾取）
	virtual int OnLButtonDown(UINT nFlags, CPoint pos) override;
	//	virtual int OnLButtonUp(UINT nFlags, CPoint pos) override;
	virtual int OnMouseMove(UINT nFlags, CPoint pos) override;
	//取消Esc
	virtual int Cancel() override;
private:
	CPoint mCenter, mStartPos, mEndPos; // 鼠标按下时的位置
	CCG2D2021xxxxxx名字Doc* mDoc;
};
