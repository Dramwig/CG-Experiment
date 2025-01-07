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

// CG3D2021xxxxxx名字Doc.cpp: CCG3D2021xxxxxx名字Doc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CG3D2021xxxxxx名字.h"
#endif

#include "CG3D2021xxxxxx名字Doc.h"
#include <propkey.h>
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
#include "CG3DRubiksCube.h"
#include "CG3DSphere.h"
#include "CG3DCone.h"
#include "CG3DCylinder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCG3D2021xxxxxx名字Doc

IMPLEMENT_DYNCREATE(CCG3D2021xxxxxx名字Doc, CDocument)

BEGIN_MESSAGE_MAP(CCG3D2021xxxxxx名字Doc, CDocument)
	ON_UPDATE_COMMAND_UI(ID_PEN_COLOR, &CCG3D2021xxxxxx名字Doc::OnUpdatePenColor)
	ON_UPDATE_COMMAND_UI(ID_PEN_WIDTH, &CCG3D2021xxxxxx名字Doc::OnUpdatePenWidth)
	ON_UPDATE_COMMAND_UI(ID_PEN_STYLE, &CCG3D2021xxxxxx名字Doc::OnUpdatePenStyle)
	ON_UPDATE_COMMAND_UI(ID_PEN_FILL, &CCG3D2021xxxxxx名字Doc::OnUpdatePenFill)
	ON_UPDATE_COMMAND_UI(ID_ROTATE, &CCG3D2021xxxxxx名字Doc::OnUpdateRotate)
	ON_COMMAND(ID_UP_ROTATE_POS, &CCG3D2021xxxxxx名字Doc::OnUpRotatePos)
	ON_COMMAND(ID_UP_ROTATE_NEG, &CCG3D2021xxxxxx名字Doc::OnUpRotateNeg)
	ON_COMMAND(ID_RIGHT_ROTATE_POS, &CCG3D2021xxxxxx名字Doc::OnRightRotatePos)
	ON_COMMAND(ID_RIGHT_ROTATE_NEG, &CCG3D2021xxxxxx名字Doc::OnRightRotateNeg)
	ON_COMMAND(ID_FRONT_ROTATE_POS, &CCG3D2021xxxxxx名字Doc::OnFrontRotatePos)
	ON_COMMAND(ID_FRONT_ROTATE_NEG, &CCG3D2021xxxxxx名字Doc::OnFrontRotateNeg)
	ON_COMMAND(ID_LEFT_ROTATE_POS, &CCG3D2021xxxxxx名字Doc::OnLeftRotatePos)
	ON_COMMAND(ID_LEFT_ROTATE_NEG, &CCG3D2021xxxxxx名字Doc::OnLeftRotateNeg)
	ON_COMMAND(ID_BACK_ROTATE_POS, &CCG3D2021xxxxxx名字Doc::OnBackRotatePos)
	ON_COMMAND(ID_BACK_ROTATE_NEG, &CCG3D2021xxxxxx名字Doc::OnBackRotateNeg)
	ON_COMMAND(ID_DOWN_ROTATE_POS, &CCG3D2021xxxxxx名字Doc::OnDownRotatePos)
	ON_COMMAND(ID_DOWN_ROTATE_NEG, &CCG3D2021xxxxxx名字Doc::OnDownRotateNeg)
	ON_COMMAND(ID_LEFT_VIEW, &CCG3D2021xxxxxx名字Doc::OnLeftView)
	ON_COMMAND(ID_RIGHT_VIEW, &CCG3D2021xxxxxx名字Doc::OnRightView)
	ON_COMMAND(ID_FRONT_VIEW, &CCG3D2021xxxxxx名字Doc::OnFrontView)
	ON_COMMAND(ID_BACK_VIEW, &CCG3D2021xxxxxx名字Doc::OnBackView)
	ON_COMMAND(ID_CREATE_RubiksCube, &CCG3D2021xxxxxx名字Doc::OnCreateRubikscube)
	ON_COMMAND(ID_DOWN_VIEW, &CCG3D2021xxxxxx名字Doc::OnDownView)
	ON_COMMAND(ID_UP_VIEW, &CCG3D2021xxxxxx名字Doc::OnUpView)
	ON_COMMAND(ID_SUB_VIEW, &CCG3D2021xxxxxx名字Doc::OnSubView)
	ON_COMMAND(ID_WINDOWS_POS, &CCG3D2021xxxxxx名字Doc::OnWindowsPos)
	ON_COMMAND(ID_WINDOWS_NEG, &CCG3D2021xxxxxx名字Doc::OnWindowsNeg)
	ON_COMMAND(ID_INIT_SCENE, &CCG3D2021xxxxxx名字Doc::OnInitScene)
	ON_COMMAND(ID_REMOVE_LAST_LIGHT, &CCG3D2021xxxxxx名字Doc::OnRemoveLastLight)
	ON_COMMAND(ID_REMOVE_ALL_LIGHT, &CCG3D2021xxxxxx名字Doc::OnRemoveAllLight)
	ON_COMMAND(ID_INIT_LIGHT, &CCG3D2021xxxxxx名字Doc::OnInitLight)
	ON_UPDATE_COMMAND_UI(ID_MATERIAL_COLOR, &CCG3D2021xxxxxx名字Doc::OnUpdateMaterialColor)
	ON_UPDATE_COMMAND_UI(ID_BASE_MATERIAL, &CCG3D2021xxxxxx名字Doc::OnUpdateBaseMaterial)
	ON_COMMAND(ID_anime1, &CCG3D2021xxxxxx名字Doc::Onanime1)
