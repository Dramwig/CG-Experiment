#ifndef _CG3DCamera_H_INCLUDED 
#define _CG3DCamera_H_INCLUDED 

#include "CGObject.h" 
#include "CG2DViewPort.h" 

class CG3DCamera : public CGObject
{
	DECLARE_SERIAL(CG3DCamera)
public:
	CG3DCamera();
	CG3DCamera(const CString& name);
	virtual ~CG3DCamera() = default;

	virtual void Serialize(CArchive& ar) override;
	//视口 
	const CG2DViewPort& viewport() const { return mViewPort; }
	CG2DViewPort& viewport() { return mViewPort; }

	//客户区 
	void SetClientWidth(int width) { mClientWidth = width; }
	void SetClientHeight(int height) { mClientHeight = height; }
	int ClientWidth() const { return mClientWidth; }
	int ClientHeight() const { return mClientHeight; }

	//观察体 
	double Left() const { return mLeft; }
	double Bottom() const { return mBottom; }
	double Right() const { return mRight; }
	double Top() const { return  mTop; }
	double Near() const { return mNear; }
	double Far() const { return mFar; }
	//观察坐标系 
	double EyeX() const { return mEyeX; }
	double EyeY() const { return mEyeY; }
	double EyeZ() const { return mEyeZ; }
	double UpX() const { return mUpX; }
	double UpY() const { return mUpY; }
	double UpZ() const { return mUpZ; }
	//被观察点 
	double RefX() const { return mRefX; }
	double RefY() const { return mRefY; }
	double RefZ() const { return mRefZ; }

	//取景定义，设置渲染模式下的投影变换 
	//mode=0为正交投影（三维），mode=1为透视投影，mode=2或其他为正交投影（二维） 
	int ProjectionMode() { return mProjectionMode; }
	void SetProjectionMode(int mode) { if (mode >= 0 && mode <= 2) mProjectionMode = mode; }
	virtual void Projection(int mode = 0);

	//移动相机 
	void Move(double tx, double ty, double tz);
	void SetEye(double x, double y, double z);
	//观察窗口（左下、右上）调整，保持与视口相同高宽比 
	void Zoom(const Vec2d& lb, const Vec2d& rt);
	void Zoom(double r);
	//重置相机坐标系及近、远截面 
	void Reset();

protected:
	CG2DViewPort mViewPort; //对应视口，在设备坐标系（客户区）中定义，默认与客户区相同大小。 
	int mClientWidth = 1;
	int mClientHeight = 1;

	//需要序列化的属性 
	//投影模式，0=正交投影（三维），1=透视投影，2=正交投影（二维） 
	int mProjectionMode = 0;
	//视图客户区矩形 
	//观察空间（在观察坐标系中定义）矩形的左、右、下、上 
	double mLeft = -10.0;
	double mBottom = -10.0;
	double mRight = 10.0;
	double mTop = 10.0;
	double mNear = 1.0;   //近截面 
	double mFar = 100000.0;  //远截面 
	//相机位置，表示观察坐标系原点的在世界坐标系中的位置 
	double mEyeX = 0.0;
	double mEyeY = 0.0;
	double mEyeZ = 1000.0;
	//向上方向(默认0,1,0)，二维中用到x，y，表示观察坐标系Y轴的方向矢量 
	double mUpX = 0.0;
	double mUpY = 1.0;
	double mUpZ = 0.0;
	//被观察点(默认0,0,0)（三维） 
	double mRefX = 0.0;
	double mRefY = 0.0;
	double mRefZ = 0.0;
};

#endif //_CG3DCamera_H_INCLUDED 
