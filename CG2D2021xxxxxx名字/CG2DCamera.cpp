#include "pch.h"
#include "CG2DCamera.h"
IMPLEMENT_SERIAL(CG2DCamera, CGObject, 1)
CG2DCamera::CG2DCamera()
	:CGObject(CString("CG2DCamera"))
	, mViewPort(0, 0, 1, 1) //需要根据具体设置进行修改
{
	cameraViewportOffleft = 0;
	cameraViewportOffbottom = 0;
	cameraViewportOffright = -0;
	cameraViewportOfftop = -0;
}
CG2DCamera::CG2DCamera(const CString& name)
	: CGObject(CString(name))
	, mViewPort(0, 0, 1, 1) //需要根据具体设置进行修改
{
	cameraViewportOffleft = 0;
	cameraViewportOffbottom = 0;
	cameraViewportOffright = -0;
	cameraViewportOfftop = -0;
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
	//return Vec2i(int(p.x()), int(-p.y())+ mClientHeight);
	//如果画布坐标系在客户区中心，x向右，y向上，则使用以下函数。必须配套对应
	//return Vec2i(int(p.x()+ mClientWidth/2.0), int(-p.y() + mClientHeight /2.0));
	//观察流程
	Vec2d v(p);
	v = WCStoVCS(v); //从世界坐标系转到观察坐标系
	v = VCStoNCS(v); //从观察坐标系转到虚拟设备坐标系
	Vec2i v2 = NCStoDCS(v); //从虚拟设备坐标系转到设备坐标系
	
	return v2; 
}

