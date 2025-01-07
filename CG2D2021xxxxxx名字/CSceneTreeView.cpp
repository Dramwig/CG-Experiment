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

// CSceneTreeView.cpp: CSceneTreeView ���ʵ��
//

#include "pch.h"
#include "framework.h"
#include "CG2D2021xxxxxx����.h"

#include "CG2D2021xxxxxx����Doc.h"
#include "CSceneTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSceneTreeView

IMPLEMENT_DYNCREATE(CSceneTreeView, CTreeView)

BEGIN_MESSAGE_MAP(CSceneTreeView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CSceneTreeView::OnTvnSelchanged)
END_MESSAGE_MAP()


// CSceneTreeView ����/����

CSceneTreeView::CSceneTreeView()
{
	// TODO: �ڴ˴���ӹ������
}

CSceneTreeView::~CSceneTreeView()
{
}

BOOL CSceneTreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CTreeView::PreCreateWindow(cs);
}

void CSceneTreeView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: ���� GetTreeCtrl() ֱ�ӷ��� TreeView �����ؼ���
	//  �Ӷ������������ TreeView��
}


// CSceneTreeView ���

#ifdef _DEBUG
void CSceneTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CSceneTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CCG2D2021xxxxxx����Doc* CSceneTreeView::GetDocument() // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCG2D2021xxxxxx����Doc)));
	return (CCG2D2021xxxxxx����Doc*)m_pDocument;
}
#endif //_DEBUG


// CSceneTreeView ��Ϣ�������


void CSceneTreeView::OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
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
			if (strText == _T("ͼ�ζ���"))
			{
				strText = treeCtrl.GetItemText(hItem);
				//ʵ�ֵ�ѡ��ÿ��ֻѡһ�����������ѡ��
				bool ret = pDoc->scene()->UnselectAll();
				//�������ǻ�ѡ�У�������ʾ
				if (pDoc->scene()->Selected(strText) != nullptr || ret == true)
				{
					pDoc->UpdateAllViews(nullptr);
				}
			}
		}
	}
	*pResult = 0;
}

void CSceneTreeView::UpdateSceneTree() //�����ĵ��еĳ������³���������ʾ
{
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (!pDoc->scene())
		return;
	CTreeCtrl& treeCtrl = GetTreeCtrl();
	treeCtrl.DeleteAllItems();
	HTREEITEM hRoot = treeCtrl.InsertItem(_T("ͼ�γ���"), 0, 0);
	treeCtrl.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);
	HTREEITEM hClass = treeCtrl.InsertItem(_T("ͼ�ζ���"), 1, 1, hRoot);
	CG2DRenderable* pr = nullptr;
	unsigned i = 0;
	while (pr = pDoc->scene()->getRenderable(i))
	{
		//Name�Ǵ�CGObject�̳У�����ʹ��Name()="...."���ж�������
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
	// TODO: �ڴ����ר�ô����/����û���
	UpdateSceneTree();
}
