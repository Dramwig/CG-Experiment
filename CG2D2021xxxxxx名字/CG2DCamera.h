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
	//���л�
	virtual void Serialize(CArchive& ar) override;
	//�ӿ�
	const CG2DViewPort& viewport() const { return mViewPort; }
	CG2DViewPort& viewport() { return mViewPort; }
	//�ͻ���
	void SetClientWidth(int width) { mClientWidth = width; }
	void SetClientHeight(int height) { mClientHeight = height; }
	int ClientWidth() const { return mClientWidth; }
	int ClientHeight() const { return mClientHeight; }
	//��������ϵת�����ӿڣ���ά��(��������ϵ�еĵ�λ�ö�Ӧ���ӿ��е�λ�ã�
	virtual Vec2i WorldtoViewPort(const Vec2d& p);
	//�ӿ�ת������������ϵ����ά��(�ӿ��еĵ�λ�ö�Ӧ����������ϵ�е�λ�ã�
	virtual Vec2d ViewPorttoWorld(const Vec2i& p);
	virtual Vec2d ViewPorttoWorld(const Vec2d& p);
	//�۲촰�ڿ�����ӿڿ�ȵı���
	double WidthFactorWindowtoViewPort();
	//�۲촰�ڸ߶����ӿڸ߶ȵı���
	double HeightFactorWindowtoViewPort();
	//�۲촰��
	double Left() const { return mLeft; }
	double Bottom() const { return mBottom; }
	double Right() const { return mRight; }
	double Top() const { return mTop; }
	void SetAspectRatio(double aspect); //���ù۲촰�ڵĿ�߱�
	int cameraViewportOffleft, cameraViewportOffbottom, cameraViewportOffright, cameraViewportOfftop;//�ӿڱ߽�ƫ��
protected:
	CG2DViewPort mViewPort; //��Ӧ�ӿڣ����豸����ϵ���ͻ������ж��壬Ĭ����ͻ�����ͬ��С��
	//��ͼ�ͻ�������
	int mClientWidth = 1;
	int mClientHeight = 1;
	//�۲�������۲췶Χ���۲촰�ڣ���ά��)
	double mLeft = -1000, mBottom = -1000, mRight = 1000, mTop = 1000; //�۲촰�ڣ��ڹ۲�����ϵ�ж��壩���ε����ҡ��¡���(Ĭ�� - 1000, -1000, 1000, 1000����ΪҪ�������ڱ߽�)
protected:
	//��ƽ��ʸ��ȷ������ԭ�㣬��ת�Ƕ�ȷ������ϵ����
	Mat3 mMat; //�۲�����ϵ�������������ϵ�ı任������������ʽ��
public:
	//�۲촰������
	void SetWindowLeft(double left);
	void SetWindowBottom(double bottom);
	void SetWindowRight(double right);
	void SetWindowTop(double top);
	void Zoom(double ratio); //�۲촰�����ţ���ά������������ͬ�������ţ�����Ӧ����0��
	void Zoom(const Vec2d& lb, const Vec2d& rt);//�۲촰�����ţ���ά����ָ�����ڲ�������Ҫ��֤������ͬ�������ţ�
	//�۲�����ϵ����
	void Move(double tx, double ty); //�ƶ��۲�����ϵ����ά��
	void Rotate(double degree); //��ת�۲�����ϵ��������ϵԭ�㣬��ʱ�뷽��Ϊ������λ���ȣ�����ά��
	void Reset(); //���õ��۲�����ϵĬ�ϲ�������ά��
	//�ӿ����ã�ͨ��viewport()�õ��ӿ�
	void ViewportOffset(); 
	void ViewportOffset(int offleft, int offbottom, int offright, int offtop); //�߽��ƶ�
	void ViewportSet(int width, int height);
	//�����豸����ϵ���ӿڲ������ӿ�mViewPort��������Կͻ�����Ҫת��������������豸����ϵ��
	int NCSViewPortLeft() const { return mViewPort.left(); }
	int NCSViewPortBottom() const {
		return mClientHeight - mViewPort.height() - mViewPort.bottom();
	}
	int NCSViewPortRight() const { return mViewPort.left() + mViewPort.width(); }
	int NCSViewPortTop() const { return mClientHeight - mViewPort.bottom(); }
	//��άͼ�ι۲�任����������ϵ���۲�����ϵ������ά��
	Vec2d WCStoVCS(const Vec2d& p);
	//��άͼ�δ��ӱ任���۲�����ϵ���淶���豸����ϵ������ά����ʵ����ʹ�������豸����ϵ����淶���豸����ϵ��
	Vec2d VCStoNCS(const Vec2d& p);
	//��άͼ���ӿڱ任���淶����ϵ���豸����ϵ������ά����ʵ����ʹ�������豸����ϵ����淶���豸����ϵ��
	Vec2i NCStoDCS(const Vec2d& p);
	//�豸����ϵ���淶���豸����ϵ����ά����ʵ����ʹ�������豸����ϵ����淶���豸����ϵ��
	Vec2d DCStoNCS(const Vec2i& p);
	Vec2d DCStoNCS(const Vec2d& p);
	//�淶���豸����ϵ���۲�����ϵ����ά����ʵ����ʹ�������豸����ϵ����淶���豸����ϵ��
	Vec2d NCStoVCS(const Vec2d& p);
	//�۲�����ϵ����������ϵ����ά��
	Vec2d VCStoWCS(const Vec2d& p);

};
#endif //_CG2DCamera_H_INCLUDED
