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

// CG2D2021xxxxxx����View.cpp: CCG2D2021xxxxxx����View ���ʵ��
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "CG2D2021xxxxxx����.h"
#endif

#include "CG2D2021xxxxxx����Doc.h"
#include "CG2D2021xxxxxx����View.h"
#include "CG2DCamera.h"
#include "MainFrm.h"
#include <vector>
#include <utility>
#include "CG2DCamera.h"
#include "CG2DRenderable.h"
#include "CG2DLineSegment.h"
#include "CG2DLineSegmentCreateCommand.h"
#include "CG2DPolylineCreateCommand.h"
#include "CG2DPolygonCreateCommand.h"
#include "CG2DCircleCenterRadiusCreateCommand.h"
#include "CG2DRenderablePickCommand.h"
#include "CG2DRenderablePickInBoxCommand.h"
#include "CG2DRenderableMoveCommand.h"
#include "CG2DRenderableRotateCommand.h"
#include "CG2DCameraMoveCommand.h"
#include "CG2DWindowBoxCommand.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PI acos(-1)


// CCG2D2021xxxxxx����View

IMPLEMENT_DYNCREATE(CCG2D2021xxxxxx����View, CView)

BEGIN_MESSAGE_MAP(CCG2D2021xxxxxx����View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_DRAW_CDC, &CCG2D2021xxxxxx����View::OnDrawCDC)
	ON_COMMAND(ID_DRAW_POINT, &CCG2D2021xxxxxx����View::OnDrawPoint)
	ON_COMMAND(ID_ALGORITHM_LINE, &CCG2D2021xxxxxx����View::OnAlgorithmLine)
	ON_COMMAND(ID_ALGORITHM_CIRCLE, &CCG2D2021xxxxxx����View::OnAlgorithmCircle)
	ON_COMMAND(ID_ALGORITHM_FILL, &CCG2D2021xxxxxx����View::OnAlgorithmFill)
	ON_COMMAND(ID_ALGORITHM_TIMING, &CCG2D2021xxxxxx����View::OnAlgorithmTiming)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONDBLCLK()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
	ON_COMMAND(ID_DRAW_LINESEGMENT, &CCG2D2021xxxxxx����View::OnDrawLinesegment)
	ON_COMMAND(ID_DRAW_POLYLINE, &CCG2D2021xxxxxx����View::OnDrawPolyline)
	ON_UPDATE_COMMAND_UI(ID_DRAW_LINESEGMENT, &CCG2D2021xxxxxx����View::OnUpdateDrawLinesegment)
	ON_UPDATE_COMMAND_UI(ID_DRAW_POLYLINE, &CCG2D2021xxxxxx����View::OnUpdateDrawPolyline)
	ON_COMMAND(ID_DRAW_POLYGON, &CCG2D2021xxxxxx����View::OnDrawPolygon)
	ON_UPDATE_COMMAND_UI(ID_DRAW_POLYGON, &CCG2D2021xxxxxx����View::OnUpdateDrawPolygon)
	ON_COMMAND(ID_DRAW_CIRCLE, &CCG2D2021xxxxxx����View::OnDrawCircle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CIRCLE, &CCG2D2021xxxxxx����View::OnUpdateDrawCircle)
	ON_COMMAND(ID_PICK_ONE, &CCG2D2021xxxxxx����View::OnPickOne)
	ON_UPDATE_COMMAND_UI(ID_PICK_ONE, &CCG2D2021xxxxxx����View::OnUpdatePickOne)
	ON_COMMAND(ID_TRANSLATE_LEFT, &CCG2D2021xxxxxx����View::OnTranslateLeft)
	ON_COMMAND(ID_TRANSLATE_RIGHT, &CCG2D2021xxxxxx����View::OnTranslateRight)
	ON_COMMAND(ID_TRANSLATE_UP, &CCG2D2021xxxxxx����View::OnTranslateUp)
	ON_COMMAND(ID_TRANSLATE_DOWN, &CCG2D2021xxxxxx����View::OnTranslateDown)
	ON_COMMAND(ID_PICK_BOX, &CCG2D2021xxxxxx����View::OnPickBox)
	ON_UPDATE_COMMAND_UI(ID_PICK_BOX, &CCG2D2021xxxxxx����View::OnUpdatePickBox)
	ON_COMMAND(ID_TRANSLATE_ZOOM_IN, &CCG2D2021xxxxxx����View::OnTranslateZoomIn)
	ON_COMMAND(ID_TRANSLATE_ZOOM_OUT, &CCG2D2021xxxxxx����View::OnTranslateZoomOut)
	ON_COMMAND(ID_TRANSLATE_SYM_X, &CCG2D2021xxxxxx����View::OnTranslateSymX)
	ON_COMMAND(ID_TRANSLATE_SYM_Y, &CCG2D2021xxxxxx����View::OnTranslateSymY)
	ON_COMMAND(ID_TRANSLATE_SYM_O, &CCG2D2021xxxxxx����View::OnTranslateSymO)
	ON_COMMAND(ID_TRANSLATE_SYM_XY, &CCG2D2021xxxxxx����View::OnTranslateSymXy)
	ON_COMMAND(ID_TRANSLATE_SYM_XnY, &CCG2D2021xxxxxx����View::OnTranslateSymXny)
	ON_COMMAND(ID_TRANSLATE_MISKNIP_X, &CCG2D2021xxxxxx����View::OnTranslateMisknipX)
	ON_COMMAND(ID_TRANSLATE_MISKNIP_Y, &CCG2D2021xxxxxx����View::OnTranslateMisknipY)
	ON_COMMAND(ID_TRANSLATE_MISKNIP_XY, &CCG2D2021xxxxxx����View::OnTranslateMisknipXy)
	ON_COMMAND(ID_TRANSLATE_MOVE, &CCG2D2021xxxxxx����View::OnTranslateMove)
	ON_UPDATE_COMMAND_UI(ID_TRANSLATE_MOVE, &CCG2D2021xxxxxx����View::OnUpdateTranslateMove)
	ON_COMMAND(ID_TRANSLATE_ROTATE, &CCG2D2021xxxxxx����View::OnTranslateRotate)
	ON_UPDATE_COMMAND_UI(ID_TRANSLATE_ROTATE, &CCG2D2021xxxxxx����View::OnUpdateTranslateRotate)
	ON_COMMAND(ID_CAMERA_LEFT, &CCG2D2021xxxxxx����View::OnCameraLeft)
	ON_COMMAND(ID_CAMERA_RIGHT, &CCG2D2021xxxxxx����View::OnCameraRight)
	ON_COMMAND(ID_CAMERA_UP, &CCG2D2021xxxxxx����View::OnCameraUp)
	ON_COMMAND(ID_CAMERA_DOWN, &CCG2D2021xxxxxx����View::OnCameraDown)
	ON_COMMAND(ID_CAMERA_FAR, &CCG2D2021xxxxxx����View::OnCameraFar)
	ON_COMMAND(ID_CAMERA_CLOSE, &CCG2D2021xxxxxx����View::OnCameraClose)
	ON_COMMAND(ROTATION_COUNTER, &CCG2D2021xxxxxx����View::OnCounter)
	ON_COMMAND(ROTATION_CLOCKWISE, &CCG2D2021xxxxxx����View::OnClockwise)
	ON_COMMAND(ROTATION_RESET, &CCG2D2021xxxxxx����View::OnReset)
	ON_COMMAND(ID_Window_LEFT_ADD, &CCG2D2021xxxxxx����View::OnWindowLeftAdd)
	ON_COMMAND(ID_WINDOW_LEFT_DECREASE, &CCG2D2021xxxxxx����View::OnWindowLeftDecrease)
	ON_COMMAND(ID_WINDOW_RIGHT_ADD, &CCG2D2021xxxxxx����View::OnWindowRightAdd)
	ON_COMMAND(ID_WINDOW_RIGHT_DECREASE, &CCG2D2021xxxxxx����View::OnWindowRightDecrease)
	ON_COMMAND(ID_WINDOW_BOTTOM_ADD, &CCG2D2021xxxxxx����View::OnWindowBottomAdd)
	ON_COMMAND(ID_WINDOW_BOTTOM_DECREASE, &CCG2D2021xxxxxx����View::OnWindowBottomDecrease)
	ON_COMMAND(ID_WINDOW_TOP_ADD, &CCG2D2021xxxxxx����View::OnWindowTopAdd)
	ON_COMMAND(ID_WINDOW_TOP_DECREASE, &CCG2D2021xxxxxx����View::OnWindowTopDecrease)
	ON_COMMAND(ID_WINDOW_REDUCE, &CCG2D2021xxxxxx����View::OnWindowReduce)
	ON_COMMAND(ID_WINDOW_EXPAND, &CCG2D2021xxxxxx����View::OnWindowExpand)
	ON_COMMAND(ID_VIEWPOINT_LEFT_ADD, &CCG2D2021xxxxxx����View::OnViewpointLeftAdd)
	ON_COMMAND(ID_VIEWPOINT_LEFT_DECREASE, &CCG2D2021xxxxxx����View::OnViewpointLeftDecrease)
	ON_COMMAND(ID_VIEWPOINT_RIGHT_ADD, &CCG2D2021xxxxxx����View::OnViewpointRightAdd)
	ON_COMMAND(ID_VIEWPOINT_RIGHT_DECREASE, &CCG2D2021xxxxxx����View::OnViewpointRightDecrease)
	ON_COMMAND(ID_VIEWPOINT_BOTTOM_ADD, &CCG2D2021xxxxxx����View::OnViewpointBottomAdd)
	ON_COMMAND(ID_VIEWPOINT_BOTTOM_DECREASE, &CCG2D2021xxxxxx����View::OnViewpointBottomDecrease)
	ON_COMMAND(ID_VIEWPOINT_TOP_ADD, &CCG2D2021xxxxxx����View::OnViewpointTopAdd)
	ON_COMMAND(ID_VIEWPOINT_TOP_DECREASE, &CCG2D2021xxxxxx����View::OnViewpointTopDecrease)
	ON_COMMAND(ID_VIEWPOINT_RESET, &CCG2D2021xxxxxx����View::OnViewpointReset)
	ON_COMMAND(ID_WINDOW_RESET, &CCG2D2021xxxxxx����View::OnWindowReset)
	ON_COMMAND(ID_CAMERA_MOVE, &CCG2D2021xxxxxx����View::OnCameraMove)
	ON_UPDATE_COMMAND_UI(ID_CAMERA_MOVE, &CCG2D2021xxxxxx����View::OnUpdateCameraMove)
	ON_COMMAND(ID_WINDOW_BOX, &CCG2D2021xxxxxx����View::OnWindowBox)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_BOX, &CCG2D2021xxxxxx����View::OnUpdateWindowBox)
	ON_COMMAND(ID_WINDOW_OVERALL, &CCG2D2021xxxxxx����View::OnWindowOverall)
	ON_COMMAND(ID_Aspect_Ratio, &CCG2D2021xxxxxx����View::OnAspectRatio)
	ON_COMMAND(ID_REMOVE_ALL, &CCG2D2021xxxxxx����View::OnRemoveAll)
	ON_COMMAND(ID_BTN_TIMER1, &CCG2D2021xxxxxx����View::OnBtnTimer1)
	ON_UPDATE_COMMAND_UI(ID_BTN_TIMER1, &CCG2D2021xxxxxx����View::OnUpdateBtnTimer1)
	ON_COMMAND(ID_BTN_FIREWORKS, &CCG2D2021xxxxxx����View::OnBtnFireworks)
