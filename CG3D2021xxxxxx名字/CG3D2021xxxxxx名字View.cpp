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

// CG3D2021xxxxxx名字View.cpp: CCG3D2021xxxxxx名字View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CG3D2021xxxxxx名字.h"
#endif

#include "CG3D2021xxxxxx名字Doc.h"
#include "CG3D2021xxxxxx名字View.h"
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
#include "CInputMaterial.h"
#include "CInputLight.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCG3D2021xxxxxx名字View

IMPLEMENT_DYNCREATE(CCG3D2021xxxxxx名字View, CView)

BEGIN_MESSAGE_MAP(CCG3D2021xxxxxx名字View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_COMMAND(ID_TriangularFan, &CCG3D2021xxxxxx名字View::OnTriangularfan)
	ON_COMMAND(ID_ClosedFoldedLine, &CCG3D2021xxxxxx名字View::OnClosedfoldedline)
	ON_COMMAND(ID_LineSegment, &CCG3D2021xxxxxx名字View::OnLinesegment)
	ON_COMMAND(ID_FoldedLine, &CCG3D2021xxxxxx名字View::OnFoldedline)
	ON_COMMAND(ID_Polygon, &CCG3D2021xxxxxx名字View::OnPolygon)
	ON_COMMAND(ID_Triangle, &CCG3D2021xxxxxx名字View::OnTriangle)
	ON_COMMAND(ID_Quad, &CCG3D2021xxxxxx名字View::OnQuad)
	ON_COMMAND(ID_TriangularStrip, &CCG3D2021xxxxxx名字View::OnTriangularstrip)
	ON_COMMAND(ID_QuadStrip, &CCG3D2021xxxxxx名字View::OnQuadstrip)
	ON_COMMAND(ID_REMOVE_ALL, &CCG3D2021xxxxxx名字View::OnRemoveAll)
	ON_COMMAND(ID_SPHERE, &CCG3D2021xxxxxx名字View::OnSphere)
	ON_COMMAND(ID_UPDATE_MATERIAL, &CCG3D2021xxxxxx名字View::OnUpdateMaterial)
	ON_COMMAND(ID_Custom_Materials, &CCG3D2021xxxxxx名字View::OnCustomMaterials)
	ON_COMMAND(ID_Custom_point_light_sources, &CCG3D2021xxxxxx名字View::OnCustompointlightsources)
	ON_COMMAND(ID_Custom_line_light_source, &CCG3D2021xxxxxx名字View::OnCustomlinelightsource)
	ON_COMMAND(ID_Custom_Spotlight, &CCG3D2021xxxxxx名字View::OnCustomSpotlight)
	ON_COMMAND(ID_NTN_TIMER1, &CCG3D2021xxxxxx名字View::OnNtnTimer1)
	ON_UPDATE_COMMAND_UI(ID_NTN_TIMER1, &CCG3D2021xxxxxx名字View::OnUpdateNtnTimer1)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CCG3D2021xxxxxx名字View 构造/析构

CCG3D2021xxxxxx名字View::CCG3D2021xxxxxx名字View() noexcept
{
	// TODO: 在此处添加构造代码

}

CCG3D2021xxxxxx名字View::~CCG3D2021xxxxxx名字View()
{
}

BOOL CCG3D2021xxxxxx名字View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 
	//  CREATESTRUCT cs 来修改窗口类或样式 
	cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS; //非常重要 
	return CView::PreCreateWindow(cs);
}

// CCG3D2021xxxxxx名字View 绘图

void CCG3D2021xxxxxx名字View::OnDraw(CDC* /*pDC*/)
{
	CCG3D2021xxxxxx名字Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码 
	pDoc->RenderScene(this);
}

void CCG3D2021xxxxxx名字View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCG3D2021xxxxxx名字View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCG3D2021xxxxxx名字View 诊断

#ifdef _DEBUG
void CCG3D2021xxxxxx名字View::AssertValid() const
{
	CView::AssertValid();
}

