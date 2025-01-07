#include "pch.h"
#include "CG2DLineSegment.h"
#include "CG2DRenderContext.h"
#include "CG2DCamera.h"
IMPLEMENT_SERIAL(CG2DLineSegment, CG2DRenderable, 1)
CG2DLineSegment::CG2DLineSegment()
	: CG2DLineSegment(Vec2d(0, 0), Vec2d(0, 0)) //委托构造函数
{
}
CG2DLineSegment::CG2DLineSegment(const Vec2d & s, const Vec2d & e)
	: CG2DRenderable(CString("CG2DLineSegment")), mStart(s), mEnd(e)
{
	mName.Format(_T("直线段-%ld"), sID);
}
CG2DLineSegment::CG2DLineSegment(const Vec2d & s, const Vec2d & dir, double length)
	: CG2DLineSegment(s, Vec2d(0, 0)) //委托构造函数
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
	mName.Format(_T("直线段-%ld"), sID);
}
CG2DLineSegment::CG2DLineSegment(const CG2DLineSegment & other)
	: CG2DLineSegment(other.mStart, other.mEnd) //委托构造函数
{
}
CG2DLineSegment::~CG2DLineSegment()
{
}
//序列化
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
//绘制
void CG2DLineSegment::Render(CG2DRenderContext* pRC, CG2DCamera* pCamera) //绘制对象，使用指定相机
{
	if (pRC == nullptr || pCamera == nullptr)
		return;
	HDC hDC = pRC->GetMemHDC();
	//使用变换矩阵后图形的绘制要使用矩阵计算
	Vec3d s = mMat * Vec3d(mStart); //计算实际起点
	Vec3d e = mMat * Vec3d(mEnd); //计算实际终点
	Vec2i v1 = pCamera->WorldtoViewPort(Vec2d(s.x(), s.y()));
	Vec2i v2 = pCamera->WorldtoViewPort(Vec2d(e.x(), e.y()));
	//测试算法
	int algrithm = pRC->LineAlgorithm(); //通过绘制环境对应的View获取Ribbon面板中选中的直线段绘制算法
	if (algrithm == (int)LineAlgorithm::CDC)
	{ //根据线段的线型、线宽、颜色属性创建画笔
		CPen pen(penStyle(), penWidth(), penColor());
		if (hDC != 0) //使用Windows的图形设备接口API（GDI函数）绘制
		{ //画笔选入绘制环境
			HPEN hOldPen = (HPEN)::SelectObject(hDC, pen.GetSafeHandle());
			::MoveToEx(hDC, v1.x(), v1.y(), nullptr);
			::LineTo(hDC, v2.x(), v2.y());
			::SelectObject(hDC, hOldPen); //恢复原绘制环境的画笔
		}

	}
	else if (algrithm == (int)LineAlgorithm::DDA)
		pRC->DDALine(v1.x(), v1.y(), v2.x(), v2.y(), penColor());
	else if (algrithm == (int)LineAlgorithm::MidPoint)
		pRC->MidPointLine(v1.x(), v1.y(), v2.x(), v2.y(), penColor());
	else if (algrithm == (int)LineAlgorithm::Bresenham)
		pRC->BresenhamLine(v1.x(), v1.y(), v2.x(), v2.y(), penColor());
	//此处仅以绘制对象包围盒的方式显示对象被选中，也可以自行确定选中显示方式
	DrawSelectedBoundingBoxi(hDC, this, pCamera);
}

//包围盒与拾取相关
void CG2DLineSegment::computeBoundingBox() //计算包围盒
{
	mABox.setNull();  //先清空
	Vec3d s = mMat * Vec3d(mStart);		//计算实际起点
	Vec3d e = mMat * Vec3d(mEnd);		//计算实际终点
	mABox.addPoint(Vec2d(s.x(), s.y()));	//起点
	mABox.addPoint(Vec2d(e.x(), e.y()));	//终点
	setBoundsDirty(false);
}

bool CG2DLineSegment::Picked(const Vec2d& p, double radius) //是否拾取到
{
	//（给定位置和范围，范围r可以根据需要设为圆半径或正方形边长的一半）
	setBoundsDirty(true);
	ABox2d abox = BoundingABox();
	ABox2d sbox(p, radius);
	Vec3d s = mMat * Vec3d(mStart); //根据几何变换计算实际起点
	Vec3d e = mMat * Vec3d(mEnd); //根据几何变换计算实际终点
	Vec2d End(e.x(), e.y()), Start(s.x(), s.y());
	if (abox.intersects(sbox)) //如果点在线段包围盒内，进一步判断距离
	{
		//点到直线段的距离（矢量法：P点到线段SE）
		Vec2d ES = End - Start;
		Vec2d PS = p - Start;
		Vec2d PE = p - End;
		double c = ES.dot(PS);//ES*PS
		if (c <= 0) //P点在ES延长线方向
			return false;
		double d = ES.lengthSquared();
		if (c >= d) //P点在SE延长线方向
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

// 获取在视口内的包围盒(仅用于绘制对象的包围盒）
ABox2i CG2DLineSegment::BoundingABoxi(CG2DCamera* pCamera)
{
	Vec3d s = mMat * Vec3d(mStart); //根据几何变换计算实际起点
	Vec3d e = mMat * Vec3d(mEnd); //根据几何变换计算实际终点
	Vec2i v1 = pCamera->WorldtoViewPort(Vec2d(s.x(), s.y()));
	Vec2i v2 = pCamera->WorldtoViewPort(Vec2d(e.x(), e.y()));
	ABox2i abox;
	abox.addPoint(v1);
	abox.addPoint(v2);
	return abox;
}