END_MESSAGE_MAP()

// CCG2D2021xxxxxx����View ����/����

CCG2D2021xxxxxx����View::CCG2D2021xxxxxx����View() noexcept
{
	// TODO: �ڴ˴���ӹ������

}

CCG2D2021xxxxxx����View::~CCG2D2021xxxxxx����View()
{
}

BOOL CCG2D2021xxxxxx����View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CCG2D2021xxxxxx����View ��ͼ

void GetDCSize(CDC* pDC, int& width, int& height)
{
	if (pDC == nullptr)
		return;

	CRect rect;
	CWnd* pWnd = pDC->GetWindow(); // ��ȡ��CDC�������CWnd����
	if (pWnd != nullptr)
	{
		pWnd->GetClientRect(&rect); // ��ȡ�ͻ�����С
		width = rect.Width();  // �ͻ������
		height = rect.Height();  // �ͻ����߶�
	}
}

void SetBackgroundColor(CDC* pDC, COLORREF color)
{
	ASSERT_VALID(pDC);
	if (!pDC)
		return;

	int width, height;
	GetDCSize(pDC, width, height);
	CRect rect(0, 0, width, height);
	CBrush brush(color);
	pDC->FillRect(&rect, &brush);
}

//���ڵ�
void DrawBlackDot(CDC* pDC, int centerX, int centerY, int radius = 5)
{
	// ���û��ʺͻ�ˢΪ��ɫ
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));  // 1���ؿ�ĺ�ɫ����
	CBrush brush(RGB(0, 0, 0));  // ��ɫ��ˢ

	// ����ɵĻ��ʺͻ�ˢ
	CPen* pOldPen = pDC->SelectObject(&pen);
	CBrush* pOldBrush = pDC->SelectObject(&brush);

	// ����ڵ�ı߽�
	int left = centerX - radius;
	int top = centerY - radius;
	int right = centerX + radius;
	int bottom = centerY + radius;

	// ���ƺڵ�
	pDC->Ellipse(left, top, right, bottom);

	// �ָ��ɵĻ��ʺͻ�ˢ
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

// ����һ��ָ����ɫ����Բ��
void DrawFilledCircle(CDC* pDC, int x, int y, int radius, COLORREF fillColor) {
	ASSERT_VALID(pDC);  // ����豸�����ĵ���Ч��
	if (!pDC)
		return;

	// ��������Բ�������Ļ��ʣ����ｫ���ɫҲ��������
	CPen pen(PS_SOLID, 1, fillColor);
	CPen* pOldPen = pDC->SelectObject(&pen);  // ����ɵĻ��ʣ���ʹ���»���

	// �����������Ļ�ˢ
	CBrush brush(fillColor);
	CBrush* pOldBrush = pDC->SelectObject(&brush);  // ����ɵĻ�ˢ����ʹ���»�ˢ

	// ��������Բ��
	pDC->Ellipse(x - radius, y - radius, x + radius, y + radius);

	// �ָ�֮ǰ�Ļ��ʺͻ�ˢ
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}


