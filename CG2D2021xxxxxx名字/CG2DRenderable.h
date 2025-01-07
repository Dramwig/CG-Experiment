#ifndef _CG2DRenderable_H_INCLUDED
#define _CG2DRenderable_H_INCLUDED
#include "CGObject.h"
#include "AABBox2.h"
#include "Matrix33.h"
#include "CG2DCamera.h"
//ʹ�õ��������ָ�룬������Ԥ����
class CG2DRenderContext;
class CG2DCamera;
class CG2DScene;
class CG2DRenderable : public CGObject
{
	DECLARE_SERIAL(CG2DRenderable)
public:
	CG2DRenderable();
	CG2DRenderable(const CString& name);
	CG2DRenderable(const CG2DRenderable& other) = default;
	virtual ~CG2DRenderable() = default;
	//���л�
	virtual void Serialize(CArchive& ar) override;
	//������ӵ������������볡���Ĺ���
	void addToScene(CG2DScene* s) { mScene = s; }
	CG2DScene* scene() const { return mScene; }
	//����
	virtual void Render(CG2DRenderContext* pRC, CG2DCamera* pCamera); //���ƶ���ʹ��ָ�����
	//һ���άͼ�����ԣ��߿����͡���ɫ��
	void setPenColor(COLORREF color) { mPenColor = color; }
	COLORREF penColor() const { return mPenColor; }
	void setPenWidth(int width) { mPenWidth = width; }
	int penWidth() const { return mPenWidth; }
	void setPenStyle(int style) { mPenStyle = style; }
	int penStyle() const { return mPenStyle; }
	//��ά���ͼ���������
	void setBrushColor(COLORREF color) { mBrushColor = color; }
	COLORREF brushColor() const { return mBrushColor; }
	void setBrushStyle(int style) { mBrushStyle = style; }
	int brushStyle() const { return mBrushStyle; }
	void setHatchStyle(int style) { mHatchStyle = style; }
	int hatchStyle() const { return mHatchStyle; }
	//��Χ����ʰȡ���
	ABox2d& BoundingABox(); //AABB��Χ�У�����������
	bool boundsDirty() const { return mBoundsDirty; } //�����Χ���Ƿ���Ҫ���¼���
	void setBoundsDirty(bool dirty) { mBoundsDirty = dirty; } //���ð�Χ���Ƿ���Ҫ���¼���
	virtual void computeBoundingBox(); //�������İ�Χ��,����������������д
	//����״̬���壨Ҳ����ö�����ͣ�
	static const int sNormal = 0; //����״̬
	static const int sSelected = 1; //ѡ��״̬
	int status() const { return mStatus; }
	void setStatus(int s) { mStatus = s; }
protected:
	COLORREF mPenColor = RGB(0, 0, 0); //������ɫ
	int mPenWidth = 1; //�����߿�
	int mPenStyle = PS_SOLID; //��������
	COLORREF mBrushColor = RGB(0, 0, 0); //��ˢ��ɫ
	int mBrushStyle = BS_SOLID; //��ˢ��ʽ
	int mHatchStyle = HS_HORIZONTAL; //��Ӱ��ʽ
	CG2DScene* mScene = nullptr; //����ʵ�������ĳ�������������볡��ʱ�Զ��������á�
	ABox2d mABox;//�������ΰ�Χ�У���Ҫ����mBoundsDirty�ж��Ƿ����¼���
	bool mBoundsDirty = true; //��Χ���Ƿ��Ѹı�
	int mStatus = 0; //״̬
public:
	virtual bool Picked(const Vec2d& p, double radius); //����ά���Ƿ�ʰȡ��
	virtual bool Picked(const ABox2d& box); //����ά���Ƿ�ʰȡ��
	virtual void DrawSelectedBoundingBox(HDC hDC, CG2DRenderable* renderable, CG2DCamera* pCamera); //����ѡ�а�Χ��
	virtual void DrawSelectedBoundingBoxi(HDC hDC, CG2DRenderable* renderable, CG2DCamera* pCamera); //����ѡ�а�Χ��
	//ͼ�μ��α任
	virtual void Translate(double tx, double ty); //ƽ��
	virtual void Rotate(double angle, double cx, double cy); //��ת����ʱ��Ϊ�����ȣ�
	virtual void Scale(double sx, double sy); //���ţ���������ԭ�����ţ�
	virtual void Scale(double sx, double sy, double cx, double cy); //���ţ�����ָ���ο������ţ�
	virtual void MirrorXAxis(); //����X��Գƣ���ά��
	virtual void MirrorYAxis(); //����Y��Գƣ���ά��
	virtual void MirrorYeqPosX(); //����y=x�Գƣ���ά��
	virtual void MirrorYeNegPX(); //����y=-x�Գƣ���ά��
	virtual void MirrorOrigin(); //����ԭ��Գƣ���ά��
	virtual void Mirror(const Vec2d& vs, const Vec2d& ve); //�����߶�se�Գƣ���ά��
	virtual void ShearXAxis(double shx); //��X�����
	virtual void ShearYAxis(double shy); //��Y�����
	virtual void ShearXYAxis(double shx, double shy); //��X��Y�����
	virtual void Transform(const Mat3d& mat); //���α任����˸�������
protected:
	Mat3d mMat; //����������ϵ�ı任����������ʽ��
public: //ʵ��ο�5
	//��ȡ���ӿ��ڵİ�Χ��(�����ڻ��ƶ���İ�Χ�У�����Ҫ������������д
	virtual ABox2i BoundingABoxi(CG2DCamera* pCamera);
public: //ʵ��ο�6
	//��ʱ���ص�����Ҫ������������дʵ�ֶ�̬ 
	virtual bool TimerCallback() { return false; }
	bool TimerCallbackEnabled() const { return mTimerCallbackEnabled; }
	void EnableTimerCallback(bool e = true) { mTimerCallbackEnabled = e; }
protected:
	//Ĭ������£�ʱ��ص��������ã���Ҫ�ڶ�̬���������� 
	bool mTimerCallbackEnabled = false;
};
#endif //_CG2DRenderable_H_INCLUDED
