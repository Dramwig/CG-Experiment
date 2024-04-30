#ifndef _CG2DLine_H_INCLUDED
#define _CG2DLine_H_INCLUDED
#include "Vector2.h"
#include "CG2DRenderable.h"
class CG2DLine : public CG2DRenderable
{
	DECLARE_SERIAL(CG2DLine)
public:
	CG2DLine();
	CG2DLine(const Vec2d& s, const Vec2d& e); //根据两点构建
	CG2DLine(const CG2DLine& other);
	virtual ~CG2DLine();
public:
	//序列化
	virtual void Serialize(CArchive& ar) override;
	//绘制，使用CGDI2DRenderContext、CGDI2DCamera
	virtual void Render(CG2DRenderContext* pRC, CG2DCamera* pCamera) override; //绘制对象，使用指定相机
	//包围盒与拾取相关
	virtual void computeBoundingBox(); //计算包围盒
protected:
	Vec2d mStart, mEnd; //起点、终点坐标
};
#endif //_CG2DLineSegment_H_INCLUDED
