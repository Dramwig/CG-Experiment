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

// CSceneTreeView.h: CSceneTreeView 类的接口
//


#pragma once

class CCG2D2021xxxxxx名字Doc;

class CSceneTreeView : public CTreeView
{
protected: // 仅从序列化创建
	CSceneTreeView();
	DECLARE_DYNCREATE(CSceneTreeView)

// 特性
public:
	CCG2D2021xxxxxx名字Doc* GetDocument();

// 操作
public:

// 重写
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CSceneTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	afx_msg void OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
public:
	void UpdateSceneTree(); //根据文档中的场景更新场景树的显示
};

#ifndef _DEBUG  // CSceneTreeView.cpp 中的调试版本
inline CCG2D2021xxxxxx名字Doc* CSceneTreeView::GetDocument()
   { return reinterpret_cast<CCG2D2021xxxxxx名字Doc*>(m_pDocument); }
#endif