//����Բ��
void DrawArc(CDC* pDC, int x, int y, int r, int lineWide, COLORREF color)
{
	CRect rect(x - r, y - r, x + r, y + r);
	// �������Ϊ���ε��Ҳ��е�
	CPoint ptStart(x, y + r);
	// �����յ�Ϊ���εĵײ��е�
	CPoint ptEnd(x, y - r);

	// �Զ��廭�ʣ�ʹ�ú��������������ɫ���߿�
	CPen customPen(PS_SOLID, lineWide, color);

	// ���浱ǰ����
	CPen* pOldPen = pDC->SelectObject(&customPen);

	// ʹ���Զ��廭�ʻ���Բ�����ϰ벿��
	pDC->Arc(&rect, ptStart, ptEnd);
	// ����Բ�����°벿��
	pDC->Arc(&rect, ptEnd, ptStart);

	// �ָ�ԭ���Ļ���
	pDC->SelectObject(pOldPen);
}

// �����Ȼ�
void DrawPie(CDC* pDC, int x, int y, int r, COLORREF color, double angle)
{
	CRect rect(x - r, y - r, x + r, y + r);

	// �Ȼ������ʼ����Բ�Ķ����е�
	CPoint ptEnd(x, y - r);
	double M_PI = 3.141592653;

	// ���ݽǶȼ����Ȼ����յ�
	double radAngle = angle * M_PI / 180.0; // ���Ƕ�ת��Ϊ����
	CPoint ptStart(int(x + r * sin(radAngle)), int(y - r * cos(radAngle)));

	// �Զ��廭�ʺͻ�ˢ��ʹ�ú��������������ɫ
	CPen customPen(PS_SOLID, 1, color); // �߿���Ϊ1����С�����Ե�����Ŀɼ���
	CBrush customBrush(color); // ʹ����ͬ����ɫ���

	// ���浱ǰ���ʺͻ�ˢ
	CPen* pOldPen = pDC->SelectObject(&customPen);
	CBrush* pOldBrush = pDC->SelectObject(&customBrush);

	// ʹ���Զ��廭ˢ����Ȼ�
	pDC->Pie(&rect,ptStart, ptEnd);

	// �ָ�ԭ���Ļ��ʺͻ�ˢ
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}


// ���ƴ�Բ��������߶�
void DrawLineAtAngle(CDC* pDC, int x, int y, int r1, int r2, double angle, int lineWide, COLORREF color)
{
	double M_PI = 3.141592653;
	// ���ǶȴӶ�ת��Ϊ����
	double radAngle = angle * M_PI / 180.0;

	// ���������յ�
	CPoint ptStart(int(x + r1 * sin(radAngle)), int(y - r1 * cos(radAngle)));
	CPoint ptEnd(int(x + r2 * sin(radAngle)), int(y - r2 * cos(radAngle)));

	// �Զ��廭�ʣ�ʹ�ú��������������ɫ���߿�
	CPen customPen(PS_SOLID, lineWide, color);

	// ���浱ǰ����
	CPen* pOldPen = pDC->SelectObject(&customPen);

	// �����߶�
	pDC->MoveTo(ptStart);
	pDC->LineTo(ptEnd);

	// �ָ�ԭ���Ļ���
	pDC->SelectObject(pOldPen);
}


// ����һ��ָ���ض������С������
void DrawTriangleAtAngle(CDC* pDC, int x, int y, int r, double angle, int lineWide, COLORREF color)
{
	double M_PI = 3.141592653;
	// ���ǶȴӶ�ת��Ϊ����
	double radAngle = angle * M_PI / 180.0;

	// ���������εļ������
	CPoint ptTip(int(x + r * sin(radAngle)), int(y - r * cos(radAngle)));

	// ���������ε�������������
	double sideAngle = 3.0 * M_PI / 180.0; // 30�ȵı߽�
	int sideLength = int(r * 0.9); // ��߳���
	CPoint ptBase1(int(x + sideLength * sin(radAngle - sideAngle)), int(y - sideLength * cos(radAngle - sideAngle)));
	CPoint ptBase2(int(x + sideLength * sin(radAngle + sideAngle)), int(y - sideLength * cos(radAngle + sideAngle)));

	// �Զ��廭�ʺͻ�ˢ��ʹ�ú��������������ɫ
	CPen customPen(PS_SOLID, lineWide, color);
	CBrush customBrush(color);

	// ���浱ǰ���ʺͻ�ˢ
	CPen* pOldPen = pDC->SelectObject(&customPen);
	CBrush* pOldBrush = pDC->SelectObject(&customBrush);

	// ����������
	CPoint triangle[3] = { ptTip, ptBase1, ptBase2 };
	pDC->Polygon(triangle, 3);

	// �ָ�ԭ���Ļ��ʺͻ�ˢ
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

// ����ָ����С����ɫ���ı�����ָ�������ĵ�Ϊ����
void DrawTextCentered(CDC* pDC, const CString& text, int center_x, int center_y, int fontSize, COLORREF color)
{
	// ������ѡ������
	CFont font;
	font.CreatePointFont(fontSize * 10, _T("Arial"));
	CFont* pOldFont = pDC->SelectObject(&font);

	// ��ȡ�ı��ߴ�
	CSize textSize = pDC->GetTextExtent(text);

	// �����ı����ε����ϽǺ����½�����
	CRect rect(center_x - textSize.cx / 2, center_y - textSize.cy / 2,
		center_x + textSize.cx / 2, center_y + textSize.cy / 2);

	// �����ı���ɫ
	pDC->SetTextColor(color);

	// ���ñ���ģʽΪ͸��
	pDC->SetBkMode(TRANSPARENT);

	// �����ı�
	pDC->DrawText(text, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	// �ָ�ԭ��������
	pDC->SelectObject(pOldFont);
}




void CCG2D2021xxxxxx����View::OnDraw(CDC* pDC)
{
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->RenderScene(this);
	//Prompt(_T("OnDraw"));
}

void CCG2D2021xxxxxx����View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCG2D2021xxxxxx����View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCG2D2021xxxxxx����View ���

#ifdef _DEBUG
void CCG2D2021xxxxxx����View::AssertValid() const
{
	CView::AssertValid();
}

void CCG2D2021xxxxxx����View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCG2D2021xxxxxx����Doc* CCG2D2021xxxxxx����View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCG2D2021xxxxxx����Doc)));
	return (CCG2D2021xxxxxx����Doc*)m_pDocument;
}
#endif //_DEBUG


// CCG2D2021xxxxxx����View ��Ϣ�������

