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

// CG2D2021xxxxxx����Doc.cpp: CCG2D2021xxxxxx����Doc ���ʵ��
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "CG2D2021xxxxxx����.h"
#endif

#include "CG2D2021xxxxxx����Doc.h"
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
#include "Sparkler2D.h"
#include "CInputDialog1.h"
#include "Fireworks2D.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCG2D2021xxxxxx����Doc

IMPLEMENT_DYNCREATE(CCG2D2021xxxxxx����Doc, CDocument)

BEGIN_MESSAGE_MAP(CCG2D2021xxxxxx����Doc, CDocument)
	ON_UPDATE_COMMAND_UI(ID_PEN_COLOR, &CCG2D2021xxxxxx����Doc::OnUpdatePenColor)
	ON_UPDATE_COMMAND_UI(ID_PEN_WIDTH, &CCG2D2021xxxxxx����Doc::OnUpdatePenWidth)
	ON_UPDATE_COMMAND_UI(ID_PEN_STYLE, &CCG2D2021xxxxxx����Doc::OnUpdatePenStyle)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_COLOR, &CCG2D2021xxxxxx����Doc::OnUpdateBrushColor)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_STYLE, &CCG2D2021xxxxxx����Doc::OnUpdateBrushStyle)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_HATCH, &CCG2D2021xxxxxx����Doc::OnUpdateBrushHatch)
	ON_UPDATE_COMMAND_UI(ID_ALGOR_LINE, &CCG2D2021xxxxxx����Doc::OnUpdateAlgorLine)
	ON_UPDATE_COMMAND_UI(ID_ALGOR_CIRCLE, &CCG2D2021xxxxxx����Doc::OnUpdateAlgorCircle)
	ON_UPDATE_COMMAND_UI(ID_ALGOR_POLYGON, &CCG2D2021xxxxxx����Doc::OnUpdateAlgorPolygon)
	ON_UPDATE_COMMAND_UI(ID_ALGOR_SEEDFILL, &CCG2D2021xxxxxx����Doc::OnUpdateAlgorSeedfill)
	ON_UPDATE_COMMAND_UI(ID_BOUND_COLOR, &CCG2D2021xxxxxx����Doc::OnUpdateBoundColor)
	ON_UPDATE_COMMAND_UI(ID_INNER_COLOR, &CCG2D2021xxxxxx����Doc::OnUpdateInnerColor)
	ON_COMMAND(ID_BTN_PARTICLE, &CCG2D2021xxxxxx����Doc::OnBtnParticle)
	//ON_COMMAND(ID_BTN_FIREWORKS, &CCG2D2021xxxxxx����Doc::OnBtnFireworks)
	ON_COMMAND(ID_BTN_REMOVEALL, &CCG2D2021xxxxxx����Doc::OnBtnRemoveall)
END_MESSAGE_MAP()

BOOL CCG2D2021xxxxxx����Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CCG2D2021xxxxxx����Doc ���л�

void CCG2D2021xxxxxx����Doc::Serialize(CArchive& ar)
{
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
void CCG2D2021xxxxxx����Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CCG2D2021xxxxxx����Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CCG2D2021xxxxxx����Doc::SetSearchContent(const CString& value)
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

// CCG2D2021xxxxxx����Doc ���

#ifdef _DEBUG
void CCG2D2021xxxxxx����Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCG2D2021xxxxxx����Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCG2D2021xxxxxx����Doc ����

CCG2D2021xxxxxx����Doc::CCG2D2021xxxxxx����Doc() noexcept
{
	// TODO: �ڴ����һ���Թ������
	mScene = new CG2DScene();
	mCameras.Add(new CG2DCamera());

	////����ϵͳ 
	//mScene->addParticleSystem(new Sparkler2D(mScene));

	//// �������ֱ�߶ε�������Ҫ����"CG2DLineSegment.h"����������Ϻ�ɾ����
	//mScene->addRenderable(new CG2DLineSegment(Vec2d(100, 100), Vec2d(500, 200)));
	//mScene->addRenderable(new CG2DRay(Vec2d(-100, -100), Vec2d(-10, -20)));
	//mScene->addRenderable(new CG2DLine(Vec2d(0, 0), Vec2d(200, 500)));

	//// ����������ߵ�������
	//CG2DPolyline* polyline = new CG2DPolyline();
	//polyline->addPoint(Vec2d(300, 300));
	//polyline->addPoint(Vec2d(400, 400));
	//polyline->addPoint(Vec2d(500, 300));
	//mScene->addRenderable(polyline);

	//// ��Ӳ���Բ����Բ��������
	//mScene->addRenderable(new CG2DArc(Vec2d(300, 300), 100, 0, PI / 2 * 3));
	//mScene->addRenderable(new CG2DCircle(Vec2d(0, 0), 100));

	//// ������Ӷ���ε�������
	//CG2DPolygon* polygon = new CG2DPolygon();
	//polygon->addPoint(Vec2d(100, 100));
	//polygon->addPoint(Vec2d(200, 100));
	//polygon->addPoint(Vec2d(200, 200));
	//polygon->addPoint(Vec2d(100, 200));
	//mScene->addRenderable(polygon);

	//// ��Ӳ�����Բ��������
	//mScene->addRenderable(new CG2DEllipse(Vec2d(0, 0), 100, 50));
}

CCG2D2021xxxxxx����Doc::~CCG2D2021xxxxxx����Doc()
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
bool CCG2D2021xxxxxx����Doc::addRenderable(CG2DRenderable* r)
{
	if (r && mScene && r->IsKindOf(RUNTIME_CLASS(CG2DRenderable)))
	{
		bool ret = mScene->addRenderable(r);
		UpdateAllViews(nullptr); //��ӳɹ�������ʾ
		return ret;
	}
	return false;
}
bool CCG2D2021xxxxxx����Doc::delReaderable(CG2DRenderable* r)
{
	if (r && mScene && r->IsKindOf(RUNTIME_CLASS(CG2DRenderable)))
	{
		bool ret = mScene->delRenderable(r);
		UpdateAllViews(nullptr); //ɾ���ɹ�������ʾ
		return ret;
	}
	return false;
}
void CCG2D2021xxxxxx����Doc::clearScene()
{
	if (mScene)
		mScene->removeAllRenderable();
}
bool CCG2D2021xxxxxx����Doc::RenderScene(CG2DRenderContext* pRC)
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
	pCamera->viewport().set(0, 0, w ,h);
	pCamera->ViewportOffset();
	pRC->Ready(pCamera);
	bool ret = mScene->Render(pRC, pCamera);
	pRC->Finish(pCamera);
	return ret;
}


