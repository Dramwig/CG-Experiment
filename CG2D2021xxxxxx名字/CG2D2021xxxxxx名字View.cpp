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

// CG2D2021xxxxxx名字View.cpp: CCG2D2021xxxxxx名字View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CG2D2021xxxxxx名字.h"
#endif

#include "CG2D2021xxxxxx名字Doc.h"
#include "CG2D2021xxxxxx名字View.h"
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


// CCG2D2021xxxxxx名字View

IMPLEMENT_DYNCREATE(CCG2D2021xxxxxx名字View, CView)

BEGIN_MESSAGE_MAP(CCG2D2021xxxxxx名字View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_DRAW_CDC, &CCG2D2021xxxxxx名字View::OnDrawCDC)
	ON_COMMAND(ID_DRAW_POINT, &CCG2D2021xxxxxx名字View::OnDrawPoint)
	ON_COMMAND(ID_ALGORITHM_LINE, &CCG2D2021xxxxxx名字View::OnAlgorithmLine)
	ON_COMMAND(ID_ALGORITHM_CIRCLE, &CCG2D2021xxxxxx名字View::OnAlgorithmCircle)
	ON_COMMAND(ID_ALGORITHM_FILL, &CCG2D2021xxxxxx名字View::OnAlgorithmFill)
	ON_COMMAND(ID_ALGORITHM_TIMING, &CCG2D2021xxxxxx名字View::OnAlgorithmTiming)
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
	ON_COMMAND(ID_DRAW_LINESEGMENT, &CCG2D2021xxxxxx名字View::OnDrawLinesegment)
	ON_COMMAND(ID_DRAW_POLYLINE, &CCG2D2021xxxxxx名字View::OnDrawPolyline)
	ON_UPDATE_COMMAND_UI(ID_DRAW_LINESEGMENT, &CCG2D2021xxxxxx名字View::OnUpdateDrawLinesegment)
	ON_UPDATE_COMMAND_UI(ID_DRAW_POLYLINE, &CCG2D2021xxxxxx名字View::OnUpdateDrawPolyline)
	ON_COMMAND(ID_DRAW_POLYGON, &CCG2D2021xxxxxx名字View::OnDrawPolygon)
	ON_UPDATE_COMMAND_UI(ID_DRAW_POLYGON, &CCG2D2021xxxxxx名字View::OnUpdateDrawPolygon)
	ON_COMMAND(ID_DRAW_CIRCLE, &CCG2D2021xxxxxx名字View::OnDrawCircle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CIRCLE, &CCG2D2021xxxxxx名字View::OnUpdateDrawCircle)
	ON_COMMAND(ID_PICK_ONE, &CCG2D2021xxxxxx名字View::OnPickOne)
	ON_UPDATE_COMMAND_UI(ID_PICK_ONE, &CCG2D2021xxxxxx名字View::OnUpdatePickOne)
	ON_COMMAND(ID_TRANSLATE_LEFT, &CCG2D2021xxxxxx名字View::OnTranslateLeft)
	ON_COMMAND(ID_TRANSLATE_RIGHT, &CCG2D2021xxxxxx名字View::OnTranslateRight)
	ON_COMMAND(ID_TRANSLATE_UP, &CCG2D2021xxxxxx名字View::OnTranslateUp)
	ON_COMMAND(ID_TRANSLATE_DOWN, &CCG2D2021xxxxxx名字View::OnTranslateDown)
	ON_COMMAND(ID_PICK_BOX, &CCG2D2021xxxxxx名字View::OnPickBox)
	ON_UPDATE_COMMAND_UI(ID_PICK_BOX, &CCG2D2021xxxxxx名字View::OnUpdatePickBox)
	ON_COMMAND(ID_TRANSLATE_ZOOM_IN, &CCG2D2021xxxxxx名字View::OnTranslateZoomIn)
	ON_COMMAND(ID_TRANSLATE_ZOOM_OUT, &CCG2D2021xxxxxx名字View::OnTranslateZoomOut)
	ON_COMMAND(ID_TRANSLATE_SYM_X, &CCG2D2021xxxxxx名字View::OnTranslateSymX)
	ON_COMMAND(ID_TRANSLATE_SYM_Y, &CCG2D2021xxxxxx名字View::OnTranslateSymY)
	ON_COMMAND(ID_TRANSLATE_SYM_O, &CCG2D2021xxxxxx名字View::OnTranslateSymO)
	ON_COMMAND(ID_TRANSLATE_SYM_XY, &CCG2D2021xxxxxx名字View::OnTranslateSymXy)
	ON_COMMAND(ID_TRANSLATE_SYM_XnY, &CCG2D2021xxxxxx名字View::OnTranslateSymXny)
	ON_COMMAND(ID_TRANSLATE_MISKNIP_X, &CCG2D2021xxxxxx名字View::OnTranslateMisknipX)
	ON_COMMAND(ID_TRANSLATE_MISKNIP_Y, &CCG2D2021xxxxxx名字View::OnTranslateMisknipY)
	ON_COMMAND(ID_TRANSLATE_MISKNIP_XY, &CCG2D2021xxxxxx名字View::OnTranslateMisknipXy)
	ON_COMMAND(ID_TRANSLATE_MOVE, &CCG2D2021xxxxxx名字View::OnTranslateMove)
	ON_UPDATE_COMMAND_UI(ID_TRANSLATE_MOVE, &CCG2D2021xxxxxx名字View::OnUpdateTranslateMove)
	ON_COMMAND(ID_TRANSLATE_ROTATE, &CCG2D2021xxxxxx名字View::OnTranslateRotate)
	ON_UPDATE_COMMAND_UI(ID_TRANSLATE_ROTATE, &CCG2D2021xxxxxx名字View::OnUpdateTranslateRotate)
	ON_COMMAND(ID_CAMERA_LEFT, &CCG2D2021xxxxxx名字View::OnCameraLeft)
	ON_COMMAND(ID_CAMERA_RIGHT, &CCG2D2021xxxxxx名字View::OnCameraRight)
	ON_COMMAND(ID_CAMERA_UP, &CCG2D2021xxxxxx名字View::OnCameraUp)
	ON_COMMAND(ID_CAMERA_DOWN, &CCG2D2021xxxxxx名字View::OnCameraDown)
	ON_COMMAND(ID_CAMERA_FAR, &CCG2D2021xxxxxx名字View::OnCameraFar)
	ON_COMMAND(ID_CAMERA_CLOSE, &CCG2D2021xxxxxx名字View::OnCameraClose)
	ON_COMMAND(ROTATION_COUNTER, &CCG2D2021xxxxxx名字View::OnCounter)
	ON_COMMAND(ROTATION_CLOCKWISE, &CCG2D2021xxxxxx名字View::OnClockwise)
	ON_COMMAND(ROTATION_RESET, &CCG2D2021xxxxxx名字View::OnReset)
	ON_COMMAND(ID_Window_LEFT_ADD, &CCG2D2021xxxxxx名字View::OnWindowLeftAdd)
	ON_COMMAND(ID_WINDOW_LEFT_DECREASE, &CCG2D2021xxxxxx名字View::OnWindowLeftDecrease)
	ON_COMMAND(ID_WINDOW_RIGHT_ADD, &CCG2D2021xxxxxx名字View::OnWindowRightAdd)
	ON_COMMAND(ID_WINDOW_RIGHT_DECREASE, &CCG2D2021xxxxxx名字View::OnWindowRightDecrease)
	ON_COMMAND(ID_WINDOW_BOTTOM_ADD, &CCG2D2021xxxxxx名字View::OnWindowBottomAdd)
	ON_COMMAND(ID_WINDOW_BOTTOM_DECREASE, &CCG2D2021xxxxxx名字View::OnWindowBottomDecrease)
	ON_COMMAND(ID_WINDOW_TOP_ADD, &CCG2D2021xxxxxx名字View::OnWindowTopAdd)
	ON_COMMAND(ID_WINDOW_TOP_DECREASE, &CCG2D2021xxxxxx名字View::OnWindowTopDecrease)
	ON_COMMAND(ID_WINDOW_REDUCE, &CCG2D2021xxxxxx名字View::OnWindowReduce)
	ON_COMMAND(ID_WINDOW_EXPAND, &CCG2D2021xxxxxx名字View::OnWindowExpand)
	ON_COMMAND(ID_VIEWPOINT_LEFT_ADD, &CCG2D2021xxxxxx名字View::OnViewpointLeftAdd)
	ON_COMMAND(ID_VIEWPOINT_LEFT_DECREASE, &CCG2D2021xxxxxx名字View::OnViewpointLeftDecrease)
	ON_COMMAND(ID_VIEWPOINT_RIGHT_ADD, &CCG2D2021xxxxxx名字View::OnViewpointRightAdd)
	ON_COMMAND(ID_VIEWPOINT_RIGHT_DECREASE, &CCG2D2021xxxxxx名字View::OnViewpointRightDecrease)
	ON_COMMAND(ID_VIEWPOINT_BOTTOM_ADD, &CCG2D2021xxxxxx名字View::OnViewpointBottomAdd)
	ON_COMMAND(ID_VIEWPOINT_BOTTOM_DECREASE, &CCG2D2021xxxxxx名字View::OnViewpointBottomDecrease)
	ON_COMMAND(ID_VIEWPOINT_TOP_ADD, &CCG2D2021xxxxxx名字View::OnViewpointTopAdd)
	ON_COMMAND(ID_VIEWPOINT_TOP_DECREASE, &CCG2D2021xxxxxx名字View::OnViewpointTopDecrease)
	ON_COMMAND(ID_VIEWPOINT_RESET, &CCG2D2021xxxxxx名字View::OnViewpointReset)
	ON_COMMAND(ID_WINDOW_RESET, &CCG2D2021xxxxxx名字View::OnWindowReset)
	ON_COMMAND(ID_CAMERA_MOVE, &CCG2D2021xxxxxx名字View::OnCameraMove)
	ON_UPDATE_COMMAND_UI(ID_CAMERA_MOVE, &CCG2D2021xxxxxx名字View::OnUpdateCameraMove)
	ON_COMMAND(ID_WINDOW_BOX, &CCG2D2021xxxxxx名字View::OnWindowBox)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_BOX, &CCG2D2021xxxxxx名字View::OnUpdateWindowBox)
	ON_COMMAND(ID_WINDOW_OVERALL, &CCG2D2021xxxxxx名字View::OnWindowOverall)
	ON_COMMAND(ID_Aspect_Ratio, &CCG2D2021xxxxxx名字View::OnAspectRatio)
	ON_COMMAND(ID_REMOVE_ALL, &CCG2D2021xxxxxx名字View::OnRemoveAll)
	ON_COMMAND(ID_BTN_TIMER1, &CCG2D2021xxxxxx名字View::OnBtnTimer1)
	ON_UPDATE_COMMAND_UI(ID_BTN_TIMER1, &CCG2D2021xxxxxx名字View::OnUpdateBtnTimer1)
	ON_COMMAND(ID_BTN_FIREWORKS, &CCG2D2021xxxxxx名字View::OnBtnFireworks)
