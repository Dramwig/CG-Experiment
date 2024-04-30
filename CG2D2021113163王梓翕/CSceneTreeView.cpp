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

// CSceneTreeView.cpp: CSceneTreeView 类的实现
//

#include "pch.h"
#include "framework.h"
#include "CG2D2021113163王梓翕.h"

#include "CG2D2021113163王梓翕Doc.h"
#include "CSceneTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSceneTreeView

IMPLEMENT_DYNCREATE(CSceneTreeView, CTreeView)

BEGIN_MESSAGE_MAP(CSceneTreeView, CTreeView)
END_MESSAGE_MAP()


// CSceneTreeView 构造/析构

CSceneTreeView::CSceneTreeView()
{
	// TODO: 在此处添加构造代码
}

CSceneTreeView::~CSceneTreeView()
{
}

BOOL CSceneTreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式

	return CTreeView::PreCreateWindow(cs);
}

void CSceneTreeView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: 调用 GetTreeCtrl() 直接访问 TreeView 的树控件，
	//  从而可以用项填充 TreeView。
}


// CSceneTreeView 诊断

#ifdef _DEBUG
void CSceneTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CSceneTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CCG2D2021113163王梓翕Doc* CSceneTreeView::GetDocument() // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCG2D2021113163王梓翕Doc)));
	return (CCG2D2021113163王梓翕Doc*)m_pDocument;
}
#endif //_DEBUG


// CSceneTreeView 消息处理程序