// ʵ��3-2
void CCG2D2021xxxxxx����Doc::OnUpdatePenColor(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(true);
}


void CCG2D2021xxxxxx����Doc::OnUpdatePenWidth(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(true);
}


void CCG2D2021xxxxxx����Doc::OnUpdatePenStyle(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(true);
}


void CCG2D2021xxxxxx����Doc::OnUpdateBrushColor(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(true);
}


void CCG2D2021xxxxxx����Doc::OnUpdateBrushStyle(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(true);
}


void CCG2D2021xxxxxx����Doc::OnUpdateBrushHatch(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(true);
}


void CCG2D2021xxxxxx����Doc::OnUpdateAlgorLine(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(true);
}


void CCG2D2021xxxxxx����Doc::OnUpdateAlgorCircle(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(true);
}


void CCG2D2021xxxxxx����Doc::OnUpdateAlgorPolygon(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(true);
}


void CCG2D2021xxxxxx����Doc::OnUpdateAlgorSeedfill(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(true);
}


void CCG2D2021xxxxxx����Doc::OnUpdateBoundColor(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(true);
}


void CCG2D2021xxxxxx����Doc::OnUpdateInnerColor(CCmdUI* pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(true);
}

//�����ӿ������ȡ��Ӧ�������꣨��ά��-����Ĭ�������ת������
Vec2d CCG2D2021xxxxxx����Doc::ViewPorttoWorld(const Vec2i& p)
{
	return defaultCamera()->ViewPorttoWorld(p);
}
Vec2d CCG2D2021xxxxxx����Doc::ViewPorttoWorld(const Vec2d& p)
{
	return defaultCamera()->ViewPorttoWorld(p);
}

Vec2i CCG2D2021xxxxxx����Doc::WorldtoViewPort(const Vec2d& p)
{
	return defaultCamera()->WorldtoViewPort(p);
}

