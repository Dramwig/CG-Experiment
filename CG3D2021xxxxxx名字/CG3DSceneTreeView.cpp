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

// CG3DSceneTreeView.cpp: CG3DSceneTreeView 类的实现
//

#include "pch.h"
#include "framework.h"
#include "CG3D2021xxxxxx名字.h"

#include "CG3D2021xxxxxx名字Doc.h"
#include "CG3DSceneTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CG3DSceneTreeView

IMPLEMENT_DYNCREATE(CG3DSceneTreeView, CTreeView)

BEGIN_MESSAGE_MAP(CG3DSceneTreeView, CTreeView)
END_MESSAGE_MAP()


// CG3DSceneTreeView 构造/析构

CG3DSceneTreeView::CG3DSceneTreeView()
{
	// TODO: 在此处添加构造代码
}

CG3DSceneTreeView::~CG3DSceneTreeView()
{
}

BOOL CG3DSceneTreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式

	return CTreeView::PreCreateWindow(cs);
}

void CG3DSceneTreeView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: 调用 GetTreeCtrl() 直接访问 TreeView 的树控件，
	//  从而可以用项填充 TreeView。
}


// CG3DSceneTreeView 诊断

#ifdef _DEBUG
void CG3DSceneTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CG3DSceneTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CCG3D2021xxxxxx名字Doc* CG3DSceneTreeView::GetDocument() // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCG3D2021xxxxxx名字Doc)));
	return (CCG3D2021xxxxxx名字Doc*)m_pDocument;
}
#endif //_DEBUG


// CG3DSceneTreeView 消息处理程序
