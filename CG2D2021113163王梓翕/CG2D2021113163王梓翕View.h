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

// CG2D2021113163王梓翕View.h: CCG2D2021113163王梓翕View 类的接口
//

#pragma once
#include "CG2DRenderContext.h"
#include "UIEventListener.h" //命令模式下键盘鼠标交互的用到的基类

class CCG2D2021113163王梓翕View : public CView, public CG2DRenderContext
{
protected:
	UIEventListener* mCommand = nullptr; //交互命令

protected: // 仅从序列化创建
	CCG2D2021113163王梓翕View() noexcept;
	DECLARE_DYNCREATE(CCG2D2021113163王梓翕View)

// 特性
public:
	CCG2D2021113163王梓翕Doc* GetDocument() const;

// 操作
public:
	virtual void EraseBkgnd(); //使用背景色清除客户区背景
	virtual HWND GetHWnd() const; //获取当前客户区的窗口句柄，可用于获取客户区DC
	virtual void Ready(bool erasebkgnd = true); //每一次批量绘制前调用
	virtual void Finish();//每一次批量绘制后调用（显示）

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CCG2D2021113163王梓翕View();
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
	afx_msg void OnDrawCDC();
	afx_msg void OnDrawPoint();
	afx_msg void OnAlgorithmLine();
	afx_msg void OnAlgorithmCircle();
	afx_msg void OnAlgorithmFill();
	afx_msg void OnAlgorithmTiming();

// 绘制客户区的宽度、高度（重写基类虚函数）
public:
	virtual void GetClientWidthHeight(int& w, int& h);
	//使用相机，在指定视口中绘制
	virtual void Ready(CG2DCamera*); //每一次批量绘制前调用。生成填充视口背景，需要重新绘制图形。
	virtual void Finish(CG2DCamera*); //每一次批量绘制前调用
};

#ifndef _DEBUG  // CG2D2021113163王梓翕View.cpp 中的调试版本
inline CCG2D2021113163王梓翕Doc* CCG2D2021113163王梓翕View::GetDocument() const
   { return reinterpret_cast<CCG2D2021113163王梓翕Doc*>(m_pDocument); }
#endif

