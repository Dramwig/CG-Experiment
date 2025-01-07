#pragma once
#include "UIEventListener.h"
#include "CG2DPolygon.h"
class CG2DPolygonCreateCommand : public UIEventListener
{
public:
	CG2DPolygonCreateCommand(CView* pview = nullptr);
	~CG2DPolygonCreateCommand() = default;
	virtual int GetType() override; //��������
	//�ٶ�����������ʰȡ�߶���㡢�յ㣬�ƶ����ʱ����Ƥ����
	virtual int OnLButtonDown(UINT nFlags, CPoint pos) override;
	virtual int OnRButtonDown(UINT nFlags, CPoint pos) override;
	virtual int OnMButtonDown(UINT nFlags, CPoint pos) override;
	virtual int OnMouseMove(UINT nFlags, CPoint pos) override;
	//ȡ������ִ�е�����簴ESC����
	virtual int Cancel() override;
	virtual void DrawR2NOTLine(CPoint& mStart, CPoint& prePos)const;
protected:
	CG2DPolygon polygon;
	CPoint mLastPoint;
};
