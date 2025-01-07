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

// CG3D2021xxxxxx����View.cpp: CCG3D2021xxxxxx����View ���ʵ��
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "CG3D2021xxxxxx����.h"
#endif

#include "CG3D2021xxxxxx����Doc.h"
#include "CG3D2021xxxxxx����View.h"
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


// CCG3D2021xxxxxx����View

IMPLEMENT_DYNCREATE(CCG3D2021xxxxxx����View, CView)

BEGIN_MESSAGE_MAP(CCG3D2021xxxxxx����View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_COMMAND(ID_TriangularFan, &CCG3D2021xxxxxx����View::OnTriangularfan)
	ON_COMMAND(ID_ClosedFoldedLine, &CCG3D2021xxxxxx����View::OnClosedfoldedline)
	ON_COMMAND(ID_LineSegment, &CCG3D2021xxxxxx����View::OnLinesegment)
	ON_COMMAND(ID_FoldedLine, &CCG3D2021xxxxxx����View::OnFoldedline)
	ON_COMMAND(ID_Polygon, &CCG3D2021xxxxxx����View::OnPolygon)
	ON_COMMAND(ID_Triangle, &CCG3D2021xxxxxx����View::OnTriangle)
	ON_COMMAND(ID_Quad, &CCG3D2021xxxxxx����View::OnQuad)
	ON_COMMAND(ID_TriangularStrip, &CCG3D2021xxxxxx����View::OnTriangularstrip)
	ON_COMMAND(ID_QuadStrip, &CCG3D2021xxxxxx����View::OnQuadstrip)
	ON_COMMAND(ID_REMOVE_ALL, &CCG3D2021xxxxxx����View::OnRemoveAll)
	ON_COMMAND(ID_SPHERE, &CCG3D2021xxxxxx����View::OnSphere)
	ON_COMMAND(ID_UPDATE_MATERIAL, &CCG3D2021xxxxxx����View::OnUpdateMaterial)
	ON_COMMAND(ID_Custom_Materials, &CCG3D2021xxxxxx����View::OnCustomMaterials)
	ON_COMMAND(ID_Custom_point_light_sources, &CCG3D2021xxxxxx����View::OnCustompointlightsources)
	ON_COMMAND(ID_Custom_line_light_source, &CCG3D2021xxxxxx����View::OnCustomlinelightsource)
	ON_COMMAND(ID_Custom_Spotlight, &CCG3D2021xxxxxx����View::OnCustomSpotlight)
	ON_COMMAND(ID_NTN_TIMER1, &CCG3D2021xxxxxx����View::OnNtnTimer1)
	ON_UPDATE_COMMAND_UI(ID_NTN_TIMER1, &CCG3D2021xxxxxx����View::OnUpdateNtnTimer1)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CCG3D2021xxxxxx����View ����/����

CCG3D2021xxxxxx����View::CCG3D2021xxxxxx����View() noexcept
{
	// TODO: �ڴ˴���ӹ������

}

CCG3D2021xxxxxx����View::~CCG3D2021xxxxxx����View()
{
}

BOOL CCG3D2021xxxxxx����View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� 
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ 
	cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS; //�ǳ���Ҫ 
	return CView::PreCreateWindow(cs);
}

// CCG3D2021xxxxxx����View ��ͼ

void CCG3D2021xxxxxx����View::OnDraw(CDC* /*pDC*/)
{
	CCG3D2021xxxxxx����Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ��� 
	pDoc->RenderScene(this);
}

void CCG3D2021xxxxxx����View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCG3D2021xxxxxx����View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCG3D2021xxxxxx����View ���

#ifdef _DEBUG
void CCG3D2021xxxxxx����View::AssertValid() const
{
	CView::AssertValid();
}

void CCG3D2021xxxxxx����View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCG3D2021xxxxxx����Doc* CCG3D2021xxxxxx����View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCG3D2021xxxxxx����Doc)));
	return (CCG3D2021xxxxxx����Doc*)m_pDocument;
}
#endif //_DEBUG


