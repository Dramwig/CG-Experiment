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

// MainFrm.h: CMainFrame 类的接口
//

#pragma once
class CCG2D2021xxxxxx名字View;

class CMainFrame : public CFrameWndEx
{
	
protected: // 仅从序列化创建
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 特性
protected:
	CSplitterWnd m_wndSplitter;
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
	CCG2D2021xxxxxx名字View* GetRightPane();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

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
public:
	void ShowPrompt(const CString& str);
	void ShowCoordOnStatusBar(const CString& str);
};