END_MESSAGE_MAP()

// CCG2D2021xxxxxx名字View 构造/析构

CCG2D2021xxxxxx名字View::CCG2D2021xxxxxx名字View() noexcept
{
	// TODO: 在此处添加构造代码

}

CCG2D2021xxxxxx名字View::~CCG2D2021xxxxxx名字View()
{
}

BOOL CCG2D2021xxxxxx名字View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CCG2D2021xxxxxx名字View 绘图

void GetDCSize(CDC* pDC, int& width, int& height)
{
	if (pDC == nullptr)
		return;

	CRect rect;
	CWnd* pWnd = pDC->GetWindow(); // 获取与CDC相关联的CWnd对象
	if (pWnd != nullptr)
	{
		pWnd->GetClientRect(&rect); // 获取客户区大小
		width = rect.Width();  // 客户区宽度
		height = rect.Height();  // 客户区高度
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

//画黑点
void DrawBlackDot(CDC* pDC, int centerX, int centerY, int radius = 5)
{
	// 设置画笔和画刷为黑色
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));  // 1像素宽的黑色画笔
	CBrush brush(RGB(0, 0, 0));  // 黑色画刷

	// 保存旧的画笔和画刷
	CPen* pOldPen = pDC->SelectObject(&pen);
	CBrush* pOldBrush = pDC->SelectObject(&brush);

	// 计算黑点的边界
	int left = centerX - radius;
	int top = centerY - radius;
	int right = centerX + radius;
	int bottom = centerY + radius;

	// 绘制黑点
	pDC->Ellipse(left, top, right, bottom);

	// 恢复旧的画笔和画刷
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

// 绘制一个指定颜色填充的圆形
void DrawFilledCircle(CDC* pDC, int x, int y, int radius, COLORREF fillColor) {
	ASSERT_VALID(pDC);  // 检查设备上下文的有效性
	if (!pDC)
		return;

	// 创建用于圆形轮廓的画笔，这里将填充色也用于轮廓
	CPen pen(PS_SOLID, 1, fillColor);
	CPen* pOldPen = pDC->SelectObject(&pen);  // 保存旧的画笔，并使用新画笔

	// 创建用于填充的画刷
	CBrush brush(fillColor);
	CBrush* pOldBrush = pDC->SelectObject(&brush);  // 保存旧的画刷，并使用新画刷

	// 绘制填充的圆形
	pDC->Ellipse(x - radius, y - radius, x + radius, y + radius);

	// 恢复之前的画笔和画刷
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}


//绘制圆环
void DrawArc(CDC* pDC, int x, int y, int r, int lineWide, COLORREF color)
{
	CRect rect(x - r, y - r, x + r, y + r);
	// 设置起点为矩形的右侧中点
	CPoint ptStart(x, y + r);
	// 设置终点为矩形的底部中点
	CPoint ptEnd(x, y - r);

	// 自定义画笔：使用函数参数定义的颜色和线宽
	CPen customPen(PS_SOLID, lineWide, color);

	// 保存当前画笔
	CPen* pOldPen = pDC->SelectObject(&customPen);

	// 使用自定义画笔绘制圆环的上半部分
	pDC->Arc(&rect, ptStart, ptEnd);
	// 绘制圆环的下半部分
	pDC->Arc(&rect, ptEnd, ptStart);

	// 恢复原来的画笔
	pDC->SelectObject(pOldPen);
}

// 绘制扇环
void DrawPie(CDC* pDC, int x, int y, int r, COLORREF color, double angle)
{
	CRect rect(x - r, y - r, x + r, y + r);

	// 扇环的起点始终是圆的顶部中点
	CPoint ptEnd(x, y - r);
	double M_PI = 3.141592653;

	// 根据角度计算扇环的终点
	double radAngle = angle * M_PI / 180.0; // 将角度转换为弧度
	CPoint ptStart(int(x + r * sin(radAngle)), int(y - r * cos(radAngle)));

	// 自定义画笔和画刷：使用函数参数定义的颜色
	CPen customPen(PS_SOLID, 1, color); // 线宽设为1以最小化外边缘轮廓的可见性
	CBrush customBrush(color); // 使用相同的颜色填充

	// 保存当前画笔和画刷
	CPen* pOldPen = pDC->SelectObject(&customPen);
	CBrush* pOldBrush = pDC->SelectObject(&customBrush);

	// 使用自定义画刷填充扇环
	pDC->Pie(&rect,ptStart, ptEnd);

	// 恢复原来的画笔和画刷
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}


// 绘制从圆心向外的线段
void DrawLineAtAngle(CDC* pDC, int x, int y, int r1, int r2, double angle, int lineWide, COLORREF color)
{
	double M_PI = 3.141592653;
	// 将角度从度转换为弧度
	double radAngle = angle * M_PI / 180.0;

	// 计算起点和终点
	CPoint ptStart(int(x + r1 * sin(radAngle)), int(y - r1 * cos(radAngle)));
	CPoint ptEnd(int(x + r2 * sin(radAngle)), int(y - r2 * cos(radAngle)));

	// 自定义画笔：使用函数参数定义的颜色和线宽
	CPen customPen(PS_SOLID, lineWide, color);

	// 保存当前画笔
	CPen* pOldPen = pDC->SelectObject(&customPen);

	// 绘制线段
	pDC->MoveTo(ptStart);
	pDC->LineTo(ptEnd);

	// 恢复原来的画笔
	pDC->SelectObject(pOldPen);
}


// 绘制一个指向特定方向的小三角形
void DrawTriangleAtAngle(CDC* pDC, int x, int y, int r, double angle, int lineWide, COLORREF color)
{
	double M_PI = 3.141592653;
	// 将角度从度转换为弧度
	double radAngle = angle * M_PI / 180.0;

	// 计算三角形的尖端坐标
	CPoint ptTip(int(x + r * sin(radAngle)), int(y - r * cos(radAngle)));

	// 计算三角形的其他两个顶点
	double sideAngle = 3.0 * M_PI / 180.0; // 30度的边角
	int sideLength = int(r * 0.9); // 侧边长度
	CPoint ptBase1(int(x + sideLength * sin(radAngle - sideAngle)), int(y - sideLength * cos(radAngle - sideAngle)));
	CPoint ptBase2(int(x + sideLength * sin(radAngle + sideAngle)), int(y - sideLength * cos(radAngle + sideAngle)));

	// 自定义画笔和画刷：使用函数参数定义的颜色
	CPen customPen(PS_SOLID, lineWide, color);
	CBrush customBrush(color);

	// 保存当前画笔和画刷
	CPen* pOldPen = pDC->SelectObject(&customPen);
	CBrush* pOldBrush = pDC->SelectObject(&customBrush);

	// 绘制三角形
	CPoint triangle[3] = { ptTip, ptBase1, ptBase2 };
	pDC->Polygon(triangle, 3);

	// 恢复原来的画笔和画刷
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

// 绘制指定大小和颜色的文本，以指定的中心点为中心
void DrawTextCentered(CDC* pDC, const CString& text, int center_x, int center_y, int fontSize, COLORREF color)
{
	// 创建并选择字体
	CFont font;
	font.CreatePointFont(fontSize * 10, _T("Arial"));
	CFont* pOldFont = pDC->SelectObject(&font);

	// 获取文本尺寸
	CSize textSize = pDC->GetTextExtent(text);

	// 计算文本矩形的左上角和右下角坐标
	CRect rect(center_x - textSize.cx / 2, center_y - textSize.cy / 2,
		center_x + textSize.cx / 2, center_y + textSize.cy / 2);

	// 设置文本颜色
	pDC->SetTextColor(color);

	// 设置背景模式为透明
	pDC->SetBkMode(TRANSPARENT);

	// 绘制文本
	pDC->DrawText(text, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	// 恢复原来的字体
	pDC->SelectObject(pOldFont);
}




void CCG2D2021xxxxxx名字View::OnDraw(CDC* pDC)
{
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->RenderScene(this);
	//Prompt(_T("OnDraw"));
}

void CCG2D2021xxxxxx名字View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCG2D2021xxxxxx名字View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCG2D2021xxxxxx名字View 诊断

#ifdef _DEBUG
void CCG2D2021xxxxxx名字View::AssertValid() const
{
	CView::AssertValid();
}

void CCG2D2021xxxxxx名字View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCG2D2021xxxxxx名字Doc* CCG2D2021xxxxxx名字View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCG2D2021xxxxxx名字Doc)));
	return (CCG2D2021xxxxxx名字Doc*)m_pDocument;
}
#endif //_DEBUG


