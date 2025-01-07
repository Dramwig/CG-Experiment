#include "pch.h"
#include "CG2DScene.h"
#include "CG2DRenderable.h"
#include "CG2DCamera.h"
#include "CG2DRenderContext.h"

IMPLEMENT_SERIAL(CG2DScene, CGObject, 1)
CG2DScene::CG2DScene()
	:CGObject(CString("CG2DScene"))
{
}
CG2DScene::~CG2DScene()
{
	removeAllRenderable();
	//+ɾ������ϵͳ 
	removeAllParticleSystem();
}
//���л�
void CG2DScene::Serialize(CArchive& ar)
{
	CGObject::Serialize(ar); //�ȵ��û�������л�
	mRenderables.Serialize(ar); //����ͼ�ζ������л�
	if (ar.IsStoring())
	{
	}
	else //��ȡͼ���ļ����ڴ�ʱҪ����ͼ�γ��������Ĺ���������ͼ�ζ����Ҳ�������
	{
		size_t cnt = mRenderables.GetCount();
		for (size_t i = 0; i < cnt; i++)
		{
			mRenderables.GetAt(i)->addToScene(this); //�����볡���Ĺ���
		}
	}
}
//ͼ�ζ�����ӵ���������������֮���˫�����
bool CG2DScene::addRenderable(CG2DRenderable* pr)
{
	if (pr == nullptr || !pr->IsKindOf(RUNTIME_CLASS(CG2DRenderable)))
		return false;
	mRenderables.Add(pr);
	pr->addToScene(this);
	return true;
}
CG2DRenderable* CG2DScene::detachRenderable(CG2DRenderable* r)
{
	if (r)
	{
		r->addToScene(nullptr);
		size_t i = 0, cnt = mRenderables.GetSize();
		while (i < cnt)
		{
			if (mRenderables.GetAt(i) == r) {
				mRenderables.RemoveAt(i);
			}
			i++;
		}
	}
	return r;
}
bool CG2DScene::delRenderable(CG2DRenderable* pr)
{
	if (pr == nullptr)
		return false;
	size_t i = 0, cnt = mRenderables.GetSize();
	while (i < cnt)
	{
		if (mRenderables.GetAt(i) == pr) {
			delete mRenderables.GetAt(i);
			mRenderables.RemoveAt(i);
			return true;
		}
		i++;
	}
	return false;
}
void CG2DScene::removeAllRenderable()
{
	size_t i = 0, cnt = mRenderables.GetSize();
	while (i < cnt)
	{
		if (mRenderables.GetAt(i))
			delete mRenderables.GetAt(i);
		i++;
	}
	mRenderables.RemoveAll();
}
CG2DRenderable* CG2DScene::getRenderable(unsigned int index)
{
	if (index >= (unsigned int)mRenderables.GetSize())
		return nullptr;
	return mRenderables.GetAt(index);
}
//��Ⱦ������ָ���ͻ������ͻ������������ӿڣ���ÿ���ӿڶ�Ӧһ�������
bool CG2DScene::Render(CG2DRenderContext* pRC, CG2DCamera* pCamera)
{
	//���������о���ʵ��
	if (pRC == nullptr || pCamera == nullptr)
		return false;
	//���Ƴ����е�����ͼ�ζ���
	size_t i = 0, cnt = mRenderables.GetSize();
	while (i < cnt)
	{
		CG2DRenderable* r = mRenderables.GetAt(i);
		if (r != nullptr)
		{
			r->Render(pRC, pCamera);
		}
		i++;
	}
	//������������ϵʾ�⣨������Χ��
	//��������ϵ�����ᶨ�壨����������ϵ�е��ĸ��㣩
	Vec2d wxs(-400, 0), wxe(400, 0), wys(0, -400), wye(0, 400); //X�ᡢY��
	//ת�����ӿ�
	Vec2i vxs = pCamera->WorldtoViewPort(wxs);
	Vec2i vxe = pCamera->WorldtoViewPort(wxe);
	Vec2i vys = pCamera->WorldtoViewPort(wys);
	Vec2i vye = pCamera->WorldtoViewPort(wye);
	//����x��
	HDC hDC = pRC->GetMemHDC();
	CPen penwx(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN hOldPen = (HPEN)::SelectObject(hDC, penwx.GetSafeHandle());
	::MoveToEx(hDC, vxs.x(), vxs.y(), nullptr);
	::LineTo(hDC, vxe.x(), vxe.y());
	::SelectObject(hDC, hOldPen);
	//����y��
	CPen penwy(PS_DASH, 1, RGB(255, 0, 0));
	hOldPen = (HPEN)::SelectObject(hDC, penwy.GetSafeHandle());
	::MoveToEx(hDC, vys.x(), vys.y(), nullptr);
	::LineTo(hDC, vye.x(), vye.y());
	::SelectObject(hDC, hOldPen);
	//���ƹ۲�����ϵ
	//�۲�����ϵ��ԭʼ����
	Vec2d xsw(-300, 0), xew(300, 0), ysw(0, -300), yew(0, 300); //X�ᡢY��
	Vec3d wl(xsw), wr(xew), wb(ysw), wt(yew);
	//���ݹ۲�����ϵ�Ķ��壬�õ��۲�����ϵ����������������ϵ�е�λ�ã�����������ϵ�е��ĸ��㣩
	Vec2d wlw = pCamera->VCStoWCS(Vec2d(wl.x(), wl.y()));
	Vec2d wrw = pCamera->VCStoWCS(Vec2d(wr.x(), wr.y()));
	Vec2d wbw = pCamera->VCStoWCS(Vec2d(wb.x(), wb.y()));
	Vec2d wtw = pCamera->VCStoWCS(Vec2d(wt.x(), wt.y()));
	//�۲�����ϵ������ת�����ӿ�
	Vec2i vls = pCamera->WorldtoViewPort(wlw);
	Vec2i vre = pCamera->WorldtoViewPort(wrw);
	Vec2i vbs = pCamera->WorldtoViewPort(wbw);
	Vec2i vte = pCamera->WorldtoViewPort(wtw);
	//����x��
	CPen penvx(PS_SOLID, 1, RGB(0, 0, 255));
	hOldPen = (HPEN)::SelectObject(hDC, penvx.GetSafeHandle());
	::MoveToEx(hDC, vls.x(), vls.y(), nullptr);
	::LineTo(hDC, vre.x(), vre.y());
	::SelectObject(hDC, hOldPen);
	//����y��
	CPen penvy(PS_DASH, 1, RGB(0, 0, 255));
	hOldPen = (HPEN)::SelectObject(hDC, penvy.GetSafeHandle());
	::MoveToEx(hDC, vbs.x(), vbs.y(), nullptr);
	::LineTo(hDC, vte.x(), vte.y());
	::SelectObject(hDC, hOldPen);
	return true;
}
//��ά������Χ�м���
ABox2d CG2DScene::BoundingABox()
{
	ABox2d box;
	size_t i = 0, cnt = mRenderables.GetSize();
	while (i < cnt)
	{
		CG2DRenderable* r = mRenderables.GetAt(i);
		if (r != nullptr)
		{
			box.extend(((CG2DRenderable*)r)->BoundingABox());
		}
		i++;
	}
	return box;
}
//��ά������Χ�м���
ABox2d CG2DScene::BoundingABoxi(CG2DCamera* pCamera)
{
	ABox2d box;
	size_t i = 0, cnt = mRenderables.GetSize();
	while (i < cnt)
	{
		CG2DRenderable* r = mRenderables.GetAt(i);
		if (r != nullptr)
		{
			ABox2i box2 = ((CG2DRenderable*)r)->BoundingABoxi(pCamera);
			ABox2d box3 = ABox2d(pCamera->NCStoVCS(pCamera->DCStoNCS(Vec2d(box2.left(), box2.top()))), 
				pCamera->NCStoVCS(pCamera->DCStoNCS(Vec2d(box2.right(), box2.bottom()))));
			box.extend(box3);
		}
		i++;
	}
	return box;
}

//����ѡ�����ʰȡ����ɹ������滻ѡ�񼯣�����ʰȡ�Ķ���
CG2DRenderable* CG2DScene::UpdatePicked(const Vec2d& p, double radius) //��ѡ
{
	size_t i = 0, cnt = mRenderables.GetSize();
	while (i < cnt) //���������е�����ͼ�ζ����ж��Ƿ�ʰȡ��
	{
		CG2DRenderable* r = mRenderables.GetAt(i);
		if (r && r->Picked(p, radius))
		{
			UnselectAll(); //�滻ǰ�����ѡ��         !!!��AppendPicked��һ���ĵط�
			r->setStatus(CG2DRenderable::sSelected);
			mSelections.Add(r); //����ѡ��
			return r; //�ٶ�ֻѡ��һ��
		}
		i++;
	}
	return nullptr;
}
CG2DRenderable* CG2DScene::UpdatePicked(const ABox2d& box, bool inner/* = true*/) //��ѡ
{
	//TODO�����в���ʵ��
	size_t i = 0, cnt = mRenderables.GetSize();
	UnselectAll(); //�滻ǰ�����ѡ��         !!!��AppendPicked��һ���ĵط�
	CG2DRenderable* r = nullptr;
	while (i < cnt) //���������е�����ͼ�ζ����ж��Ƿ�ʰȡ��
	{
		r = mRenderables.GetAt(i);
		if (r && r->Picked(box))
		{
			r->setStatus(CG2DRenderable::sSelected);
			mSelections.Add(r); //����ѡ��
		}
		i++;
	}
	return r;
}
//���ѡ�����ʰȡ����ɹ��������ѡ�񼯣�����ʰȡ�Ķ���
CG2DRenderable* CG2DScene::AppendPicked(const Vec2d& p, double radius) //��ѡ
{
	size_t i = 0, cnt = mRenderables.GetSize();
	while (i < cnt) //���������е�����ͼ�ζ����ж��Ƿ�ʰȡ��
	{
		CG2DRenderable* r = mRenderables.GetAt(i);
		if (r && r->Picked(p, radius))
		{
			r->setStatus(CG2DRenderable::sSelected);
			mSelections.Add(r); //����ѡ��
			return r;
		}
		i++;
	}
	return nullptr;
}
CG2DRenderable* CG2DScene::AppendPicked(const ABox2d& box, bool inner/* = true*/) //��ѡ
{
	//TODO�����в���ʵ��
	size_t i = 0, cnt = mRenderables.GetSize();
	CG2DRenderable* r = nullptr;
	while (i < cnt) //���������е�����ͼ�ζ����ж��Ƿ�ʰȡ��
	{
		r = mRenderables.GetAt(i);
		if (r && r->Picked(box))
		{
			r->setStatus(CG2DRenderable::sSelected);
			mSelections.Add(r); //����ѡ��
		}
		i++;
	}
	return r;
}
//��ͼ�ζ�������ѡȡ�����иö��������ѡ�񼯣�����ѡȡ�Ķ���
CG2DRenderable* CG2DScene::Selected(const CString& name)
{
	size_t i = 0, cnt = mRenderables.GetSize();
	while (i < cnt)
	{
		CG2DRenderable* r = mRenderables.GetAt(i);
		if (r && r->Name() == name && r->status() != CG2DRenderable::sSelected)
		{
			r->setStatus(CG2DRenderable::sSelected); //���ö����״̬Ϊѡ��
			mSelections.Add(r); //����ѡ��
			return r;
		}
		i++;
	}
	return nullptr;
}
bool CG2DScene::Unselect(const CString& name) //����ָ������ѡ��״̬
{
	size_t i = 0, cnt = mRenderables.GetSize();
	while (i < cnt)
	{
		CG2DRenderable* r = mRenderables.GetAt(i);
		if (r && r->Name() == name)
		{
			return Unselect(r); //����ѡ��״̬
		}
		i++;
	}
	return false;
}
bool CG2DScene::Unselect(CG2DRenderable* r) //����ָ������ѡ��״̬
{
	if (r)
		r->setStatus(CG2DRenderable::sNormal); //���ö���״̬Ϊ����
	size_t i = 0, cnt = mSelections.GetSize();
	while (i < cnt) //��ѡ�������
	{
		CG2DRenderable* s = mSelections.GetAt(i);
		if (s == r)
		{
			mSelections.RemoveAt(i);
			return true; //����ж�����ѡ��״̬
		}
		i++;
	}
	return false;
}
bool CG2DScene::UnselectAll() //�������ж���ѡ��״̬
{
	size_t i = 0, cnt = mSelections.GetSize();
	while (i < cnt)
	{
		CG2DRenderable* s = mSelections.GetAt(i);
		if (s)
			s->setStatus(CG2DRenderable::sNormal);
		i++;
	}
	mSelections.RemoveAll();
	if (cnt > 0) //�����ѡ�ж���������
		return true;
	return false;
}
bool CG2DScene::SelectAll() //���ж�����Ϊѡ��
{
	mSelections.RemoveAll();
	size_t i = 0, cnt = mRenderables.GetSize();
	while (i < cnt)
	{
		CG2DRenderable* r = mRenderables.GetAt(i);
		if (r)
		{
			r->setStatus(CG2DRenderable::sSelected);
			mSelections.Add(r);
		}
		i++;
	}
	if (cnt > 0) //�����ѡ�ж�������ѡ�б��
		return true;
	return false;
}

//��άͼ�ζ���ļ��α任�����ѡ���еĶ���
bool CG2DScene::Translate(double tx, double ty) //ƽ��
{
	size_t i = 0, cnt = mSelections.GetSize();
	if (cnt == 0)
		return false;
	while (i < cnt)
	{
		CG2DRenderable* s = mSelections.GetAt(i);
		if (s)
			s->Translate(tx, ty);
		i++;
	}
	return true;
}
bool CG2DScene::Rotate(double angle, double cx, double cy) //��ת����ʱ��Ϊ�����ȣ�
{
	size_t i = 0, cnt = mSelections.GetSize();
	if (cnt == 0)
		return false;
	while (i < cnt)
	{
		CG2DRenderable* s = mSelections.GetAt(i);
		if (s)
			s->Rotate(angle, cx, cy);
		i++;
	}
	return true;
}
bool CG2DScene::Scale(double sx, double sy) //����
{
	size_t i = 0, cnt = mSelections.GetSize();
	if (cnt == 0)
		return false;
	while (i < cnt)
	{
		CG2DRenderable* s = mSelections.GetAt(i);
		if (s)
			s->Scale(sx, sy);
		i++;
	}
	return true;
}
bool CG2DScene::Scale(double sx, double sy, double cx, double cy) //���ţ�����ָ���ο������ţ�
{
	size_t i = 0, cnt = mSelections.GetSize();
	if (cnt == 0)
		return false;
	while (i < cnt)
	{
		CG2DRenderable* s = mSelections.GetAt(i);
		if (s)
			s->Scale(sx, sy, cx, cy);
		i++;
	}
	return true;
}
bool CG2DScene::MirrorXAxis() //����X��Գƣ���ά����ά��
{
	size_t i = 0, cnt = mSelections.GetSize();
	if (cnt == 0)
		return false;
	while (i < cnt)
	{
		CG2DRenderable* s = mSelections.GetAt(i);
		if (s)
			s->MirrorXAxis();
		i++;
	}
	return true;
}
bool CG2DScene::MirrorYAxis() //����Y��Գƣ���ά����ά��
{
	size_t i = 0, cnt = mSelections.GetSize();
	if (cnt == 0)
		return false;
	while (i < cnt)
	{
		CG2DRenderable* s = mSelections.GetAt(i);
		if (s)
			s->MirrorYAxis();
		i++;
	}
	return true;
}
bool CG2DScene::MirrorYeqPosX() //����y=x�Գƣ���ά����ά��
{
	size_t i = 0, cnt = mSelections.GetSize();
	if (cnt == 0)
		return false;
	while (i < cnt)
	{
		CG2DRenderable* s = mSelections.GetAt(i);
		if (s)
			s->MirrorYeqPosX();
		i++;
	}
	return true;
}
bool CG2DScene::MirrorYeNegPX() //����y=-x�Գƣ���ά����ά��
{
	size_t i = 0, cnt = mSelections.GetSize();
	if (cnt == 0)
		return false;
	while (i < cnt)
	{
		CG2DRenderable* s = mSelections.GetAt(i);
		if (s)
			s->MirrorYeNegPX();
		i++;
	}
	return true;
}
bool CG2DScene::MirrorOrigin() //����ԭ��Գƣ���ά����ά��
{
	size_t i = 0, cnt = mSelections.GetSize();
	if (cnt == 0)
		return false;
	while (i < cnt)
	{
		CG2DRenderable* s = mSelections.GetAt(i);
		if (s)
			s->MirrorOrigin();
		i++;
	}
	return true;
}
bool CG2DScene::Mirror(const Vec2d& vs, const Vec2d& ve) //�����߶�se�Գƣ���ά����ά��
{
	size_t i = 0, cnt = mSelections.GetSize();
	if (cnt == 0)
		return false;
	while (i < cnt)
	{
		CG2DRenderable* s = mSelections.GetAt(i);
		if (s)
			s->Mirror(vs, ve);
		i++;
	}
	return true;
}
bool CG2DScene::ShearXAxis(double shx) //��X�����
{
	size_t i = 0, cnt = mSelections.GetSize();
	if (cnt == 0)
		return false;
	while (i < cnt)
	{
		CG2DRenderable* s = mSelections.GetAt(i);
		if (s)
			s->ShearXAxis(shx);
		i++;
	}
	return true;
}
bool CG2DScene::ShearYAxis(double shy) //��Y�����
{
	size_t i = 0, cnt = mSelections.GetSize();
	if (cnt == 0)
		return false;
	while (i < cnt)
	{
		CG2DRenderable* s = mSelections.GetAt(i);
		if (s)
			s->ShearYAxis(shy);
		i++;
	}
	return true;
}
bool CG2DScene::ShearXYAxis(double shx, double shy) //��X��Y�����
{
	size_t i = 0, cnt = mSelections.GetSize();
	if (cnt == 0)
		return false;
	while (i < cnt)
	{
		CG2DRenderable* s = mSelections.GetAt(i);
		if (s)
			s->ShearXYAxis(shx, shy);
		i++;
	}
	return true;
}
bool CG2DScene::Transform(const Mat3d& mat) //���α任����˸�������
{
	size_t i = 0, cnt = mSelections.GetSize();
	if (cnt == 0)
		return false;
	while (i < cnt)
	{
		CG2DRenderable* s = mSelections.GetAt(i);
		if (s)
			s->Transform(mat);
		i++;
	}
	return true;
}
//��ʱ�ص�������ʵ�ֶ����� 
bool CG2DScene::TimerCallback()
{
	//����ϵͳ���������� 
	size_t i = 0, cnt = mParticleSystems.GetSize();
	while (i < cnt)
	{
		ParticleSystem2D* p = mParticleSystems.GetAt(i);
		if (p)
		{
			p->Run();
		}
		i++;
	}
	//���Ӹ��� 
	i = 0, cnt = mRenderables.GetSize();
	if (cnt == 0)
		return false;
	bool changed = false;
	while (i < cnt) //���ó�����ÿ��ͼ�ζ���Ļص�����״̬���� 
	{
		CG2DRenderable* s = mRenderables.GetAt(i);
		if (s && s->TimerCallbackEnabled())
		{
			if (s->TimerCallback())
				changed = true;
		}
		i++;
	}
	//ɾ���������������� 
	i = 0, cnt = mRenderables.GetSize();
	while (i < cnt)
	{
		CG2DRenderable* s = mRenderables.GetAt(i);
		if (s)
		{
			Particle2D* p = dynamic_cast<Particle2D*>(s);
			if (p && p->isDead())
			{
				delRenderable(s);
			}
			else
			{
				i++;
			}
		}
		cnt = mRenderables.GetSize();
	}
	return changed;
}


bool CG2DScene::addParticleSystem(ParticleSystem2D* p)
{
	if (p == nullptr || !p->IsKindOf(RUNTIME_CLASS(ParticleSystem2D)))
		return false;
	mParticleSystems.Add(p);
	p->Scene() = this;
	return true;
}
bool CG2DScene::delParticleSystem(ParticleSystem2D* p)
{
	if (p == nullptr)
		return false;
	size_t i = 0, cnt = mParticleSystems.GetSize();
	while (i < cnt)
	{
		if (mParticleSystems.GetAt(i) == p) {
			delete mParticleSystems.GetAt(i);
			mParticleSystems.RemoveAt(i);
			return true;
		}
		i++;
	}
	return false;
}
void CG2DScene::removeAllParticleSystem()
{
	size_t i = 0, cnt = mParticleSystems.GetSize();
	while (i < cnt)
	{
		if (mParticleSystems.GetAt(i))
			delete mParticleSystems.GetAt(i);
		i++;
	}
	mParticleSystems.RemoveAll();
}
