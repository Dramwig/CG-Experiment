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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCG2D2021113163王梓翕Doc

IMPLEMENT_DYNCREATE(CCG2D2021113163王梓翕Doc, CDocument)

BEGIN_MESSAGE_MAP(CCG2D2021113163王梓翕Doc, CDocument)
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

	// 测试添加直线段到场景（要包含"CG2DLineSegment.h"），测试完毕后删除。
	mScene->addRenderable(new CG2DLineSegment(Vec2d(100, 100), Vec2d(500, 200)));
	mScene->addRenderable(new CG2DRay(Vec2d(-100, -100), Vec2d(-10, -20)));
	mScene->addRenderable(new CG2DLine(Vec2d(0, 0), Vec2d(200, 500)));

	// 测试添加折线到场景中
	CG2DPolyline* polyline = new CG2DPolyline();
	polyline->addPoint(Vec2d(300, 300));
	polyline->addPoint(Vec2d(400, 400));
	polyline->addPoint(Vec2d(500, 300));
	mScene->addRenderable(polyline);

	// 添加测试圆弧、圆到场景中
	mScene->addRenderable(new CG2DArc(Vec2d(300, 300), 100, 0, PI / 2 * 3));
	mScene->addRenderable(new CG2DCircle(Vec2d(0, 0), 100));

	// 测试添加多边形到场景中
	CG2DPolygon* polygon = new CG2DPolygon();
	polygon->addPoint(Vec2d(100, 100));
	polygon->addPoint(Vec2d(200, 100));
	polygon->addPoint(Vec2d(200, 200));
	polygon->addPoint(Vec2d(100, 200));
	mScene->addRenderable(polygon);

	// 添加测试椭圆到场景中
	mScene->addRenderable(new CG2DEllipse(Vec2d(0, 0), 100, 50));
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
		return ret;
	}
	return false;
}
bool CCG2D2021113163王梓翕Doc::delReaderable(CG2DRenderable* r)
{
	if (r && mScene && r->IsKindOf(RUNTIME_CLASS(CG2DRenderable)))
	{
		bool ret = mScene->delRenderable(r);
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
	pCamera->viewport().set(0, 0, w, h);
	pRC->Ready(pCamera);
	bool ret = mScene->Render(pRC, pCamera);
	pRC->Finish(pCamera);
	return ret;
}