// CCG2D2021xxxxxx名字View 消息处理程序

void CCG2D2021xxxxxx名字View::OnDrawCDC()
{
	CClientDC dc(this); //获取客户区绘制环境，CClientDC是CDC派生类
	CClientDC  *pDC = &dc;
	// 预设颜色
	COLORREF col_background = RGB(240, 240, 240);
	COLORREF col_inside_background = RGB(50, 50, 50);
	COLORREF col_outside_background = RGB(40, 40, 40);
	COLORREF col_progressbar = RGB(99, 141, 241);
	COLORREF col_outside_silhouettes = RGB(69, 69, 69); //外轮廓
	COLORREF col_inside_silhouettes = RGB(226, 226, 226); //内轮廓
	COLORREF col_white = RGB(250, 250, 250);
	COLORREF col_black = RGB(30, 30, 30);
	// 计算
	int width, height;
	GetDCSize(pDC, width, height); //获取客户区大小
	int centerX = width / 2;
	int centerY = height / 2;
	// 参数
	int outside_R = 500;
	int outside_W = 50;
	int inside_R = 370;
	int inside_W = 50;
	double angle = 360.0 / 100 * 88;
	double angle_line1 = 360.0 / 100 * 87.5;
	double angle_line2 = 65;
	// 绘制图形
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
	// 调用函数绘制文本
	DrawTextCentered(pDC, L"88.0", centerX, centerY, 100, col_white);
	DrawTextCentered(pDC, L"FLOW RATE", centerX, centerY - 170, 25, col_white);
	DrawTextCentered(pDC, L"LPM", centerX + 200, centerY + 150, 20, col_white);
	
}