void CCG2D2021xxxxxx����View::OnDrawCDC()
{
	CClientDC dc(this); //��ȡ�ͻ������ƻ�����CClientDC��CDC������
	CClientDC  *pDC = &dc;
	// Ԥ����ɫ
	COLORREF col_background = RGB(240, 240, 240);
	COLORREF col_inside_background = RGB(50, 50, 50);
	COLORREF col_outside_background = RGB(40, 40, 40);
	COLORREF col_progressbar = RGB(99, 141, 241);
	COLORREF col_outside_silhouettes = RGB(69, 69, 69); //������
	COLORREF col_inside_silhouettes = RGB(226, 226, 226); //������
	COLORREF col_white = RGB(250, 250, 250);
	COLORREF col_black = RGB(30, 30, 30);
	// ����
	int width, height;
	GetDCSize(pDC, width, height); //��ȡ�ͻ�����С
	int centerX = width / 2;
	int centerY = height / 2;
	// ����
	int outside_R = 500;
	int outside_W = 50;
	int inside_R = 370;
	int inside_W = 50;
	double angle = 360.0 / 100 * 88;
	double angle_line1 = 360.0 / 100 * 87.5;
	double angle_line2 = 65;
	// ����ͼ��
	SetBackgroundColor(pDC, col_background);
	DrawFilledCircle(pDC, centerX, centerY, outside_R, col_outside_background);
	DrawPie(pDC, centerX, centerY, outside_R, col_progressbar, angle);
	DrawArc(pDC, centerX, centerY, outside_R, outside_W, col_outside_silhouettes);
	DrawFilledCircle(pDC, centerX, centerY, inside_R, col_inside_background);
	DrawArc(pDC, centerX, centerY, inside_R, inside_W, col_inside_silhouettes);
	DrawLineAtAngle(pDC, centerX, centerY, inside_R + inside_W / 2 + 5, outside_R - outside_W / 2 - 5, angle_line1, 5, col_white);
	DrawTriangleAtAngle(pDC, centerX, centerY, inside_R + inside_W / 2 - 5, angle_line1, 5, col_black);
	DrawLineAtAngle(pDC, centerX, centerY, inside_R + inside_W / 2 + 5, outside_R - outside_W / 2 - 5, angle_line2, 5, col_white);
	DrawTriangleAtAngle(pDC, centerX, centerY, inside_R + inside_W / 2 - 5, angle_line2, 5, col_black);
	// ���ú��������ı�
	DrawTextCentered(pDC, L"88.0", centerX, centerY, 100, col_white);
	DrawTextCentered(pDC, L"FLOW RATE", centerX, centerY - 170, 25, col_white);
	DrawTextCentered(pDC, L"LPM", centerX + 200, centerY + 150, 20, col_white);
	
}

void CCG2D2021xxxxxx����View::OnDrawPoint()
{
	CClientDC dc(this); //��ȡ�ͻ������ƻ�����CClientDC��CDC������
	//����ʾ��
	int width, height;
	GetDCSize(&dc, width, height); //��ȡ�ͻ�����С
	//ÿ��һ�����뻭һ����
	int interval = 100;
	for (int i = interval; i < width; i += interval)
	{
		for (int j = interval; j < height; j += interval)
		{
			DrawBlackDot(&dc, i, j);
		}
	}
}

void CCG2D2021xxxxxx����View::EraseBkgnd() //ʹ�ñ���ɫ����ͻ�������
{
	CBrush backBrush(mBkgndColor);
	CClientDC dc(this);
	CBrush* pOldBrush = dc.SelectObject(&backBrush);
	CRect rect;
	dc.GetClipBox(&rect);
	dc.PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	dc.SelectObject(pOldBrush);
}
HWND CCG2D2021xxxxxx����View::GetHWnd() const
{
	return GetSafeHwnd();
}
void CCG2D2021xxxxxx����View::Ready(bool erasebkgnd) //ÿһ����������ǰ����
{
	CG2DRenderContext::Ready(erasebkgnd);
	CRect rc;
	GetClientRect(&rc);
	if (mMemHDC == nullptr)
	{
		mMemHDC = ::CreateCompatibleDC(GetDC()->GetSafeHdc());
		mMemHBMP = ::CreateCompatibleBitmap(GetDC()->GetSafeHdc(), rc.Width(), rc.Height());
		::SelectObject(mMemHDC, mMemHBMP);
	}
	if (erasebkgnd)
	{
		HBRUSH br = ::CreateSolidBrush(mBkgndColor);
		::FillRect(mMemHDC, &rc, br);
		::DeleteObject(br);
	}
	mReady = true;
}
void CCG2D2021xxxxxx����View::Finish() //ÿһ���������ƺ���ã���ʾ��
{
	if (!mReady || mMemHDC == nullptr)
		return;
	CRect rc;
	GetClientRect(&rc);
	::BitBlt(GetDC()->GetSafeHdc(), 0, 0, rc.Width(), rc.Height(), mMemHDC, 0, 0, SRCCOPY);
}

void CCG2D2021xxxxxx����View::OnAlgorithmLine()
{
	Ready();

	const int sides = 12;
	const double radius = 100; // ʮ�����εİ뾶
	const double centerX = 100; // ʮ���������ĵ� x ����
	const double centerY = 100; // ʮ���������ĵ� y ����

	int x[25], y[25];

	for (int i = 0; i < sides; ++i) {
		double angle = 2 * PI * i / sides; // ����ÿ���Ƕ�
		x[i] = int(centerX + radius * cos(angle)); // ���� x ����
		y[i] = int(centerY + radius * sin(angle)); // ���� y ����
	}

	// ���ַ�������ʮ������
	int j = 0;
	for (int i = 0; i < sides; ++i) {
		j = (j+5) % sides;
		DDALine(x[j] + 50, y[j]+50, x[(j + 5) % sides] + 50, y[(j + 5) % sides] + 50, RGB(255, 0, 0));
	}
	j = 0;
	for (int i = 0; i < sides; ++i) {
		j = (j + 5) % sides;
		DDALine(x[j] + 350, y[j] + 50, x[(j + 5) % sides] + 350, y[(j +5) % sides] + 50, RGB(0, 255, 0));
	}
	j = 0;
	for (int i = 0; i < sides; ++i) {
		j = (j + 5) % sides;
		DDALine(x[j] + 650, y[j] + 50, x[(j + 5) % sides] + 650, y[(j + 5) % sides] + 50, RGB(0, 0, 255));
	}
	Finish();
}


void CCG2D2021xxxxxx����View::OnAlgorithmCircle()
{
	Ready();
	float delta = float(PI) / 6;
	for (float i = delta; i < 2 * PI; i += delta)
	{
		MidPointCircleArc(500, 500, int(100+i*20), RGB(0, 0, 0), 0, i);
	}
	for (float i = delta; i < 2 * PI; i += delta)
	{
		MidPointCircleArc(1000, 500, int(100 + i * 20), RGB(0, 0, 0), i, i + delta);
	}
	for (float i = delta; i < 2 * PI; i += delta)
	{
		MidPointCircle(1500, 500, int(100 + i * 20), RGB(0, 0, 0));
	}
	Finish();
}


