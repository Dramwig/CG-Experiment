#pragma once
#include "UIEventListener.h"
class CG2DRenderablePickInBoxCommand : public UIEventListener
{
public:
	CG2DRenderablePickInBoxCommand(CView* pview = nullptr);
	~CG2DRenderablePickInBoxCommand() = default;
	virtual int GetType() override; //��������
	virtual void DrawRect(CView* mView, CPoint start, CPoint end);
	//����¼�����������������ʰȡ��
	virtual int OnLButtonDown(UINT nFlags, CPoint pos) override;
	virtual int OnLButtonUp(UINT nFlags, CPoint pos) override;
	virtual int OnMouseMove(UINT nFlags, CPoint pos) override;
	//ȡ��Esc
	virtual int Cancel() override;
private:
	CPoint mStartPos, prePos; // ��갴��ʱ��λ��
	bool mIsLongPress; // �Ƿ��ڳ���״̬
};
