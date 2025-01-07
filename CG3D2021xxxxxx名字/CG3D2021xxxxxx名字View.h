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

// CG3D2021xxxxxx名字View.h: CCG3D2021xxxxxx名字View 类的接口
//

#pragma once
#include "CG3DRenderContext.h"
#include "CGLight.h"

class CCG3D2021xxxxxx名字View : public CView, public CG3DRenderContext
{
protected: // 仅从序列化创建
	CCG3D2021xxxxxx名字View() noexcept;
	DECLARE_DYNCREATE(CCG3D2021xxxxxx名字View)

// 特性
public:
	CCG3D2021xxxxxx名字Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CCG3D2021xxxxxx名字View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()


public:
	//重写基类的虚函数 
	virtual void GetClientWidthHeight(int& w, int& h) override;
	virtual bool SetupRenderContext() override;
	virtual void Ready(CG3DCamera*) override;
	virtual void Finish(CG3DCamera*) override;
protected:
	virtual bool SetupPixelFormat(void) override;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);

public:
	//画笔属性 
	COLORREF PenColor() const;
	int PenWidth() const;
	int PenStyle() const;
	int PenFill() const;
	int Rotate() const;
	//显示提示信息 
	void Prompt(const CString& str);
	afx_msg void OnTriangularfan();
	afx_msg void OnClosedfoldedline();
	afx_msg void OnLinesegment();
	afx_msg void OnFoldedline();
	afx_msg void OnPolygon();
	afx_msg void OnTriangle();
	afx_msg void OnQuad();
	afx_msg void OnTriangularstrip();
	afx_msg void OnQuadstrip();
	afx_msg void OnRemoveAll();
	afx_msg void OnSphere();
public://实验7
	COLORREF MaterialColor() const;
	int MaterialStyle() const;
	afx_msg void OnUpdateMaterial();
	afx_msg void OnCustomMaterials();
	afx_msg void OnCustompointlightsources();
	afx_msg void OnCustomlinelightsource();
	afx_msg void OnCustomSpotlight();
	CGLight* CustomLight();
	afx_msg void OnNtnTimer1();
	afx_msg void OnUpdateNtnTimer1(CCmdUI* pCmdUI);
protected:
	UINT_PTR mAnimateTimer = 0;
	//动画定时器
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // CG3D2021xxxxxx名字View.cpp 中的调试版本
inline CCG3D2021xxxxxx名字Doc* CCG3D2021xxxxxx名字View::GetDocument() const
   { return reinterpret_cast<CCG3D2021xxxxxx名字Doc*>(m_pDocument); }
#endif

