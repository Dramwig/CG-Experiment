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

// CG3DSceneTreeView.h: CG3DSceneTreeView 类的接口
//


#pragma once

class CCG3D2021xxxxxx名字Doc;

class CG3DSceneTreeView : public CTreeView
{
protected: // 仅从序列化创建
	CG3DSceneTreeView();
	DECLARE_DYNCREATE(CG3DSceneTreeView)

// 特性
public:
	CCG3D2021xxxxxx名字Doc* GetDocument();

// 操作
public:

// 重写
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CG3DSceneTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // CG3DSceneTreeView.cpp 中的调试版本
inline CCG3D2021xxxxxx名字Doc* CG3DSceneTreeView::GetDocument()
   { return reinterpret_cast<CCG3D2021xxxxxx名字Doc*>(m_pDocument); }
#endif

