#pragma once
#include "UIEventListener.h"
class CG2DCameraMoveCommand : public UIEventListener
{
public:
	CG2DCameraMoveCommand(CView* pview = nullptr);
	~CG2DCameraMoveCommand() = default;
	virtual int GetType() override; //��������
	//�ٶ�����������ʰȡ�߶���㡢�յ㣬�ƶ����ʱ����Ƥ����
	virtual int OnLButtonDown(UINT nFlags, CPoint pos) override;
	virtual int OnMouseMove(UINT nFlags, CPoint pos) override;
	//ȡ������ִ�е�����簴ESC����
	virtual int Cancel() override;
protected:
	CPoint mStart; //����ĵ�һ����Ϊ�߶����
	CPoint mEnd; //����ĵڶ�����Ϊ�߶��յ�
};
