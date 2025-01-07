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

// MainFrm.cpp: CMainFrame ���ʵ��
//

#include "pch.h"
#include "framework.h"
#include "CG2D2021xxxxxx����.h"

#include "MainFrm.h"
#include "CSceneTreeView.h"
#include "CG2D2021xxxxxx����View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CMainFrame ����/����

CMainFrame::CMainFrame() noexcept
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// ���� Visual Studio 2005 ��ʽͣ��������Ϊ
	CDockingManager::SetDockingMode(DT_SMART);
	// ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// �������ڻ��������û�����Ԫ�ص��Ӿ�������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	// �������������
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CSceneTreeView), CSize(100, 100), pContext) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CCG2D2021xxxxxx����View), CSize(100, 100), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}

	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������

//��������
COLORREF CMainFrame::PenColor() const
{
	CMFCRibbonColorButton* pPenColor =
		(CMFCRibbonColorButton*)m_wndRibbonBar.FindByID(ID_PEN_COLOR);
	if (pPenColor)
		return pPenColor->GetColor();
	return RGB(0, 0, 0);
}
int CMainFrame::PenWidth() const
{
	CMFCRibbonEdit* pPenWidth = (CMFCRibbonEdit*)m_wndRibbonBar.FindByID(ID_PEN_WIDTH);
	if (pPenWidth)
		return _ttoi(pPenWidth->GetEditText());
	return 1;
}
int CMainFrame::PenStyle() const
{
	CMFCRibbonComboBox* pPenStyle = (CMFCRibbonComboBox*)m_wndRibbonBar.FindByID(ID_PEN_STYLE);
	if (pPenStyle)
		return pPenStyle->GetCurSel();
	return 0;
}
//��ˢ����
COLORREF CMainFrame::BrushColor() const
{
	CMFCRibbonColorButton* pBrushColor =
		(CMFCRibbonColorButton*)m_wndRibbonBar.FindByID(ID_BRUSH_COLOR);
	if (pBrushColor)
		return pBrushColor->GetColor();
	return RGB(255, 255, 255);
}
int CMainFrame::BrushStyle() const
{
	CMFCRibbonComboBox* pBrushStyle = (CMFCRibbonComboBox*)m_wndRibbonBar.FindByID(ID_BRUSH_STYLE);
	if (pBrushStyle)
		return pBrushStyle->GetCurSel();
	return -1;
}
int CMainFrame::HatchStyle() const
{
	CMFCRibbonComboBox* pHatchStyle = (CMFCRibbonComboBox*)m_wndRibbonBar.FindByID(ID_BRUSH_HATCH);
	if (pHatchStyle)
		return pHatchStyle->GetCurSel();
	return -1;
}
//�����㷨
int CMainFrame::LineAlgorithm() const
{
	CMFCRibbonComboBox* pLineAlgorithm =
		(CMFCRibbonComboBox*)m_wndRibbonBar.FindByID(ID_ALGOR_LINE);
	if (pLineAlgorithm)
		return pLineAlgorithm->GetCurSel();
	return 0;
}
int CMainFrame::CircleAlgorithm() const
{
	CMFCRibbonComboBox* pCircleAlgorithm =
		(CMFCRibbonComboBox*)m_wndRibbonBar.FindByID(ID_ALGOR_CIRCLE);
	if (pCircleAlgorithm)
		return pCircleAlgorithm->GetCurSel();
	return 0;
}
int CMainFrame::FillAlgorithm() const
{
	CMFCRibbonComboBox* pFillAlgorithm =
		(CMFCRibbonComboBox*)m_wndRibbonBar.FindByID(ID_ALGOR_POLYGON);
	if (pFillAlgorithm)
		return pFillAlgorithm->GetCurSel();
	return 0;
}
int CMainFrame::SeedAlgorithm() const
{
	CMFCRibbonComboBox* pFillAlgorithm =
		(CMFCRibbonComboBox*)m_wndRibbonBar.FindByID(ID_ALGOR_SEEDFILL);
	if (pFillAlgorithm)
		return pFillAlgorithm->GetCurSel();
	return 0;
}
//��������ı߽���ɫ
COLORREF CMainFrame::BoundColor() const
{
	CMFCRibbonColorButton* pBoundColor =
		(CMFCRibbonColorButton*)m_wndRibbonBar.FindByID(ID_BOUND_COLOR);
	if (pBoundColor)
		return pBoundColor->GetColor();
	return RGB(0, 0, 0);
}
//����������ڵ���ɫ
COLORREF CMainFrame::FloodColor() const
{
	CMFCRibbonColorButton* pBackColor =
		(CMFCRibbonColorButton*)m_wndRibbonBar.FindByID(ID_INNER_COLOR);
	if (pBackColor)
		return pBackColor->GetColor();
	return RGB(255, 255, 255);
}
//��״̬������ʾ��ʾ��Ϣ
void CMainFrame::ShowPrompt(const CString& str)
{
	m_wndStatusBar.GetElement(0)->SetText(str);
	m_wndStatusBar.Invalidate();
	m_wndStatusBar.UpdateWindow();
}
//��״̬������ʾ�ӿ����ꡢ��������
void CMainFrame::ShowCoordOnStatusBar(const CString& str)
{
	m_wndStatusBar.GetExElement(0)->SetText(str);
	m_wndStatusBar.Invalidate();
	m_wndStatusBar.UpdateWindow();
}
