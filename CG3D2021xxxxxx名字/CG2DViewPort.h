#ifndef _CG2DViewPort_H_INCLUDED
#define _CG2DViewPort_H_INCLUDED
#include "AABBox2.h"
#include "Vector3.h"
#include "CGObject.h"
// 视口：绘图客户区中相对于视口坐标系的一个矩形区域。与一个相机关联。
class CG2DViewPort : public CGObject
{
	DECLARE_SERIAL(CG2DViewPort)
public:
	//默认构造（left=0, bottom=0, width=0, height=0）
	CG2DViewPort();
	CG2DViewPort(int left, int bottom, int width, int height);
	virtual ~CG2DViewPort() = default;
	virtual void Serialize(CArchive& ar);
	bool isNull() { return mWidth == 0 || mHeight == 0; }
	//设置函数，要确保minCorner是左下角、maxCorner是右上角
	//设置（left、bottom、width、height）
	void set(int xl, int yb, int w, int h) { mXLeft = xl; mYBottom = yb; mWidth = w; mHeight = h; }
	void setLeft(int left) { mXLeft = left; }
	void setBottom(int bottom) { mYBottom = bottom; }
	void setWidth(int width) { mWidth = width; }
	void setHeith(int height) { mHeight = height; }
	void setX(int x) { mXLeft = x; }
	int x() const { return mXLeft; }
	void setY(int y) { mYBottom = y; }
	int y() const { return mYBottom; }
	int left() const { return mXLeft; }
	int bottom() const { return mYBottom; }
	int width() const { return mWidth; }
	int height() const { return mHeight; }
	Vec2f center() const { return Vec2f(mXLeft + mWidth / 2.0f, mYBottom + mHeight / 2.0f); }
	Recti rect() const { return Recti(Vec2i(left(), bottom()), Vec2i(width(), height())); }
	void setClearColor(COLORREF c) { mClearColor = c; }
	COLORREF clearColor() const { return mClearColor; }
	//相对于设备坐标系的点是否在视口内
	bool isPointInside(int x, int y) const;
protected:
	int mXLeft = 0; //左下角X坐标，相对于设备坐标系
	int mYBottom = 0; //左下角Y坐标，相对于设备坐标系
	int mWidth = 1; //视口宽度（X方向）
	int mHeight = 1; //视口高度（Y方向）
	COLORREF mClearColor = RGB(255, 255, 255); //背景色
};
#endif //_CG2DViewPort_H_INCLUDED
