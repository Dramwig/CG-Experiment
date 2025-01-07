#ifndef _CG2DRenderablePickCommand_H_INCLUDED
#define _CG2DRenderablePickCommand_H_INCLUDED
#include "UIEventListener.h"
class CG2DRenderablePickCommand : public UIEventListener
{
public:
	CG2DRenderablePickCommand(CView* pview = nullptr);
	~CG2DRenderablePickCommand() = default;
	virtual int GetType() override; //命令类型
	//鼠标事件（鼠标左键单击用于拾取）
	virtual int OnLButtonDown(UINT nFlags, CPoint pos) override;
	virtual int OnMouseMove(UINT nFlags, CPoint pos) override;
	//取消Esc
	virtual int Cancel() override;
};
#endif //_CG2DRenderablePickCommand_H_INCLUDED