void CCG3D2021xxxxxx名字View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCG3D2021xxxxxx名字Doc* CCG3D2021xxxxxx名字View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCG3D2021xxxxxx名字Doc)));
	return (CCG3D2021xxxxxx名字Doc*)m_pDocument;
}
#endif //_DEBUG


// CCG3D2021xxxxxx名字View 消息处理程序
//绘制客户区的宽度、高度（必须在派生类中实现） 
void CCG3D2021xxxxxx名字View::GetClientWidthHeight(int& w, int& h)
{
	CRect rc;
	GetClientRect(&rc);
	w = rc.Width();
	h = rc.Height();
}

bool CCG3D2021xxxxxx名字View::SetupRenderContext()
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

void CCG3D2021xxxxxx名字View::Ready(CG3DCamera* pCamera)
{
	wglMakeCurrent(mHDC, mHGLRC);

	GLclampf r, g, b;
	r = (GLclampf)GetRValue(mBkgndColor) / 255.0;
	g = (GLclampf)GetGValue(mBkgndColor) / 255.0;
	b = (GLclampf)GetBValue(mBkgndColor) / 255.0;
	//设置背景色和最远深度，并清除颜色缓存和深度缓存 
	glClearColor(r, g, b, 0.0f);
	mBkgndDepth = pCamera->Far();
	glClearDepth(mBkgndDepth);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void CCG3D2021xxxxxx名字View::Finish(CG3DCamera*)
{
	glFlush();
	SwapBuffers(mHDC);
	wglMakeCurrent(mHDC, NULL);
}

bool CCG3D2021xxxxxx名字View::SetupPixelFormat(void)
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

int CCG3D2021xxxxxx名字View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码 
	if (!SetupRenderContext())
		return -1;
	return 0;
}


void CCG3D2021xxxxxx名字View::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码 
	if (mAnimateTimer != 0)
	{
		KillTimer(mAnimateTimer);
		mAnimateTimer = 0;
	}

	if (mPalette)
	{
		DeleteObject(mPalette);
		mPalette = 0;
	}
	::wglMakeCurrent(NULL, NULL);
	::wglDeleteContext(mHGLRC);
}


void CCG3D2021xxxxxx名字View::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}

//画笔属性 
COLORREF CCG3D2021xxxxxx名字View::PenColor() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return RGB(0, 0, 0);
	return pMainWnd->PenColor();
}


int CCG3D2021xxxxxx名字View::PenWidth() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 1;
	return pMainWnd->PenWidth();
}


int CCG3D2021xxxxxx名字View::PenStyle() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 0;
	return pMainWnd->PenStyle();
}

int CCG3D2021xxxxxx名字View::PenFill() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 0;
	return pMainWnd->PenFill();
}

int CCG3D2021xxxxxx名字View::Rotate() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 45;
	return pMainWnd->Rotate();
}

//状态栏上显示提示信息 
void CCG3D2021xxxxxx名字View::Prompt(const CString& str)
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (pMainWnd != nullptr)
	{
		pMainWnd->ShowPrompt(str);
	}
}

