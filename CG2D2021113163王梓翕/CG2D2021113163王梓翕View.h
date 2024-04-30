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
//3-2
#include "vector2.h" //坐标转换用到
class CG2DCamera; //类声明中只用到指针，使用前置声明。在cpp文件中包含相应头文件
class CG2DRenderable; //类声明中只用到指针，使用前置声明。在cpp文件中包含相应头文件
#include "AABBox2.h"

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

// 实验3-2
public:
	//画笔属性
	COLORREF PenColor() const;
	int PenWidth() const;
	int PenStyle() const;
	//画刷属性
	COLORREF BrushColor() const;
	int BrushStyle() const;
	int HatchStyle() const;
	//绘制算法（重写的基类的虚函数）
	int LineAlgorithm() const;
	int CircleAlgorithm() const;
	int FillAlgorithm() const;
	int SeedAlgorithm() const;
	//点阵区域的边界颜色
	COLORREF BoundColor() const;
	//点阵区域的内点颜色
	COLORREF FloodColor() const;
	//显示提示信息
	void Prompt(const CString& str);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDrawLinesegment();
	afx_msg void OnDrawPolyline();
	afx_msg void OnUpdateDrawLinesegment(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawPolyline(CCmdUI* pCmdUI);
public:
	//图形对象添加到场景
	bool addRenderable(CG2DRenderable* r);
	bool delReaderable(CG2DRenderable* r);
	//根据视口坐标获取对应场景坐标（二维）-调用文档类默认相机的转换函数
	Vec2d ViewPorttoWorld(const Vec2i& p);
	Vec2i WorldtoViewPort(const Vec2d& p);
	afx_msg void OnDrawPolygon();
	afx_msg void OnUpdateDrawPolygon(CCmdUI* pCmdUI);
	afx_msg void OnDrawCircle();
	afx_msg void OnUpdateDrawCircle(CCmdUI* pCmdUI);
public:
	//更新选择（如果拾取对象成功，则替换选择集，返回拾取的对象）
	CG2DRenderable* UpdatePicked(const Vec2d& p, double radius); //点选
	CG2DRenderable* UpdatePicked(const ABox2d& box, bool inner = true); //框选（包含才选中？）
	//添加选择（如果拾取对象成功，则加入选择集，返回拾取的对象）
	CG2DRenderable* AppendPicked(const Vec2d& p, double radius); //点选
	CG2DRenderable* AppendPicked(const ABox2d& box, bool inner = true); //框选（包含才选中？）
	afx_msg void OnPickOne();
	afx_msg void OnUpdatePickOne(CCmdUI* pCmdUI);
	afx_msg void OnPickBox();
	afx_msg void OnUpdatePickBox(CCmdUI* pCmdUI);
	afx_msg void OnTranslateMove();
	afx_msg void OnUpdateTranslateMove(CCmdUI* pCmdUI);
	afx_msg void OnTranslateLeft();
	afx_msg void OnTranslateRight();
	afx_msg void OnTranslateUp();
	afx_msg void OnTranslateDown();
	afx_msg void OnTranslateZoomIn();
	afx_msg void OnTranslateZoomOut();
	afx_msg void OnTranslateSymX();
	afx_msg void OnTranslateSymY();
	afx_msg void OnTranslateSymO();
	afx_msg void OnTranslateSymXy();
	afx_msg void OnTranslateSymXny();
	afx_msg void OnTranslateMisknipX();
	afx_msg void OnTranslateMisknipY();
	afx_msg void OnTranslateMisknipXy();
	afx_msg void OnTranslateRotate();
	afx_msg void OnUpdateTranslateRotate(CCmdUI* pCmdUI);
};

#ifndef _DEBUG  // CG2D2021113163王梓翕View.cpp 中的调试版本
inline CCG2D2021113163王梓翕Doc* CCG2D2021113163王梓翕View::GetDocument() const
   { return reinterpret_cast<CCG2D2021113163王梓翕Doc*>(m_pDocument); }
#endif

