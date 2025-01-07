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
	//�ӿ� 
	const CG2DViewPort& viewport() const { return mViewPort; }
	CG2DViewPort& viewport() { return mViewPort; }

	//�ͻ��� 
	void SetClientWidth(int width) { mClientWidth = width; }
	void SetClientHeight(int height) { mClientHeight = height; }
	int ClientWidth() const { return mClientWidth; }
	int ClientHeight() const { return mClientHeight; }

	//�۲��� 
	double Left() const { return mLeft; }
	double Bottom() const { return mBottom; }
	double Right() const { return mRight; }
	double Top() const { return  mTop; }
	double Near() const { return mNear; }
	double Far() const { return mFar; }
	//�۲�����ϵ 
	double EyeX() const { return mEyeX; }
	double EyeY() const { return mEyeY; }
	double EyeZ() const { return mEyeZ; }
	double UpX() const { return mUpX; }
	double UpY() const { return mUpY; }
	double UpZ() const { return mUpZ; }
	//���۲�� 
	double RefX() const { return mRefX; }
	double RefY() const { return mRefY; }
	double RefZ() const { return mRefZ; }

	//ȡ�����壬������Ⱦģʽ�µ�ͶӰ�任 
	//mode=0Ϊ����ͶӰ����ά����mode=1Ϊ͸��ͶӰ��mode=2������Ϊ����ͶӰ����ά�� 
	int ProjectionMode() { return mProjectionMode; }
	void SetProjectionMode(int mode) { if (mode >= 0 && mode <= 2) mProjectionMode = mode; }
	virtual void Projection(int mode = 0);

	//�ƶ���� 
	void Move(double tx, double ty, double tz);
	void SetEye(double x, double y, double z);
	//�۲촰�ڣ����¡����ϣ��������������ӿ���ͬ�߿�� 
	void Zoom(const Vec2d& lb, const Vec2d& rt);
	void Zoom(double r);
	//�����������ϵ������Զ���� 
	void Reset();

protected:
	CG2DViewPort mViewPort; //��Ӧ�ӿڣ����豸����ϵ���ͻ������ж��壬Ĭ����ͻ�����ͬ��С�� 
	int mClientWidth = 1;
	int mClientHeight = 1;

	//��Ҫ���л������� 
	//ͶӰģʽ��0=����ͶӰ����ά����1=͸��ͶӰ��2=����ͶӰ����ά�� 
	int mProjectionMode = 0;
	//��ͼ�ͻ������� 
	//�۲�ռ䣨�ڹ۲�����ϵ�ж��壩���ε����ҡ��¡��� 
	double mLeft = -10.0;
	double mBottom = -10.0;
	double mRight = 10.0;
	double mTop = 10.0;
	double mNear = 1.0;   //������ 
	double mFar = 100000.0;  //Զ���� 
	//���λ�ã���ʾ�۲�����ϵԭ�������������ϵ�е�λ�� 
	double mEyeX = 0.0;
	double mEyeY = 0.0;
	double mEyeZ = 1000.0;
	//���Ϸ���(Ĭ��0,1,0)����ά���õ�x��y����ʾ�۲�����ϵY��ķ���ʸ�� 
	double mUpX = 0.0;
	double mUpY = 1.0;
	double mUpZ = 0.0;
	//���۲��(Ĭ��0,0,0)����ά�� 
	double mRefX = 0.0;
	double mRefY = 0.0;
	double mRefZ = 0.0;
};

#endif //_CG3DCamera_H_INCLUDED 