void CCG2D2021xxxxxx����View::OnAlgorithmFill()
{
	Ready();
	//����һ���򵥵Ķ����
	std::vector<CPoint> pnts;
	pnts.push_back(CPoint(100, 100));
	pnts.push_back(CPoint(200, 100));
	pnts.push_back(CPoint(200, 200));
	pnts.push_back(CPoint(100, 200));
	ScanLinePolygonFill(pnts, RGB(0, 255, 0));


	//����һ���򵥵Ķ����
	std::vector<CPoint> pnts2;
	pnts2.push_back(CPoint(300, 100));
	pnts2.push_back(CPoint(400, 100));
	pnts2.push_back(CPoint(450, 150));
	pnts2.push_back(CPoint(400, 200));
	pnts2.push_back(CPoint(300, 200));
	pnts2.push_back(CPoint(350, 150));
	ScanLinePolygonFill(pnts2, RGB(0, 0, 255));


	//����һ���������
	std::vector<CPoint> pnts3;
	pnts3.push_back(CPoint(500, 150));
	pnts3.push_back(CPoint(530, 130));
	pnts3.push_back(CPoint(550, 100));
	pnts3.push_back(CPoint(570, 130));
	pnts3.push_back(CPoint(600, 150));
	pnts3.push_back(CPoint(570, 170));
	pnts3.push_back(CPoint(550, 200));
	pnts3.push_back(CPoint(530, 170));
	ScanLinePolygonFill(pnts3, RGB(255, 0, 0));


	//����һ���������
	std::vector<CPoint> pnts5;
	pnts5.push_back(CPoint(700, 100));
	pnts5.push_back(CPoint(750, 150));
	pnts5.push_back(CPoint(800, 100));
	pnts5.push_back(CPoint(800, 200));
	pnts5.push_back(CPoint(700, 200));
	ScanLinePolygonFill(pnts5, RGB(255, 0, 255));

	// ���Ʊ���
	const int sides = 5;
	const double radius = 100; 
	const double centerX = 100; 
	const double centerY = 100;
	int x[25], y[25];
	for (int i = 0; i < sides; ++i) {
		double angle = 2 * PI * i / sides; // ����ÿ���Ƕ�
		x[i] = int(centerX + radius * cos(angle)); // ���� x ����
		y[i] = int(centerY + radius * sin(angle)); // ���� y ����
	}
	int j = 0;
	for (int i = 0; i < sides; ++i) {
		j = (j + 3) % sides;
		DDALine(x[j] + 50, y[j] + 150, x[(j + 3) % sides] + 50, y[(j + 3) % sides] + 150, RGB(255, 0, 0));
	}
	j = 0;
	for (int i = 0; i < sides; ++i) {
		j = (j + 3) % sides;
		DDALine(x[j] + 350, y[j] + 150, x[(j + 3) % sides] + 350, y[(j + 3) % sides] + 150, RGB(0, 255, 0));
	}
	j = 0;
	for (int i = 0; i < sides; ++i) {
		j = (j + 3) % sides;
		DDALine(x[j] + 650, y[j] + 150, x[(j + 3) % sides] + 650, y[(j + 3) % sides] + 150, RGB(0, 0, 255));
	}

	// ��������㷨
	BoundFill4(100, 210, RGB(255, 0, 0), RGB(106, 212, 221));
	BoundFill4(170, 200, RGB(255, 0, 0), RGB(106, 212, 221));
	BoundFill4(450, 250, RGB(0, 255, 0), RGB(106, 212, 221));
	BoundFill4(770, 200, RGB(0, 0, 255), RGB(106, 212, 221));

	MidPointCircle(900, 200, 130, RGB(0, 0, 0));
	BoundFill4(900, 200, RGB(0, 0, 0), RGB(255, 235, 178));

	FloodFill4(370, 150, RGB(0, 0, 255), RGB(145, 43, 188));
	FloodFill4(450, 250, RGB(106, 212, 221), RGB(145, 43, 188));

	

	Finish();
}


void CCG2D2021xxxxxx����View::OnAlgorithmTiming()
{
	Ready(true);
	//�������һ��������ֱ�߶εĶ˵����꣺
	//���в����������ɴ���
	static const int VERTEXS = 20000;
	CPoint v[VERTEXS];
	srand((unsigned int)time(0));//��ʼ������Ϊ���ֵ
	CRect rc;
	GetClientRect(&rc);
	for (int i = 0; i < VERTEXS; i++)
	{
		v[i].x = rand() % rc.Width();
		v[i].y = rand() % rc.Height();
	}
	//��ʱ�����õ��ĺ����� QueryPerformanceFrequency��QueryPerformanceCounter
	//���в����ʱ����
	//�����ʱ�õĲ���
	LARGE_INTEGER frequency, start, end; //��ʱ
	double fitDDA, fitMID, fitBRE; //��ʱ
	QueryPerformanceFrequency(&frequency);
	//DDA�㷨���Ʋ���ʱ
	QueryPerformanceCounter(&start); //����ǰ��ʱ
	for (int i = 0; i < VERTEXS; i += 2)
	{
		DDALine(v[i].x, v[i].y, v[i + 1].x, v[i + 1].y, RGB(0, 0, 0));
	}
	QueryPerformanceCounter(&end); //���ƽ�����ʱ
	//�������ʱ��
	fitDDA = (double)(end.QuadPart - start.QuadPart) / (double)frequency.QuadPart;
	//�е��㷨���Ʋ���ʱ
	QueryPerformanceCounter(&start); //����ǰ��ʱ
	for (int i = 0; i < VERTEXS; i += 2)
	{
		MidPointLine(v[i].x, v[i].y, v[i + 1].x, v[i + 1].y, RGB(0, 0, 0));
	}
	QueryPerformanceCounter(&end); //���ƽ�����ʱ
	//�������ʱ��
	fitMID = (double)(end.QuadPart - start.QuadPart) / (double)frequency.QuadPart;
	//Bresenham�㷨���Ʋ���ʱ
	QueryPerformanceCounter(&start); //����ǰ��ʱ
	for (int i = 0; i < VERTEXS; i += 2)
	{
		BresenhamLine(v[i].x, v[i].y, v[i + 1].x, v[i + 1].y, RGB(0, 0, 0));
	}
	QueryPerformanceCounter(&end); //���ƽ�����ʱ
	//�������ʱ��
	fitBRE = (double)(end.QuadPart - start.QuadPart) / (double)frequency.QuadPart;
	Finish();
	//��ʾ���㷨���Ƶ�ʱ��
	//���в������
	CString strFitin;
	strFitin.Format(_T("DDALine��%.6f"), fitDDA);
	AfxMessageBox(strFitin);
	strFitin.Format(_T("MidPointLine��%.6f"), fitMID);
	AfxMessageBox(strFitin);
	strFitin.Format(_T("BresenhamLine��%.6f"), fitBRE);
	AfxMessageBox(strFitin);
}

//���ƿͻ����Ŀ�ȡ��߶ȣ���д�����麯����
void CCG2D2021xxxxxx����View::GetClientWidthHeight(int& w, int& h)
{
	CRect rc;
	GetClientRect(&rc);
	w = rc.Width();
	h = rc.Height();
}
void CCG2D2021xxxxxx����View::Ready(CG2DCamera* camera) //ÿһ����������ǰ���á���������ӿڱ�������Ҫ���»���ͼ�Ρ�
{
	if (!camera)
	return;
	CG2DRenderContext::Ready(camera);
	mMemHDC = ::CreateCompatibleDC(GetDC()->GetSafeHdc());
	CG2DViewPort& vp = camera->viewport();
	int mClientWidth = camera->ClientWidth();
	int mClientHeight = camera->ClientHeight();
	mMemHBMP = ::CreateCompatibleBitmap(GetDC()->GetSafeHdc(), mClientWidth, mClientHeight);
	::SelectObject(mMemHDC, mMemHBMP);
	HBRUSH br = ::CreateSolidBrush(vp.clearColor());
	CRect rc(0, 0, mClientWidth, mClientHeight);
	::FillRect(mMemHDC, &rc, br);
	::DeleteObject(br);
	mReady = true;
	}