void CCG2D2021xxxxxx名字View::OnDrawPoint()
{
	CClientDC dc(this); //获取客户区绘制环境，CClientDC是CDC派生类
	//绘制示例
	int width, height;
	GetDCSize(&dc, width, height); //获取客户区大小
	//每隔一定距离画一个点
	int interval = 100;
	for (int i = interval; i < width; i += interval)
	{
		for (int j = interval; j < height; j += interval)
		{
			DrawBlackDot(&dc, i, j);
		}
	}
}

void CCG2D2021xxxxxx名字View::EraseBkgnd() //使用背景色清除客户区背景
{
	CBrush backBrush(mBkgndColor);
	CClientDC dc(this);
	CBrush* pOldBrush = dc.SelectObject(&backBrush);
	CRect rect;
	dc.GetClipBox(&rect);
	dc.PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	dc.SelectObject(pOldBrush);
}
HWND CCG2D2021xxxxxx名字View::GetHWnd() const
{
	return GetSafeHwnd();
}
void CCG2D2021xxxxxx名字View::Ready(bool erasebkgnd) //每一次批量绘制前调用
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
void CCG2D2021xxxxxx名字View::Finish() //每一次批量绘制后调用（显示）
{
	if (!mReady || mMemHDC == nullptr)
		return;
	CRect rc;
	GetClientRect(&rc);
	::BitBlt(GetDC()->GetSafeHdc(), 0, 0, rc.Width(), rc.Height(), mMemHDC, 0, 0, SRCCOPY);
}

