#include "pch.h"
#include "CG2DCamera.h"
IMPLEMENT_SERIAL(CG2DCamera, CGObject, 1)
CG2DCamera::CG2DCamera()
	:CGObject(CString("CG2DCamera"))
	, mViewPort(0, 0, 1, 1) //需要根据具体设置进行修改
{
}
CG2DCamera::CG2DCamera(const CString& name)
	: CGObject(CString(name))
	, mViewPort(0, 0, 1, 1) //需要根据具体设置进行修改
{
}
void CG2DCamera::Serialize(CArchive& ar)
{
	CGObject::Serialize(ar);
	mViewPort.Serialize(ar);
	if (ar.IsStoring())
	{
		ar << mLeft << mBottom << mRight << mTop;
	}
	else
	{
		ar >> mLeft >> mBottom >> mRight >> mTop;
	}
}
//世界坐标系转换到视口（二维）
Vec2i CG2DCamera::WorldtoViewPort(const Vec2d& p)
{
	//此处简单映射实现用于测试，画布坐标系设在客户区左下角，x向右，y向上。
	//观察窗口与视口一样的大小。视口与客户区重叠
	//return Vec2i(int(p.x()), int(-p.y()) + mClientHeight);
	//如果画布坐标系在客户区中心，x向右，y向上，则使用以下函数。必须配套对应
	return Vec2i(int(p.x()+ mClientWidth/2.0), int(-p.y() + mClientHeight /2.0));
}
//视口转换到世界坐标系（二维）
Vec2d CG2DCamera::ViewPorttoWorld(const Vec2i& p)
{
	//此处简单映射实现用于测试，画布坐标系设在客户区左下角，x向右，y向上。
	//观察窗口与视口一样的大小。视口与客户区重叠
	//return Vec2d(p.x(), double(mClientHeight) - p.y());
	//如果画布坐标系在客户区中心，x向右，y向上，则使用以下函数。 必须配套对应
	return Vec2d(p.x() - mClientWidth/2.0, mClientHeight/2.0 - p.y());
}
//观察窗口宽度与视口宽度的比例
double CG2DCamera::WidthFactorWindowtoViewPort()
{
	return (mRight - mLeft) / mViewPort.width();
}
//观察窗口高度与视口高度的比例
double CG2DCamera::HeightFactorWindowtoViewPort()
{
	return (mTop - mBottom) / mViewPort.height();
}
