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

// CG3DSceneTreeView.h: CG3DSceneTreeView ��Ľӿ�
//


#pragma once

class CCG3D2021xxxxxx����Doc;

class CG3DSceneTreeView : public CTreeView
{
protected: // �������л�����
	CG3DSceneTreeView();
	DECLARE_DYNCREATE(CG3DSceneTreeView)

// ����
public:
	CCG3D2021xxxxxx����Doc* GetDocument();

// ����
public:

// ��д
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CG3DSceneTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // CG3DSceneTreeView.cpp �еĵ��԰汾
inline CCG3D2021xxxxxx����Doc* CG3DSceneTreeView::GetDocument()
   { return reinterpret_cast<CCG3D2021xxxxxx����Doc*>(m_pDocument); }
#endif