void CCG2D2021xxxxxx名字View::OnAlgorithmLine()
{
	Ready();

	const int sides = 12;
	const double radius = 100; // 十二边形的半径
	const double centerX = 100; // 十二边形中心的 x 坐标
	const double centerY = 100; // 十二边形中心的 y 坐标

	int x[25], y[25];

	for (int i = 0; i < sides; ++i) {
		double angle = 2 * PI * i / sides; // 计算每个角度
		x[i] = int(centerX + radius * cos(angle)); // 计算 x 坐标
		y[i] = int(centerY + radius * sin(angle)); // 计算 y 坐标
	}

	// 三种方法绘制十二边形
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


void CCG2D2021xxxxxx名字View::OnAlgorithmCircle()
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


void CCG2D2021xxxxxx名字View::OnAlgorithmFill()
{
	Ready();
	//绘制一个简单的多边形
	std::vector<CPoint> pnts;
	pnts.push_back(CPoint(100, 100));
	pnts.push_back(CPoint(200, 100));
	pnts.push_back(CPoint(200, 200));
	pnts.push_back(CPoint(100, 200));
	ScanLinePolygonFill(pnts, RGB(0, 255, 0));


	//绘制一个简单的多边形
	std::vector<CPoint> pnts2;
	pnts2.push_back(CPoint(300, 100));
	pnts2.push_back(CPoint(400, 100));
	pnts2.push_back(CPoint(450, 150));
	pnts2.push_back(CPoint(400, 200));
	pnts2.push_back(CPoint(300, 200));
	pnts2.push_back(CPoint(350, 150));
	ScanLinePolygonFill(pnts2, RGB(0, 0, 255));


	//绘制一个凹多边形
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


	//绘制一个凹多边形
	std::vector<CPoint> pnts5;
	pnts5.push_back(CPoint(700, 100));
	pnts5.push_back(CPoint(750, 150));
	pnts5.push_back(CPoint(800, 100));
	pnts5.push_back(CPoint(800, 200));
	pnts5.push_back(CPoint(700, 200));
	ScanLinePolygonFill(pnts5, RGB(255, 0, 255));

	// 绘制边线
	const int sides = 5;
	const double radius = 100; 
	const double centerX = 100; 
	const double centerY = 100;
	int x[25], y[25];
	for (int i = 0; i < sides; ++i) {
		double angle = 2 * PI * i / sides; // 计算每个角度
		x[i] = int(centerX + radius * cos(angle)); // 计算 x 坐标
		y[i] = int(centerY + radius * sin(angle)); // 计算 y 坐标
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

	// 种子填充算法
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


void CCG2D2021xxxxxx名字View::OnAlgorithmTiming()
{
	Ready(true);
	//随机生成一定数量的直线段的端点坐标：
	//自行补充坐标生成代码
	static const int VERTEXS = 20000;
	CPoint v[VERTEXS];
	srand((unsigned int)time(0));//初始化种子为随机值
	CRect rc;
	GetClientRect(&rc);
	for (int i = 0; i < VERTEXS; i++)
	{
		v[i].x = rand() % rc.Width();
		v[i].y = rand() % rc.Height();
	}
	//计时方法用到的函数： QueryPerformanceFrequency、QueryPerformanceCounter
	//自行补充计时代码
	//定义计时用的参数
	LARGE_INTEGER frequency, start, end; //计时
	double fitDDA, fitMID, fitBRE; //用时
	QueryPerformanceFrequency(&frequency);
	//DDA算法绘制并计时
	QueryPerformanceCounter(&start); //绘制前计时
	for (int i = 0; i < VERTEXS; i += 2)
	{
		DDALine(v[i].x, v[i].y, v[i + 1].x, v[i + 1].y, RGB(0, 0, 0));
	}
	QueryPerformanceCounter(&end); //绘制结束计时
	//算出持续时间
	fitDDA = (double)(end.QuadPart - start.QuadPart) / (double)frequency.QuadPart;
	//中点算法绘制并计时
	QueryPerformanceCounter(&start); //绘制前计时
	for (int i = 0; i < VERTEXS; i += 2)
	{
		MidPointLine(v[i].x, v[i].y, v[i + 1].x, v[i + 1].y, RGB(0, 0, 0));
	}
	QueryPerformanceCounter(&end); //绘制结束计时
	//算出持续时间
	fitMID = (double)(end.QuadPart - start.QuadPart) / (double)frequency.QuadPart;
	//Bresenham算法绘制并计时
	QueryPerformanceCounter(&start); //绘制前计时
	for (int i = 0; i < VERTEXS; i += 2)
	{
		BresenhamLine(v[i].x, v[i].y, v[i + 1].x, v[i + 1].y, RGB(0, 0, 0));
	}
	QueryPerformanceCounter(&end); //绘制结束计时
	//算出持续时间
	fitBRE = (double)(end.QuadPart - start.QuadPart) / (double)frequency.QuadPart;
	Finish();
	//显示各算法绘制的时间
	//自行补充代码
	CString strFitin;
	strFitin.Format(_T("DDALine：%.6f"), fitDDA);
	AfxMessageBox(strFitin);
	strFitin.Format(_T("MidPointLine：%.6f"), fitMID);
	AfxMessageBox(strFitin);
	strFitin.Format(_T("BresenhamLine：%.6f"), fitBRE);
	AfxMessageBox(strFitin);
}

//绘制客户区的宽度、高度（重写基类虚函数）
void CCG2D2021xxxxxx名字View::GetClientWidthHeight(int& w, int& h)
{
	CRect rc;
	GetClientRect(&rc);
	w = rc.Width();
	h = rc.Height();
}
void CCG2D2021xxxxxx名字View::Ready(CG2DCamera* camera) //每一次批量绘制前调用。生成填充视口背景，需要重新绘制图形。
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
void CCG2D2021xxxxxx名字View::Finish(CG2DCamera* camera) //每一次批量绘制后调用（显示）
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

// 实验3-2

//画笔属性
COLORREF CCG2D2021xxxxxx名字View::PenColor() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return RGB(0, 0, 0);
	return pMainWnd->PenColor();
}
int CCG2D2021xxxxxx名字View::PenWidth() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 1;
	return pMainWnd->PenWidth();
}
int CCG2D2021xxxxxx名字View::PenStyle() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return PS_SOLID;
	return pMainWnd->PenStyle();
}
//画刷属性
COLORREF CCG2D2021xxxxxx名字View::BrushColor() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return RGB(255, 255, 255);
	return pMainWnd->BrushColor();
}
int CCG2D2021xxxxxx名字View::BrushStyle() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 0;
	return pMainWnd->BrushStyle();
}
int CCG2D2021xxxxxx名字View::HatchStyle() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 0;
	return pMainWnd->HatchStyle();
}
//绘制算法
int CCG2D2021xxxxxx名字View::LineAlgorithm() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 0;
	return pMainWnd->LineAlgorithm();
}
int CCG2D2021xxxxxx名字View::CircleAlgorithm() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 0;
	return pMainWnd->CircleAlgorithm();
}
int CCG2D2021xxxxxx名字View::FillAlgorithm() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 0;
	return pMainWnd->FillAlgorithm();
}
int CCG2D2021xxxxxx名字View::SeedAlgorithm() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 0;
	return pMainWnd->SeedAlgorithm();
}
//点阵区域的边界颜色
COLORREF CCG2D2021xxxxxx名字View::BoundColor() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 0;
	return pMainWnd->BoundColor();
}
//点阵区域的内点颜色
COLORREF CCG2D2021xxxxxx名字View::FloodColor() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 0;
	return pMainWnd->FloodColor();
}
//状态栏上显示提示信息
void CCG2D2021xxxxxx名字View::Prompt(const CString& str)
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (pMainWnd != nullptr)
	{
		pMainWnd->ShowPrompt(str);
	}
}

