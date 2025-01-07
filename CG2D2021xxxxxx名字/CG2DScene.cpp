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
	//+删除粒子系统 
	removeAllParticleSystem();
}
//序列化
void CG2DScene::Serialize(CArchive& ar)
{
	CGObject::Serialize(ar); //先调用基类的序列化
	mRenderables.Serialize(ar); //所用图形对象序列化
	if (ar.IsStoring())
	{
	}
	else //读取图形文件到内存时要建立图形场景与对象的关联，否则图形对象找不到场景
	{
		size_t cnt = mRenderables.GetCount();
		for (size_t i = 0; i < cnt; i++)
		{
			mRenderables.GetAt(i)->addToScene(this); //建立与场景的关联
		}
	}
}
//图形对象添加到场景，建立两者之间的双向关联
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
//渲染场景到指定客户区（客户区包含若干视口），每个视口对应一个相机。
bool CG2DScene::Render(CG2DRenderContext* pRC, CG2DCamera* pCamera)
{
	//在派生类中具体实现
	if (pRC == nullptr || pCamera == nullptr)
		return false;
	//绘制场景中的所有图形对象
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
	//绘制世界坐标系示意（给定范围）
	//世界坐标系的两轴定义（在世界坐标系中的四个点）
	Vec2d wxs(-400, 0), wxe(400, 0), wys(0, -400), wye(0, 400); //X轴、Y轴
	//转换到视口
	Vec2i vxs = pCamera->WorldtoViewPort(wxs);
	Vec2i vxe = pCamera->WorldtoViewPort(wxe);
	Vec2i vys = pCamera->WorldtoViewPort(wys);
	Vec2i vye = pCamera->WorldtoViewPort(wye);
	//绘制x轴
	HDC hDC = pRC->GetMemHDC();
	CPen penwx(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN hOldPen = (HPEN)::SelectObject(hDC, penwx.GetSafeHandle());
	::MoveToEx(hDC, vxs.x(), vxs.y(), nullptr);
	::LineTo(hDC, vxe.x(), vxe.y());
	::SelectObject(hDC, hOldPen);
	//绘制y轴
	CPen penwy(PS_DASH, 1, RGB(255, 0, 0));
	hOldPen = (HPEN)::SelectObject(hDC, penwy.GetSafeHandle());
	::MoveToEx(hDC, vys.x(), vys.y(), nullptr);
	::LineTo(hDC, vye.x(), vye.y());
	::SelectObject(hDC, hOldPen);
	//绘制观察坐标系
	//观察坐标系的原始定义
	Vec2d xsw(-300, 0), xew(300, 0), ysw(0, -300), yew(0, 300); //X轴、Y轴
	Vec3d wl(xsw), wr(xew), wb(ysw), wt(yew);
	//根据观察坐标系的定义，得到观察坐标系坐标轴在世界坐标系中的位置（在世界坐标系中的四个点）
	Vec2d wlw = pCamera->VCStoWCS(Vec2d(wl.x(), wl.y()));
	Vec2d wrw = pCamera->VCStoWCS(Vec2d(wr.x(), wr.y()));
	Vec2d wbw = pCamera->VCStoWCS(Vec2d(wb.x(), wb.y()));
	Vec2d wtw = pCamera->VCStoWCS(Vec2d(wt.x(), wt.y()));
	//观察坐标系坐标轴转换到视口
	Vec2i vls = pCamera->WorldtoViewPort(wlw);
	Vec2i vre = pCamera->WorldtoViewPort(wrw);
	Vec2i vbs = pCamera->WorldtoViewPort(wbw);
	Vec2i vte = pCamera->WorldtoViewPort(wtw);
	//绘制x轴
	CPen penvx(PS_SOLID, 1, RGB(0, 0, 255));
	hOldPen = (HPEN)::SelectObject(hDC, penvx.GetSafeHandle());
	::MoveToEx(hDC, vls.x(), vls.y(), nullptr);
	::LineTo(hDC, vre.x(), vre.y());
	::SelectObject(hDC, hOldPen);
	//绘制y轴
	CPen penvy(PS_DASH, 1, RGB(0, 0, 255));
	hOldPen = (HPEN)::SelectObject(hDC, penvy.GetSafeHandle());
	::MoveToEx(hDC, vbs.x(), vbs.y(), nullptr);
	::LineTo(hDC, vte.x(), vte.y());
	::SelectObject(hDC, hOldPen);
	return true;
}
//二维场景包围盒计算
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
//二维场景包围盒计算
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

//更新选择（如果拾取对象成功，则替换选择集，返回拾取的对象）
CG2DRenderable* CG2DScene::UpdatePicked(const Vec2d& p, double radius) //点选
{
	size_t i = 0, cnt = mRenderables.GetSize();
	while (i < cnt) //遍历场景中的所有图形对象，判断是否拾取到
	{
		CG2DRenderable* r = mRenderables.GetAt(i);
		if (r && r->Picked(p, radius))
		{
			UnselectAll(); //替换前先清空选择集         !!!和AppendPicked不一样的地方
			r->setStatus(CG2DRenderable::sSelected);
			mSelections.Add(r); //加入选择集
			return r; //假定只选中一个
		}
		i++;
	}
	return nullptr;
}
CG2DRenderable* CG2DScene::UpdatePicked(const ABox2d& box, bool inner/* = true*/) //框选
{
	//TODO：自行补充实现
	size_t i = 0, cnt = mRenderables.GetSize();
	UnselectAll(); //替换前先清空选择集         !!!和AppendPicked不一样的地方
	CG2DRenderable* r = nullptr;
	while (i < cnt) //遍历场景中的所有图形对象，判断是否拾取到
	{
		r = mRenderables.GetAt(i);
		if (r && r->Picked(box))
		{
			r->setStatus(CG2DRenderable::sSelected);
			mSelections.Add(r); //加入选择集
		}
		i++;
	}
	return r;
}
//添加选择（如果拾取对象成功，则加入选择集，返回拾取的对象）
CG2DRenderable* CG2DScene::AppendPicked(const Vec2d& p, double radius) //点选
{
	size_t i = 0, cnt = mRenderables.GetSize();
	while (i < cnt) //遍历场景中的所有图形对象，判断是否拾取到
	{
		CG2DRenderable* r = mRenderables.GetAt(i);
		if (r && r->Picked(p, radius))
		{
			r->setStatus(CG2DRenderable::sSelected);
			mSelections.Add(r); //加入选择集
			return r;
		}
		i++;
	}
	return nullptr;
}
CG2DRenderable* CG2DScene::AppendPicked(const ABox2d& box, bool inner/* = true*/) //框选
{
	//TODO：自行补充实现
	size_t i = 0, cnt = mRenderables.GetSize();
	CG2DRenderable* r = nullptr;
	while (i < cnt) //遍历场景中的所有图形对象，判断是否拾取到
	{
		r = mRenderables.GetAt(i);
		if (r && r->Picked(box))
		{
			r->setStatus(CG2DRenderable::sSelected);
			mSelections.Add(r); //加入选择集
		}
		i++;
	}
	return r;
}
//按图形对象名称选取（如有该对象，则加入选择集，返回选取的对象）
CG2DRenderable* CG2DScene::Selected(const CString& name)
{
	size_t i = 0, cnt = mRenderables.GetSize();
	while (i < cnt)
	{
		CG2DRenderable* r = mRenderables.GetAt(i);
		if (r && r->Name() == name && r->status() != CG2DRenderable::sSelected)
		{
			r->setStatus(CG2DRenderable::sSelected); //设置对象的状态为选中
			mSelections.Add(r); //加入选择集
			return r;
		}
		i++;
	}
	return nullptr;
}
bool CG2DScene::Unselect(const CString& name) //撤销指定对象选中状态
{
	size_t i = 0, cnt = mRenderables.GetSize();
	while (i < cnt)
	{
		CG2DRenderable* r = mRenderables.GetAt(i);
		if (r && r->Name() == name)
		{
			return Unselect(r); //撤销选中状态
		}
		i++;
	}
	return false;
}
bool CG2DScene::Unselect(CG2DRenderable* r) //撤销指定对象选中状态
{
	if (r)
		r->setStatus(CG2DRenderable::sNormal); //设置对象状态为正常
	size_t i = 0, cnt = mSelections.GetSize();
	while (i < cnt) //从选择集中清除
	{
		CG2DRenderable* s = mSelections.GetAt(i);
		if (s == r)
		{
			mSelections.RemoveAt(i);
			return true; //如果有对象撤销选中状态
		}
		i++;
	}
	return false;
}
bool CG2DScene::UnselectAll() //撤销所有对象选中状态
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
	if (cnt > 0) //如果有选中对象被清除标记
		return true;
	return false;
}
bool CG2DScene::SelectAll() //所有对象设为选中
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
	if (cnt > 0) //如果有选中对象设置选中标记
		return true;
	return false;
}