//����ѡ�����ʰȡ����ɹ������滻ѡ�񼯣�����ʰȡ�Ķ���
CG2DRenderable* CCG2D2021xxxxxx����Doc::UpdatePicked(const Vec2d& p, double radius) //��ѡ
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
CG2DRenderable* CCG2D2021xxxxxx����Doc::UpdatePicked(const ABox2d& box, bool inner/* = true*/) //��ѡ��������ѡ�У���
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
//���ѡ�����ʰȡ����ɹ��������ѡ�񼯣�����ʰȡ�Ķ���
CG2DRenderable* CCG2D2021xxxxxx����Doc::AppendPicked(const Vec2d& p, double radius) //��ѡ
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
CG2DRenderable* CCG2D2021xxxxxx����Doc::AppendPicked(const ABox2d& box, bool inner/* = true*/) //��ѡ��������ѡ�У���
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
bool CCG2D2021xxxxxx����Doc::UnselectAll() //�������ж���ѡ��״̬
{
	if (mScene && mScene->UnselectAll())
		UpdateAllViews(nullptr);
	return false;
}
//��άͼ�ζ���ļ��α任�����ѡ���еĶ���
bool CCG2D2021xxxxxx����Doc::Translate(double tx, double ty) //ƽ��
{
	if (mScene && mScene->Translate(tx, ty))
	{
		return true;
	}
	return false;
}
bool CCG2D2021xxxxxx����Doc::Rotate(double angle, double cx, double cy) //��ת����ʱ��Ϊ=�����ȣ�
{
	if (mScene && mScene->Rotate(angle, cx, cy))
	{
		return true;
	}
	return false;
}
bool CCG2D2021xxxxxx����Doc::Scale(double sx, double sy) //����
{
	if (mScene && mScene->Scale(sx, sy))
	{
		return true;
	}
	return false;
}
bool CCG2D2021xxxxxx����Doc::Scale(double sx, double sy, double cx, double cy) //���ţ�����ָ���ο������ţ�
{
	if (mScene && mScene->Scale(sx, sy, cx, cy))
	{
		return true;
	}
	return false;
}
bool CCG2D2021xxxxxx����Doc::MirrorXAxis() //����X��Գƣ���ά����ά��
{
	if (mScene && mScene->MirrorXAxis())
	{
		return true;
	}
	return false;
}
bool CCG2D2021xxxxxx����Doc::MirrorYAxis() //����Y��Գƣ���ά����ά��
{
	if (mScene && mScene->MirrorYAxis())
	{
		return true;
	}
	return false;
}
bool CCG2D2021xxxxxx����Doc::MirrorYeqPosX()//����y=x�Գƣ���ά����ά��
{
	if (mScene && mScene->MirrorYeqPosX())
	{
		return true;
	}
	return false;
}
bool CCG2D2021xxxxxx����Doc::MirrorYeNegPX()//����y=-x�Գƣ���ά����ά��
{
	if (mScene && mScene->MirrorYeNegPX())
	{
		return true;
	}
	return false;
}
bool CCG2D2021xxxxxx����Doc::MirrorOrigin() //����ԭ��Գƣ���ά����ά��
{
	if (mScene && mScene->MirrorOrigin())
	{
		return true;
	}
	return false;
}
bool CCG2D2021xxxxxx����Doc::Mirror(const Vec2d& vs, const Vec2d& ve) //�����߶�se�Գƣ���ά����ά��
{
	if (mScene && mScene->Mirror(vs, ve))
	{
		return true;
	}
	return false;
}
bool CCG2D2021xxxxxx����Doc::ShearXAxis(double shx) //��X�����
{
	if (mScene && mScene->ShearXAxis(shx))
	{
		return true;
	}
	return false;
}
bool CCG2D2021xxxxxx����Doc::ShearYAxis(double shy) //��Y�����
{
	if (mScene && mScene->ShearYAxis(shy))
	{
		return true;
	}
	return false;
}
bool CCG2D2021xxxxxx����Doc::ShearXYAxis(double shx, double shy) //��X��Y�����
{
	if (mScene && mScene->ShearXYAxis(shx, shy))
	{
		return true;
	}
	return false;
}
bool CCG2D2021xxxxxx����Doc::Transform(const Mat3d & mat) //���α任����˸�������
{
	if (mScene && mScene->Transform(mat))
	{
		return true;
	}
	return false;
}
//Ĭ������Ĺ۲�����ϵ
void CCG2D2021xxxxxx����Doc::MoveCamera(double tx, double ty) //ƽ��������۲�����ϵ��
{
	CG2DCamera* pCamera = defaultCamera();
	if (pCamera != nullptr)
	{
		pCamera->Move(tx, ty);
	}
}
void CCG2D2021xxxxxx����Doc::RotateCamera(double degree) //ת��������۲�����ϵ��
{
	CG2DCamera* pCamera = defaultCamera();
	if (pCamera != nullptr)
	{
		pCamera->Rotate(degree);
	}
}
void CCG2D2021xxxxxx����Doc::ResetCamera() //���������Ĭ�ϲ������۲�����ϵ��
{
	CG2DCamera* pCamera = defaultCamera();
	if (pCamera != nullptr)
	{
		pCamera->Reset();
	}
}
//Ĭ������Ĺ۲촰��
void CCG2D2021xxxxxx����Doc::ZoomCamera(const Vec2d& lb, const Vec2d& rt) //�۲촰�����½ǡ����Ͻ�
{
	CG2DCamera* pCamera = defaultCamera();
	if (pCamera != nullptr)
	{
		pCamera->Zoom(lb, rt);
	}
}
void CCG2D2021xxxxxx����Doc::ZoomCamera(double ratio) //�����۲촰�ڵ����ű�������
{
	CG2DCamera* pCamera = defaultCamera();
	if (pCamera != nullptr)
	{
		pCamera->Zoom(ratio);
	}
}
void CCG2D2021xxxxxx����Doc::CameraShowAll() //��ʾȫ������
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
void CCG2D2021xxxxxx����Doc::CameraWindowOffset(double offleft, double offbottom, double offright, double offtop) //�߽��ƶ�
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