void CCG2D2021xxxxxx名字View::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}


void CCG2D2021xxxxxx名字View::OnDestroy()
{
	__super::OnDestroy();

	// TODO: 在此处添加消息处理程序代码 
	if (mAnimateTimer != 0)
	{
		KillTimer(mAnimateTimer);
		mAnimateTimer = 0;
	}
}


void CCG2D2021xxxxxx名字View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nChar == VK_ESCAPE) //如果按下了ESC键，则中断当前的绘制命令（如果正在执行）
	{
		if (mCommand)
		{
			mCommand->Cancel();
			delete mCommand;
			mCommand = nullptr;
		}
		//TODO：如果有选中的图形对象，此处撤销拾取状态。
		else
		{
			CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
			ASSERT_VALID(pDoc);
			if (pDoc)
				pDoc->UnselectAll();
		}
	}
	if (mCommand) //命令模式，转发到对应命令对象去处理该事件
		mCommand->OnKeyDown(nChar, nRepCnt, nFlags);
	__super::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CCG2D2021xxxxxx名字View::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (mCommand) //命令模式，转发到对应命令对象去处理该事件
		mCommand->OnKeyUp(nChar, nRepCnt, nFlags);
	__super::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CCG2D2021xxxxxx名字View::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (mCommand) //命令模式，转发到对应命令对象去处理该事件
		mCommand->OnLButtonDblClk(nFlags, point);
	__super::OnLButtonDblClk(nFlags, point);
}


void CCG2D2021xxxxxx名字View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (mCommand) //命令模式，转发到对应命令对象去处理该事件
		mCommand->OnLButtonDown(nFlags, point);
	__super::OnLButtonDown(nFlags, point);
}


void CCG2D2021xxxxxx名字View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (mCommand) //命令模式，转发到对应命令对象去处理该事件
		mCommand->OnLButtonUp(nFlags, point);
	__super::OnLButtonUp(nFlags, point);
}


void CCG2D2021xxxxxx名字View::OnMButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (mCommand) //命令模式，转发到对应命令对象去处理该事件
		mCommand->OnMButtonDblClk(nFlags, point);
	__super::OnMButtonDblClk(nFlags, point);
}


void CCG2D2021xxxxxx名字View::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (mCommand) //命令模式，转发到对应命令对象去处理该事件
		mCommand->OnMButtonDown(nFlags, point);
	__super::OnMButtonDown(nFlags, point);
}


void CCG2D2021xxxxxx名字View::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (mCommand) //命令模式，转发到对应命令对象去处理该事件
		mCommand->OnMButtonUp(nFlags, point);
	__super::OnMButtonUp(nFlags, point);
}


void CCG2D2021xxxxxx名字View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//__super::OnMouseMove(nFlags, point);
	
		
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (pDoc != nullptr && pMainWnd != nullptr)
	{
		Vec2d v = pDoc->ViewPorttoWorld(Vec2i(point.x, point.y));
		CString str;
		str.Format(_T("视口坐标 ( %d, %d ) : 世界坐标 (%.2f , %.2f) "), point.x, point.y, v.x(),
			v.y());
		pMainWnd->ShowCoordOnStatusBar(str); //显示到状态栏
	}
	//命令模式，进行消息转发，进一步根据当前的命令状态处理鼠标移动事件
	if (mCommand)
		mCommand->OnMouseMove(nFlags, point);
	__super::OnMouseMove(nFlags, point);
	
}


BOOL CCG2D2021xxxxxx名字View::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (mCommand) //命令模式，转发到对应命令对象去处理该事件
		mCommand->OnMouseWheel(nFlags, zDelta, pt);
	return __super::OnMouseWheel(nFlags, zDelta, pt);
}


void CCG2D2021xxxxxx名字View::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (mCommand) //命令模式，转发到对应命令对象去处理该事件
		mCommand->OnRButtonDblClk(nFlags, point);
	__super::OnRButtonDblClk(nFlags, point);
}


void CCG2D2021xxxxxx名字View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (mCommand) //命令模式，转发到对应命令对象去处理该事件
		mCommand->OnRButtonDown(nFlags, point);
	__super::OnRButtonDown(nFlags, point);
}


void CCG2D2021xxxxxx名字View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值 
	if (mAnimateTimer == nIDEvent)
	{
		CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
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


void CCG2D2021xxxxxx名字View::OnDrawLinesegment()
{
	// TODO: 在此添加命令处理程序代码
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	mCommand = new CG2DLineSegmentCreateCommand(this); //创建绘制直线段的命令对象
}

void CCG2D2021xxxxxx名字View::OnUpdateDrawLinesegment(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	//当前命令是否是绘制直线段命令
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == static_cast<int>(CommandType::cmd2dLineSegment));
}

void CCG2D2021xxxxxx名字View::OnDrawPolyline()
{
	// TODO: 在此添加命令处理程序代码
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	mCommand = new CG2DPolylineCreateCommand(this);
}

void CCG2D2021xxxxxx名字View::OnUpdateDrawPolyline(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	//当前命令是否是绘制直线段命令
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == static_cast<int>(CommandType::cmd2dPolyline));
}

void CCG2D2021xxxxxx名字View::OnDrawPolygon()
{
	// TODO: 在此添加命令处理程序代码
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	mCommand = new CG2DPolygonCreateCommand(this);
}


void CCG2D2021xxxxxx名字View::OnUpdateDrawPolygon(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == static_cast<int>(CommandType::cmd2dPolygon));
}


void CCG2D2021xxxxxx名字View::OnDrawCircle()
{
	// TODO: 在此添加命令处理程序代码
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	mCommand = new CG2DCircleCenterRadiusCreateCommand(this);
}


void CCG2D2021xxxxxx名字View::OnUpdateDrawCircle(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == static_cast<int>(CommandType::cmd2dCircleCenterRadius));
}


