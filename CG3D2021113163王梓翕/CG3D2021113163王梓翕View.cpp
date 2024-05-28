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
#include "MainFrm.h"
#include "CG3DCube.h" 
#include "CG3DClosedFoldedLine.h"
#include "CG3DFoldedLine.h"
#include "CG3DLineSegment.h"
#include "CG3DPolygon.h"
#include "CG3DQuad.h"
#include "CG3DQuadStrip.h"
#include "CG3DTriangle.h"
#include "CG3DTriangularFan.h"
#include "CG3DTriangularStrip.h"
#include "CG3DSphere.h"
#include "CInputDialog1.h"

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
	ON_COMMAND(ID_TriangularFan, &CCG3D2021113163王梓翕View::OnTriangularfan)
	ON_COMMAND(ID_ClosedFoldedLine, &CCG3D2021113163王梓翕View::OnClosedfoldedline)
	ON_COMMAND(ID_LineSegment, &CCG3D2021113163王梓翕View::OnLinesegment)
	ON_COMMAND(ID_FoldedLine, &CCG3D2021113163王梓翕View::OnFoldedline)
	ON_COMMAND(ID_Polygon, &CCG3D2021113163王梓翕View::OnPolygon)
	ON_COMMAND(ID_Triangle, &CCG3D2021113163王梓翕View::OnTriangle)
	ON_COMMAND(ID_Quad, &CCG3D2021113163王梓翕View::OnQuad)
	ON_COMMAND(ID_TriangularStrip, &CCG3D2021113163王梓翕View::OnTriangularstrip)
	ON_COMMAND(ID_QuadStrip, &CCG3D2021113163王梓翕View::OnQuadstrip)
	ON_COMMAND(ID_REMOVE_ALL, &CCG3D2021113163王梓翕View::OnRemoveAll)
	ON_COMMAND(ID_SPHERE, &CCG3D2021113163王梓翕View::OnSphere)
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

//画笔属性 
COLORREF CCG3D2021113163王梓翕View::PenColor() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return RGB(0, 0, 0);
	return pMainWnd->PenColor();
}


int CCG3D2021113163王梓翕View::PenWidth() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 1;
	return pMainWnd->PenWidth();
}


int CCG3D2021113163王梓翕View::PenStyle() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 0;
	return pMainWnd->PenStyle();
}

int CCG3D2021113163王梓翕View::PenFill() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 0;
	return pMainWnd->PenFill();
}

int CCG3D2021113163王梓翕View::Rotate() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 45;
	return pMainWnd->Rotate();
}

//状态栏上显示提示信息 
void CCG3D2021113163王梓翕View::Prompt(const CString& str)
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (pMainWnd != nullptr)
	{
		pMainWnd->ShowPrompt(str);
	}
}

void CCG3D2021113163王梓翕View::OnTriangularfan()
{
	// TODO: 在此添加命令处理程序代码
	CCG3D2021113163王梓翕Doc* pDoc = GetDocument();
	if (pDoc)
	{
		CG3DTriangularFan* cube = new CG3DTriangularFan();
		cube->addPoint(Vec3f(0, 0, 0));
		cube->addPoint(Vec3f(-400, 0, 0));
		cube->addPoint(Vec3f(-300, -300, 0));
		cube->addPoint(Vec3f(0, -400, 0));
		cube->addPoint(Vec3f(300, -300, 0));
		cube->Rotate(Rotate(), 1, 1, 1); //绕直线(0,0,0)(1,1,1)旋转45度便于观察 
		cube->setPenColor(PenColor());
		cube->setPenWidth(PenWidth());
		cube->setPenStyle(PenStyle());
		cube->setPenFill(PenFill());
		pDoc->AddRenderable(cube);
		Invalidate(true);
		UpdateWindow();
		//CString str;
		//str.Format(_T("%d"), Rotate()); // 格式化整数为字符串
		//Prompt(str); // 显示整数
	}
}