void CCG2D2021xxxxxx����View::Finish(CG2DCamera* camera) //ÿһ���������ƺ���ã���ʾ��
{
	if (!mReady)
		return;
	if (camera == nullptr || camera != mCamera)
		return;
	CG2DViewPort& vp = camera->viewport();
	int mClientWidth = camera->ClientWidth();
	int mClientHeight = camera->ClientHeight();
	::BitBlt(GetDC()->GetSafeHdc(), vp.x(), vp.y(), vp.width(), vp.height(), mMemHDC, 
		vp.x(), vp.y(), SRCCOPY);
}

// ʵ��3-2

//��������
COLORREF CCG2D2021xxxxxx����View::PenColor() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return RGB(0, 0, 0);
	return pMainWnd->PenColor();
}
int CCG2D2021xxxxxx����View::PenWidth() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 1;
	return pMainWnd->PenWidth();
}
int CCG2D2021xxxxxx����View::PenStyle() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return PS_SOLID;
	return pMainWnd->PenStyle();
}
//��ˢ����
COLORREF CCG2D2021xxxxxx����View::BrushColor() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return RGB(255, 255, 255);
	return pMainWnd->BrushColor();
}
int CCG2D2021xxxxxx����View::BrushStyle() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 0;
	return pMainWnd->BrushStyle();
}
int CCG2D2021xxxxxx����View::HatchStyle() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 0;
	return pMainWnd->HatchStyle();
}
//�����㷨
int CCG2D2021xxxxxx����View::LineAlgorithm() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 0;
	return pMainWnd->LineAlgorithm();
}
int CCG2D2021xxxxxx����View::CircleAlgorithm() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 0;
	return pMainWnd->CircleAlgorithm();
}
int CCG2D2021xxxxxx����View::FillAlgorithm() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 0;
	return pMainWnd->FillAlgorithm();
}
int CCG2D2021xxxxxx����View::SeedAlgorithm() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 0;
	return pMainWnd->SeedAlgorithm();
}
//��������ı߽���ɫ
COLORREF CCG2D2021xxxxxx����View::BoundColor() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 0;
	return pMainWnd->BoundColor();
}
//����������ڵ���ɫ
COLORREF CCG2D2021xxxxxx����View::FloodColor() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 0;
	return pMainWnd->FloodColor();
}
//״̬������ʾ��ʾ��Ϣ
void CCG2D2021xxxxxx����View::Prompt(const CString& str)
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (pMainWnd != nullptr)
	{
		pMainWnd->ShowPrompt(str);
	}
}

void CCG2D2021xxxxxx����View::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
}


void CCG2D2021xxxxxx����View::OnDestroy()
{
	__super::OnDestroy();

	// TODO: �ڴ˴������Ϣ���������� 
	if (mAnimateTimer != 0)
	{
		KillTimer(mAnimateTimer);
		mAnimateTimer = 0;
	}
}


void CCG2D2021xxxxxx����View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nChar == VK_ESCAPE) //���������ESC�������жϵ�ǰ�Ļ�������������ִ�У�
	{
		if (mCommand)
		{
			mCommand->Cancel();
			delete mCommand;
			mCommand = nullptr;
		}
		//TODO�������ѡ�е�ͼ�ζ��󣬴˴�����ʰȡ״̬��
		else
		{
			CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
			ASSERT_VALID(pDoc);
			if (pDoc)
				pDoc->UnselectAll();
		}
	}
	if (mCommand) //����ģʽ��ת������Ӧ�������ȥ������¼�
		mCommand->OnKeyDown(nChar, nRepCnt, nFlags);
	__super::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CCG2D2021xxxxxx����View::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (mCommand) //����ģʽ��ת������Ӧ�������ȥ������¼�
		mCommand->OnKeyUp(nChar, nRepCnt, nFlags);
	__super::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CCG2D2021xxxxxx����View::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (mCommand) //����ģʽ��ת������Ӧ�������ȥ������¼�
		mCommand->OnLButtonDblClk(nFlags, point);
	__super::OnLButtonDblClk(nFlags, point);
}


void CCG2D2021xxxxxx����View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (mCommand) //����ģʽ��ת������Ӧ�������ȥ������¼�
		mCommand->OnLButtonDown(nFlags, point);
	__super::OnLButtonDown(nFlags, point);
}


void CCG2D2021xxxxxx����View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (mCommand) //����ģʽ��ת������Ӧ�������ȥ������¼�
		mCommand->OnLButtonUp(nFlags, point);
	__super::OnLButtonUp(nFlags, point);
}


void CCG2D2021xxxxxx����View::OnMButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (mCommand) //����ģʽ��ת������Ӧ�������ȥ������¼�
		mCommand->OnMButtonDblClk(nFlags, point);
	__super::OnMButtonDblClk(nFlags, point);
}


void CCG2D2021xxxxxx����View::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (mCommand) //����ģʽ��ת������Ӧ�������ȥ������¼�
		mCommand->OnMButtonDown(nFlags, point);
	__super::OnMButtonDown(nFlags, point);
}


void CCG2D2021xxxxxx����View::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (mCommand) //����ģʽ��ת������Ӧ�������ȥ������¼�
		mCommand->OnMButtonUp(nFlags, point);
	__super::OnMButtonUp(nFlags, point);
}


void CCG2D2021xxxxxx����View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//__super::OnMouseMove(nFlags, point);
	
		
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (pDoc != nullptr && pMainWnd != nullptr)
	{
		Vec2d v = pDoc->ViewPorttoWorld(Vec2i(point.x, point.y));
		CString str;
		str.Format(_T("�ӿ����� ( %d, %d ) : �������� (%.2f , %.2f) "), point.x, point.y, v.x(),
			v.y());
		pMainWnd->ShowCoordOnStatusBar(str); //��ʾ��״̬��
	}
	//����ģʽ��������Ϣת������һ�����ݵ�ǰ������״̬��������ƶ��¼�
	if (mCommand)
		mCommand->OnMouseMove(nFlags, point);
	__super::OnMouseMove(nFlags, point);
	
}


BOOL CCG2D2021xxxxxx����View::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (mCommand) //����ģʽ��ת������Ӧ�������ȥ������¼�
		mCommand->OnMouseWheel(nFlags, zDelta, pt);
	return __super::OnMouseWheel(nFlags, zDelta, pt);
}


void CCG2D2021xxxxxx����View::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (mCommand) //����ģʽ��ת������Ӧ�������ȥ������¼�
		mCommand->OnRButtonDblClk(nFlags, point);
	__super::OnRButtonDblClk(nFlags, point);
}


void CCG2D2021xxxxxx����View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (mCommand) //����ģʽ��ת������Ӧ�������ȥ������¼�
		mCommand->OnRButtonDown(nFlags, point);
	__super::OnRButtonDown(nFlags, point);
}


