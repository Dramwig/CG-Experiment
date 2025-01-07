#pragma once
#include "UIEventListener.h"
class CG2DRenderableMoveCommand : public UIEventListener
{
public:
	CG2DRenderableMoveCommand(CView* pview = nullptr, CCG2D2021xxxxxx����Doc* pDoc = nullptr);
	~CG2DRenderableMoveCommand() = default;
	virtual int GetType() override; //��������
	//����¼�����������������ʰȡ��
	virtual int OnLButtonDown(UINT nFlags, CPoint pos) override;
//	virtual int OnLButtonUp(UINT nFlags, CPoint pos) override;
	virtual int OnMouseMove(UINT nFlags, CPoint pos) override;
	//ȡ��Esc
	virtual int Cancel() override;
private:
	CPoint mStartPos, prePos; // ��갴��ʱ��λ��
	CCG2D2021xxxxxx����Doc* mDoc;
};
