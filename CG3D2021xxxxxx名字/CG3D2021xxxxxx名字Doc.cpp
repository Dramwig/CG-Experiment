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

// CG3D2021xxxxxx����Doc.cpp: CCG3D2021xxxxxx����Doc ���ʵ��
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "CG3D2021xxxxxx����.h"
#endif

#include "CG3D2021xxxxxx����Doc.h"
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

// CCG3D2021xxxxxx����Doc

IMPLEMENT_DYNCREATE(CCG3D2021xxxxxx����Doc, CDocument)

BEGIN_MESSAGE_MAP(CCG3D2021xxxxxx����Doc, CDocument)
	ON_UPDATE_COMMAND_UI(ID_PEN_COLOR, &CCG3D2021xxxxxx����Doc::OnUpdatePenColor)
	ON_UPDATE_COMMAND_UI(ID_PEN_WIDTH, &CCG3D2021xxxxxx����Doc::OnUpdatePenWidth)
	ON_UPDATE_COMMAND_UI(ID_PEN_STYLE, &CCG3D2021xxxxxx����Doc::OnUpdatePenStyle)
	ON_UPDATE_COMMAND_UI(ID_PEN_FILL, &CCG3D2021xxxxxx����Doc::OnUpdatePenFill)
	ON_UPDATE_COMMAND_UI(ID_ROTATE, &CCG3D2021xxxxxx����Doc::OnUpdateRotate)
	ON_COMMAND(ID_UP_ROTATE_POS, &CCG3D2021xxxxxx����Doc::OnUpRotatePos)
	ON_COMMAND(ID_UP_ROTATE_NEG, &CCG3D2021xxxxxx����Doc::OnUpRotateNeg)
	ON_COMMAND(ID_RIGHT_ROTATE_POS, &CCG3D2021xxxxxx����Doc::OnRightRotatePos)
	ON_COMMAND(ID_RIGHT_ROTATE_NEG, &CCG3D2021xxxxxx����Doc::OnRightRotateNeg)
	ON_COMMAND(ID_FRONT_ROTATE_POS, &CCG3D2021xxxxxx����Doc::OnFrontRotatePos)
	ON_COMMAND(ID_FRONT_ROTATE_NEG, &CCG3D2021xxxxxx����Doc::OnFrontRotateNeg)
	ON_COMMAND(ID_LEFT_ROTATE_POS, &CCG3D2021xxxxxx����Doc::OnLeftRotatePos)
	ON_COMMAND(ID_LEFT_ROTATE_NEG, &CCG3D2021xxxxxx����Doc::OnLeftRotateNeg)
	ON_COMMAND(ID_BACK_ROTATE_POS, &CCG3D2021xxxxxx����Doc::OnBackRotatePos)
	ON_COMMAND(ID_BACK_ROTATE_NEG, &CCG3D2021xxxxxx����Doc::OnBackRotateNeg)
	ON_COMMAND(ID_DOWN_ROTATE_POS, &CCG3D2021xxxxxx����Doc::OnDownRotatePos)
	ON_COMMAND(ID_DOWN_ROTATE_NEG, &CCG3D2021xxxxxx����Doc::OnDownRotateNeg)
	ON_COMMAND(ID_LEFT_VIEW, &CCG3D2021xxxxxx����Doc::OnLeftView)
	ON_COMMAND(ID_RIGHT_VIEW, &CCG3D2021xxxxxx����Doc::OnRightView)
	ON_COMMAND(ID_FRONT_VIEW, &CCG3D2021xxxxxx����Doc::OnFrontView)
	ON_COMMAND(ID_BACK_VIEW, &CCG3D2021xxxxxx����Doc::OnBackView)
	ON_COMMAND(ID_CREATE_RubiksCube, &CCG3D2021xxxxxx����Doc::OnCreateRubikscube)
	ON_COMMAND(ID_DOWN_VIEW, &CCG3D2021xxxxxx����Doc::OnDownView)
	ON_COMMAND(ID_UP_VIEW, &CCG3D2021xxxxxx����Doc::OnUpView)
	ON_COMMAND(ID_SUB_VIEW, &CCG3D2021xxxxxx����Doc::OnSubView)
	ON_COMMAND(ID_WINDOWS_POS, &CCG3D2021xxxxxx����Doc::OnWindowsPos)
	ON_COMMAND(ID_WINDOWS_NEG, &CCG3D2021xxxxxx����Doc::OnWindowsNeg)
	ON_COMMAND(ID_INIT_SCENE, &CCG3D2021xxxxxx����Doc::OnInitScene)
	ON_COMMAND(ID_REMOVE_LAST_LIGHT, &CCG3D2021xxxxxx����Doc::OnRemoveLastLight)
	ON_COMMAND(ID_REMOVE_ALL_LIGHT, &CCG3D2021xxxxxx����Doc::OnRemoveAllLight)
	ON_COMMAND(ID_INIT_LIGHT, &CCG3D2021xxxxxx����Doc::OnInitLight)
	ON_UPDATE_COMMAND_UI(ID_MATERIAL_COLOR, &CCG3D2021xxxxxx����Doc::OnUpdateMaterialColor)
	ON_UPDATE_COMMAND_UI(ID_BASE_MATERIAL, &CCG3D2021xxxxxx����Doc::OnUpdateBaseMaterial)
	ON_COMMAND(ID_anime1, &CCG3D2021xxxxxx����Doc::Onanime1)
