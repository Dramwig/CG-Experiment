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

// CG3DSceneTreeView.cpp: CG3DSceneTreeView ���ʵ��
//

#include "pch.h"
#include "framework.h"
#include "CG3D2021xxxxxx����.h"

#include "CG3D2021xxxxxx����Doc.h"
#include "CG3DSceneTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CG3DSceneTreeView

IMPLEMENT_DYNCREATE(CG3DSceneTreeView, CTreeView)

BEGIN_MESSAGE_MAP(CG3DSceneTreeView, CTreeView)
END_MESSAGE_MAP()


// CG3DSceneTreeView ����/����

CG3DSceneTreeView::CG3DSceneTreeView()
{
	// TODO: �ڴ˴���ӹ������
}

CG3DSceneTreeView::~CG3DSceneTreeView()
{
}

BOOL CG3DSceneTreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CTreeView::PreCreateWindow(cs);
}

void CG3DSceneTreeView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: ���� GetTreeCtrl() ֱ�ӷ��� TreeView �����ؼ���
	//  �Ӷ������������ TreeView��
}


// CG3DSceneTreeView ���

#ifdef _DEBUG
void CG3DSceneTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CG3DSceneTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CCG3D2021xxxxxx����Doc* CG3DSceneTreeView::GetDocument() // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCG3D2021xxxxxx����Doc)));
	return (CCG3D2021xxxxxx����Doc*)m_pDocument;
}
#endif //_DEBUG


// CG3DSceneTreeView ��Ϣ�������
