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

// CG3D2021xxxxxx����View.h: CCG3D2021xxxxxx����View ��Ľӿ�
//

#pragma once
#include "CG3DRenderContext.h"
#include "CGLight.h"

class CCG3D2021xxxxxx����View : public CView, public CG3DRenderContext
{
protected: // �������л�����
	CCG3D2021xxxxxx����View() noexcept;
	DECLARE_DYNCREATE(CCG3D2021xxxxxx����View)

// ����
public:
	CCG3D2021xxxxxx����Doc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CCG3D2021xxxxxx����View();
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
	//��д������麯�� 
	virtual void GetClientWidthHeight(int& w, int& h) override;
	virtual bool SetupRenderContext() override;
	virtual void Ready(CG3DCamera*) override;
	virtual void Finish(CG3DCamera*) override;
protected:
	virtual bool SetupPixelFormat(void) override;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);

public:
	//�������� 
	COLORREF PenColor() const;
	int PenWidth() const;
	int PenStyle() const;
	int PenFill() const;
	int Rotate() const;
	//��ʾ��ʾ��Ϣ 
	void Prompt(const CString& str);
	afx_msg void OnTriangularfan();
	afx_msg void OnClosedfoldedline();
	afx_msg void OnLinesegment();
	afx_msg void OnFoldedline();
	afx_msg void OnPolygon();
	afx_msg void OnTriangle();
	afx_msg void OnQuad();
	afx_msg void OnTriangularstrip();
	afx_msg void OnQuadstrip();
	afx_msg void OnRemoveAll();
	afx_msg void OnSphere();
public://ʵ��7
	COLORREF MaterialColor() const;
	int MaterialStyle() const;
	afx_msg void OnUpdateMaterial();
	afx_msg void OnCustomMaterials();
	afx_msg void OnCustompointlightsources();
	afx_msg void OnCustomlinelightsource();
	afx_msg void OnCustomSpotlight();
	CGLight* CustomLight();
	afx_msg void OnNtnTimer1();
	afx_msg void OnUpdateNtnTimer1(CCmdUI* pCmdUI);
protected:
	UINT_PTR mAnimateTimer = 0;
	//������ʱ��
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // CG3D2021xxxxxx����View.cpp �еĵ��԰汾
inline CCG3D2021xxxxxx����Doc* CCG3D2021xxxxxx����View::GetDocument() const
   { return reinterpret_cast<CCG3D2021xxxxxx����Doc*>(m_pDocument); }
#endif