//图形对象添加到场景
bool CCG2D2021xxxxxx名字View::addRenderable(CG2DRenderable* r)
{
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return false;
	bool ret = pDoc->addRenderable(r);
	// TODO：此处可以补充场景树的更新显示
	return ret;
}
bool CCG2D2021xxxxxx名字View::delReaderable(CG2DRenderable* r)
{
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return false;
	bool ret = pDoc->delReaderable(r);
	// TODO：此处可以补充场景树的更新显示
	return ret;
}
//根据视口坐标获取对应场景坐标（二维）-调用文档类默认相机的转换函数
Vec2d CCG2D2021xxxxxx名字View::ViewPorttoWorld(const Vec2i& p)
{
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return Vec2d();
	return pDoc->ViewPorttoWorld(p);
}
Vec2d CCG2D2021xxxxxx名字View::ViewPorttoWorld(const Vec2d& p)
{
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return Vec2d();
	return pDoc->ViewPorttoWorld(p);
}
Vec2i CCG2D2021xxxxxx名字View::WorldtoViewPort(const Vec2d& p)
{
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return Vec2i();
	return pDoc->WorldtoViewPort(p);
}

//更新选择（如果拾取对象成功，则替换选择集，返回拾取的对象）
CG2DRenderable* CCG2D2021xxxxxx名字View::UpdatePicked(const Vec2d& p, double radius) //点选
{
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc)
	{
		return pDoc->UpdatePicked(p, radius);
	}
	return nullptr;
}
CG2DRenderable* CCG2D2021xxxxxx名字View::UpdatePicked(const ABox2d & box, bool inner/* = true*/) //框选（包含才选中？）
{
	CCG2D2021xxxxxx名字Doc * pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc)
	{
		return pDoc->UpdatePicked(box, inner);
	}
	return nullptr;
}
//添加选择（如果拾取对象成功，则加入选择集，返回拾取的对象）
CG2DRenderable* CCG2D2021xxxxxx名字View::AppendPicked(const Vec2d& p, double radius) //点选
{
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc)
	{
		return pDoc->AppendPicked(p, radius);
	}
	return nullptr;
}
CG2DRenderable* CCG2D2021xxxxxx名字View::AppendPicked(const ABox2d& box, bool inner/* = true*/) //框选（包含才选中？）
{
	CCG2D2021xxxxxx名字Doc * pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc)
	{
		return pDoc->AppendPicked(box, inner);
	}
	return nullptr;
}

void CCG2D2021xxxxxx名字View::OnPickOne()
{
	// TODO: 在此添加命令处理程序代码
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	mCommand = new CG2DRenderablePickCommand(this);
}
void CCG2D2021xxxxxx名字View::OnUpdatePickOne(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	//当前命令是否是拾取图形对象
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == static_cast<int>(CommandType::cmd2dPickRenderable));
}
void CCG2D2021xxxxxx名字View::OnPickBox()
{
	// TODO: 在此添加命令处理程序代码
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	mCommand = new CG2DRenderablePickInBoxCommand(this);
}
void CCG2D2021xxxxxx名字View::OnUpdatePickBox(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	//当前命令是否是拾取图形对象
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == static_cast<int>(CommandType::cmd2dPickInBoxRenderable));
}

void CCG2D2021xxxxxx名字View::OnTranslateMove()
{
	// TODO: 在此添加命令处理程序代码
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	mCommand = new CG2DRenderableMoveCommand(this, pDoc);
}


void CCG2D2021xxxxxx名字View::OnUpdateTranslateMove(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	//当前命令是否是拾取图形对象
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == static_cast<int>(CommandType::cmd2dMoveRenderable));
}


void CCG2D2021xxxxxx名字View::OnTranslateRotate()
{
	// TODO: 在此添加命令处理程序代码
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	mCommand = new CG2DRenderableRotateCommand(this, pDoc);
}


void CCG2D2021xxxxxx名字View::OnUpdateTranslateRotate(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	//当前命令是否是拾取图形对象
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == static_cast<int>(CommandType::cmd2dRotateRenderable));
}


void CCG2D2021xxxxxx名字View::OnTranslateLeft()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->Translate(-5, 0); //假定每次移动5个单位
		Invalidate(true);
		UpdateWindow();
	}
}
void CCG2D2021xxxxxx名字View::OnTranslateRight()
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->Translate(5, 0); //假定每次移动5个单位
		Invalidate(true);
		UpdateWindow();
	}
}
void CCG2D2021xxxxxx名字View::OnTranslateUp()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->Translate(0, 5); //假定每次移动5个单位
		Invalidate(true);
		UpdateWindow();
	}
}
void CCG2D2021xxxxxx名字View::OnTranslateDown()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->Translate(0, -5); //假定每次移动5个单位
		Invalidate(true);
		UpdateWindow();
	}
}

void CCG2D2021xxxxxx名字View::OnTranslateZoomIn() //放大
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->Scale(1.05, 1.05); //假定每次移动5个单位
		Invalidate(true);
		UpdateWindow();
	}
}

void CCG2D2021xxxxxx名字View::OnTranslateZoomOut() //缩小
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->Scale(0.95, 0.95); //假定每次移动5个单位
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG2D2021xxxxxx名字View::OnTranslateSymX()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->MirrorXAxis(); //假定每次移动5个单位
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG2D2021xxxxxx名字View::OnTranslateSymY()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->MirrorYAxis(); //假定每次移动5个单位
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG2D2021xxxxxx名字View::OnTranslateSymO()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->MirrorOrigin(); //假定每次移动5个单位
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG2D2021xxxxxx名字View::OnTranslateSymXy()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->MirrorYeqPosX(); //假定每次移动5个单位
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG2D2021xxxxxx名字View::OnTranslateSymXny()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->MirrorYeNegPX(); //假定每次移动5个单位
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG2D2021xxxxxx名字View::OnTranslateMisknipX()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->ShearXAxis(1.001); 
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG2D2021xxxxxx名字View::OnTranslateMisknipY()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->ShearYAxis(1.001);
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG2D2021xxxxxx名字View::OnTranslateMisknipXy()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->ShearXYAxis(1.001, 1.001);
		Invalidate(true);
		UpdateWindow();
	}
}


void CCG2D2021xxxxxx名字View::OnCameraDown()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->MoveCamera(0, -5); //假定每次移动5个单位
		Invalidate(true);
		//UpdateWindow();
	}
}


