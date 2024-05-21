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

// CG3D2021113163王梓翕View.cpp: CCG3D2021113163王梓翕View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CG3D2021113163王梓翕.h"
#endif

#include "CG3D2021113163王梓翕Doc.h"
#include "CG3D2021113163王梓翕View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCG3D2021113163王梓翕View

IMPLEMENT_DYNCREATE(CCG3D2021113163王梓翕View, CView)

BEGIN_MESSAGE_MAP(CCG3D2021113163王梓翕View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CCG3D2021113163王梓翕View 构造/析构

CCG3D2021113163王梓翕View::CCG3D2021113163王梓翕View() noexcept
{
	// TODO: 在此处添加构造代码

}

CCG3D2021113163王梓翕View::~CCG3D2021113163王梓翕View()
{
}

BOOL CCG3D2021113163王梓翕View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 
	//  CREATESTRUCT cs 来修改窗口类或样式 
	cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS; //非常重要 
	return CView::PreCreateWindow(cs);
}

// CCG3D2021113163王梓翕View 绘图

void CCG3D2021113163王梓翕View::OnDraw(CDC* /*pDC*/)
{
	CCG3D2021113163王梓翕Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码 
	pDoc->RenderScene(this);
}

void CCG3D2021113163王梓翕View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCG3D2021113163王梓翕View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCG3D2021113163王梓翕View 诊断

#ifdef _DEBUG
void CCG3D2021113163王梓翕View::AssertValid() const
{
	CView::AssertValid();
}

void CCG3D2021113163王梓翕View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCG3D2021113163王梓翕Doc* CCG3D2021113163王梓翕View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCG3D2021113163王梓翕Doc)));
	return (CCG3D2021113163王梓翕Doc*)m_pDocument;
}
#endif //_DEBUG


// CCG3D2021113163王梓翕View 消息处理程序
//绘制客户区的宽度、高度（必须在派生类中实现） 
void CCG3D2021113163王梓翕View::GetClientWidthHeight(int& w, int& h)
{
	CRect rc;
	GetClientRect(&rc);
	w = rc.Width();
	h = rc.Height();
}

bool CCG3D2021113163王梓翕View::SetupRenderContext()
{
	if (!SetupPixelFormat())
		return false;

	mHGLRC = ::wglCreateContext(mHDC);
	::wglMakeCurrent(mHDC, mHGLRC);

	//根据需要设置参数; 
	glEnable(GL_DEPTH_TEST); //启用深度测试（消隐） 
	glEnable(GL_CULL_FACE); //启用剔除（背向面剔除） 
	glFrontFace(GL_CCW); //面的正方向：逆时针方向顶点序列。很重要，会影响到面的可见性 
	glDrawBuffer(GL_BACK); //绘制到后缓存（需交换缓存） 

	return mHGLRC != 0;
}

void CCG3D2021113163王梓翕View::Ready(CG3DCamera*)
{
	wglMakeCurrent(mHDC, mHGLRC);

	GLclampf r, g, b;
	r = (GLclampf)GetRValue(mBkgndColor) / 255.0;
	g = (GLclampf)GetGValue(mBkgndColor) / 255.0;
	b = (GLclampf)GetBValue(mBkgndColor) / 255.0;
	//设置背景色和最远深度，并清除颜色缓存和深度缓存 
	glClearColor(r, g, b, 0.0f);
	glClearDepth(mBkgndDepth);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void CCG3D2021113163王梓翕View::Finish(CG3DCamera*)
{
	glFlush();
	SwapBuffers(mHDC);
	wglMakeCurrent(mHDC, NULL);
}

bool CCG3D2021113163王梓翕View::SetupPixelFormat(void)
{
	mHWnd = GetSafeHwnd();
	mHDC = GetDC()->GetSafeHdc();
	if (!mHWnd || !mHDC)
		return false;

	PIXELFORMATDESCRIPTOR pfd = {
	 sizeof(PIXELFORMATDESCRIPTOR),    // pfd结构的大小  
	 1,                                // 版本号  
	 PFD_DRAW_TO_WINDOW |              // 支持在窗口中绘图  
	 PFD_SUPPORT_OPENGL |              // 支持 OpenGL  
	 PFD_DOUBLEBUFFER,                 // 双缓存模式  
	 PFD_TYPE_RGBA,                    // RGBA 颜色模式  
	 24,                               // 24 位颜色深度  
	 0, 0, 0, 0, 0, 0,                 // 忽略颜色位  
	 0,                                // 没有非透明度缓存  
	 0,                                // 忽略移位位  
	 0,                                // 无累加缓存  
	 0, 0, 0, 0,                       // 忽略累加位  
	 32,                               // 32 位深度缓存      
	 0,                                // 无模板缓存  
	 0,                                // 无辅助缓存 
	PFD_MAIN_PLANE,               // 主层  
	 0,                                // 保留  
	0, 0, 0                            // 忽略层,可见性和损毁掩模  
	};
int iPixelFormat;
// 为设备描述表得到最匹配的像素格式  
if ((iPixelFormat = ChoosePixelFormat(mHDC, &pfd)) == 0)
{
	AfxMessageBox(_T("ChoosePixelFormat Failed"), NULL, MB_OK);
	return false;
}

// 设置最匹配的像素格式为当前的像素格式  
if (SetPixelFormat(mHDC, iPixelFormat, &pfd) == FALSE)
{
	AfxMessageBox(_T("SetPixelFormat Failed"), NULL, MB_OK);
	return false;
}
if (pfd.dwFlags & PFD_NEED_PALETTE)
{
	//设置逻辑调色板 
	struct
	{
		WORD Version;
		WORD NumberOfEntries;
		PALETTEENTRY aEntries[256];
	} logicalPalette = { 0x300, 256 };
	BYTE reds[] = { 0, 36, 72, 109, 145, 182, 218, 255 };
	BYTE greens[] = { 0, 36, 72, 109, 145, 182, 218, 255 };
	BYTE blues[] = { 0, 85, 170, 255 };

	for (int colorNum = 0; colorNum < 256; ++colorNum)
	{
		logicalPalette.aEntries[colorNum].peRed =
			reds[colorNum & 0x07];
		logicalPalette.aEntries[colorNum].peGreen =
			greens[(colorNum >> 0x03) & 0x07];
		logicalPalette.aEntries[colorNum].peBlue =
			blues[(colorNum >> 0x06) & 0x03];
		logicalPalette.aEntries[colorNum].peFlags = 0;
	}
	mPalette = CreatePalette((LOGPALETTE*)&logicalPalette);
}
return true;
}

int CCG3D2021113163王梓翕View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码 
	if (!SetupRenderContext())
		return -1;
	return 0;
}


void CCG3D2021113163王梓翕View::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码 
	if (mPalette)
	{
		DeleteObject(mPalette);
		mPalette = 0;
	}
	::wglMakeCurrent(NULL, NULL);
	::wglDeleteContext(mHGLRC);
}


void CCG3D2021113163王梓翕View::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}