// CCG3D2021xxxxxx����View ��Ϣ�������
//���ƿͻ����Ŀ�ȡ��߶ȣ���������������ʵ�֣� 
void CCG3D2021xxxxxx����View::GetClientWidthHeight(int& w, int& h)
{
	CRect rc;
	GetClientRect(&rc);
	w = rc.Width();
	h = rc.Height();
}

bool CCG3D2021xxxxxx����View::SetupRenderContext()
{
	if (!SetupPixelFormat())
		return false;

	mHGLRC = ::wglCreateContext(mHDC);
	::wglMakeCurrent(mHDC, mHGLRC);

	//������Ҫ���ò���; 
	glEnable(GL_DEPTH_TEST); //������Ȳ��ԣ������� 
	glEnable(GL_CULL_FACE); //�����޳����������޳��� 
	glFrontFace(GL_CCW); //�����������ʱ�뷽�򶥵����С�����Ҫ����Ӱ�쵽��Ŀɼ��� 
	glDrawBuffer(GL_BACK); //���Ƶ��󻺴棨�轻�����棩 

	return mHGLRC != 0;
}

void CCG3D2021xxxxxx����View::Ready(CG3DCamera* pCamera)
{
	wglMakeCurrent(mHDC, mHGLRC);

	GLclampf r, g, b;
	r = (GLclampf)GetRValue(mBkgndColor) / 255.0;
	g = (GLclampf)GetGValue(mBkgndColor) / 255.0;
	b = (GLclampf)GetBValue(mBkgndColor) / 255.0;
	//���ñ���ɫ����Զ��ȣ��������ɫ�������Ȼ��� 
	glClearColor(r, g, b, 0.0f);
	mBkgndDepth = pCamera->Far();
	glClearDepth(mBkgndDepth);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void CCG3D2021xxxxxx����View::Finish(CG3DCamera*)
{
	glFlush();
	SwapBuffers(mHDC);
	wglMakeCurrent(mHDC, NULL);
}

bool CCG3D2021xxxxxx����View::SetupPixelFormat(void)
{
	mHWnd = GetSafeHwnd();
	mHDC = GetDC()->GetSafeHdc();
	if (!mHWnd || !mHDC)
		return false;

	PIXELFORMATDESCRIPTOR pfd = {
	 sizeof(PIXELFORMATDESCRIPTOR),    // pfd�ṹ�Ĵ�С  
	 1,                                // �汾��  
	 PFD_DRAW_TO_WINDOW |              // ֧���ڴ����л�ͼ  
	 PFD_SUPPORT_OPENGL |              // ֧�� OpenGL  
	 PFD_DOUBLEBUFFER,                 // ˫����ģʽ  
	 PFD_TYPE_RGBA,                    // RGBA ��ɫģʽ  
	 24,                               // 24 λ��ɫ���  
	 0, 0, 0, 0, 0, 0,                 // ������ɫλ  
	 0,                                // û�з�͸���Ȼ���  
	 0,                                // ������λλ  
	 0,                                // ���ۼӻ���  
	 0, 0, 0, 0,                       // �����ۼ�λ  
	 32,                               // 32 λ��Ȼ���      
	 0,                                // ��ģ�建��  
	 0,                                // �޸������� 
	PFD_MAIN_PLANE,               // ����  
	 0,                                // ����  
	0, 0, 0                            // ���Բ�,�ɼ��Ժ������ģ  
	};
int iPixelFormat;
// Ϊ�豸������õ���ƥ������ظ�ʽ  
if ((iPixelFormat = ChoosePixelFormat(mHDC, &pfd)) == 0)
{
	AfxMessageBox(_T("ChoosePixelFormat Failed"), NULL, MB_OK);
	return false;
}

// ������ƥ������ظ�ʽΪ��ǰ�����ظ�ʽ  
if (SetPixelFormat(mHDC, iPixelFormat, &pfd) == FALSE)
{
	AfxMessageBox(_T("SetPixelFormat Failed"), NULL, MB_OK);
	return false;
}
if (pfd.dwFlags & PFD_NEED_PALETTE)
{
	//�����߼���ɫ�� 
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

int CCG3D2021xxxxxx����View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ������� 
	if (!SetupRenderContext())
		return -1;
	return 0;
}


void CCG3D2021xxxxxx����View::OnDestroy()
{
	CView::OnDestroy();

	// TODO: �ڴ˴������Ϣ���������� 
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


void CCG3D2021xxxxxx����View::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
}

//�������� 
COLORREF CCG3D2021xxxxxx����View::PenColor() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return RGB(0, 0, 0);
	return pMainWnd->PenColor();
}


int CCG3D2021xxxxxx����View::PenWidth() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 1;
	return pMainWnd->PenWidth();
}


