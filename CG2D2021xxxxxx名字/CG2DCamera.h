#ifndef _CG2DCamera_H_INCLUDED
#define _CG2DCamera_H_INCLUDED
#include "CGObject.h"
#include "CG2DViewPort.h"
#include "Matrix33.h"
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
	virtual Vec2d ViewPorttoWorld(const Vec2d& p);
	//观察窗口宽度与视口宽度的比例
	double WidthFactorWindowtoViewPort();
	//观察窗口高度与视口高度的比例
	double HeightFactorWindowtoViewPort();
	//观察窗口
	double Left() const { return mLeft; }
	double Bottom() const { return mBottom; }
	double Right() const { return mRight; }
	double Top() const { return mTop; }
	void SetAspectRatio(double aspect); //设置观察窗口的宽高比
	int cameraViewportOffleft, cameraViewportOffbottom, cameraViewportOffright, cameraViewportOfftop;//视口边界偏移
protected:
	CG2DViewPort mViewPort; //对应视口，在设备坐标系（客户区）中定义，默认与客户区相同大小。
	//视图客户区矩形
	int mClientWidth = 1;
	int mClientHeight = 1;
	//观察参数（观察范围：观察窗口（二维）)
	double mLeft = -1000, mBottom = -1000, mRight = 1000, mTop = 1000; //观察窗口（在观察坐标系中定义）矩形的左、右、下、上(默认 - 1000, -1000, 1000, 1000，因为要操作窗口边界)
protected:
	//由平移矢量确定坐标原点，旋转角度确定坐标系方向
	Mat3 mMat; //观察坐标系相对于世界坐标系的变换矩阵（列向量形式）
public:
	//观察窗口设置
	void SetWindowLeft(double left);
	void SetWindowBottom(double bottom);
	void SetWindowRight(double right);
	void SetWindowTop(double top);
	void Zoom(double ratio); //观察窗口缩放（二维），两个方向同比例缩放，参数应大于0。
	void Zoom(const Vec2d& lb, const Vec2d& rt);//观察窗口缩放（二维）（指定窗口参数，但要保证两方向同比例缩放）
	//观察坐标系设置
	void Move(double tx, double ty); //移动观察坐标系（二维）
	void Rotate(double degree); //旋转观察坐标系（绕坐标系原点，逆时针方向为正，单位：度）（二维）
	void Reset(); //重置到观察坐标系默认参数（二维）
	//视口设置：通过viewport()得到视口
	void ViewportOffset(); 
	void ViewportOffset(int offleft, int offbottom, int offright, int offtop); //边界移动
	void ViewportSet(int width, int height);
	//虚拟设备坐标系中视口参数（视口mViewPort定义是相对客户区，要转换到相对于虚拟设备坐标系）
	int NCSViewPortLeft() const { return mViewPort.left(); }
	int NCSViewPortBottom() const {
		return mClientHeight - mViewPort.height() - mViewPort.bottom();
	}
	int NCSViewPortRight() const { return mViewPort.left() + mViewPort.width(); }
	int NCSViewPortTop() const { return mClientHeight - mViewPort.bottom(); }
	//二维图形观察变换（世界坐标系到观察坐标系）（二维）
	Vec2d WCStoVCS(const Vec2d& p);
	//二维图形窗视变换（观察坐标系到规范化设备坐标系）（二维）（实验中使用虚拟设备坐标系代替规范化设备坐标系）
	Vec2d VCStoNCS(const Vec2d& p);
	//二维图形视口变换（规范坐标系到设备坐标系）（二维）（实验中使用虚拟设备坐标系代替规范化设备坐标系）
	Vec2i NCStoDCS(const Vec2d& p);
	//设备坐标系到规范化设备坐标系（二维）（实验中使用虚拟设备坐标系代替规范化设备坐标系）
	Vec2d DCStoNCS(const Vec2i& p);
	Vec2d DCStoNCS(const Vec2d& p);
	//规范化设备坐标系到观察坐标系（二维）（实验中使用虚拟设备坐标系代替规范化设备坐标系）
	Vec2d NCStoVCS(const Vec2d& p);
	//观察坐标系到世界坐标系（二维）
	Vec2d VCStoWCS(const Vec2d& p);

};
#endif //_CG2DCamera_H_INCLUDED