void CCG3D2021xxxxxx名字View::OnTriangularfan()
{
	// TODO: 在此添加命令处理程序代码
	CCG3D2021xxxxxx名字Doc* pDoc = GetDocument();
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


void CCG3D2021xxxxxx名字View::OnClosedfoldedline()
{
	// TODO: 在此添加命令处理程序代码
	CCG3D2021xxxxxx名字Doc* pDoc = GetDocument();
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


void CCG3D2021xxxxxx名字View::OnLinesegment()
{
	// TODO: 在此添加命令处理程序代码
	CCG3D2021xxxxxx名字Doc* pDoc = GetDocument();
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


void CCG3D2021xxxxxx名字View::OnFoldedline()
{
	// TODO: 在此添加命令处理程序代码
	CCG3D2021xxxxxx名字Doc* pDoc = GetDocument();
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


void CCG3D2021xxxxxx名字View::OnPolygon()
{
	// TODO: 在此添加命令处理程序代码
	CCG3D2021xxxxxx名字Doc* pDoc = GetDocument();
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


void CCG3D2021xxxxxx名字View::OnTriangle()
{
	// TODO: 在此添加命令处理程序代码
	CCG3D2021xxxxxx名字Doc* pDoc = GetDocument();
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


void CCG3D2021xxxxxx名字View::OnQuad()
{
	// TODO: 在此添加命令处理程序代码
	CCG3D2021xxxxxx名字Doc* pDoc = GetDocument();
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


void CCG3D2021xxxxxx名字View::OnTriangularstrip()
{
	// TODO: 在此添加命令处理程序代码
	CCG3D2021xxxxxx名字Doc* pDoc = GetDocument();
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


void CCG3D2021xxxxxx名字View::OnQuadstrip()
{
	// TODO: 在此添加命令处理程序代码
	CCG3D2021xxxxxx名字Doc* pDoc = GetDocument();
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


void CCG3D2021xxxxxx名字View::OnRemoveAll()
{
	// TODO: 在此添加命令处理程序代码
	
	CCG3D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->RemoveAll();
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG3D2021xxxxxx名字View::OnSphere()
{
	// TODO: 在此添加命令处理程序代码
	CCG3D2021xxxxxx名字Doc* pDoc = GetDocument();
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

//画笔属性 
COLORREF CCG3D2021xxxxxx名字View::MaterialColor() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return RGB(1, 1, 1);
	return pMainWnd->MaterialColor();
}

int CCG3D2021xxxxxx名字View::MaterialStyle() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 0;
	return pMainWnd->MaterialStyle();
}

void CCG3D2021xxxxxx名字View::OnUpdateMaterial()
{
	// TODO: 在此添加命令处理程序代码
	CCG3D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		COLORREF newColor = MaterialColor(); // 假设GetSelectedColor()是一个返回COLORREF类型的成员函数
		int newStyle = MaterialStyle(); // 同理，假设GetSelectedStyle()返回选定的样式

		/*CString colorMsg;
		colorMsg.Format(_T("选择的颜色: RGB(%d, %d, %d)"), GetRValue(newColor), GetGValue(newColor), GetBValue(newColor));
		AfxMessageBox(colorMsg);

		CString styleMsg;
		styleMsg.Format(_T("选择的样式: %d"), newStyle);
		AfxMessageBox(styleMsg);*/

		BYTE r = GetRValue(newColor); // 获取红色分量
		BYTE g = GetGValue(newColor); // 获取绿色分量
		BYTE b = GetBValue(newColor); // 获取蓝色分量

		// 将每个分量从0-255转换为0.0-1.0
		float red = (r) / 255.0f;
		float green = (g) / 255.0f;
		float blue = (b) / 255.0f;

		Vec4f color = Vec4f(red, green, blue, 1);

		switch (newStyle) {
			case 0:
				pDoc->sphere->Appearance().Material().setMetallicMaterial(color);
				pDoc->cone->Appearance().Material().setMetallicMaterial(color);
				pDoc->cylinder->Appearance().Material().setMetallicMaterial(color);
				break;
			case 1:
				pDoc->sphere->Appearance().Material().setPlasticMaterial(color);
				pDoc->cone->Appearance().Material().setPlasticMaterial(color);
				pDoc->cylinder->Appearance().Material().setPlasticMaterial(color);
				break;
			case 2:
				pDoc->sphere->Appearance().Material().setGlassMaterial(color);
				pDoc->cone->Appearance().Material().setGlassMaterial(color);
				pDoc->cylinder->Appearance().Material().setGlassMaterial(color);
				break;
			case 3:
				pDoc->sphere->Appearance().Material().setWoodenMaterial(color);
				pDoc->cone->Appearance().Material().setWoodenMaterial(color);
				pDoc->cylinder->Appearance().Material().setWoodenMaterial(color);
				break;
			case 4:
				pDoc->sphere->Appearance().Material().setCeramicMaterial(color);
				pDoc->cone->Appearance().Material().setCeramicMaterial(color);
				pDoc->cylinder->Appearance().Material().setCeramicMaterial(color);
				break;
			case 5:
				pDoc->sphere->Appearance().Material().setRubberMaterial(color);
				pDoc->cone->Appearance().Material().setRubberMaterial(color);
				pDoc->cylinder->Appearance().Material().setRubberMaterial(color);
				break;
			default:
				// It's often good to have a default case to handle unexpected values
				// You can put an error message or default behavior here
				break;
		}
		Invalidate(true);
		UpdateWindow();
	}
}

// 边界检查函数
template<typename T>
T Clamp(T value, T min, T max) {
	return std::max(min, std::min(value, max));
}

void CCG3D2021xxxxxx名字View::OnCustomMaterials()
{
	CCG3D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		CInputMaterial dlg;
		dlg.mTitle = _T("请输入材质参数"); //根据需要设置对话框标题 
		if (dlg.DoModal() == IDOK) //对话框中点击了【确定】按钮，取回输入的数据 
		{
			

			// 初始化或更新环境光系数
			Vec4f mFrontAmbient = Vec4f((Clamp(dlg.Ar, 0, 255)) / 255.0f,
				(Clamp(dlg.Ag, 0, 255)) / 255.0f,
				(Clamp(dlg.Ab, 0, 255)) / 255.0f,
				1.0f);

			// 漫反射系数
			Vec4f mFrontDiffuse = Vec4f((Clamp(dlg.Dr, 0, 255)) / 255.0f,
				(Clamp(dlg.Dg, 0, 255)) / 255.0f,
				(Clamp(dlg.Db, 0, 255)) / 255.0f,
				1.0f);

			// 镜面反射系数
			Vec4f mFrontSpecular = Vec4f((Clamp(dlg.Sr, 0, 255)) / 255.0f,
				(Clamp(dlg.Sg, 0, 255)) / 255.0f,
				(Clamp(dlg.Sb, 0, 255)) / 255.0f, // 这里纠正了之前的假设，Sb应保留
				1.0f);

			// 散射系数
			Vec4f mFrontEmission = Vec4f((Clamp(dlg.Er, 0, 255)) / 255.0f,
				(Clamp(dlg.Eg, 0, 255)) / 255.0f,
				(Clamp(dlg.Eb, 0, 255)) / 255.0f,
				1.0f);

			// Shininess（光泽度）不需要转换为Vec4f，直接赋值即可
			float Shin = (Clamp(dlg.Shin, 0.0f, 128.0f)); // 假设Sr是光泽度的整数表示，转换为浮点数
			
			/*CString styleMsg;
			styleMsg.Format(_T("选择的样式: %f"), mFrontSpecular.z());
			AfxMessageBox(styleMsg); */
			mFrontSpecular = Vec4f(0, 0, 1, 1);

			if (pDoc->sphere) {
				pDoc->sphere->Appearance().Material().setFrontAmbient(mFrontAmbient);
				pDoc->sphere->Appearance().Material().setFrontDiffuse(mFrontDiffuse);
				pDoc->sphere->Appearance().Material().setFrontSpecular(mFrontSpecular);
				pDoc->sphere->Appearance().Material().setFrontEmission(mFrontEmission);
				pDoc->sphere->Appearance().Material().setFrontShininess(Shin);
			}
			if (pDoc->cone) {
				pDoc->cone->Appearance().Material().setFrontAmbient(mFrontAmbient);
				pDoc->cone->Appearance().Material().setFrontDiffuse(mFrontDiffuse);
				pDoc->cone->Appearance().Material().setFrontSpecular(mFrontSpecular);
				pDoc->cone->Appearance().Material().setFrontEmission(mFrontEmission);
				pDoc->cone->Appearance().Material().setFrontShininess(Shin);
			}
			if (pDoc->cylinder) {
				pDoc->cylinder->Appearance().Material().setFrontAmbient(mFrontAmbient);
				pDoc->cylinder->Appearance().Material().setFrontDiffuse(mFrontDiffuse);
				pDoc->cylinder->Appearance().Material().setFrontSpecular(mFrontSpecular);
				pDoc->cylinder->Appearance().Material().setFrontEmission(mFrontEmission);
				pDoc->cylinder->Appearance().Material().setFrontShininess(Shin);
			}

		}
		Invalidate(true);
		UpdateWindow();
	}
}


CGLight* CCG3D2021xxxxxx名字View::CustomLight() {
	CCG3D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		CInputLight dlg;
		dlg.mTitle = _T("请输入光源长度"); //根据需要设置对话框标题 
		if (dlg.DoModal() == IDOK) //对话框中点击了【确定】按钮，取回输入的数据 
		{
			Vec4f Ambient = Vec4f((Clamp(dlg.Ar, 0.0f, 255.0f)) / 255.0f,
				(Clamp(dlg.Ag, 0.0f, 255.0f)) / 255.0f,
				(Clamp(dlg.Ab, 0.0f, 255.0f)) / 255.0f,
				1.0f);
			Vec4f Diffuse = Vec4f((Clamp(dlg.Dr, 0.0f, 255.0f)) / 255.0f,
				(Clamp(dlg.Dg, 0.0f, 255.0f)) / 255.0f,
				(Clamp(dlg.Db, 0.0f, 255.0f)) / 255.0f,
				1.0f);
			Vec4f Specular = Vec4f((Clamp(dlg.Sr, 0.0f, 255.0f)) / 255.0f,
				(Clamp(dlg.Sg, 0.0f, 255.0f)) / 255.0f,
				(Clamp(dlg.Sb, 0.0f, 255.0f)) / 255.0f, // 这里纠正了之前的假设，Sb应保留
				1.0f);
			Vec3f Pos = Vec3f(dlg.Px, dlg.Py, dlg.Pz);
			Vec3f Dir = Vec3f(dlg.Dx, dlg.Dy, dlg.Dz);
			if (Dir == Vec3f(0, 0, 0))
				Dir = -Pos;
			float SpotExponent = Clamp(dlg.SpotCut, 0.0f, 128.0f), mSpotCutoff = Clamp(dlg.SpotCut, 0.0f, 180.0f);
			if (mSpotCutoff > 90.0f) mSpotCutoff = 180.0f;
			float Att1 = dlg.At1, Att2 = dlg.At2, Att3 = dlg.At3;

			CGLight* light = new CGLight();
			light->setAmbient(Ambient);
			light->setDiffuse(Diffuse);
			light->setSpecular(Specular);
			light->setPosition(Pos);
			light->setSpotlightParameters(Dir, SpotExponent, mSpotCutoff);
			light->setAttenuation(Att1, Att2, Att3);
			pDoc->mScene->AddLight(light);
			return light;
		}
	}
	return nullptr;
}
void CCG3D2021xxxxxx名字View::OnCustompointlightsources()
{
	CGLight* light = CustomLight();
	if (light)
		light->setAsPointLight();
	UpdateWindow();
	Invalidate(true);
}
void CCG3D2021xxxxxx名字View::OnCustomlinelightsource()
{
	CGLight* light = CustomLight();
	if (light)
		light->setAsDirectionalLight();
	UpdateWindow();
	Invalidate(true);
}
void CCG3D2021xxxxxx名字View::OnCustomSpotlight()
{
	CGLight* light = CustomLight();
	if (light)
		light->setAsSpotLight();
	UpdateWindow();
	Invalidate(true);
}


void CCG3D2021xxxxxx名字View::OnNtnTimer1()
{
	if (mAnimateTimer == 0)//判断定时器有没有启动 
	{
		mAnimateTimer = SetTimer(1, 50, NULL);//启动定时器 50 毫秒。可根据动画帧频要求设置 
	}
	else
	{
		KillTimer(mAnimateTimer);//关闭定时器
		mAnimateTimer = 0;
	}
}


void CCG3D2021xxxxxx名字View::OnUpdateNtnTimer1(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(mAnimateTimer != 0);
}


void CCG3D2021xxxxxx名字View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (mAnimateTimer == nIDEvent)
	{
		CCG3D2021xxxxxx名字Doc* pDoc = GetDocument();
		if (pDoc)
		{
			if (pDoc->TimerCallback())
			{
				Invalidate();
				//UpdateWindow(); 
			}
		}
	}
	__super::OnTimer(nIDEvent);
}
