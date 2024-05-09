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

// CG2D2021113163王梓翕Doc.cpp: CCG2D2021113163王梓翕Doc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CG2D2021113163王梓翕.h"
#endif

#include "CG2D2021113163王梓翕Doc.h"
#include "CG2DLineSegment.h"
#include "CG2DRay.h"
#include "CG2DLine.h"
#include "CG2DPolyline.h"
#include "CG2DArc.h"
#include "CG2DCircle.h"
#include "CG2DEllipse.h"
#include "CG2DPolygon.h"
#include <propkey.h>
#include "AABBox2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCG2D2021113163王梓翕Doc

IMPLEMENT_DYNCREATE(CCG2D2021113163王梓翕Doc, CDocument)

BEGIN_MESSAGE_MAP(CCG2D2021113163王梓翕Doc, CDocument)
	ON_UPDATE_COMMAND_UI(ID_PEN_COLOR, &CCG2D2021113163王梓翕Doc::OnUpdatePenColor)
	ON_UPDATE_COMMAND_UI(ID_PEN_WIDTH, &CCG2D2021113163王梓翕Doc::OnUpdatePenWidth)
	ON_UPDATE_COMMAND_UI(ID_PEN_STYLE, &CCG2D2021113163王梓翕Doc::OnUpdatePenStyle)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_COLOR, &CCG2D2021113163王梓翕Doc::OnUpdateBrushColor)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_STYLE, &CCG2D2021113163王梓翕Doc::OnUpdateBrushStyle)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_HATCH, &CCG2D2021113163王梓翕Doc::OnUpdateBrushHatch)
	ON_UPDATE_COMMAND_UI(ID_ALGOR_LINE, &CCG2D2021113163王梓翕Doc::OnUpdateAlgorLine)
	ON_UPDATE_COMMAND_UI(ID_ALGOR_CIRCLE, &CCG2D2021113163王梓翕Doc::OnUpdateAlgorCircle)
	ON_UPDATE_COMMAND_UI(ID_ALGOR_POLYGON, &CCG2D2021113163王梓翕Doc::OnUpdateAlgorPolygon)
	ON_UPDATE_COMMAND_UI(ID_ALGOR_SEEDFILL, &CCG2D2021113163王梓翕Doc::OnUpdateAlgorSeedfill)
	ON_UPDATE_COMMAND_UI(ID_BOUND_COLOR, &CCG2D2021113163王梓翕Doc::OnUpdateBoundColor)
	ON_UPDATE_COMMAND_UI(ID_INNER_COLOR, &CCG2D2021113163王梓翕Doc::OnUpdateInnerColor)
END_MESSAGE_MAP()

BOOL CCG2D2021113163王梓翕Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CCG2D2021113163王梓翕Doc 序列化

void CCG2D2021113163王梓翕Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CCG2D2021113163王梓翕Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CCG2D2021113163王梓翕Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CCG2D2021113163王梓翕Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCG2D2021113163王梓翕Doc 诊断

#ifdef _DEBUG
void CCG2D2021113163王梓翕Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCG2D2021113163王梓翕Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCG2D2021113163王梓翕Doc 命令

CCG2D2021113163王梓翕Doc::CCG2D2021113163王梓翕Doc() noexcept
{
	// TODO: 在此添加一次性构造代码
	mScene = new CG2DScene();
	mCameras.Add(new CG2DCamera());
	cameraViewportOffleft = 0;
	cameraViewportOffbottom = 0;
	cameraViewportOffright = 0;
	cameraViewportOfftop = 0;

	//// 测试添加直线段到场景（要包含"CG2DLineSegment.h"），测试完毕后删除。
	//mScene->addRenderable(new CG2DLineSegment(Vec2d(100, 100), Vec2d(500, 200)));
	//mScene->addRenderable(new CG2DRay(Vec2d(-100, -100), Vec2d(-10, -20)));
	//mScene->addRenderable(new CG2DLine(Vec2d(0, 0), Vec2d(200, 500)));

	//// 测试添加折线到场景中
	//CG2DPolyline* polyline = new CG2DPolyline();
	//polyline->addPoint(Vec2d(300, 300));
	//polyline->addPoint(Vec2d(400, 400));
	//polyline->addPoint(Vec2d(500, 300));
	//mScene->addRenderable(polyline);

	//// 添加测试圆弧、圆到场景中
	//mScene->addRenderable(new CG2DArc(Vec2d(300, 300), 100, 0, PI / 2 * 3));
	//mScene->addRenderable(new CG2DCircle(Vec2d(0, 0), 100));

	//// 测试添加多边形到场景中
	//CG2DPolygon* polygon = new CG2DPolygon();
	//polygon->addPoint(Vec2d(100, 100));
	//polygon->addPoint(Vec2d(200, 100));
	//polygon->addPoint(Vec2d(200, 200));
	//polygon->addPoint(Vec2d(100, 200));
	//mScene->addRenderable(polygon);

	//// 添加测试椭圆到场景中
	//mScene->addRenderable(new CG2DEllipse(Vec2d(0, 0), 100, 50));
}

