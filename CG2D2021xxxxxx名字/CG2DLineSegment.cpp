#include "pch.h"
#include "CG2DLineSegment.h"
#include "CG2DRenderContext.h"
#include "CG2DCamera.h"
IMPLEMENT_SERIAL(CG2DLineSegment, CG2DRenderable, 1)
CG2DLineSegment::CG2DLineSegment()
	: CG2DLineSegment(Vec2d(0, 0), Vec2d(0, 0)) //ί�й��캯��
{
}
CG2DLineSegment::CG2DLineSegment(const Vec2d & s, const Vec2d & e)
	: CG2DRenderable(CString("CG2DLineSegment")), mStart(s), mEnd(e)
{
	mName.Format(_T("ֱ�߶�-%ld"), sID);
}
CG2DLineSegment::CG2DLineSegment(const Vec2d & s, const Vec2d & dir, double length)
	: CG2DLineSegment(s, Vec2d(0, 0)) //ί�й��캯��
{
	double dirlen = dir.length();
	if (dirlen)
	{
		mEnd.x() = mStart.x() + length * dir.x() / dirlen;
		mEnd.y() = mStart.y() + length * dir.y() / dirlen;
	}
	else
	{
		mEnd.x() = mStart.x();
		mEnd.y() = mStart.y();
	}
	mName.Format(_T("ֱ�߶�-%ld"), sID);
}
CG2DLineSegment::CG2DLineSegment(const CG2DLineSegment & other)
	: CG2DLineSegment(other.mStart, other.mEnd) //ί�й��캯��
{
}
CG2DLineSegment::~CG2DLineSegment()
{
}
//���л�
void CG2DLineSegment::Serialize(CArchive & ar)
{
	CG2DRenderable::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << mStart.x() << mStart.y() << mEnd.x() << mEnd.y();
	}
	else
	{
		ar >> mStart.x() >> mStart.y() >> mEnd.x() >> mEnd.y();
	}
}
//����
void CG2DLineSegment::Render(CG2DRenderContext* pRC, CG2DCamera* pCamera) //���ƶ���ʹ��ָ�����
{
	if (pRC == nullptr || pCamera == nullptr)
		return;
	HDC hDC = pRC->GetMemHDC();
	//ʹ�ñ任�����ͼ�εĻ���Ҫʹ�þ������
	Vec3d s = mMat * Vec3d(mStart); //����ʵ�����
	Vec3d e = mMat * Vec3d(mEnd); //����ʵ���յ�
	Vec2i v1 = pCamera->WorldtoViewPort(Vec2d(s.x(), s.y()));
	Vec2i v2 = pCamera->WorldtoViewPort(Vec2d(e.x(), e.y()));
	//�����㷨
	int algrithm = pRC->LineAlgorithm(); //ͨ�����ƻ�����Ӧ��View��ȡRibbon�����ѡ�е�ֱ�߶λ����㷨
	if (algrithm == (int)LineAlgorithm::CDC)
	{ //�����߶ε����͡��߿���ɫ���Դ�������
		CPen pen(penStyle(), penWidth(), penColor());
		if (hDC != 0) //ʹ��Windows��ͼ���豸�ӿ�API��GDI����������
		{ //����ѡ����ƻ���
			HPEN hOldPen = (HPEN)::SelectObject(hDC, pen.GetSafeHandle());
			::MoveToEx(hDC, v1.x(), v1.y(), nullptr);
			::LineTo(hDC, v2.x(), v2.y());
			::SelectObject(hDC, hOldPen); //�ָ�ԭ���ƻ����Ļ���
		}

	}
	else if (algrithm == (int)LineAlgorithm::DDA)
		pRC->DDALine(v1.x(), v1.y(), v2.x(), v2.y(), penColor());
	else if (algrithm == (int)LineAlgorithm::MidPoint)
		pRC->MidPointLine(v1.x(), v1.y(), v2.x(), v2.y(), penColor());
	else if (algrithm == (int)LineAlgorithm::Bresenham)
		pRC->BresenhamLine(v1.x(), v1.y(), v2.x(), v2.y(), penColor());
	//�˴����Ի��ƶ����Χ�еķ�ʽ��ʾ����ѡ�У�Ҳ��������ȷ��ѡ����ʾ��ʽ
	DrawSelectedBoundingBoxi(hDC, this, pCamera);
}

//��Χ����ʰȡ���
void CG2DLineSegment::computeBoundingBox() //�����Χ��
{
	mABox.setNull();  //�����
	Vec3d s = mMat * Vec3d(mStart);		//����ʵ�����
	Vec3d e = mMat * Vec3d(mEnd);		//����ʵ���յ�
	mABox.addPoint(Vec2d(s.x(), s.y()));	//���
	mABox.addPoint(Vec2d(e.x(), e.y()));	//�յ�
	setBoundsDirty(false);
}

bool CG2DLineSegment::Picked(const Vec2d& p, double radius) //�Ƿ�ʰȡ��
{
	//������λ�úͷ�Χ����Χr���Ը�����Ҫ��ΪԲ�뾶�������α߳���һ�룩
	setBoundsDirty(true);
	ABox2d abox = BoundingABox();
	ABox2d sbox(p, radius);
	Vec3d s = mMat * Vec3d(mStart); //���ݼ��α任����ʵ�����
	Vec3d e = mMat * Vec3d(mEnd); //���ݼ��α任����ʵ���յ�
	Vec2d End(e.x(), e.y()), Start(s.x(), s.y());
	if (abox.intersects(sbox)) //��������߶ΰ�Χ���ڣ���һ���жϾ���
	{
		//�㵽ֱ�߶εľ��루ʸ������P�㵽�߶�SE��
		Vec2d ES = End - Start;
		Vec2d PS = p - Start;
		Vec2d PE = p - End;
		double c = ES.dot(PS);//ES*PS
		if (c <= 0) //P����ES�ӳ��߷���
			return false;
		double d = ES.lengthSquared();
		if (c >= d) //P����SE�ӳ��߷���
			return false;
		double r = c / d;
		double px = Start.x() + (End.x() - Start.x()) * r;
		double py = Start.y() + (End.y() - Start.y()) * r;
		Vec2d S = Vec2d(px, py);
		double dis = (p - S).length();
		if (dis <= radius)
			return true;
	}
	return false;
}

// ��ȡ���ӿ��ڵİ�Χ��(�����ڻ��ƶ���İ�Χ�У�
ABox2i CG2DLineSegment::BoundingABoxi(CG2DCamera* pCamera)
{
	Vec3d s = mMat * Vec3d(mStart); //���ݼ��α任����ʵ�����
	Vec3d e = mMat * Vec3d(mEnd); //���ݼ��α任����ʵ���յ�
	Vec2i v1 = pCamera->WorldtoViewPort(Vec2d(s.x(), s.y()));
	Vec2i v2 = pCamera->WorldtoViewPort(Vec2d(e.x(), e.y()));
	ABox2i abox;
	abox.addPoint(v1);
	abox.addPoint(v2);
	return abox;
}
