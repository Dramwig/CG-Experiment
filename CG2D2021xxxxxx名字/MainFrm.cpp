// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "CG2D2021xxxxxx名字.h"

#include "MainFrm.h"
#include "CSceneTreeView.h"
#include "CG2D2021xxxxxx名字View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
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
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// 设置用于绘制所有用户界面元素的视觉管理器
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	// 创建拆分器窗口
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CSceneTreeView), CSize(100, 100), pContext) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CCG2D2021xxxxxx名字View), CSize(100, 100), pContext))
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
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

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


// CMainFrame 消息处理程序

//画笔属性
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
//画刷属性
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
//绘制算法
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
//点阵区域的边界颜色
COLORREF CMainFrame::BoundColor() const
{
	CMFCRibbonColorButton* pBoundColor =
		(CMFCRibbonColorButton*)m_wndRibbonBar.FindByID(ID_BOUND_COLOR);
	if (pBoundColor)
		return pBoundColor->GetColor();
	return RGB(0, 0, 0);
}
//点阵区域的内点颜色
COLORREF CMainFrame::FloodColor() const
{
	CMFCRibbonColorButton* pBackColor =
		(CMFCRibbonColorButton*)m_wndRibbonBar.FindByID(ID_INNER_COLOR);
	if (pBackColor)
		return pBackColor->GetColor();
	return RGB(255, 255, 255);
}
//在状态栏上显示提示信息
void CMainFrame::ShowPrompt(const CString& str)
{
	m_wndStatusBar.GetElement(0)->SetText(str);
	m_wndStatusBar.Invalidate();
	m_wndStatusBar.UpdateWindow();
}
//在状态栏上显示视口坐标、世界坐标
void CMainFrame::ShowCoordOnStatusBar(const CString& str)
{
	m_wndStatusBar.GetExElement(0)->SetText(str);
	m_wndStatusBar.Invalidate();
	m_wndStatusBar.UpdateWindow();
}