CCG2D2021113163王梓翕Doc::~CCG2D2021113163王梓翕Doc()
{
	if (mScene)
		delete mScene;
	size_t cnt = mCameras.GetCount();
	for (size_t i = 0; i < cnt; i++)
	{
		delete mCameras[i];
	}
	mCameras.RemoveAll();
}
bool CCG2D2021113163王梓翕Doc::addRenderable(CG2DRenderable* r)
{
	if (r && mScene && r->IsKindOf(RUNTIME_CLASS(CG2DRenderable)))
	{
		bool ret = mScene->addRenderable(r);
		UpdateAllViews(nullptr); //添加成功更新显示
		return ret;
	}
	return false;
}
bool CCG2D2021113163王梓翕Doc::delReaderable(CG2DRenderable* r)
{
	if (r && mScene && r->IsKindOf(RUNTIME_CLASS(CG2DRenderable)))
	{
		bool ret = mScene->delRenderable(r);
		UpdateAllViews(nullptr); //删除成功更新显示
		return ret;
	}
	return false;
}
bool CCG2D2021113163王梓翕Doc::RenderScene(CG2DRenderContext* pRC)
{
	if (pRC == nullptr)
		return false;
	int w, h;
	pRC->GetClientWidthHeight(w, h);
	if (w <= 0 && h <= 0)
		return false;
	CG2DCamera* pCamera = defaultCamera();
	if (pCamera == nullptr)
		return false;
	pCamera->SetClientWidth(w);
	pCamera->SetClientHeight(h);
	pCamera->viewport().set(cameraViewportOffleft, 
		cameraViewportOffbottom, 
		w + cameraViewportOffright - cameraViewportOffleft,
		h + cameraViewportOfftop - cameraViewportOffbottom
	);
	pRC->Ready(pCamera);
	bool ret = mScene->Render(pRC, pCamera);
	pRC->Finish(pCamera);
	return ret;
}


// 实验3-2
void CCG2D2021113163王梓翕Doc::OnUpdatePenColor(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}


void CCG2D2021113163王梓翕Doc::OnUpdatePenWidth(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}


void CCG2D2021113163王梓翕Doc::OnUpdatePenStyle(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}


void CCG2D2021113163王梓翕Doc::OnUpdateBrushColor(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}


void CCG2D2021113163王梓翕Doc::OnUpdateBrushStyle(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}


void CCG2D2021113163王梓翕Doc::OnUpdateBrushHatch(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}


void CCG2D2021113163王梓翕Doc::OnUpdateAlgorLine(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}


void CCG2D2021113163王梓翕Doc::OnUpdateAlgorCircle(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}


void CCG2D2021113163王梓翕Doc::OnUpdateAlgorPolygon(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}


void CCG2D2021113163王梓翕Doc::OnUpdateAlgorSeedfill(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}


void CCG2D2021113163王梓翕Doc::OnUpdateBoundColor(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}


void CCG2D2021113163王梓翕Doc::OnUpdateInnerColor(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}

//根据视口坐标获取对应场景坐标（二维）-调用默认相机的转换函数
Vec2d CCG2D2021113163王梓翕Doc::ViewPorttoWorld(const Vec2i& p)
{
	return defaultCamera()->ViewPorttoWorld(p);
}

Vec2i CCG2D2021113163王梓翕Doc::WorldtoViewPort(const Vec2d& p)
{
	return defaultCamera()->WorldtoViewPort(p);
}