END_MESSAGE_MAP()


bool Light0CallBack(CGRenderState* pRS)
{
	if (pRS != nullptr && pRS->IsKindOf(RUNTIME_CLASS(CGLight)))
	{
		//�˴���pRS��Դ������ز�������ı�λ�á���ɫ��Ч���� 
		CGLight* plight = dynamic_cast<CGLight*>(pRS);
		if (plight != nullptr)
		{
			//��Դ���Բ�����ʵ�ֹ�Դ���� 

			return true;
		}
	}
	return false;
}

// CCG3D2021xxxxxx����Doc ����/����

CCG3D2021xxxxxx����Doc::CCG3D2021xxxxxx����Doc() noexcept
{
	// TODO: �ڴ����һ���Թ������ 
	mScene = new CG3DScene();
	mCameras.Add(new CG3DCamera());

	//�����ǲ��Դ��룬���Գɹ�Ҫɾ�� 
	//CG3DCube* cube = new CG3DCube(600);
	//cube->Rotate(45, 1, 1, 1); //��ֱ��(0,0,0)(1,1,1)��ת45�ȱ��ڹ۲� 
	//mScene->addRenderable(cube);

}

CCG3D2021xxxxxx����Doc::~CCG3D2021xxxxxx����Doc()
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

BOOL CCG3D2021xxxxxx����Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CCG3D2021xxxxxx����Doc ���л�

void CCG3D2021xxxxxx����Doc::Serialize(CArchive& ar)
{
	mScene->Serialize(ar); //�������л� 
	mCameras[0]->Serialize(ar); //������л� 
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢���� 
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش��� 
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CCG3D2021xxxxxx����Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CCG3D2021xxxxxx����Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CCG3D2021xxxxxx����Doc::SetSearchContent(const CString& value)
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

// CCG3D2021xxxxxx����Doc ���

#ifdef _DEBUG
void CCG3D2021xxxxxx����Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCG3D2021xxxxxx����Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCG3D2021xxxxxx����Doc ����

bool CCG3D2021xxxxxx����Doc::addRenderable(CG3DRenderable* r)
{
	if (r && mScene && r->IsKindOf(RUNTIME_CLASS(CG3DRenderable)))
	{
		bool ret = mScene->addRenderable(r);
		UpdateAllViews(nullptr); //��ӳɹ�������ʾ 
		return ret;
	}
	return false;
}

bool CCG3D2021xxxxxx����Doc::delReaderable(CG3DRenderable* r)
{
	if (r && mScene && r->IsKindOf(RUNTIME_CLASS(CG3DRenderable)))
	{
		bool ret = mScene->delRenderable(r);
		UpdateAllViews(nullptr); //ɾ���ɹ�������ʾ 
		return ret;
	}
	return false;
}

bool CCG3D2021xxxxxx����Doc::RenderScene(CG3DRenderContext * pRC)
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
	//pCamera->SetProjectionMode(0); //͸��ͶӰ��Ҫ�޸�������������ϼ���ƽ�棩

	pRC->Ready(pCamera);
	bool ret = mScene->Render(pRC, pCamera);
	pRC->Finish(pCamera);
	return ret;
}

