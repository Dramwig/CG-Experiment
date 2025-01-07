// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û�����
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο�����
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// CG2D2021xxxxxx����View.h: CCG2D2021xxxxxx����View ��Ľӿ�
//

#pragma once
#include "CG2DRenderContext.h"
#include "UIEventListener.h" //����ģʽ�¼�����꽻�����õ��Ļ���
//3-2
#include "vector2.h" //����ת���õ�
class CG2DCamera; //��������ֻ�õ�ָ�룬ʹ��ǰ����������cpp�ļ��а�����Ӧͷ�ļ�
class CG2DRenderable; //��������ֻ�õ�ָ�룬ʹ��ǰ����������cpp�ļ��а�����Ӧͷ�ļ�
#include "AABBox2.h"

class CCG2D2021xxxxxx����View : public CView, public CG2DRenderContext
{
protected:
	UIEventListener* mCommand = nullptr; //��������

protected: // �������л�����
	CCG2D2021xxxxxx����View() noexcept;
	DECLARE_DYNCREATE(CCG2D2021xxxxxx����View)

// ����
public:
	CCG2D2021xxxxxx����Doc* GetDocument() const;

// ����
public:
	virtual void EraseBkgnd(); //ʹ�ñ���ɫ����ͻ�������
	virtual HWND GetHWnd() const; //��ȡ��ǰ�ͻ����Ĵ��ھ���������ڻ�ȡ�ͻ���DC
	virtual void Ready(bool erasebkgnd = true); //ÿһ����������ǰ����
	virtual void Finish();//ÿһ���������ƺ���ã���ʾ��

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CCG2D2021xxxxxx����View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawCDC();
	afx_msg void OnDrawPoint();
	afx_msg void OnAlgorithmLine();
	afx_msg void OnAlgorithmCircle();
	afx_msg void OnAlgorithmFill();
	afx_msg void OnAlgorithmTiming();

// ���ƿͻ����Ŀ�ȡ��߶ȣ���д�����麯����
public:
	virtual void GetClientWidthHeight(int& w, int& h);
	//ʹ���������ָ���ӿ��л���
	virtual void Ready(CG2DCamera*); //ÿһ����������ǰ���á���������ӿڱ�������Ҫ���»���ͼ�Ρ�
	virtual void Finish(CG2DCamera*); //ÿһ����������ǰ����

// ʵ��3-2
public:
	//��������
	COLORREF PenColor() const;
	int PenWidth() const;
	int PenStyle() const;
	//��ˢ����
	COLORREF BrushColor() const;
	int BrushStyle() const;
	int HatchStyle() const;
	//�����㷨����д�Ļ�����麯����
	int LineAlgorithm() const;
	int CircleAlgorithm() const;
	int FillAlgorithm() const;
	int SeedAlgorithm() const;
	//��������ı߽���ɫ
	COLORREF BoundColor() const;
	//����������ڵ���ɫ
	COLORREF FloodColor() const;
	//��ʾ��ʾ��Ϣ
	void Prompt(const CString& str);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDrawLinesegment();
	afx_msg void OnDrawPolyline();
	afx_msg void OnUpdateDrawLinesegment(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawPolyline(CCmdUI* pCmdUI);
public:
	//ͼ�ζ�����ӵ�����
	bool addRenderable(CG2DRenderable* r);
	bool delReaderable(CG2DRenderable* r);
	//�����ӿ������ȡ��Ӧ�������꣨��ά��-�����ĵ���Ĭ�������ת������
	Vec2d ViewPorttoWorld(const Vec2i& p);
	Vec2d ViewPorttoWorld(const Vec2d& p);
	Vec2i WorldtoViewPort(const Vec2d& p);
	afx_msg void OnDrawPolygon();
	afx_msg void OnUpdateDrawPolygon(CCmdUI* pCmdUI);
	afx_msg void OnDrawCircle();
	afx_msg void OnUpdateDrawCircle(CCmdUI* pCmdUI);
public:
	//����ѡ�����ʰȡ����ɹ������滻ѡ�񼯣�����ʰȡ�Ķ���
	CG2DRenderable* UpdatePicked(const Vec2d& p, double radius); //��ѡ
	CG2DRenderable* UpdatePicked(const ABox2d& box, bool inner = true); //��ѡ��������ѡ�У���
	//���ѡ�����ʰȡ����ɹ��������ѡ�񼯣�����ʰȡ�Ķ���
	CG2DRenderable* AppendPicked(const Vec2d& p, double radius); //��ѡ
	CG2DRenderable* AppendPicked(const ABox2d& box, bool inner = true); //��ѡ��������ѡ�У���
	afx_msg void OnPickOne();
	afx_msg void OnUpdatePickOne(CCmdUI* pCmdUI);
	afx_msg void OnPickBox();
	afx_msg void OnUpdatePickBox(CCmdUI* pCmdUI);
	afx_msg void OnTranslateMove();
	afx_msg void OnUpdateTranslateMove(CCmdUI* pCmdUI);
	afx_msg void OnTranslateLeft();
	afx_msg void OnTranslateRight();
	afx_msg void OnTranslateUp();
	afx_msg void OnTranslateDown();
	afx_msg void OnTranslateZoomIn();
	afx_msg void OnTranslateZoomOut();
	afx_msg void OnTranslateSymX();
	afx_msg void OnTranslateSymY();
	afx_msg void OnTranslateSymO();
	afx_msg void OnTranslateSymXy();
	afx_msg void OnTranslateSymXny();
	afx_msg void OnTranslateMisknipX();
	afx_msg void OnTranslateMisknipY();
	afx_msg void OnTranslateMisknipXy();
	afx_msg void OnTranslateRotate();
	afx_msg void OnUpdateTranslateRotate(CCmdUI* pCmdUI);
	afx_msg void OnCameraLeft();
	afx_msg void OnCameraRight();
	afx_msg void OnCameraUp();
	afx_msg void OnCameraDown();
	afx_msg void OnCounter();
	afx_msg void OnClockwise();
	afx_msg void OnReset();
	afx_msg void OnCameraFar();
	afx_msg void OnCameraClose();
	afx_msg void OnWindowLeftAdd();
	afx_msg void OnWindowLeftDecrease();
	afx_msg void OnWindowRightAdd();
	afx_msg void OnWindowRightDecrease();
	afx_msg void OnWindowBottomAdd();
	afx_msg void OnWindowTopAdd();
	afx_msg void OnWindowTopDecrease();
	afx_msg void OnWindowReduce();
	afx_msg void OnWindowExpand();
	afx_msg void OnWindowBottomDecrease();
	afx_msg void OnViewpointLeftAdd();
	afx_msg void OnViewpointLeftDecrease();
	afx_msg void OnViewpointRightAdd();
	afx_msg void OnViewpointRightDecrease();
	afx_msg void OnViewpointBottomAdd();
	afx_msg void OnViewpointBottomDecrease();
	afx_msg void OnViewpointTopAdd();
	afx_msg void OnViewpointTopDecrease();
	afx_msg void OnViewpointReset();
	afx_msg void OnWindowReset();
	afx_msg void OnCameraMove();
	afx_msg void OnUpdateCameraMove(CCmdUI* pCmdUI);
	afx_msg void OnWindowBox();
	afx_msg void OnUpdateWindowBox(CCmdUI* pCmdUI);
	void CameraMoveOffset(double dx, double dy);
	void CameraWindowSet(double left, double bottom, double right, double top);
	afx_msg void OnWindowOverall();
	afx_msg void OnAspectRatio();
	afx_msg void OnRemoveAll();
protected:
	UINT_PTR mAnimateTimer = 0;
	//������ʱ�� 
public:
	afx_msg void OnBtnTimer1();
	afx_msg void OnUpdateBtnTimer1(CCmdUI* pCmdUI);
	afx_msg void OnBtnFireworks();
};

#ifndef _DEBUG  // CG2D2021xxxxxx����View.cpp �еĵ��԰汾
inline CCG2D2021xxxxxx����Doc* CCG2D2021xxxxxx����View::GetDocument() const
   { return reinterpret_cast<CCG2D2021xxxxxx����Doc*>(m_pDocument); }
#endif

