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

// CSceneTreeView.h: CSceneTreeView ��Ľӿ�
//


#pragma once

class CCG2D2021xxxxxx����Doc;

class CSceneTreeView : public CTreeView
{
protected: // �������л�����
	CSceneTreeView();
	DECLARE_DYNCREATE(CSceneTreeView)

// ����
public:
	CCG2D2021xxxxxx����Doc* GetDocument();

// ����
public:

// ��д
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CSceneTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	afx_msg void OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
public:
	void UpdateSceneTree(); //�����ĵ��еĳ������³���������ʾ
};

#ifndef _DEBUG  // CSceneTreeView.cpp �еĵ��԰汾
inline CCG2D2021xxxxxx����Doc* CSceneTreeView::GetDocument()
   { return reinterpret_cast<CCG2D2021xxxxxx����Doc*>(m_pDocument); }
#endif