void CCG2D2021xxxxxx名字View::OnCameraUp()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->MoveCamera(0, 5); //假定每次移动5个单位
		Invalidate(true);
		//UpdateWindow();
	}
}


void CCG2D2021xxxxxx名字View::OnCameraRight()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->MoveCamera(5, 0); //假定每次移动5个单位
		Invalidate(true);
		//UpdateWindow();
	}
}


void CCG2D2021xxxxxx名字View::OnCameraLeft()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->MoveCamera(-5, 0); //假定每次移动5个单位
		Invalidate(true);
		//UpdateWindow();
	}
}

//逆时针旋转
void CCG2D2021xxxxxx名字View::OnCounter()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->RotateCamera(3); //假定每次移动5个单位
		Invalidate(true);
		//UpdateWindow();u/asdas
	}
}

//顺时针旋转
void CCG2D2021xxxxxx名字View::OnClockwise()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->RotateCamera(-3); //假定每次移动5个单位
		Invalidate(true);
		//UpdateWindow();
	}
}

//重置相机
void CCG2D2021xxxxxx名字View::OnReset()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->ResetCamera(); //假定每次移动5个单位
		Invalidate(true);
		//UpdateWindow();
	}
}

void CCG2D2021xxxxxx名字View::OnCameraFar()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->ZoomCamera(1.1);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx名字View::OnCameraClose()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->ZoomCamera(10.0 / 11);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx名字View::OnWindowLeftAdd()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraWindowOffset(5, 0, 0, 0);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx名字View::OnWindowLeftDecrease()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraWindowOffset(-5, 0, 0, 0);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx名字View::OnWindowRightAdd()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraWindowOffset(0, 0, 5, 0);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx名字View::OnWindowRightDecrease()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraWindowOffset(0, 0, -5, 0);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx名字View::OnWindowBottomAdd()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraWindowOffset(0, 5, 0, 0);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx名字View::OnWindowTopAdd()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraWindowOffset(0, 0, 0, 5);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx名字View::OnWindowTopDecrease()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraWindowOffset(0, 0, 0, -5);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx名字View::OnWindowReduce()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraWindowOffset(10, 10, -10, -10);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx名字View::OnWindowExpand()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraWindowOffset(-10, -10, 10, 10);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx名字View::OnWindowBottomDecrease()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraWindowOffset(0, -5, 0, 0);
		Invalidate(true);
	}
}

void CCG2D2021xxxxxx名字View::OnViewpointLeftAdd()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraViewportOffset(10, 0, 0, 0);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx名字View::OnViewpointLeftDecrease()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraViewportOffset(-10, 0, 0, 0);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx名字View::OnViewpointRightAdd()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraViewportOffset(0, 0, 10, 0);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx名字View::OnViewpointRightDecrease()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraViewportOffset(0, 0, -10, 0);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx名字View::OnViewpointBottomAdd()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraViewportOffset(0, 0, 0, -10);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx名字View::OnViewpointBottomDecrease()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraViewportOffset(0, 0, 0, 10);
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx名字View::OnViewpointTopAdd()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraViewportOffset(0, -10, 0, 0);
		Invalidate(true);
	}
}



void CCG2D2021xxxxxx名字View::OnViewpointTopDecrease()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraViewportOffset(0, 10, 0, 0);
		Invalidate(true);
	}
}

void CCG2D2021xxxxxx名字View::OnViewpointReset()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraViewportReset();
		Invalidate(true);
	}
}


void CCG2D2021xxxxxx名字View::OnWindowReset()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->WindowReset();
		Invalidate(true);
	}
}

void CCG2D2021xxxxxx名字View::OnCameraMove()
{
	// TODO: 在此添加命令处理程序代码
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	mCommand = new CG2DCameraMoveCommand(this); //创建绘制直线段的命令对象
}


void CCG2D2021xxxxxx名字View::OnUpdateCameraMove(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == static_cast<int>(CommandType::cmd2dCameraMove));
}


void CCG2D2021xxxxxx名字View::OnWindowBox()
{
	// TODO: 在此添加命令处理程序代码
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	mCommand = new CG2DWindowBoxCommand(this); //创建绘制直线段的命令对象
}


void CCG2D2021xxxxxx名字View::OnUpdateWindowBox(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == static_cast<int>(CommandType::cmd2dWindowBox));
}

void CCG2D2021xxxxxx名字View::CameraMoveOffset(double dx, double dy) 
{
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->MoveCamera(dx, dy); 
		Invalidate(true); //实时显示
	}
}

void CCG2D2021xxxxxx名字View::CameraWindowSet(double left, double bottom, double right, double top)
{
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraWindowSet(left, bottom, right, top);
		Invalidate(true); //实时显示
	}
}

void CCG2D2021xxxxxx名字View::OnWindowOverall()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraWindowOverall(); 
		Invalidate(true); //实时显示
	}
}


void CCG2D2021xxxxxx名字View::OnAspectRatio()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->CameraAspectRatio(); //假定每次移动5个单位
		Invalidate(true); //实时显示
	}
}


void CCG2D2021xxxxxx名字View::OnRemoveAll()
{
	// TODO: 在此添加命令处理程序代码
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->clearScene(); //假定每次移动5个单位
		Invalidate(true); //实时显示
	}
}


void CCG2D2021xxxxxx名字View::OnBtnTimer1()
{
	// TODO: 在此添加命令处理程序代码 
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

void CCG2D2021xxxxxx名字View::OnUpdateBtnTimer1(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码 
	pCmdUI->SetCheck(mAnimateTimer != 0);
}


void CCG2D2021xxxxxx名字View::OnBtnFireworks()
{
	CCG2D2021xxxxxx名字Doc* pDoc = GetDocument();
	if (pDoc)
	{
		CG2DLineSegment* pLine = new CG2DLineSegment(Vec2d(0,0), Vec2d(0,0));
		pLine->setPenColor(RGB(0, 0, 0));
		pLine->setPenWidth(10000);
		//pLine->setPenStyle(view->PenStyle());
		addRenderable(pLine); //创建成功，添加到场景
		pDoc->OnBtnFireworks(); //假定每次移动5个单位
	}
}
