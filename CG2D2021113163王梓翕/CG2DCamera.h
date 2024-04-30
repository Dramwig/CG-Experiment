#ifndef _CG2DCamera_H_INCLUDED
#define _CG2DCamera_H_INCLUDED
#include "CGObject.h"
#include "CG2DViewPort.h"
class CG2DCamera : public CGObject
{
	DECLARE_SERIAL(CG2DCamera)
public:
	CG2DCamera();
	CG2DCamera(const CString& name);
	virtual ~CG2DCamera() = default;
	//序列化
	virtual void Serialize(CArchive& ar) override;
	//视口
	const CG2DViewPort& viewport() const { return mViewPort; }
	CG2DViewPort& viewport() { return mViewPort; }
	//客户区
	void SetClientWidth(int width) { mClientWidth = width; }
	void SetClientHeight(int height) { mClientHeight = height; }
	int ClientWidth() const { return mClientWidth; }
	int ClientHeight() const { return mClientHeight; }
	//世界坐标系转换到视口（二维）(世界坐标系中的点位置对应到视口中的位置）
	virtual Vec2i WorldtoViewPort(const Vec2d& p);
	//视口转换到世界坐标系（二维）(视口中的点位置对应到世界坐标系中的位置）
	virtual Vec2d ViewPorttoWorld(const Vec2i& p);
	//观察窗口宽度与视口宽度的比例
	double WidthFactorWindowtoViewPort();
	//观察窗口高度与视口高度的比例
	double HeightFactorWindowtoViewPort();
	//观察窗口
	double Left() const { return mLeft; }
	double Bottom() const { return mBottom; }
	double Right() const { return mRight; }
	double Top() const { return mTop; }
protected:
	CG2DViewPort mViewPort; //对应视口，在设备坐标系（客户区）中定义，默认与客户区相同大小。
	//视图客户区矩形
	int mClientWidth = 1;
	int mClientHeight = 1;
	//观察参数（观察范围：观察窗口（二维）)
	double mLeft = -1, mBottom = -1, mRight = 1, mTop = 1; //观察窗口（在观察坐标系中定义）矩形的左、右、下、上(默认0, 0, 1, 1)
};
#endif //_CG2DCamera_H_INCLUDED