//视口转换到世界坐标系（二维）
Vec2d CG2DCamera::ViewPorttoWorld(const Vec2i& p)
{
	//此处简单映射实现用于测试，画布坐标系设在客户区左下角，x向右，y向上。
	//观察窗口与视口一样的大小。视口与客户区重叠
	//return Vec2d(p.x(), double(mClientHeight)-p.y());
	//如果画布坐标系在客户区中心，x向右，y向上，则使用以下函数。 必须配套对应
	//return Vec2d(p.x() - mClientWidth/2.0, mClientHeight/2.0 - p.y());
	//观察流程
	Vec2d v = DCStoNCS(p);//从设备坐标系转到虚拟设备坐标系
	v = NCStoVCS(v); //从虚拟设备坐标系转到观察坐标系
	return VCStoWCS(v); //从观察坐标系转到世界坐标系
}
Vec2d CG2DCamera::ViewPorttoWorld(const Vec2d& p)
{
	Vec2d v = DCStoNCS(p);//从设备坐标系转到虚拟设备坐标系
	v = NCStoVCS(v); //从虚拟设备坐标系转到观察坐标系
	return VCStoWCS(v); //从观察坐标系转到世界坐标系
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
//观察窗口设置
void CG2DCamera::SetAspectRatio(double aspect) //设置观察窗口的宽高比
{

}
void CG2DCamera::SetWindowLeft(double left)
{
	if (left < mRight)
		mLeft = left;
}
void CG2DCamera::SetWindowBottom(double bottom)
{
	if (bottom < mTop)
		mBottom = bottom;
}
void CG2DCamera::SetWindowRight(double right)
{
	if (right > mLeft)
		mRight = right;
}
void CG2DCamera::SetWindowTop(double top)
{
	if (top > mBottom)
		mTop = top;
}

void CG2DCamera::Zoom(double ratio) //观察窗口缩放（二维），两个方向同比例缩放，参数应大于0。
{	
	if (ratio>0) {
		mMat.preMultiply(Mat3d::getScaling(ratio, ratio));
	}
	else {
		throw std::runtime_error("错误的缩放比例，ratio小于0");
	}
}
void CG2DCamera::Zoom(const Vec2d& lb, const Vec2d& rt)//观察窗口缩放（二维）（指定窗口参数，但要保证两方向同比例缩放）
{

}
//观察坐标系设置
void CG2DCamera::Move(double tx, double ty)//移动观察坐标系（二维）
{
	mMat.preMultiply(Mat3d::getTranslation(tx, ty));
}
void CG2DCamera::Rotate(double degree)//旋转观察坐标系（绕坐标系原点，逆时针方向为正，单位：度）（二维）
{
	mMat.preMultiply(Mat3d::getRotation(degree, Vector2<double>(0, 0)));
}
void CG2DCamera::Reset() //重置到观察坐标系默认参数（二维）
{
	mMat.setIdentity();
}
//视口设置：通过viewport()得到视口
void CG2DCamera::ViewportOffset() //边界移动
{
	ViewportOffset(cameraViewportOffleft, cameraViewportOffbottom, cameraViewportOffright, cameraViewportOfftop);
}
void CG2DCamera::ViewportOffset(int offleft , int offbottom, int offright, int offtop) //边界移动
{
	mViewPort.setLeft(mViewPort.left() + offleft);
	mViewPort.setBottom(mViewPort.bottom() + offbottom);
	mViewPort.setWidth(mViewPort.width() + offright - offleft);
	mViewPort.setHeith(mViewPort.height() + offtop - offbottom);
}
void CG2DCamera::ViewportSet(int width, int height)
{
	mViewPort.setWidth(width);
	mViewPort.setHeith(height);
}

//二维图形观察变换（世界坐标系到观察坐标系）（二维）
Vec2d CG2DCamera::WCStoVCS(const Vec2d& p) {
	Mat3 nMat = mMat.getInverse(); //逆变换矩阵
	Vec3d s = nMat * Vec3d(p);
	return Vec2d(s.x(), s.y());
}

//二维图形窗视变换（观察坐标系到规范化设备坐标系）（二维）（实验中使用虚拟设备坐标系代替规范化设备坐标系）
Vec2d CG2DCamera::VCStoNCS(const Vec2d& p) {
	Mat3 moveMat = Mat3d::getTranslation(-mLeft, -mBottom);
	Mat3 scaleMat = Mat3d::getScaling((NCSViewPortRight()- NCSViewPortLeft()) / (mRight - mLeft), (NCSViewPortTop()- NCSViewPortBottom()) / (mTop - mBottom));
	Mat3 move2Mat = Mat3d::getTranslation(NCSViewPortLeft(), NCSViewPortBottom());
	int test = NCSViewPortRight();
	int test2 = NCSViewPortLeft();
	int test3 = NCSViewPortRight()- NCSViewPortLeft();
	double test4 = (NCSViewPortRight() - NCSViewPortLeft()) / (mRight - mLeft);
	Mat3 nMat = move2Mat * scaleMat * moveMat;
	Vec3d s = nMat * Vec3d(p);
	return Vec2d(s.x(), s.y());
}

//二维图形视口变换（规范坐标系到设备坐标系）（二维）（实验中使用虚拟设备坐标系代替规范化设备坐标系）
Vec2i CG2DCamera::NCStoDCS(const Vec2d& p) {
	return Vec2i(int(p.x()), int(mClientHeight - p.y()));
}

//设备坐标系到规范化设备坐标系（二维）（实验中使用虚拟设备坐标系代替规范化设备坐标系）
Vec2d CG2DCamera::DCStoNCS(const Vec2i& p) {
	return Vec2d(p.x(), mClientHeight - p.y());
}
Vec2d CG2DCamera::DCStoNCS(const Vec2d& p) {
	return Vec2d(p.x(), mClientHeight - p.y());
}

//规范化设备坐标系到观察坐标系（二维）（实验中使用虚拟设备坐标系代替规范化设备坐标系）
Vec2d CG2DCamera::NCStoVCS(const Vec2d& p) {
	Mat3 moveMat = Mat3d::getTranslation(-mLeft, -mBottom);
	Mat3 scaleMat = Mat3d::getScaling((NCSViewPortRight() - NCSViewPortLeft()) / (mRight - mLeft), (NCSViewPortTop() - NCSViewPortBottom()) / (mTop - mBottom));
	Mat3 move2Mat = Mat3d::getTranslation(NCSViewPortLeft(), NCSViewPortBottom());
	Mat3 nMat = move2Mat * scaleMat * moveMat;
	Vec3d s = nMat.getInverse() * Vec3d(p);
	return Vec2d(s.x(), s.y());
}

//观察坐标系到世界坐标系（二维）
Vec2d CG2DCamera::VCStoWCS(const Vec2d& p) {
	Vec3d s = mMat * Vec3d(p); //计算实际起点
	return Vec2d(s.x(), s.y());
}