int CCG3D2021xxxxxx����View::PenStyle() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 0;
	return pMainWnd->PenStyle();
}

int CCG3D2021xxxxxx����View::PenFill() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 0;
	return pMainWnd->PenFill();
}

int CCG3D2021xxxxxx����View::Rotate() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 45;
	return pMainWnd->Rotate();
}

//״̬������ʾ��ʾ��Ϣ 
void CCG3D2021xxxxxx����View::Prompt(const CString& str)
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (pMainWnd != nullptr)
	{
		pMainWnd->ShowPrompt(str);
	}
}

void CCG3D2021xxxxxx����View::OnTriangularfan()
{
	// TODO: �ڴ���������������
	CCG3D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		CG3DTriangularFan* cube = new CG3DTriangularFan();
		cube->addPoint(Vec3f(0, 0, 0));
		cube->addPoint(Vec3f(-400, 0, 0));
		cube->addPoint(Vec3f(-300, -300, 0));
		cube->addPoint(Vec3f(0, -400, 0));
		cube->addPoint(Vec3f(300, -300, 0));
		cube->Rotate(Rotate(), 1, 1, 1); //��ֱ��(0,0,0)(1,1,1)��ת45�ȱ��ڹ۲� 
		cube->setPenColor(PenColor());
		cube->setPenWidth(PenWidth());
		cube->setPenStyle(PenStyle());
		cube->setPenFill(PenFill());
		pDoc->AddRenderable(cube);
		Invalidate(true);
		UpdateWindow();
		//CString str;
		//str.Format(_T("%d"), Rotate()); // ��ʽ������Ϊ�ַ���
		//Prompt(str); // ��ʾ����
	}
}