void CCG2D2021xxxxxx����View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ 
	if (mAnimateTimer == nIDEvent)
	{
		CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
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


void CCG2D2021xxxxxx����View::OnDrawLinesegment()
{
	// TODO: �ڴ���������������
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	mCommand = new CG2DLineSegmentCreateCommand(this); //��������ֱ�߶ε��������
}

void CCG2D2021xxxxxx����View::OnUpdateDrawLinesegment(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	//��ǰ�����Ƿ��ǻ���ֱ�߶�����
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == static_cast<int>(CommandType::cmd2dLineSegment));
}

void CCG2D2021xxxxxx����View::OnDrawPolyline()
{
	// TODO: �ڴ���������������
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	mCommand = new CG2DPolylineCreateCommand(this);
}

void CCG2D2021xxxxxx����View::OnUpdateDrawPolyline(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	//��ǰ�����Ƿ��ǻ���ֱ�߶�����
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == static_cast<int>(CommandType::cmd2dPolyline));
}

void CCG2D2021xxxxxx����View::OnDrawPolygon()
{
	// TODO: �ڴ���������������
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	mCommand = new CG2DPolygonCreateCommand(this);
}


void CCG2D2021xxxxxx����View::OnUpdateDrawPolygon(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == static_cast<int>(CommandType::cmd2dPolygon));
}


void CCG2D2021xxxxxx����View::OnDrawCircle()
{
	// TODO: �ڴ���������������
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	mCommand = new CG2DCircleCenterRadiusCreateCommand(this);
}


void CCG2D2021xxxxxx����View::OnUpdateDrawCircle(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == static_cast<int>(CommandType::cmd2dCircleCenterRadius));
}


//ͼ�ζ�����ӵ�����
bool CCG2D2021xxxxxx����View::addRenderable(CG2DRenderable* r)
{
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return false;
	bool ret = pDoc->addRenderable(r);
	// TODO���˴����Բ��䳡�����ĸ�����ʾ
	return ret;
}
bool CCG2D2021xxxxxx����View::delReaderable(CG2DRenderable* r)
{
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return false;
	bool ret = pDoc->delReaderable(r);
	// TODO���˴����Բ��䳡�����ĸ�����ʾ
	return ret;
}
//�����ӿ������ȡ��Ӧ�������꣨��ά��-�����ĵ���Ĭ�������ת������
Vec2d CCG2D2021xxxxxx����View::ViewPorttoWorld(const Vec2i& p)
{
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return Vec2d();
	return pDoc->ViewPorttoWorld(p);
}
Vec2d CCG2D2021xxxxxx����View::ViewPorttoWorld(const Vec2d& p)
{
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return Vec2d();
	return pDoc->ViewPorttoWorld(p);
}
Vec2i CCG2D2021xxxxxx����View::WorldtoViewPort(const Vec2d& p)
{
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return Vec2i();
	return pDoc->WorldtoViewPort(p);
}

//����ѡ�����ʰȡ����ɹ������滻ѡ�񼯣�����ʰȡ�Ķ���
CG2DRenderable* CCG2D2021xxxxxx����View::UpdatePicked(const Vec2d& p, double radius) //��ѡ
{
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc)
	{
		return pDoc->UpdatePicked(p, radius);
	}
	return nullptr;
}
CG2DRenderable* CCG2D2021xxxxxx����View::UpdatePicked(const ABox2d & box, bool inner/* = true*/) //��ѡ��������ѡ�У���
{
	CCG2D2021xxxxxx����Doc * pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc)
	{
		return pDoc->UpdatePicked(box, inner);
	}
	return nullptr;
}
//���ѡ�����ʰȡ����ɹ��������ѡ�񼯣�����ʰȡ�Ķ���
CG2DRenderable* CCG2D2021xxxxxx����View::AppendPicked(const Vec2d& p, double radius) //��ѡ
{
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc)
	{
		return pDoc->AppendPicked(p, radius);
	}
	return nullptr;
}
CG2DRenderable* CCG2D2021xxxxxx����View::AppendPicked(const ABox2d& box, bool inner/* = true*/) //��ѡ��������ѡ�У���
{
	CCG2D2021xxxxxx����Doc * pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc)
	{
		return pDoc->AppendPicked(box, inner);
	}
	return nullptr;
}

void CCG2D2021xxxxxx����View::OnPickOne()
{
	// TODO: �ڴ���������������
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	mCommand = new CG2DRenderablePickCommand(this);
}
void CCG2D2021xxxxxx����View::OnUpdatePickOne(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	//��ǰ�����Ƿ���ʰȡͼ�ζ���
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == static_cast<int>(CommandType::cmd2dPickRenderable));
}
void CCG2D2021xxxxxx����View::OnPickBox()
{
	// TODO: �ڴ���������������
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	mCommand = new CG2DRenderablePickInBoxCommand(this);
}
void CCG2D2021xxxxxx����View::OnUpdatePickBox(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	//��ǰ�����Ƿ���ʰȡͼ�ζ���
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == static_cast<int>(CommandType::cmd2dPickInBoxRenderable));
}

void CCG2D2021xxxxxx����View::OnTranslateMove()
{
	// TODO: �ڴ���������������
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	mCommand = new CG2DRenderableMoveCommand(this, pDoc);
}


void CCG2D2021xxxxxx����View::OnUpdateTranslateMove(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	//��ǰ�����Ƿ���ʰȡͼ�ζ���
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == static_cast<int>(CommandType::cmd2dMoveRenderable));
}


void CCG2D2021xxxxxx����View::OnTranslateRotate()
{
	// TODO: �ڴ���������������
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	mCommand = new CG2DRenderableRotateCommand(this, pDoc);
}


void CCG2D2021xxxxxx����View::OnUpdateTranslateRotate(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	//��ǰ�����Ƿ���ʰȡͼ�ζ���
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == static_cast<int>(CommandType::cmd2dRotateRenderable));
}


void CCG2D2021xxxxxx����View::OnTranslateLeft()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->Translate(-5, 0); //�ٶ�ÿ���ƶ�5����λ
		Invalidate(true);
		UpdateWindow();
	}
}
void CCG2D2021xxxxxx����View::OnTranslateRight()
{
	// TODO: �ڴ������������û����洦��������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->Translate(5, 0); //�ٶ�ÿ���ƶ�5����λ
		Invalidate(true);
		UpdateWindow();
	}
}
void CCG2D2021xxxxxx����View::OnTranslateUp()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->Translate(0, 5); //�ٶ�ÿ���ƶ�5����λ
		Invalidate(true);
		UpdateWindow();
	}
}
void CCG2D2021xxxxxx����View::OnTranslateDown()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->Translate(0, -5); //�ٶ�ÿ���ƶ�5����λ
		Invalidate(true);
		UpdateWindow();
	}
}

void CCG2D2021xxxxxx����View::OnTranslateZoomIn() //�Ŵ�
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->Scale(1.05, 1.05); //�ٶ�ÿ���ƶ�5����λ
		Invalidate(true);
		UpdateWindow();
	}
}

