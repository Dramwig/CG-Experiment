#ifndef _CG2DLineSegment_H_INCLUDED
#define _CG2DLineSegment_H_INCLUDED
#include "Vector2.h"
#include "CG2DRenderable.h"
class CG2DLineSegment : public CG2DRenderable
{
	DECLARE_SERIAL(CG2DLineSegment)
public:
	CG2DLineSegment();
	CG2DLineSegment(const Vec2d& s, const Vec2d& e); //根据两点构建
	CG2DLineSegment(const Vec2d& s, const Vec2d& dir, double length); //根据起点、方向、长度构建
	CG2DLineSegment(const CG2DLineSegment& other);
	virtual ~CG2DLineSegment();
public:
	//序列化
	virtual void Serialize(CArchive& ar) override;
	//绘制，使用CGDI2DRenderContext、CGDI2DCamera
	virtual void Render(CG2DRenderContext* pRC, CG2DCamera* pCamera) override; //绘制对象，使用指定相机
	//包围盒与拾取相关
	virtual void computeBoundingBox(); //计算包围盒
protected:
	Vec2d mStart, mEnd; //起点、终点坐标
public:
	virtual bool Picked(const Vec2d& p, double radius); //（二维）是否拾取到
	virtual ABox2i BoundingABoxi(CG2DCamera* pCamera); //获取在视口内的包围盒(仅用于绘制对象的包围盒）
};
#endif //_CG2DLineSegment_H_INCLUDED
