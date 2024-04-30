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
	//绘制线段对象，线段对象的数据是基于世界坐标系，绘制时要转换到设备坐标系
	Vec2i v1 = pCamera->WorldtoViewPort(mStart);
	Vec2i v2 = pCamera->WorldtoViewPort(mEnd);
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
}
//包围盒与拾取相关
void CG2DLineSegment::computeBoundingBox() //计算包围盒
{
	mABox.setNull(); //先清空
	mABox.addPoint(mStart); //起点
	mABox.addPoint(mEnd); //终点
	setBoundsDirty(false); //设置包围盒已经计算
}