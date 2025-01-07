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

//ȡ�����壬������Ⱦģʽ�µ�ͶӰ�任 
void CG3DCamera::Projection(int mode/* = 0*/)
{
	//�����۲촰�����ӿ�ͬ���� 
	Zoom(Vec2d(Left(), Bottom()), Vec2d(Right(), Top()));
	//�����ӿ� 
	glViewport(mViewPort.x(), mViewPort.y(), mViewPort.width(), mViewPort.height());

	//����ͶӰ�任 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glRenderMode(GL_RENDER);  //������Ⱦ����ѡ�� 
	if (mode == 0) //��ƽ��ͶӰ������ͶӰ�� 
	{
		glOrtho(mLeft, mRight, mBottom, mTop, mNear, mFar);
	}
	else if (mode == 1) //͸��ͶӰ 
	{
		glFrustum(mLeft, mRight, mBottom, mTop, mNear, mFar);
		//gluPerspective(45, (wRight- wLeft)/(wTop- wBottom), wNear, wFar); 
	}
	else //����ͶӰ����άЧ���� 
	{
		gluOrtho2D(mLeft, mRight, mBottom, mTop);
	}

	//ģ����ͼ�任 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); //�ӵ㣨������������������ϵ 
	gluLookAt(mEyeX, mEyeY, mEyeZ, mRefX, mRefY, mRefZ, mUpX, mUpY, mUpZ); //�����ӵ���� 
}
//�ƶ��ӵ㣨��ά�� 
void CG3DCamera::Move(double tx, double ty, double tz) //�ƶ��۲�����ϵ����ά�� 
{
	mEyeX += tx;
	mEyeY += ty;
	mEyeZ += tz;
}
void CG3DCamera::SetEye(double x, double y, double z) {
	mEyeX = x; mEyeY = y; mEyeZ = z;
}

//�۲촰�����š����ڽ�����ȡ�۲촰�ڣ��ڿͻ����п���� 
void CG3DCamera::Zoom(const Vec2d& lb, const Vec2d& rt)
{
	//�ӿڿ�߱� 
	double aspect = double(mViewPort.width()) / double(mViewPort.height());
	double h = rt.y() - lb.y();
	double w = rt.x() - lb.x();
	if (aspect > 1)
	{
		w = aspect * h; //�Ը߶�Ϊ��׼�����ֹ۲촰�����ӿڵĸ߿����ͬ��ʹ�۲�Ч�������Ρ� 
		mBottom = lb.y();
		mTop = rt.y();
		mLeft = -w / 2;
		mRight = w / 2;
	}
	else
	{
		h = w / aspect; //�Կ��Ϊ��׼�����ֹ۲촰�����ӿڵĸ߿����ͬ��ʹ�۲�Ч�������Ρ� 
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
void CG3DCamera::Reset() //���õ�Ĭ�ϲ��� 
{
	//�˴��������۲�����ϵ�����ֹ۲촰�ڲ��� 
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