void CCG3D2021xxxxxx����View::OnClosedfoldedline()
{
	// TODO: �ڴ���������������
	CCG3D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		CG3DClosedFoldedLine* cube = new CG3DClosedFoldedLine();
		cube->addPoint(Vec3f(0, 0, 0));
		cube->addPoint(Vec3f(1000, 0, 0));
		cube->addPoint(Vec3f(0, 1000, 0));
		cube->addPoint(Vec3f(-500, 0, 0));
		cube->addPoint(Vec3f(0, -100, 0));
		cube->Rotate(Rotate(), 1, 1, 1); //��ֱ��(0,0,0)(1,1,1)��ת45�ȱ��ڹ۲� 
		cube->setPenColor(PenColor());
		cube->setPenWidth(PenWidth());
		cube->setPenStyle(PenStyle());
		cube->setPenFill(PenFill());
		pDoc->AddRenderable(cube);
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG3D2021xxxxxx����View::OnLinesegment()
{
	// TODO: �ڴ���������������
	CCG3D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		CG3DLineSegment* cube = new CG3DLineSegment();
		cube->addPoint(Vec3f(-100, 0, 0));
		cube->addPoint(Vec3f(0, 300, 0));
		cube->addPoint(Vec3f(100, 0, 0));
		cube->addPoint(Vec3f(200, 300, 0));
		cube->addPoint(Vec3f(300, 0, 0));
		cube->addPoint(Vec3f(400, 300, 0));
		cube->Rotate(Rotate(), 1, 1, 1); //��ֱ��(0,0,0)(1,1,1)��ת45�ȱ��ڹ۲� 
		cube->setPenColor(PenColor());
		cube->setPenWidth(PenWidth());
		cube->setPenStyle(PenStyle());
		cube->setPenFill(PenFill());
		pDoc->AddRenderable(cube);
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG3D2021xxxxxx����View::OnFoldedline()
{
	// TODO: �ڴ���������������
	CCG3D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		CG3DFoldedLine* cube = new CG3DFoldedLine();
		cube->addPoint(Vec3f(0, 0, 0));
		cube->addPoint(Vec3f(1000, 0, 0));
		cube->addPoint(Vec3f(0, 1000, 0));
		cube->addPoint(Vec3f(-500, 0, 0));
		cube->addPoint(Vec3f(0, -100, 0));
		cube->Rotate(Rotate(), 1, 1, 1); //��ֱ��(0,0,0)(1,1,1)��ת45�ȱ��ڹ۲� 
		cube->setPenColor(PenColor());
		cube->setPenWidth(PenWidth());
		cube->setPenStyle(PenStyle());
		cube->setPenFill(PenFill());
		pDoc->AddRenderable(cube);
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG3D2021xxxxxx����View::OnPolygon()
{
	// TODO: �ڴ���������������
	CCG3D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		CG3DPolygon* cube = new CG3DPolygon();
		cube->addPoint(Vec3f(0, 0, 0));
		cube->addPoint(Vec3f(400, 0, 0));
		cube->addPoint(Vec3f(500, 400, 0));
		cube->addPoint(Vec3f(200, 600, 0));
		cube->addPoint(Vec3f(-100, 400, 0));
		cube->Rotate(Rotate(), 1, 1, 1); //��ֱ��(0,0,0)(1,1,1)��ת45�ȱ��ڹ۲� 
		cube->setPenColor(PenColor());
		cube->setPenWidth(PenWidth());
		cube->setPenStyle(PenStyle());
		cube->setPenFill(PenFill());
		pDoc->AddRenderable(cube);
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG3D2021xxxxxx����View::OnTriangle()
{
	// TODO: �ڴ���������������
	CCG3D2021xxxxxx����Doc* pDoc = GetDocument();
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
		cube->Rotate(Rotate(), 1, 1, 1); //��ֱ��(0,0,0)(1,1,1)��ת45�ȱ��ڹ۲� 
		cube->setPenColor(PenColor());
		cube->setPenWidth(PenWidth());
		cube->setPenStyle(PenStyle());
		cube->setPenFill(PenFill());
		pDoc->AddRenderable(cube);
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG3D2021xxxxxx����View::OnQuad()
{
	// TODO: �ڴ���������������
	CCG3D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		CG3DQuad* cube = new CG3DQuad();  //ֻ�����һ��
		cube->addPoint(Vec3f(-100, 100, 0));
		cube->addPoint(Vec3f(-100, -100, 0));
		cube->addPoint(Vec3f(100, -100, 0));
		cube->addPoint(Vec3f(100, 100, 0));
		cube->addPoint(Vec3f(300, 100, 0));
		cube->addPoint(Vec3f(400, -100, 0));
		cube->addPoint(Vec3f(400, -100, 0));
		cube->addPoint(Vec3f(300, 100, 0));
		cube->Rotate(Rotate(), 1, 1, 1); //��ֱ��(0,0,0)(1,1,1)��ת45�ȱ��ڹ۲� 
		cube->setPenColor(PenColor());
		cube->setPenWidth(PenWidth());
		cube->setPenStyle(PenStyle());
		cube->setPenFill(PenFill());
		pDoc->AddRenderable(cube);
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG3D2021xxxxxx����View::OnTriangularstrip()
{
	// TODO: �ڴ���������������
	CCG3D2021xxxxxx����Doc* pDoc = GetDocument();
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
		cube->Rotate(Rotate(), 1, 1, 1); //��ֱ��(0,0,0)(1,1,1)��ת45�ȱ��ڹ۲� 
		cube->setPenColor(PenColor());
		cube->setPenWidth(PenWidth());
		cube->setPenStyle(PenStyle());
		cube->setPenFill(PenFill());
		pDoc->AddRenderable(cube);
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG3D2021xxxxxx����View::OnQuadstrip()
{
	// TODO: �ڴ���������������
	CCG3D2021xxxxxx����Doc* pDoc = GetDocument();
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
		cube->Rotate(Rotate(), 1, 1, 1); //��ֱ��(0,0,0)(1,1,1)��ת45�ȱ��ڹ۲� 
		cube->setPenColor(PenColor());
		cube->setPenWidth(PenWidth());
		cube->setPenStyle(PenStyle());
		cube->setPenFill(PenFill());
		pDoc->AddRenderable(cube);
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG3D2021xxxxxx����View::OnRemoveAll()
{
	// TODO: �ڴ���������������
	
	CCG3D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->RemoveAll();
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG3D2021xxxxxx����View::OnSphere()
{
	// TODO: �ڴ���������������
	CCG3D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		CInputDialog1 dlg;
		dlg.mTitle = _T("��������������"); //������Ҫ���öԻ������ 
		CG3DSphere* cube = new CG3DSphere();
		cube->setRadius(1000);
		cube->setSlices(20);
		cube->setStacks(4);
		if (dlg.DoModal() == IDOK) //�Ի����е���ˡ�ȷ������ť��ȡ����������� 
		{
			//����ʵ����Ҫʹ����������� 
			//�������������ֵ�����ַ���ת��Ϊ��ֵ 
			double Radius = _ttof(dlg.mValue1);
			int Slices = _ttof(dlg.mValue2);
			int Stacks = _ttof(dlg.mValue3);
			cube->setRadius(Radius);
			cube->setSlices(Slices);
			cube->setStacks(Stacks);

			//�˴�ֻ��ʾ��������� 
			//AfxMessageBox(dlg.mValue1);
			//AfxMessageBox(dlg.mValue2);
			//AfxMessageBox(dlg.mValue3);
		}
		cube->Rotate(Rotate(), 1, 1, 1); //��ֱ��(0,0,0)(1,1,1)��ת45�ȱ��ڹ۲� 
		cube->setPenColor(PenColor());
		cube->setPenWidth(PenWidth());
		cube->setPenStyle(PenStyle());
		cube->setPenFill(PenFill());
		pDoc->AddRenderable(cube);
		Invalidate(true);
		UpdateWindow();
	}
}

//�������� 
COLORREF CCG3D2021xxxxxx����View::MaterialColor() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return RGB(1, 1, 1);
	return pMainWnd->MaterialColor();
}

int CCG3D2021xxxxxx����View::MaterialStyle() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 0;
	return pMainWnd->MaterialStyle();
}

void CCG3D2021xxxxxx����View::OnUpdateMaterial()
{
	// TODO: �ڴ���������������
	CCG3D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		COLORREF newColor = MaterialColor(); // ����GetSelectedColor()��һ������COLORREF���͵ĳ�Ա����
		int newStyle = MaterialStyle(); // ͬ������GetSelectedStyle()����ѡ������ʽ

		/*CString colorMsg;
		colorMsg.Format(_T("ѡ�����ɫ: RGB(%d, %d, %d)"), GetRValue(newColor), GetGValue(newColor), GetBValue(newColor));
		AfxMessageBox(colorMsg);

		CString styleMsg;
		styleMsg.Format(_T("ѡ�����ʽ: %d"), newStyle);
		AfxMessageBox(styleMsg);*/

		BYTE r = GetRValue(newColor); // ��ȡ��ɫ����
		BYTE g = GetGValue(newColor); // ��ȡ��ɫ����
		BYTE b = GetBValue(newColor); // ��ȡ��ɫ����

		// ��ÿ��������0-255ת��Ϊ0.0-1.0
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

// �߽��麯��
template<typename T>
T Clamp(T value, T min, T max) {
	return std::max(min, std::min(value, max));
}

void CCG3D2021xxxxxx����View::OnCustomMaterials()
{
	CCG3D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		CInputMaterial dlg;
		dlg.mTitle = _T("��������ʲ���"); //������Ҫ���öԻ������ 
		if (dlg.DoModal() == IDOK) //�Ի����е���ˡ�ȷ������ť��ȡ����������� 
		{
			

			// ��ʼ������»�����ϵ��
			Vec4f mFrontAmbient = Vec4f((Clamp(dlg.Ar, 0, 255)) / 255.0f,
				(Clamp(dlg.Ag, 0, 255)) / 255.0f,
				(Clamp(dlg.Ab, 0, 255)) / 255.0f,
				1.0f);

			// ������ϵ��
			Vec4f mFrontDiffuse = Vec4f((Clamp(dlg.Dr, 0, 255)) / 255.0f,
				(Clamp(dlg.Dg, 0, 255)) / 255.0f,
				(Clamp(dlg.Db, 0, 255)) / 255.0f,
				1.0f);

			// ���淴��ϵ��
			Vec4f mFrontSpecular = Vec4f((Clamp(dlg.Sr, 0, 255)) / 255.0f,
				(Clamp(dlg.Sg, 0, 255)) / 255.0f,
				(Clamp(dlg.Sb, 0, 255)) / 255.0f, // ���������֮ǰ�ļ��裬SbӦ����
				1.0f);

			// ɢ��ϵ��
			Vec4f mFrontEmission = Vec4f((Clamp(dlg.Er, 0, 255)) / 255.0f,
				(Clamp(dlg.Eg, 0, 255)) / 255.0f,
				(Clamp(dlg.Eb, 0, 255)) / 255.0f,
				1.0f);

			// Shininess������ȣ�����Ҫת��ΪVec4f��ֱ�Ӹ�ֵ����
			float Shin = (Clamp(dlg.Shin, 0.0f, 128.0f)); // ����Sr�ǹ���ȵ�������ʾ��ת��Ϊ������
			
			/*CString styleMsg;
			styleMsg.Format(_T("ѡ�����ʽ: %f"), mFrontSpecular.z());
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


CGLight* CCG3D2021xxxxxx����View::CustomLight() {
	CCG3D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		CInputLight dlg;
		dlg.mTitle = _T("�������Դ����"); //������Ҫ���öԻ������ 
		if (dlg.DoModal() == IDOK) //�Ի����е���ˡ�ȷ������ť��ȡ����������� 
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
				(Clamp(dlg.Sb, 0.0f, 255.0f)) / 255.0f, // ���������֮ǰ�ļ��裬SbӦ����
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
void CCG3D2021xxxxxx����View::OnCustompointlightsources()
{
	CGLight* light = CustomLight();
	if (light)
		light->setAsPointLight();
	UpdateWindow();
	Invalidate(true);
}
void CCG3D2021xxxxxx����View::OnCustomlinelightsource()
{
	CGLight* light = CustomLight();
	if (light)
		light->setAsDirectionalLight();
	UpdateWindow();
	Invalidate(true);
}
void CCG3D2021xxxxxx����View::OnCustomSpotlight()
{
	CGLight* light = CustomLight();
	if (light)
		light->setAsSpotLight();
	UpdateWindow();
	Invalidate(true);
}


void CCG3D2021xxxxxx����View::OnNtnTimer1()
{
	if (mAnimateTimer == 0)//�ж϶�ʱ����û������ 
	{
		mAnimateTimer = SetTimer(1, 50, NULL);//������ʱ�� 50 ���롣�ɸ��ݶ���֡ƵҪ������ 
	}
	else
	{
		KillTimer(mAnimateTimer);//�رն�ʱ��
		mAnimateTimer = 0;
	}
}


void CCG3D2021xxxxxx����View::OnUpdateNtnTimer1(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(mAnimateTimer != 0);
}


void CCG3D2021xxxxxx����View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (mAnimateTimer == nIDEvent)
	{
		CCG3D2021xxxxxx����Doc* pDoc = GetDocument();
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
