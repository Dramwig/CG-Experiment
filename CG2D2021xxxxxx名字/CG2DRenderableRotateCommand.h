#pragma once
#include "UIEventListener.h"
class CG2DRenderableRotateCommand : public UIEventListener
{
public:
	CG2DRenderableRotateCommand(CView* pview = nullptr, CCG2D2021xxxxxx����Doc* pDoc = nullptr);
	~CG2DRenderableRotateCommand() = default;
	virtual int GetType() override; //��������
	//����¼�����������������ʰȡ��
	virtual int OnLButtonDown(UINT nFlags, CPoint pos) override;
	//	virtual int OnLButtonUp(UINT nFlags, CPoint pos) override;
	virtual int OnMouseMove(UINT nFlags, CPoint pos) override;
	//ȡ��Esc
	virtual int Cancel() override;
private:
	CPoint mCenter, mStartPos, mEndPos; // ��갴��ʱ��λ��
	CCG2D2021xxxxxx����Doc* mDoc;
};