END_MESSAGE_MAP()


bool Light0CallBack(CGRenderState* pRS)
{
	if (pRS != nullptr && pRS->IsKindOf(RUNTIME_CLASS(CGLight)))
	{
		//此处对pRS光源进行相关操作，如改变位置、颜色等效果。 
		CGLight* plight = dynamic_cast<CGLight*>(pRS);
		if (plight != nullptr)
		{
			//光源属性操作，实现光源动画 

			return true;
		}
	}
	return false;
}

// CCG3D2021xxxxxx名字Doc 构造/析构

CCG3D2021xxxxxx名字Doc::CCG3D2021xxxxxx名字Doc() noexcept
{
	// TODO: 在此添加一次性构造代码 
	mScene = new CG3DScene();
	mCameras.Add(new CG3DCamera());

	//以下是测试代码，测试成功要删除 
	//CG3DCube* cube = new CG3DCube(600);
	//cube->Rotate(45, 1, 1, 1); //绕直线(0,0,0)(1,1,1)旋转45度便于观察 
	//mScene->addRenderable(cube);

}

CCG3D2021xxxxxx名字Doc::~CCG3D2021xxxxxx名字Doc()
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

BOOL CCG3D2021xxxxxx名字Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CCG3D2021xxxxxx名字Doc 序列化