void CCG3D2021xxxxxx����Doc::OnUpdatePenColor(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(true);
}
void CCG3D2021xxxxxx����Doc::OnUpdatePenWidth(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(true);
}
void CCG3D2021xxxxxx����Doc::OnUpdatePenStyle(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(true);
}
void CCG3D2021xxxxxx����Doc::OnUpdatePenFill(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(true);
}
void CCG3D2021xxxxxx����Doc::AddRenderable(CG3DRenderable* R) {
	mScene->addRenderable(R);
}
void CCG3D2021xxxxxx����Doc::RemoveAll()
{
	// TODO: �ڴ���������������
	mScene->removeAllRenderable();
}
void CCG3D2021xxxxxx����Doc::OnUpdateRotate(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(true);
}
void CCG3D2021xxxxxx����Doc::OnUpRotatePos()
{
	// TODO: �ڴ���������������
	mRubiksCube->UpRotate(true);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx����Doc::OnUpRotateNeg()
{
	// TODO: �ڴ���������������
	mRubiksCube->UpRotate(false);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx����Doc::OnRightRotatePos()
{
	// TODO: �ڴ���������������
	mRubiksCube->RightRotate(true);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx����Doc::OnRightRotateNeg()
{
	// TODO: �ڴ���������������
	mRubiksCube->RightRotate(false);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx����Doc::OnFrontRotatePos()
{
	// TODO: �ڴ���������������
	mRubiksCube->FrontRotate(true);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx����Doc::OnFrontRotateNeg()
{
	// TODO: �ڴ���������������
	mRubiksCube->FrontRotate(false);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx����Doc::OnLeftRotatePos()
{
	// TODO: �ڴ���������������
	mRubiksCube->LeftRotate(true);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx����Doc::OnLeftRotateNeg()
{
	// TODO: �ڴ���������������
	mRubiksCube->LeftRotate(false);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx����Doc::OnBackRotatePos()
{
	// TODO: �ڴ���������������
	mRubiksCube->BackRotate(true);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx����Doc::OnBackRotateNeg()
{
	// TODO: �ڴ���������������
	mRubiksCube->BackRotate(false);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx����Doc::OnDownRotatePos()
{
	// TODO: �ڴ���������������
	mRubiksCube->DownRotate(true);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx����Doc::OnDownRotateNeg()
{
	// TODO: �ڴ���������������
	mRubiksCube->DownRotate(false);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx����Doc::OnCreateRubikscube()
{
	// TODO: �ڴ���������������
	/*if(mRubiksCube)
		delete mRubiksCube;*/
	mRubiksCube = new CG3DRubiksCube(600);
	//mRubiksCube->Rotate(20, 1, 1, 1);
	mScene->addRenderable(mRubiksCube);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx����Doc::OnLeftView()
{
	// TODO: �ڴ���������������
	defaultCamera()->SetEye(-1000, 0, 0);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx����Doc::OnRightView()
{
	// TODO: �ڴ���������������
	defaultCamera()->SetEye(1000, 0, 0);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx����Doc::OnFrontView()
{
	// TODO: �ڴ���������������
	defaultCamera()->SetEye(0, 0, 1000);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx����Doc::OnBackView()
{
	// TODO: �ڴ���������������
	defaultCamera()->SetEye(0, 0, -1000);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx����Doc::OnDownView()
{
	// TODO: �ڴ���������������
	defaultCamera()->SetEye(0, 1000, 0.0001);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx����Doc::OnUpView()
{
	// TODO: �ڴ���������������
	defaultCamera()->SetEye(0, -1000, 0.0001);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx����Doc::OnSubView()
{
	// TODO: �ڴ���������������
	defaultCamera()->SetEye(1000/sqrt(3), 1000 / sqrt(3), 1000 / sqrt(3));
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx����Doc::OnWindowsPos()
{
	// TODO: �ڴ���������������
	defaultCamera()->Zoom(1.25);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx����Doc::OnWindowsNeg()
{
	// TODO: �ڴ���������������
	defaultCamera()->Zoom(0.8);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx����Doc::OnInitScene()
{
	// TODO: �ڴ���������������
	RemoveAll();
	//���� 
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
void CCG3D2021xxxxxx����Doc::OnInitLight()
{
	// TODO: �ڴ���������������
	// ��Դ
	CGLight* light0 = new CGLight();
	light0->setAsPointLight();
	mScene->AddLight(light0);
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx����Doc::OnRemoveLastLight()
{
	// TODO: �ڴ���������������
	//AfxMessageBox(_T("1��"), MB_OK | MB_ICONINFORMATION);
	mScene->RemoveLastLight();
	//mScene->TimerCallback();
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx����Doc::OnRemoveAllLight()
{
	// TODO: �ڴ���������������
	//AfxMessageBox(_T("2��"), MB_OK | MB_ICONINFORMATION);
	mScene->RemoveAllLights();
	UpdateAllViews(nullptr);
}
void CCG3D2021xxxxxx����Doc::OnUpdateMaterialColor(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(true);
}
void CCG3D2021xxxxxx����Doc::OnUpdateBaseMaterial(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(true);
}

//������ʱ�ص�����������и�����Ҫ�ػ��򷵻�true�� 
bool CCG3D2021xxxxxx����Doc::TimerCallback()
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

void CCG3D2021xxxxxx����Doc::Onanime1()
{
	// TODO: �ڴ���������������
	// TODO: �ڴ���������������
	RemoveAll();
	OnRemoveAllLight();
	//���� 
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