//二维图形对象的几何变换（针对选择集中的对象）
bool CG2DScene::Translate(double tx, double ty) //平移
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
bool CG2DScene::Rotate(double angle, double cx, double cy) //旋转（逆时针为正，度）
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
bool CG2DScene::Scale(double sx, double sy) //缩放
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
bool CG2DScene::Scale(double sx, double sy, double cx, double cy) //缩放（关于指定参考点缩放）
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
bool CG2DScene::MirrorXAxis() //关于X轴对称（二维、三维）
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
bool CG2DScene::MirrorYAxis() //关于Y轴对称（二维、三维）
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
bool CG2DScene::MirrorYeqPosX() //关于y=x对称（二维、三维）
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
bool CG2DScene::MirrorYeNegPX() //关于y=-x对称（二维、三维）
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
bool CG2DScene::MirrorOrigin() //关于原点对称（二维、三维）
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
bool CG2DScene::Mirror(const Vec2d& vs, const Vec2d& ve) //关于线段se对称（二维、三维）
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
bool CG2DScene::ShearXAxis(double shx) //沿X轴错切
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
bool CG2DScene::ShearYAxis(double shy) //沿Y轴错切
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
bool CG2DScene::ShearXYAxis(double shx, double shy) //沿X、Y轴错切
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
bool CG2DScene::Transform(const Mat3d& mat) //几何变换（左乘给定矩阵）
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
//定时回调（用于实现动画） 
bool CG2DScene::TimerCallback()
{
	//粒子系统产生新粒子 
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
	//粒子更新 
	i = 0, cnt = mRenderables.GetSize();
	if (cnt == 0)
		return false;
	bool changed = false;
	while (i < cnt) //调用场景中每个图形对象的回调进行状态更新 
	{
		CG2DRenderable* s = mRenderables.GetAt(i);
		if (s && s->TimerCallbackEnabled())
		{
			if (s->TimerCallback())
				changed = true;
		}
		i++;
	}
	//删除生命结束的粒子 
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