//更新选择（如果拾取对象成功，则替换选择集，返回拾取的对象）
CG2DRenderable* CCG2D2021113163王梓翕Doc::UpdatePicked(const Vec2d& p, double radius) //点选
{
	if (mScene)
	{
		CG2DRenderable* r = mScene->UpdatePicked(p, radius);
		if (r)
		{
			UpdateAllViews(nullptr);
		}
		return r;
	}
	return nullptr;
}
CG2DRenderable* CCG2D2021113163王梓翕Doc::UpdatePicked(const ABox2d& box, bool inner/* = true*/) //框选（包含才选中？）
{
	if (mScene)
	{
		CG2DRenderable* r = mScene->UpdatePicked(box, inner);
		if (r)
		{
			UpdateAllViews(nullptr);
		}
		return r;
	}
	return nullptr;
}
//添加选择（如果拾取对象成功，则加入选择集，返回拾取的对象）
CG2DRenderable* CCG2D2021113163王梓翕Doc::AppendPicked(const Vec2d& p, double radius) //点选
{
	if (mScene)
	{
		CG2DRenderable* r = mScene->AppendPicked(p, radius);
		if (r)
		{
			UpdateAllViews(nullptr);
		}
		return r;
	}
	return nullptr;
}
CG2DRenderable* CCG2D2021113163王梓翕Doc::AppendPicked(const ABox2d& box, bool inner/* = true*/) //框选（包含才选中？）
{
	if (mScene)
	{
		CG2DRenderable* r = mScene->AppendPicked(box, inner);
		if (r)
		{
			UpdateAllViews(nullptr);
		}
		return r;
	}
	return nullptr;
}
bool CCG2D2021113163王梓翕Doc::UnselectAll() //撤销所有对象选中状态
{
	if (mScene && mScene->UnselectAll())
		UpdateAllViews(nullptr);
	return false;
}
//二维图形对象的几何变换（针对选择集中的对象）
bool CCG2D2021113163王梓翕Doc::Translate(double tx, double ty) //平移
{
	if (mScene && mScene->Translate(tx, ty))
	{
		return true;
	}
	return false;
}
bool CCG2D2021113163王梓翕Doc::Rotate(double angle, double cx, double cy) //旋转（逆时针为=正，度）
{
	if (mScene && mScene->Rotate(angle, cx, cy))
	{
		return true;
	}
	return false;
}
bool CCG2D2021113163王梓翕Doc::Scale(double sx, double sy) //缩放
{
	if (mScene && mScene->Scale(sx, sy))
	{
		return true;
	}
	return false;
}
bool CCG2D2021113163王梓翕Doc::Scale(double sx, double sy, double cx, double cy) //缩放（关于指定参考点缩放）
{
	if (mScene && mScene->Scale(sx, sy, cx, cy))
	{
		return true;
	}
	return false;
}
bool CCG2D2021113163王梓翕Doc::MirrorXAxis() //关于X轴对称（二维、三维）
{
	if (mScene && mScene->MirrorXAxis())
	{
		return true;
	}
	return false;
}
bool CCG2D2021113163王梓翕Doc::MirrorYAxis() //关于Y轴对称（二维、三维）
{
	if (mScene && mScene->MirrorYAxis())
	{
		return true;
	}
	return false;
}
bool CCG2D2021113163王梓翕Doc::MirrorYeqPosX()//关于y=x对称（二维、三维）
{
	if (mScene && mScene->MirrorYeqPosX())
	{
		return true;
	}
	return false;
}
bool CCG2D2021113163王梓翕Doc::MirrorYeNegPX()//关于y=-x对称（二维、三维）
{
	if (mScene && mScene->MirrorYeNegPX())
	{
		return true;
	}
	return false;
}
bool CCG2D2021113163王梓翕Doc::MirrorOrigin() //关于原点对称（二维、三维）
{
	if (mScene && mScene->MirrorOrigin())
	{
		return true;
	}
	return false;
}
bool CCG2D2021113163王梓翕Doc::Mirror(const Vec2d& vs, const Vec2d& ve) //关于线段se对称（二维、三维）
{
	if (mScene && mScene->Mirror(vs, ve))
	{
		return true;
	}
	return false;
}
bool CCG2D2021113163王梓翕Doc::ShearXAxis(double shx) //沿X轴错切
{
	if (mScene && mScene->ShearXAxis(shx))
	{
		return true;
	}
	return false;
}
bool CCG2D2021113163王梓翕Doc::ShearYAxis(double shy) //沿Y轴错切
{
	if (mScene && mScene->ShearYAxis(shy))
	{
		return true;
	}
	return false;
}
bool CCG2D2021113163王梓翕Doc::ShearXYAxis(double shx, double shy) //沿X、Y轴错切
{
	if (mScene && mScene->ShearXYAxis(shx, shy))
	{
		return true;
	}
	return false;
}
bool CCG2D2021113163王梓翕Doc::Transform(const Mat3d & mat) //几何变换（左乘给定矩阵）
{
	if (mScene && mScene->Transform(mat))
	{
		return true;
	}
	return false;
}
//默认相机的观察坐标系
void CCG2D2021113163王梓翕Doc::MoveCamera(double tx, double ty) //平移相机（观察坐标系）
{
	CG2DCamera* pCamera = defaultCamera();
	if (pCamera != nullptr)
	{
		pCamera->Move(tx, ty);
	}
}
void CCG2D2021113163王梓翕Doc::RotateCamera(double degree) //转动相机（观察坐标系）
{
	CG2DCamera* pCamera = defaultCamera();
	if (pCamera != nullptr)
	{
		pCamera->Rotate(degree);
	}
}
void CCG2D2021113163王梓翕Doc::ResetCamera() //重置相机到默认参数（观察坐标系）
{
	CG2DCamera* pCamera = defaultCamera();
	if (pCamera != nullptr)
	{
		pCamera->Reset();
	}
}
//默认相机的观察窗口
void CCG2D2021113163王梓翕Doc::ZoomCamera(const Vec2d& lb, const Vec2d& rt) //观察窗口左下角、右上角
{
	CG2DCamera* pCamera = defaultCamera();
	if (pCamera != nullptr)
	{
		pCamera->Zoom(lb, rt);
	}
}
void CCG2D2021113163王梓翕Doc::ZoomCamera(double ratio) //给定观察窗口的缩放比例（）
{
	CG2DCamera* pCamera = defaultCamera();
	if (pCamera != nullptr)
	{
		pCamera->Zoom(ratio);
	}
}
void CCG2D2021113163王梓翕Doc::CameraShowAll() //显示全部场景
{
	CG2DCamera* pCamera = defaultCamera();
	if (pCamera != nullptr)
	{
		if (mScene)
		{
			ABox2d box = mScene->BoundingABox();
			if (box.isNull())
			{
			}
			else
			{
				pCamera->Zoom(box.minCorner(), box.maxCorner());
			}
		}
	}
}
void CCG2D2021113163王梓翕Doc::CameraWindowOffset(double offleft, double offbottom, double offright, double offtop) //边界移动
{
	CG2DCamera* pCamera = defaultCamera();
	if (pCamera != nullptr)
	{
		pCamera->SetWindowLeft(pCamera->Left() + offleft);
		pCamera->SetWindowBottom(pCamera->Bottom() + offbottom);
		pCamera->SetWindowRight(pCamera->Right() + offright);
		pCamera->SetWindowTop(pCamera->Top() + offtop);
	}
}