void CCG2D2021xxxxxx����View::OnTranslateZoomOut() //��С
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->Scale(0.95, 0.95); //�ٶ�ÿ���ƶ�5����λ
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG2D2021xxxxxx����View::OnTranslateSymX()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->MirrorXAxis(); //�ٶ�ÿ���ƶ�5����λ
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG2D2021xxxxxx����View::OnTranslateSymY()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->MirrorYAxis(); //�ٶ�ÿ���ƶ�5����λ
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG2D2021xxxxxx����View::OnTranslateSymO()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->MirrorOrigin(); //�ٶ�ÿ���ƶ�5����λ
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG2D2021xxxxxx����View::OnTranslateSymXy()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->MirrorYeqPosX(); //�ٶ�ÿ���ƶ�5����λ
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG2D2021xxxxxx����View::OnTranslateSymXny()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->MirrorYeNegPX(); //�ٶ�ÿ���ƶ�5����λ
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG2D2021xxxxxx����View::OnTranslateMisknipX()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->ShearXAxis(1.001); 
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG2D2021xxxxxx����View::OnTranslateMisknipY()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->ShearYAxis(1.001);
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG2D2021xxxxxx����View::OnTranslateMisknipXy()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->ShearXYAxis(1.001, 1.001);
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG2D2021xxxxxx����View::OnCameraDown()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->MoveCamera(0, -5); //�ٶ�ÿ���ƶ�5����λ
		Invalidate(true);
		//UpdateWindow();
	}
}


void CCG2D2021xxxxxx����View::OnCameraUp()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->MoveCamera(0, 5); //�ٶ�ÿ���ƶ�5����λ
		Invalidate(true);
		//UpdateWindow();
	}
}


void CCG2D2021xxxxxx����View::OnCameraRight()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->MoveCamera(5, 0); //�ٶ�ÿ���ƶ�5����λ
		Invalidate(true);
		//UpdateWindow();
	}
}


void CCG2D2021xxxxxx����View::OnCameraLeft()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->MoveCamera(-5, 0); //�ٶ�ÿ���ƶ�5����λ
		Invalidate(true);
		//UpdateWindow();
	}
}

//��ʱ����ת
void CCG2D2021xxxxxx����View::OnCounter()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->RotateCamera(3); //�ٶ�ÿ���ƶ�5����λ
		Invalidate(true);
		//UpdateWindow();u/asdas
	}
}

//˳ʱ����ת
void CCG2D2021xxxxxx����View::OnClockwise()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->RotateCamera(-3); //�ٶ�ÿ���ƶ�5����λ
		Invalidate(true);
		//UpdateWindow();
	}
}

//�������
void CCG2D2021xxxxxx����View::OnReset()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->ResetCamera(); //�ٶ�ÿ���ƶ�5����λ
		Invalidate(true);
		//UpdateWindow();
	}
}

void CCG2D2021xxxxxx����View::OnCameraFar()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->ZoomCamera(1.1);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx����View::OnCameraClose()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->ZoomCamera(10.0 / 11);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx����View::OnWindowLeftAdd()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraWindowOffset(5, 0, 0, 0);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx����View::OnWindowLeftDecrease()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraWindowOffset(-5, 0, 0, 0);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx����View::OnWindowRightAdd()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraWindowOffset(0, 0, 5, 0);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx����View::OnWindowRightDecrease()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraWindowOffset(0, 0, -5, 0);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx����View::OnWindowBottomAdd()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraWindowOffset(0, 5, 0, 0);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx����View::OnWindowTopAdd()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraWindowOffset(0, 0, 0, 5);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx����View::OnWindowTopDecrease()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraWindowOffset(0, 0, 0, -5);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx����View::OnWindowReduce()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraWindowOffset(10, 10, -10, -10);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx����View::OnWindowExpand()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraWindowOffset(-10, -10, 10, 10);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx����View::OnWindowBottomDecrease()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraWindowOffset(0, -5, 0, 0);
		Invalidate(true);
	}
}

void CCG2D2021xxxxxx����View::OnViewpointLeftAdd()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraViewportOffset(10, 0, 0, 0);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx����View::OnViewpointLeftDecrease()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraViewportOffset(-10, 0, 0, 0);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx����View::OnViewpointRightAdd()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraViewportOffset(0, 0, 10, 0);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx����View::OnViewpointRightDecrease()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraViewportOffset(0, 0, -10, 0);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx����View::OnViewpointBottomAdd()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraViewportOffset(0, 0, 0, -10);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx����View::OnViewpointBottomDecrease()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraViewportOffset(0, 0, 0, 10);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx����View::OnViewpointTopAdd()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraViewportOffset(0, -10, 0, 0);
		Invalidate(true);
	}
}



void CCG2D2021xxxxxx����View::OnViewpointTopDecrease()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraViewportOffset(0, 10, 0, 0);
		Invalidate(true);
	}
}

void CCG2D2021xxxxxx����View::OnViewpointReset()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraViewportReset();
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx����View::OnWindowReset()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->WindowReset();
		Invalidate(true);
	}
}

void CCG2D2021xxxxxx����View::OnCameraMove()
{
	// TODO: �ڴ���������������
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	mCommand = new CG2DCameraMoveCommand(this); //��������ֱ�߶ε��������
}


void CCG2D2021xxxxxx����View::OnUpdateCameraMove(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == static_cast<int>(CommandType::cmd2dCameraMove));
}


void CCG2D2021xxxxxx����View::OnWindowBox()
{
	// TODO: �ڴ���������������
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	mCommand = new CG2DWindowBoxCommand(this); //��������ֱ�߶ε��������
}


void CCG2D2021xxxxxx����View::OnUpdateWindowBox(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == static_cast<int>(CommandType::cmd2dWindowBox));
}

void CCG2D2021xxxxxx����View::CameraMoveOffset(double dx, double dy) 
{
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->MoveCamera(dx, dy); 
		Invalidate(true); //ʵʱ��ʾ
	}
}

void CCG2D2021xxxxxx����View::CameraWindowSet(double left, double bottom, double right, double top)
{
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraWindowSet(left, bottom, right, top);
		Invalidate(true); //ʵʱ��ʾ
	}
}

void CCG2D2021xxxxxx����View::OnWindowOverall()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraWindowOverall(); 
		Invalidate(true); //ʵʱ��ʾ
	}
}


void CCG2D2021xxxxxx����View::OnAspectRatio()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraAspectRatio(); //�ٶ�ÿ���ƶ�5����λ
		Invalidate(true); //ʵʱ��ʾ
	}
}


void CCG2D2021xxxxxx����View::OnRemoveAll()
{
	// TODO: �ڴ���������������
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->clearScene(); //�ٶ�ÿ���ƶ�5����λ
		Invalidate(true); //ʵʱ��ʾ
	}
}


void CCG2D2021xxxxxx����View::OnBtnTimer1()
{
	// TODO: �ڴ��������������� 
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

void CCG2D2021xxxxxx����View::OnUpdateBtnTimer1(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦�������� 
	pCmdUI->SetCheck(mAnimateTimer != 0);
}


void CCG2D2021xxxxxx����View::OnBtnFireworks()
{
	CCG2D2021xxxxxx����Doc* pDoc = GetDocument();
	if (pDoc)
	{
		CG2DLineSegment* pLine = new CG2DLineSegment(Vec2d(0,0), Vec2d(0,0));
		pLine->setPenColor(RGB(0, 0, 0));
		pLine->setPenWidth(10000);
		//pLine->setPenStyle(view->PenStyle());
		addRenderable(pLine); //�����ɹ�����ӵ�����
		pDoc->OnBtnFireworks(); //�ٶ�ÿ���ƶ�5����λ
	}
}
