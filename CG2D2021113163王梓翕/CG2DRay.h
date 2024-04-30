#ifndef _CG2DRay_H_INCLUDED
#define _CG2DRay_H_INCLUDED

#include "Vector2.h"
#include "CG2DRenderable.h"

class CG2DRay : public CG2DRenderable {
	DECLARE_SERIAL(CG2DRay)
public:
    CG2DRay();
    CG2DRay(const Vec2d& start, const Vec2d& direction); // 根据起点和方向构造射线
    CG2DRay(const CG2DRay& other);
    virtual ~CG2DRay();

public:
	//序列化
	virtual void Serialize(CArchive& ar) override;
	//绘制，使用CGDI2DRenderContext、CGDI2DCamera
	virtual void Render(CG2DRenderContext* pRC, CG2DCamera* pCamera) override; //绘制对象，使用指定相机
	//包围盒与拾取相关
	virtual void computeBoundingBox(); //计算包围盒

protected:
    Vec2d mStart;       // 起点
    Vec2d mDirection;   // 方向
};

#endif // _CG2DRay_H_INCLUDED