void CCG2D2021xxxxxx����Doc::CameraWindowSet(double left, double bottom, double right, double top) //�߽��ƶ�
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

void CCG2D2021xxxxxx����Doc::WindowReset()
{
	CG2DCamera* pCamera = defaultCamera();
	if (pCamera != nullptr)
	{
		CameraWindowSet(-1000, -1000, 1000, 1000);
	}
}

void CCG2D2021xxxxxx����Doc::CameraWindowOverall() 
{
	CG2DCamera* pCamera = defaultCamera();
	ABox2d box = mScene->BoundingABoxi(pCamera);
	if (pCamera != nullptr)
		if (box.isNull()) {
			WindowReset();
		}
		else 
		{
			CameraWindowSet(box.left(), box.bottom(), box.right(), box.top());
		}
}

//Ĭ��������ӿڣ�ѡ�������в��䣩
void CCG2D2021xxxxxx����Doc::CameraViewportOffset(int offleft, int offbottom, int offright, int offtop) //�߽��ƶ�
{
	CG2DCamera* pCamera = defaultCamera();
	if (pCamera != nullptr)
	{
		//pCamera->ViewportOffset(offleft, offbottom, offright, offtop);
		pCamera->cameraViewportOffleft += offleft;
		pCamera->cameraViewportOffbottom += offbottom;
		pCamera->cameraViewportOffright += offright;
		pCamera->cameraViewportOfftop += offtop;
	}
}

void CCG2D2021xxxxxx����Doc::CameraViewportReset()
{
	CG2DCamera* pCamera = defaultCamera();
	if (pCamera != nullptr)
	{
		//pCamera->ViewportOffset(offleft, offbottom, offright, offtop);
		pCamera->cameraViewportOffleft = 0;
		pCamera->cameraViewportOffbottom = 0;
		pCamera->cameraViewportOffright = 0;
		pCamera->cameraViewportOfftop = 0;
	}
}

void CCG2D2021xxxxxx����Doc::CameraViewportSet(int width, int height)
{
	CG2DCamera* pCamera = defaultCamera();
	if (pCamera != nullptr)
	{
		pCamera->ViewportSet(width, height);
	}
}

void CCG2D2021xxxxxx����Doc::CameraAspectRatio()
{
	CG2DCamera* pCamera = defaultCamera();
	if (pCamera != nullptr)
	{
		double wr = pCamera->WidthFactorWindowtoViewPort();
		double hr = pCamera->HeightFactorWindowtoViewPort();
		if (wr < hr) {
			double r = hr / wr;
			pCamera->SetWindowLeft(pCamera->Left() * r);
			pCamera->SetWindowRight(pCamera->Right() * r);
		}
		else 
		{
			double r = wr / hr;
			pCamera->SetWindowBottom(pCamera->Bottom() * r);
			pCamera->SetWindowTop(pCamera->Top() * r);
		}
	}
}

//������ʱ�ص�����������и�����Ҫ�ػ��򷵻�true�� 
bool CCG2D2021xxxxxx����Doc::TimerCallback()
{
	return mScene->TimerCallback();
}

void CCG2D2021xxxxxx����Doc::OnBtnParticle()
{
	// TODO: �ڴ��������������� 
	CInputDialog1 dlg;
	dlg.mTitle = _T("������������"); //������Ҫ���öԻ������ 
	if (dlg.DoModal() == IDOK) //�Ի����е���ˡ�ȷ������ť��ȡ����������� 
	{
		//����ʵ����Ҫʹ����������� 
		//�������������ֵ�����ַ���ת��Ϊ��ֵ 
		double len = _ttof(dlg.mValue1);
		//
		Sparkler2D* s = new Sparkler2D(mScene);
		s->setParticlesGen(int(len));
		mScene->addParticleSystem(s);
	}
}


void CCG2D2021xxxxxx����Doc::OnBtnFireworks()
{
	CInputDialog1 dlg;
	dlg.mTitle = _T("������������(�����1)"); //������Ҫ���öԻ������ 
	if (dlg.DoModal() == IDOK) //�Ի����е���ˡ�ȷ������ť��ȡ����������� 
	{
		//����ʵ����Ҫʹ����������� 
		//�������������ֵ�����ַ���ת��Ϊ��ֵ 
		double len = _ttof(dlg.mValue1);
		//
		Fireworks2D* s = new Fireworks2D(mScene);
		s->setParticlesGen(int(len));
		mScene->addParticleSystem(s);
	}
}


void CCG2D2021xxxxxx����Doc::OnBtnRemoveall()
{
	// TODO: �ڴ���������������
	mScene->removeAllParticleSystem();
}