void CCG3D2021xxxxxx名字Doc::Serialize(CArchive& ar)
{
	mScene->Serialize(ar); //场景序列化 
	mCameras[0]->Serialize(ar); //相机序列化 
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
void CCG3D2021xxxxxx名字Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CCG3D2021xxxxxx名字Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CCG3D2021xxxxxx名字Doc::SetSearchContent(const CString& value)
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

// CCG3D2021xxxxxx名字Doc 诊断

#ifdef _DEBUG
void CCG3D2021xxxxxx名字Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCG3D2021xxxxxx名字Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCG3D2021xxxxxx名字Doc 命令

bool CCG3D2021xxxxxx名字Doc::addRenderable(CG3DRenderable* r)
{
	if (r && mScene && r->IsKindOf(RUNTIME_CLASS(CG3DRenderable)))
	{
		bool ret = mScene->addRenderable(r);
		UpdateAllViews(nullptr); //添加成功更新显示 
		return ret;
	}
	return false;
}

bool CCG3D2021xxxxxx名字Doc::delReaderable(CG3DRenderable* r)
{
	if (r && mScene && r->IsKindOf(RUNTIME_CLASS(CG3DRenderable)))
	{
		bool ret = mScene->delRenderable(r);
		UpdateAllViews(nullptr); //删除成功更新显示 
		return ret;
	}
	return false;
}

bool CCG3D2021xxxxxx名字Doc::RenderScene(CG3DRenderContext * pRC)
{
	if (pRC == nullptr)
		return false;
	int w, h;
	pRC->GetClientWidthHeight(w, h);
	if (w <= 0 && h <= 0)
		return false;

	CG3DCamera* pCamera = defaultCamera();
	if (pCamera == nullptr)
		return false;
	pCamera->SetClientWidth(w);
	pCamera->SetClientHeight(h);
	pCamera->viewport().set(0, 0, w, h);

	//+ 
	pRC->Lighting(true);
	pRC->Shading(true);
	pCamera->SetProjectionMode(0);
	//pCamera->SetProjectionMode(0); //透视投影（要修改相机的左右下上及近平面）

	pRC->Ready(pCamera);
	bool ret = mScene->Render(pRC, pCamera);
	pRC->Finish(pCamera);
	return ret;
}

void CCG3D2021xxxxxx名字Doc::OnUpdatePenColor(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}
void CCG3D2021xxxxxx名字Doc::OnUpdatePenWidth(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}
void CCG3D2021xxxxxx名字Doc::OnUpdatePenStyle(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}
void CCG3D2021xxxxxx名字Doc::OnUpdatePenFill(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}
void CCG3D2021xxxxxx名字Doc::AddRenderable(CG3DRenderable* R) {
	mScene->addRenderable(R);
}
void CCG3D2021xxxxxx名字Doc::RemoveAll()
{
	// TODO: 在此添加命令处理程序代码
	mScene->removeAllRenderable();
}
void CCG3D2021xxxxxx名字Doc::OnUpdateRotate(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}
void CCG3D2021xxxxxx名字Doc::OnUpRotatePos()
{
	// TODO: 在此添加命令处理程序代码
	mRubiksCube->UpRotate(true);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx名字Doc::OnUpRotateNeg()
{
	// TODO: 在此添加命令处理程序代码
	mRubiksCube->UpRotate(false);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx名字Doc::OnRightRotatePos()
{
	// TODO: 在此添加命令处理程序代码
	mRubiksCube->RightRotate(true);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx名字Doc::OnRightRotateNeg()
{
	// TODO: 在此添加命令处理程序代码
	mRubiksCube->RightRotate(false);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx名字Doc::OnFrontRotatePos()
{
	// TODO: 在此添加命令处理程序代码
	mRubiksCube->FrontRotate(true);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx名字Doc::OnFrontRotateNeg()
{
	// TODO: 在此添加命令处理程序代码
	mRubiksCube->FrontRotate(false);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx名字Doc::OnLeftRotatePos()
{
	// TODO: 在此添加命令处理程序代码
	mRubiksCube->LeftRotate(true);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx名字Doc::OnLeftRotateNeg()
{
	// TODO: 在此添加命令处理程序代码
	mRubiksCube->LeftRotate(false);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx名字Doc::OnBackRotatePos()
{
	// TODO: 在此添加命令处理程序代码
	mRubiksCube->BackRotate(true);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx名字Doc::OnBackRotateNeg()
{
	// TODO: 在此添加命令处理程序代码
	mRubiksCube->BackRotate(false);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx名字Doc::OnDownRotatePos()
{
	// TODO: 在此添加命令处理程序代码
	mRubiksCube->DownRotate(true);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx名字Doc::OnDownRotateNeg()
{
	// TODO: 在此添加命令处理程序代码
	mRubiksCube->DownRotate(false);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx名字Doc::OnCreateRubikscube()
{
	// TODO: 在此添加命令处理程序代码
	/*if(mRubiksCube)
		delete mRubiksCube;*/
	mRubiksCube = new CG3DRubiksCube(600);
	//mRubiksCube->Rotate(20, 1, 1, 1);
	mScene->addRenderable(mRubiksCube);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx名字Doc::OnLeftView()
{
	// TODO: 在此添加命令处理程序代码
	defaultCamera()->SetEye(-1000, 0, 0);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx名字Doc::OnRightView()
{
	// TODO: 在此添加命令处理程序代码
	defaultCamera()->SetEye(1000, 0, 0);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx名字Doc::OnFrontView()
{
	// TODO: 在此添加命令处理程序代码
	defaultCamera()->SetEye(0, 0, 1000);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx名字Doc::OnBackView()
{
	// TODO: 在此添加命令处理程序代码
	defaultCamera()->SetEye(0, 0, -1000);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx名字Doc::OnDownView()
{
	// TODO: 在此添加命令处理程序代码
	defaultCamera()->SetEye(0, 1000, 0.0001);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx名字Doc::OnUpView()
{
	// TODO: 在此添加命令处理程序代码
	defaultCamera()->SetEye(0, -1000, 0.0001);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx名字Doc::OnSubView()
{
	// TODO: 在此添加命令处理程序代码
	defaultCamera()->SetEye(1000/sqrt(3), 1000 / sqrt(3), 1000 / sqrt(3));
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx名字Doc::OnWindowsPos()
{
	// TODO: 在此添加命令处理程序代码
	defaultCamera()->Zoom(1.25);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx名字Doc::OnWindowsNeg()
{
	// TODO: 在此添加命令处理程序代码
	defaultCamera()->Zoom(0.8);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx名字Doc::OnInitScene()
{
	// TODO: 在此添加命令处理程序代码
	RemoveAll();
	//球体 
	sphere = new CG3DSphere(4);
	sphere->Translate(-10, 0, 0);
	mScene->addRenderable(sphere);
	//sphere->Appearance().Material().setColorMaterialEnabled(true);
	sphere->Appearance().Material().setMetallicMaterial();
	//sphere->Appearance().Material().setFlatColor(Vec4f(0.9f, 0.1f, 0.1f, 1.0f));
	sphere->PolygonMode().setFrontFace(EPolygonMode::PM_FILL);

	cone = new CG3DCone(4, 8);
	cone->Rotate(-90, 1, 0, 0);
	cone->Translate(0, -4, 0);
	mScene->addRenderable(cone);
	//cone->Appearance().Material().setColorMaterialEnabled(true);
	cone->Appearance().Material().setPlasticMaterial();
	//cone->Appearance().Material().setFlatColor(Vec4f(0.1f, 0.9f, 0.1f, 1.0f));
	cone->PolygonMode().setFrontFace(EPolygonMode::PM_FILL);

	cylinder = new CG3DCylinder(4, 8);
	cylinder->Rotate(-90, 1, 0, 0);
	cylinder->Translate(10, -4, 0);
	mScene->addRenderable(cylinder);
	//sphere->Appearance().Material().setColorMaterialEnabled(true);
	cylinder->Appearance().Material().setGlassMaterial();
	//cylinder->Appearance().Material().setFlatColor(Vec4f(0.0f, 0.1f, 0.9f, 1.0f));
	cylinder->PolygonMode().setFrontFace(EPolygonMode::PM_FILL);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx名字Doc::OnInitLight()
{
	// TODO: 在此添加命令处理程序代码
	// 光源
	CGLight* light0 = new CGLight();
	light0->setAsPointLight();
	mScene->AddLight(light0);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx名字Doc::OnRemoveLastLight()
{
	// TODO: 在此添加命令处理程序代码
	//AfxMessageBox(_T("1！"), MB_OK | MB_ICONINFORMATION);
	mScene->RemoveLastLight();
	//mScene->TimerCallback();
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx名字Doc::OnRemoveAllLight()
{
	// TODO: 在此添加命令处理程序代码
	//AfxMessageBox(_T("2！"), MB_OK | MB_ICONINFORMATION);
	mScene->RemoveAllLights();
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx名字Doc::OnUpdateMaterialColor(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}
void CCG3D2021xxxxxx名字Doc::OnUpdateBaseMaterial(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}

//动画定时回调（如果场景有更新需要重绘则返回true） 
bool CCG3D2021xxxxxx名字Doc::TimerCallback()
{
	if (cone) {
		cone->Rotate(1, 0, 1, 0);
		Vec3f a = cone->getPosition();
		mLight2->setPosition(cone->getPosition());
	}
	else
		return false;
	if (mLight) {
		int last = (mLightMark + 1) % 3;
		mLightRBG[mLightMark] += 0.1f;
		mLightRBG[last] -= 0.1f;
		if (mLightRBG[mLightMark] >= 1) {
			mLightRBG[mLightMark] = 1;
			mLightRBG[last] = 0;
			mLightMark = (mLightMark + 1) % 3;
		}
		mLight->setDiffuse(mLightRBG);
	}
	else
		return false;
	//return mScene->TimerCallback();
	
	return true;
}

void CCG3D2021xxxxxx名字Doc::Onanime1()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: 在此添加命令处理程序代码
	RemoveAll();
	OnRemoveAllLight();
	//球体 
	sphere = new CG3DSphere(4);
	sphere->Translate(0, 0, 0);
	mScene->addRenderable(sphere);
	sphere->Appearance().Material().setMetallicMaterial();
	sphere->PolygonMode().setFrontFace(EPolygonMode::PM_FILL);

	cone = new CG3DCone(4, 8);
	cone->Rotate(-90, 1, 0, 0);
	cone->Translate(10, -4, 0);
	mScene->addRenderable(cone);
	cone->Appearance().Material().setPlasticMaterial();
	cone->PolygonMode().setFrontFace(EPolygonMode::PM_FILL);

	mLight = new CGLight();
	mLight->setAsSpotLight();
	mLight->setPosition(Vec3f(0, 10, 0));
	mLight->setSpotlightParameters(Vec3f(0, -1, 0), 5, 55);
	mLight->setDiffuse(Vec4f(1, 1, 0, 1));
	mLightRBG = Vec4f(1.0f, 1.0f, 0.0f, 1.0f);
	mLightMark = 2;
	mScene->AddLight(mLight);

	mLight2 = new CGLight();
	mLight2->setAsPointLight();
	mLight2->setPosition(Vec3f(10, -4, 0));
	mScene->AddLight(mLight2);

	UpdateAllViews(nullptr);
}
