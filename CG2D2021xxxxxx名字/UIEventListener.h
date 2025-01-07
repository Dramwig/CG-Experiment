#ifndef _UIEventListener_H_INCLUDED
#define _UIEventListener_H_INCLUDED
#include "CGObject.h"
enum class CommandType //�����������ͣ��ο����¶��壬�ɸ�����Ҫ�޸�
{
	cmdNone = 0, //�ޣ���ʾ���ָ�룬��������ͼ
	cmd2dLineSegment = 1, //������㡢�յ����ֱ�߶�
	cmd2dLine = 2, //��������������޳�ֱ��
	cmd2dRay = 3, //������㡢���򣨵ڶ���ȷ������������
	cmd2dPolyline = 4, //��������������ֱ�߶��γ�
	cmd2dCircleCenterRadius = 10, //Բ�ĺͰ뾶���ڶ���ȷ����������Բ
	cmd2dCricle2PDiameter = 11, //���������γ�Բֱ��������Բ
	cmd2dCircle2PSemi = 12, //���������γɰ�Բ����Բ�������ɵڶ���ȷ������ʱ�뷽��
	cmd2dCricle3PCircum = 13, //���������γ������Բ
	cmd2dCircle3PArc = 14, //���������γ�Բ������һ����Բ�ģ��ڶ����ǻ���㣬�����㻡�յ㣬��ʱ�뷽��
	cmd2dCircle3PFan = 15, //���������γ����Σ���һ����Բ�ģ��ڶ����ǻ���㣬�����㻡�յ㣬��ʱ�뷽��
	cmd2dCircle3PExArc = 16, //���������γ����Բ��
	cmd2dCircle3PExFan = 17, //���������γ��������
	cmd2dEllipse = 30, //ͨ����Χ���λ�����Բ
	cmd2dEllipseArc = 31, //������Բ��
	cmd2dRectangle = 40,
	cmd2dPolygon = 41,
	cmd2dRegularPolygon = 42,
	cmd2dSeedFill = 43,
	cmd2dTranslateRenderable = 100,
	cmd2dRotateRenderable = 101,
	cmd2dScaleRenderable = 102,
	cmd2dMirrorRenderable = 103,
	cmd2dShearRenderable = 104,
	cmd2dMoveRenderable = 105,
	cmd2dMoveCamera = 110,
	cmd2dRotateCamera = 111,
	cmd2dZoomCamera = 112,
	cmd2dPickRenderable = 115,
	cmd2dPickInBoxRenderable = 117,
	cmd2dRectClip = 121,
	cmd2dPolyClip = 122,
	cmd2dCameraMove = 130,
	cmd2dWindowBox = 131,
	cmdUnknown = 1000
};
//���ͼ�ͻ����Ľ�����ʹ������ģʽ����CView�������м��̡�����¼��Ĵ���
class UIEventListener : public CGObject
{
public:
	UIEventListener(CView* pview = nullptr) :mStep(0), mView(pview) { }
	~UIEventListener() = default;
	//�������ͣ�����������������д
	virtual int GetType() = 0;
	//ȡ�������ESC���жϵ�ǰ�����ִ�У�������������������д
	virtual int Cancel() = 0;
	//����¼�����ֻ����Ĭ��ʵ�֣������������Ҫ��д��Ӧ�ĺ�����
	virtual int OnLButtonUp(UINT nFlags, CPoint point) { return 0; }
	virtual int OnLButtonDown(UINT nFlags, CPoint point) { return 0; }
	virtual int OnLButtonDblClk(UINT nFlags, CPoint point) { return 0; }
	virtual int OnMouseMove(UINT nFlags, CPoint point) { return 0; }
	virtual int OnMouseWheel(UINT nFlags, short zDelta, CPoint point) { return 0; }
	virtual int OnMButtonUp(UINT nFlags, CPoint point) { return 0; }
	virtual int OnMButtonDown(UINT nFlags, CPoint point) { return 0; }
	virtual int OnMButtonDblClk(UINT nFlags, CPoint point) { return 0; }
	virtual int OnRButtonUp(UINT nFlags, CPoint point) { return 0; }
	virtual int OnRButtonDown(UINT nFlags, CPoint point) { return 0; }
	virtual int OnRButtonDblClk(UINT nFlags, CPoint point) { return 0; }
	//�����¼�����ֻ����Ĭ��ʵ�֣������������Ҫ��д��Ӧ�ĺ�����
	virtual int OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) { return 0; }
	virtual int OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) { return 0; }
	virtual int OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) { return 0; }
	virtual int OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) { return 0; }
	virtual int OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) { return 0; }
protected:
	int mStep = 0; // �����������
	CView* mView = nullptr; // �����¼��Ĵ���
};
#endif //_UIEventListener_H_INCLUDED