void CCG2D2021113163王梓翕Doc::CameraWindowSet(double left, double bottom, double right, double top) //边界移动
{
	CG2DCamera* pCamera = defaultCamera();
	if (pCamera != nullptr)
	{
		pCamera->SetWindowLeft(left);
		pCamera->SetWindowBottom(bottom);
		pCamera->SetWindowRight(right);
		pCamera->SetWindowTop(top);
	}
}

void CCG2D2021113163王梓翕Doc::WindowReset()
{
	CG2DCamera* pCamera = defaultCamera();
	if (pCamera != nullptr)
	{
		CameraWindowSet(-1000, -1000, 1000, 1000);
	}
}

void CCG2D2021113163王梓翕Doc::CameraWindowOverall() 
{
	CG2DCamera* pCamera = defaultCamera();
	ABox2d box = mScene->BoundingABox();
	if (pCamera != nullptr)
		if (box.isNull()) {
			WindowReset();
		}
		else 
		{
			Vec2d lb = defaultCamera()->WCStoVCS(Vec2d(box.left(), box.bottom()));
			Vec2d lt = defaultCamera()->WCStoVCS(Vec2d(box.left(), box.top()));
			Vec2d rt = defaultCamera()->WCStoVCS(Vec2d(box.right(), box.top()));
			Vec2d rb = defaultCamera()->WCStoVCS(Vec2d(box.right(), box.bottom()));
			double left = std::min({ lb.x(), lt.x(), rt.x(), rb.x() });
			double bottom = std::min({ lb.y(), lt.y(), rt.y(), rb.y() });
			double right = std::max({ lb.x(), lt.x(), rt.x(), rb.x() });
			double top = std::max({ lb.y(), lt.y(), rt.y(), rb.y() });
			CameraWindowSet(left, bottom, right, top);
		}
}

//默认相机的视口（选作，自行补充）
void CCG2D2021113163王梓翕Doc::CameraViewportOffset(int offleft, int offbottom, int offright, int offtop) //边界移动
{
	CG2DCamera* pCamera = defaultCamera();
	if (pCamera != nullptr)
	{
		//pCamera->ViewportOffset(offleft, offbottom, offright, offtop);
	}
	cameraViewportOffleft+=offleft;
	cameraViewportOffbottom+=offbottom;
	cameraViewportOffright+=offright;
	cameraViewportOfftop+=offtop;
}

void CCG2D2021113163王梓翕Doc::CameraViewportReset()
{
	//CG2DCamera* pCamera = defaultCamera();
	cameraViewportOffleft = 0;
	cameraViewportOffbottom = 0;
	cameraViewportOffright = 0;
	cameraViewportOfftop = 0;
}

void CCG2D2021113163王梓翕Doc::CameraViewportSet(int width, int height)
{
	CG2DCamera* pCamera = defaultCamera();
	if (pCamera != nullptr)
	{
		pCamera->ViewportSet(width, height);
	}
}