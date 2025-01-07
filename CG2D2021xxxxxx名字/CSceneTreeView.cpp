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
#include "CG2D2021xxxxxx名字.h"

#include "CG2D2021xxxxxx名字Doc.h"
#include "CSceneTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSceneTreeView

IMPLEMENT_DYNCREATE(CSceneTreeView, CTreeView)

BEGIN_MESSAGE_MAP(CSceneTreeView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CSceneTreeView::OnTvnSelchanged)
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

CCG2D2021xxxxxx名字Doc* CSceneTreeView::GetDocument() // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCG2D2021xxxxxx名字Doc)));
	return (CCG2D2021xxxxxx名字Doc*)m_pDocument;
}
#endif //_DEBUG


// CSceneTreeView 消息处理程序


void CSceneTreeView::OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (!pDoc->scene())
		return;
	CTreeCtrl& treeCtrl = GetTreeCtrl();
	HTREEITEM hItem = treeCtrl.GetSelectedItem();
	if (hItem != NULL) {
		HTREEITEM parent = treeCtrl.GetNextItem(hItem, TVGN_PARENT);
		if (parent != nullptr)
		{
			CString strText = treeCtrl.GetItemText(parent);
			if (strText == _T("图形对象"))
			{
				strText = treeCtrl.GetItemText(hItem);
				//实现单选（每次只选一个），先清空选择集
				bool ret = pDoc->scene()->UnselectAll();
				//有清除标记或被选中，更新显示
				if (pDoc->scene()->Selected(strText) != nullptr || ret == true)
				{
					pDoc->UpdateAllViews(nullptr);
				}
			}
		}
	}
	*pResult = 0;
}

void CSceneTreeView::UpdateSceneTree() //根据文档中的场景更新场景树的显示
{
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (!pDoc->scene())
		return;
	CTreeCtrl& treeCtrl = GetTreeCtrl();
	treeCtrl.DeleteAllItems();
	HTREEITEM hRoot = treeCtrl.InsertItem(_T("图形场景"), 0, 0);
	treeCtrl.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);
	HTREEITEM hClass = treeCtrl.InsertItem(_T("图形对象"), 1, 1, hRoot);
	CG2DRenderable* pr = nullptr;
	unsigned i = 0;
	while (pr = pDoc->scene()->getRenderable(i))
	{
		//Name是从CGObject继承，可以使用Name()="...."进行对象命名
		HTREEITEM hitem = treeCtrl.InsertItem(pr->Name(), 3, 3, hClass);
		if (pr->status() == CG2DRenderable::sSelected)
		{
		}
		i++;
	}
	treeCtrl.Expand(hRoot, TVE_EXPAND);
	treeCtrl.Expand(hClass, TVE_EXPAND);
}


void CSceneTreeView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: 在此添加专用代码和/或调用基类
	UpdateSceneTree();
}
