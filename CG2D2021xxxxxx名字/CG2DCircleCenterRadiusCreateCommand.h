#pragma once
#include "UIEventListener.h"
class CG2DCircleCenterRadiusCreateCommand : public UIEventListener
{
public:
	CG2DCircleCenterRadiusCreateCommand(CView* pview = nullptr);
	~CG2DCircleCenterRadiusCreateCommand() = default;
	virtual int GetType() override; //��������
	//�ٶ�����������ʰȡ�߶���㡢�յ㣬�ƶ����ʱ����Ƥ����
	virtual int OnLButtonDown(UINT nFlags, CPoint pos) override;
	virtual int OnMouseMove(UINT nFlags, CPoint pos) override;
	//ȡ������ִ�е�����簴ESC����
	virtual int Cancel() override;
protected:
	CPoint mCenter; //����ĵ�һ����Ϊ�߶����
	CPoint mEdgePoint; //����ĵڶ�����Ϊ�߶��յ�
};
