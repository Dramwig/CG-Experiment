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

// MainFrm.h: CMainFrame ��Ľӿ�
//

#pragma once
class CCG2D2021xxxxxx����View;

class CMainFrame : public CFrameWndEx
{
	
protected: // �������л�����
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// ����
protected:
	CSplitterWnd m_wndSplitter;
public:

// ����
public:

// ��д
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
	CCG2D2021xxxxxx����View* GetRightPane();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

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
public:
	void ShowPrompt(const CString& str);
	void ShowCoordOnStatusBar(const CString& str);
};


