#ifndef _CG2DRenderablePickCommand_H_INCLUDED
#define _CG2DRenderablePickCommand_H_INCLUDED
#include "UIEventListener.h"
class CG2DRenderablePickCommand : public UIEventListener
{
public:
	CG2DRenderablePickCommand(CView* pview = nullptr);
	~CG2DRenderablePickCommand() = default;
	virtual int GetType() override; //��������
	//����¼�����������������ʰȡ��
	virtual int OnLButtonDown(UINT nFlags, CPoint pos) override;
	virtual int OnMouseMove(UINT nFlags, CPoint pos) override;
	//ȡ��Esc
	virtual int Cancel() override;
};
#endif //_CG2DRenderablePickCommand_H_INCLUDED
