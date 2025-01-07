#ifndef _CG3DRenderable_H_INCLUDED 
#define _CG3DRenderable_H_INCLUDED 

#include "CGObject.h" 
#include "AABBox3.h" 
#include "Matrix44.h" 
#include "CGAppearance.h"
#include "CGPolygonMode.h"

class CG3DRenderContext;
class CG3DCamera;
class CG3DScene;

class CG3DRenderable : public CGObject
{
	DECLARE_SERIAL(CG3DRenderable)
	//+1
	//�ص�����
	typedef bool (*CG3DRenderableCallback) (CG3DRenderable*);
public:
	CG3DRenderable();
	CG3DRenderable(const CString& name);
	virtual ~CG3DRenderable();

	//���л� 
	virtual void Serialize(CArchive& ar);

	//���ƶ���������������д�� 
	virtual void Render(CG3DRenderContext* pRC, CG3DCamera* pCamera);

	//��άͼ�ζ����Χ�� 
	ABox3d& BoundingABox(); //AABB��Χ�� 
	bool boundsDirty() const { return mBoundsDirty; } //�����Χ���Ƿ���Ҫ���¼��� 
	void setBoundsDirty(bool dirty) { mBoundsDirty = dirty; }
	virtual void computeBoundingBox(); //�����Χ�У���Ҫ����������ʵ�� 

	//������ӵ������������볡���Ĺ��� 
	void addToScene(CG3DScene* s) { mScene = s; }
	CG3DScene* scene() const { return mScene; }

	//����״̬���壨Ҳ����ö�����ͣ� 
	static const int sNormal = 0; //����״̬ 
	static const int sSelected = 1; //ѡ��״̬ 
	int status() const { return mStatus; }
	void setStatus(int s) { mStatus = s; }

	//��άͼ�ζ���ļ��α任 
	void Translate(double tx, double ty, double tz);   //ƽ�ƣ���ά�� 
	void Rotate(double angle, double cx, double cy, double cz); //��ת����ά�� 
	void Scale(double sx, double sy, double sz);    //���ţ���ά�� 
	Vec3f getPosition() const {return Vec3f(mMat.e(0, 3), mMat.e(1, 3), mMat.e(2, 3));}

	void setPenColor(COLORREF color) { mPenColor = color; }
	COLORREF penColor() const { return mPenColor; }
	void setPenWidth(int width) { mPenWidth = width; }
	int penWidth() const { return mPenWidth; }
	void setPenStyle(int style) { mPenStyle = style; }
	int penStyle() const { return mPenStyle; }
	void setPenFill(int style) { mPenFill = style; }
	int penFill() const { return mPenFill; }

protected:
	Mat4d mMat;  //����������ϵ�ı任����������ʽ����Ĭ��Ϊ��λ�����븸������ϵ�غϣ� 
	ABox3d mABox; //�������ΰ�Χ�У���Ҫ����mBoundsDirty�ж��Ƿ����¼��㣬Ĭ��Ϊ�� 
	bool mBoundsDirty = true; //��Χ���Ƿ��Ѹı� 
	int mStatus = 0;   //״̬����ѡ��״̬�ȡ�0=���� 
	CG3DScene* mScene = nullptr;//����ʵ�������ĳ�������������볡��ʱ�Զ��������á� 
	COLORREF mPenColor = RGB(255, 0, 0); //������ɫ
	int mPenWidth = 1; //�����߿�
	int mPenStyle = PS_SOLID; //��������
	COLORREF mBrushColor = RGB(0, 0, 0); //��ˢ��ɫ
	int mPenFill = 0; //��ˢ��ʽ

public: //ʵ��7
	//������ע��ص� 
	void RegisterCallback(CG3DRenderableCallback callback) { mCallback = callback; }
	void UnregisterCallback() { mCallback = nullptr; }
	CG3DRenderableCallback Callback() { return mCallback; }

	//��ʱ�ص���ͨ���������TimerCallback���ã� 
	virtual bool TimerCallback();
	bool TimerCallbackEnabled() const { return mTimerCallbackEnabled; }
	void EnableTimerCallback(bool e = true) { mTimerCallbackEnabled = e; }
	//������� 
	CGAppearance& Appearance() { return mAppearance; }
	//�����ģʽ���㡢�ߡ��� 
	CGPolygonMode& PolygonMode() { return mPolygonMode; }
protected:
	//Ĭ������£�ʱ��ص��������ã���Ҫ�ڶ�̬���������� 
	bool mTimerCallbackEnabled = false;
	//�����ص� 
	CG3DRenderableCallback mCallback = nullptr;
	//������� 
	CGAppearance mAppearance;
	//�����ģʽ���㡢�ߡ��� 
	CGPolygonMode mPolygonMode;

};

#endif //_CG3DRenderable_H_INCLUDED
