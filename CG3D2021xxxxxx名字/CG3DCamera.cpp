#include "pch.h" 
#include "CG3DCamera.h" 
#include "Vector2.h" 

IMPLEMENT_SERIAL(CG3DCamera, CGObject, 1)

CG3DCamera::CG3DCamera()
	:CGObject(CString("CG3DCamera"))
{
}

CG3DCamera::CG3DCamera(const CString& name)
	: CGObject(CString(name))
{

}

void CG3DCamera::Serialize(CArchive& ar)
{
	CGObject::Serialize(ar);

	mViewPort.Serialize(ar);
	if (ar.IsStoring())
	{
		ar << mProjectionMode;
		ar << mLeft << mBottom << mRight << mTop << mNear << mFar;
		ar << mEyeX << mEyeY << mEyeZ << mUpX << mUpY << mUpZ << mRefX << mRefY << mRefZ;
	}
	else
	{
		ar >> mProjectionMode;
		ar >> mLeft >> mBottom >> mRight >> mTop >> mNear >> mFar;
		ar >> mEyeX >> mEyeY >> mEyeZ >> mUpX >> mUpY >> mUpZ >> mRefX >> mRefY >> mRefZ;
	}
}

//取景定义，设置渲染模式下的投影变换 
void CG3DCamera::Projection(int mode/* = 0*/)
{
	//调整观察窗口与视口同比例 
	Zoom(Vec2d(Left(), Bottom()), Vec2d(Right(), Top()));
	//设置视口 
	glViewport(mViewPort.x(), mViewPort.y(), mViewPort.width(), mViewPort.height());

	//设置投影变换 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glRenderMode(GL_RENDER);  //用于渲染（非选择） 
	if (mode == 0) //正平行投影（正交投影） 
	{
		glOrtho(mLeft, mRight, mBottom, mTop, mNear, mFar);
	}
	else if (mode == 1) //透视投影 
	{
		glFrustum(mLeft, mRight, mBottom, mTop, mNear, mFar);
		//gluPerspective(45, (wRight- wLeft)/(wTop- wBottom), wNear, wFar); 
	}
	else //正交投影（二维效果） 
	{
		gluOrtho2D(mLeft, mRight, mBottom, mTop);
	}

	//模型视图变换 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); //视点（相机）相对于世界坐标系 
	gluLookAt(mEyeX, mEyeY, mEyeZ, mRefX, mRefY, mRefZ, mUpX, mUpY, mUpZ); //设置视点参数 
}
//移动视点（三维） 
void CG3DCamera::Move(double tx, double ty, double tz) //移动观察坐标系（三维） 
{
	mEyeX += tx;
	mEyeY += ty;
	mEyeZ += tz;
}
void CG3DCamera::SetEye(double x, double y, double z) {
	mEyeX = x; mEyeY = y; mEyeZ = z;
}

//观察窗口缩放。用于交互获取观察窗口（在客户区中框出） 
void CG3DCamera::Zoom(const Vec2d& lb, const Vec2d& rt)
{
	//视口宽高比 
	double aspect = double(mViewPort.width()) / double(mViewPort.height());
	double h = rt.y() - lb.y();
	double w = rt.x() - lb.x();
	if (aspect > 1)
	{
		w = aspect * h; //以高度为基准，保持观察窗口与视口的高宽比相同，使观察效果不变形。 
		mBottom = lb.y();
		mTop = rt.y();
		mLeft = -w / 2;
		mRight = w / 2;
	}
	else
	{
		h = w / aspect; //以宽度为基准，保持观察窗口与视口的高宽比相同，使观察效果不变形。 
		mLeft = lb.x();
		mRight = rt.x();
		mBottom = -h / 2;
		mTop = h / 2;
	}
}
void CG3DCamera::Zoom(double r) {
	const Vec2d& lb = Vec2d(mLeft, mBottom);
	const Vec2d& rt = Vec2d(mRight, mTop);
	Zoom(lb * r, rt * r);
}
void CG3DCamera::Reset() //重置到默认参数 
{
	//此处仅调整观察坐标系，保持观察窗口参数 
	mFar = 100000.0;
	mNear = 0.0;
	mEyeX = 0.0;
	mEyeY = 0.0;
	mEyeZ = 1000.0;
	mUpX = 0.0;
	mUpY = 1.0;
	mUpZ = 0.0;
	mRefX = 0.0;
	mRefY = 0.0;
	mRefZ = 0.0;
}
