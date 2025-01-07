#include "pch.h"
#include "CG2DCamera.h"
IMPLEMENT_SERIAL(CG2DCamera, CGObject, 1)
CG2DCamera::CG2DCamera()
	:CGObject(CString("CG2DCamera"))
	, mViewPort(0, 0, 1, 1) //��Ҫ���ݾ������ý����޸�
{
	cameraViewportOffleft = 0;
	cameraViewportOffbottom = 0;
	cameraViewportOffright = -0;
	cameraViewportOfftop = -0;
}
CG2DCamera::CG2DCamera(const CString& name)
	: CGObject(CString(name))
	, mViewPort(0, 0, 1, 1) //��Ҫ���ݾ������ý����޸�
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
//��������ϵת�����ӿڣ���ά��
Vec2i CG2DCamera::WorldtoViewPort(const Vec2d& p)
{
	//�˴���ӳ��ʵ�����ڲ��ԣ���������ϵ���ڿͻ������½ǣ�x���ң�y���ϡ�
	//�۲촰�����ӿ�һ���Ĵ�С���ӿ���ͻ����ص�
	//return Vec2i(int(p.x()), int(-p.y())+ mClientHeight);
	//�����������ϵ�ڿͻ������ģ�x���ң�y���ϣ���ʹ�����º������������׶�Ӧ
	//return Vec2i(int(p.x()+ mClientWidth/2.0), int(-p.y() + mClientHeight /2.0));
	//�۲�����
	Vec2d v(p);
	v = WCStoVCS(v); //����������ϵת���۲�����ϵ
	v = VCStoNCS(v); //�ӹ۲�����ϵת�������豸����ϵ
	Vec2i v2 = NCStoDCS(v); //�������豸����ϵת���豸����ϵ
	
	return v2; 
}

//�ӿ�ת������������ϵ����ά��
Vec2d CG2DCamera::ViewPorttoWorld(const Vec2i& p)
{
	//�˴���ӳ��ʵ�����ڲ��ԣ���������ϵ���ڿͻ������½ǣ�x���ң�y���ϡ�
	//�۲촰�����ӿ�һ���Ĵ�С���ӿ���ͻ����ص�
	//return Vec2d(p.x(), double(mClientHeight)-p.y());
	//�����������ϵ�ڿͻ������ģ�x���ң�y���ϣ���ʹ�����º����� �������׶�Ӧ
	//return Vec2d(p.x() - mClientWidth/2.0, mClientHeight/2.0 - p.y());
	//�۲�����
	Vec2d v = DCStoNCS(p);//���豸����ϵת�������豸����ϵ
	v = NCStoVCS(v); //�������豸����ϵת���۲�����ϵ
	return VCStoWCS(v); //�ӹ۲�����ϵת����������ϵ
}
Vec2d CG2DCamera::ViewPorttoWorld(const Vec2d& p)
{
	Vec2d v = DCStoNCS(p);//���豸����ϵת�������豸����ϵ
	v = NCStoVCS(v); //�������豸����ϵת���۲�����ϵ
	return VCStoWCS(v); //�ӹ۲�����ϵת����������ϵ
}

//�۲촰�ڿ�����ӿڿ�ȵı���
double CG2DCamera::WidthFactorWindowtoViewPort()
{
	return (mRight - mLeft) / mViewPort.width();
}
//�۲촰�ڸ߶����ӿڸ߶ȵı���
double CG2DCamera::HeightFactorWindowtoViewPort()
{
	return (mTop - mBottom) / mViewPort.height();
}
//�۲촰������
void CG2DCamera::SetAspectRatio(double aspect) //���ù۲촰�ڵĿ�߱�
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

void CG2DCamera::Zoom(double ratio) //�۲촰�����ţ���ά������������ͬ�������ţ�����Ӧ����0��
{	
	if (ratio>0) {
		mMat.preMultiply(Mat3d::getScaling(ratio, ratio));
	}
	else {
		throw std::runtime_error("��������ű�����ratioС��0");
	}
}
void CG2DCamera::Zoom(const Vec2d& lb, const Vec2d& rt)//�۲촰�����ţ���ά����ָ�����ڲ�������Ҫ��֤������ͬ�������ţ�
{

}
//�۲�����ϵ����
void CG2DCamera::Move(double tx, double ty)//�ƶ��۲�����ϵ����ά��
{
	mMat.preMultiply(Mat3d::getTranslation(tx, ty));
}
void CG2DCamera::Rotate(double degree)//��ת�۲�����ϵ��������ϵԭ�㣬��ʱ�뷽��Ϊ������λ���ȣ�����ά��
{
	mMat.preMultiply(Mat3d::getRotation(degree, Vector2<double>(0, 0)));
}
void CG2DCamera::Reset() //���õ��۲�����ϵĬ�ϲ�������ά��
{
	mMat.setIdentity();
}
//�ӿ����ã�ͨ��viewport()�õ��ӿ�
void CG2DCamera::ViewportOffset() //�߽��ƶ�
{
	ViewportOffset(cameraViewportOffleft, cameraViewportOffbottom, cameraViewportOffright, cameraViewportOfftop);
}
void CG2DCamera::ViewportOffset(int offleft , int offbottom, int offright, int offtop) //�߽��ƶ�
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

//��άͼ�ι۲�任����������ϵ���۲�����ϵ������ά��
Vec2d CG2DCamera::WCStoVCS(const Vec2d& p) {
	Mat3 nMat = mMat.getInverse(); //��任����
	Vec3d s = nMat * Vec3d(p);
	return Vec2d(s.x(), s.y());
}

//��άͼ�δ��ӱ任���۲�����ϵ���淶���豸����ϵ������ά����ʵ����ʹ�������豸����ϵ����淶���豸����ϵ��
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

//��άͼ���ӿڱ任���淶����ϵ���豸����ϵ������ά����ʵ����ʹ�������豸����ϵ����淶���豸����ϵ��
Vec2i CG2DCamera::NCStoDCS(const Vec2d& p) {
	return Vec2i(int(p.x()), int(mClientHeight - p.y()));
}

//�豸����ϵ���淶���豸����ϵ����ά����ʵ����ʹ�������豸����ϵ����淶���豸����ϵ��
Vec2d CG2DCamera::DCStoNCS(const Vec2i& p) {
	return Vec2d(p.x(), mClientHeight - p.y());
}
Vec2d CG2DCamera::DCStoNCS(const Vec2d& p) {
	return Vec2d(p.x(), mClientHeight - p.y());
}

//�淶���豸����ϵ���۲�����ϵ����ά����ʵ����ʹ�������豸����ϵ����淶���豸����ϵ��
Vec2d CG2DCamera::NCStoVCS(const Vec2d& p) {
	Mat3 moveMat = Mat3d::getTranslation(-mLeft, -mBottom);
	Mat3 scaleMat = Mat3d::getScaling((NCSViewPortRight() - NCSViewPortLeft()) / (mRight - mLeft), (NCSViewPortTop() - NCSViewPortBottom()) / (mTop - mBottom));
	Mat3 move2Mat = Mat3d::getTranslation(NCSViewPortLeft(), NCSViewPortBottom());
	Mat3 nMat = move2Mat * scaleMat * moveMat;
	Vec3d s = nMat.getInverse() * Vec3d(p);
	return Vec2d(s.x(), s.y());
}

//�۲�����ϵ����������ϵ����ά��
Vec2d CG2DCamera::VCStoWCS(const Vec2d& p) {
	Vec3d s = mMat * Vec3d(p); //����ʵ�����
	return Vec2d(s.x(), s.y());
}