void CCG3D2021113163王梓翕View::OnClosedfoldedline()
{
	// TODO: 在此添加命令处理程序代码
	CCG3D2021113163王梓翕Doc* pDoc = GetDocument();
	if (pDoc)
	{
		CG3DClosedFoldedLine* cube = new CG3DClosedFoldedLine();
		cube->addPoint(Vec3f(0, 0, 0));
		cube->addPoint(Vec3f(1000, 0, 0));
		cube->addPoint(Vec3f(0, 1000, 0));
		cube->addPoint(Vec3f(-500, 0, 0));
		cube->addPoint(Vec3f(0, -100, 0));
		cube->Rotate(Rotate(), 1, 1, 1); //绕直线(0,0,0)(1,1,1)旋转45度便于观察 
		cube->setPenColor(PenColor());
		cube->setPenWidth(PenWidth());
		cube->setPenStyle(PenStyle());
		cube->setPenFill(PenFill());
		pDoc->AddRenderable(cube);
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG3D2021113163王梓翕View::OnLinesegment()
{
	// TODO: 在此添加命令处理程序代码
	CCG3D2021113163王梓翕Doc* pDoc = GetDocument();
	if (pDoc)
	{
		CG3DLineSegment* cube = new CG3DLineSegment();
		cube->addPoint(Vec3f(-100, 0, 0));
		cube->addPoint(Vec3f(0, 300, 0));
		cube->addPoint(Vec3f(100, 0, 0));
		cube->addPoint(Vec3f(200, 300, 0));
		cube->addPoint(Vec3f(300, 0, 0));
		cube->addPoint(Vec3f(400, 300, 0));
		cube->Rotate(Rotate(), 1, 1, 1); //绕直线(0,0,0)(1,1,1)旋转45度便于观察 
		cube->setPenColor(PenColor());
		cube->setPenWidth(PenWidth());
		cube->setPenStyle(PenStyle());
		cube->setPenFill(PenFill());
		pDoc->AddRenderable(cube);
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG3D2021113163王梓翕View::OnFoldedline()
{
	// TODO: 在此添加命令处理程序代码
	CCG3D2021113163王梓翕Doc* pDoc = GetDocument();
	if (pDoc)
	{
		CG3DFoldedLine* cube = new CG3DFoldedLine();
		cube->addPoint(Vec3f(0, 0, 0));
		cube->addPoint(Vec3f(1000, 0, 0));
		cube->addPoint(Vec3f(0, 1000, 0));
		cube->addPoint(Vec3f(-500, 0, 0));
		cube->addPoint(Vec3f(0, -100, 0));
		cube->Rotate(Rotate(), 1, 1, 1); //绕直线(0,0,0)(1,1,1)旋转45度便于观察 
		cube->setPenColor(PenColor());
		cube->setPenWidth(PenWidth());
		cube->setPenStyle(PenStyle());
		cube->setPenFill(PenFill());
		pDoc->AddRenderable(cube);
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG3D2021113163王梓翕View::OnPolygon()
{
	// TODO: 在此添加命令处理程序代码
	CCG3D2021113163王梓翕Doc* pDoc = GetDocument();
	if (pDoc)
	{
		CG3DPolygon* cube = new CG3DPolygon();
		cube->addPoint(Vec3f(0, 0, 0));
		cube->addPoint(Vec3f(400, 0, 0));
		cube->addPoint(Vec3f(500, 400, 0));
		cube->addPoint(Vec3f(200, 600, 0));
		cube->addPoint(Vec3f(-100, 400, 0));
		cube->Rotate(Rotate(), 1, 1, 1); //绕直线(0,0,0)(1,1,1)旋转45度便于观察 
		cube->setPenColor(PenColor());
		cube->setPenWidth(PenWidth());
		cube->setPenStyle(PenStyle());
		cube->setPenFill(PenFill());
		pDoc->AddRenderable(cube);
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG3D2021113163王梓翕View::OnTriangle()
{
	// TODO: 在此添加命令处理程序代码
	CCG3D2021113163王梓翕Doc* pDoc = GetDocument();
	if (pDoc)
	{
		CG3DTriangle* cube = new CG3DTriangle();
		cube->addPoint(Vec3f(0, 0, 100));
		cube->addPoint(Vec3f(100, 0, 0));
		cube->addPoint(Vec3f(0, 100, 0));
		cube->addPoint(Vec3f(200, 0, 100));
		cube->addPoint(Vec3f(300, 0, 0));
		cube->addPoint(Vec3f(200, 100, 0));
		cube->addPoint(Vec3f(400, 0, 100));
		cube->addPoint(Vec3f(500, 0, 0));
		cube->addPoint(Vec3f(400, 100, 0));
		cube->Rotate(Rotate(), 1, 1, 1); //绕直线(0,0,0)(1,1,1)旋转45度便于观察 
		cube->setPenColor(PenColor());
		cube->setPenWidth(PenWidth());
		cube->setPenStyle(PenStyle());
		cube->setPenFill(PenFill());
		pDoc->AddRenderable(cube);
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG3D2021113163王梓翕View::OnQuad()
{
	// TODO: 在此添加命令处理程序代码
	CCG3D2021113163王梓翕Doc* pDoc = GetDocument();
	if (pDoc)
	{
		CG3DQuad* cube = new CG3DQuad();  //只会绘制一个
		cube->addPoint(Vec3f(-100, 100, 0));
		cube->addPoint(Vec3f(-100, -100, 0));
		cube->addPoint(Vec3f(100, -100, 0));
		cube->addPoint(Vec3f(100, 100, 0));
		cube->addPoint(Vec3f(300, 100, 0));
		cube->addPoint(Vec3f(400, -100, 0));
		cube->addPoint(Vec3f(400, -100, 0));
		cube->addPoint(Vec3f(300, 100, 0));
		cube->Rotate(Rotate(), 1, 1, 1); //绕直线(0,0,0)(1,1,1)旋转45度便于观察 
		cube->setPenColor(PenColor());
		cube->setPenWidth(PenWidth());
		cube->setPenStyle(PenStyle());
		cube->setPenFill(PenFill());
		pDoc->AddRenderable(cube);
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG3D2021113163王梓翕View::OnTriangularstrip()
{
	// TODO: 在此添加命令处理程序代码
	CCG3D2021113163王梓翕Doc* pDoc = GetDocument();
	if (pDoc)
	{
		CG3DTriangularStrip* cube = new CG3DTriangularStrip();
		cube->addPoint(Vec3f(-100, 100, 0));
		cube->addPoint(Vec3f(-100, -100, 0));
		cube->addPoint(Vec3f(0, 100, 0));
		cube->addPoint(Vec3f(0, -100, 0));
		cube->addPoint(Vec3f(100, 100, 0));
		cube->addPoint(Vec3f(100, -100, 0));
		cube->addPoint(Vec3f(200, 100, 0));
		cube->addPoint(Vec3f(200, -100, 0));
		cube->addPoint(Vec3f(300, 200, 0));
		cube->addPoint(Vec3f(300, -200, 0));
		cube->addPoint(Vec3f(500, 0, 0));
		cube->Rotate(Rotate(), 1, 1, 1); //绕直线(0,0,0)(1,1,1)旋转45度便于观察 
		cube->setPenColor(PenColor());
		cube->setPenWidth(PenWidth());
		cube->setPenStyle(PenStyle());
		cube->setPenFill(PenFill());
		pDoc->AddRenderable(cube);
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG3D2021113163王梓翕View::OnQuadstrip()
{
	// TODO: 在此添加命令处理程序代码
	CCG3D2021113163王梓翕Doc* pDoc = GetDocument();
	if (pDoc)
	{
		CG3DQuadStrip* cube = new CG3DQuadStrip();
		cube->addPoint(Vec3f(-100, 100, 0));
		cube->addPoint(Vec3f(-100, -100, 0));
		cube->addPoint(Vec3f(100, 100, 0));
		cube->addPoint(Vec3f(100, -100, 0));
		cube->addPoint(Vec3f(300, 100, 0));
		cube->addPoint(Vec3f(300, -100, 0));
		cube->addPoint(Vec3f(500, 100, 0));
		cube->addPoint(Vec3f(500, -100, 0));
		cube->addPoint(Vec3f(700, 200, 0));
		cube->addPoint(Vec3f(700, 0, 0));
		cube->addPoint(Vec3f(900, 200, 0));
		cube->addPoint(Vec3f(900, 0, 0));
		cube->Rotate(Rotate(), 1, 1, 1); //绕直线(0,0,0)(1,1,1)旋转45度便于观察 
		cube->setPenColor(PenColor());
		cube->setPenWidth(PenWidth());
		cube->setPenStyle(PenStyle());
		cube->setPenFill(PenFill());
		pDoc->AddRenderable(cube);
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG3D2021113163王梓翕View::OnRemoveAll()
{
	// TODO: 在此添加命令处理程序代码
	
	CCG3D2021113163王梓翕Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->RemoveAll();
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG3D2021113163王梓翕View::OnSphere()
{
	// TODO: 在此添加命令处理程序代码
	
	
	CCG3D2021113163王梓翕Doc* pDoc = GetDocument();
	if (pDoc)
	{
		CInputDialog1 dlg;
		dlg.mTitle = _T("请输入球体属性"); //根据需要设置对话框标题 
		CG3DSphere* cube = new CG3DSphere();
		cube->setRadius(1000);
		cube->setSlices(20);
		cube->setStacks(4);
		if (dlg.DoModal() == IDOK) //对话框中点击了【确定】按钮，取回输入的数据 
		{
			//根据实际需要使用输入的数据 
			//假如输入的是数值，则将字符串转换为数值 
			double Radius = _ttof(dlg.mValue1);
			int Slices = _ttof(dlg.mValue2);
			int Stacks = _ttof(dlg.mValue3);
			cube->setRadius(Radius);
			cube->setSlices(Slices);
			cube->setStacks(Stacks);

			//此处只显示输入的数据 
			//AfxMessageBox(dlg.mValue1);
			//AfxMessageBox(dlg.mValue2);
			//AfxMessageBox(dlg.mValue3);
		}
		cube->Rotate(Rotate(), 1, 1, 1); //绕直线(0,0,0)(1,1,1)旋转45度便于观察 
		cube->setPenColor(PenColor());
		cube->setPenWidth(PenWidth());
		cube->setPenStyle(PenStyle());
		cube->setPenFill(PenFill());
		pDoc->AddRenderable(cube);
		Invalidate(true);
		UpdateWindow();
	}
}
