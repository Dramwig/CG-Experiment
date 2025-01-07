#ifndef _CG2DScene_H_INCLUDED
#define _CG2DScene_H_INCLUDED
#include "CGObject.h"
#include "AABBox2.h"
#include "Matrix33.h"
#include "ParticleSystem2D.h"
//ʹ�õ��������ָ�룬������Ԥ����
class CG2DRenderable;
class CG2DCamera;
class CG2DRenderContext;
class CG2DScene : public CGObject
{
	DECLARE_SERIAL(CG2DScene)
public:
	CG2DScene();
	virtual ~CG2DScene();
	virtual void Serialize(CArchive& ar) override;
	//�������е�ͼ�ζ���
	bool addRenderable(CG2DRenderable*);
	bool delRenderable(CG2DRenderable*);
	void removeAllRenderable();
	CG2DRenderable* getRenderable(unsigned int index);
	CG2DRenderable* detachRenderable(CG2DRenderable*);
	//��Ⱦ����
	bool Render(CG2DRenderContext* pRC, CG2DCamera* pCamera);
	//��ά������Χ�м���
	ABox2d BoundingABox();
	ABox2d BoundingABoxi(CG2DCamera* pCamera);
protected:
	//ͼ�ζ����б�
	CTypedPtrArray<CObArray, CG2DRenderable*> mRenderables;
	//ͼ�ζ���ѡ��
	CTypedPtrArray<CObArray, CG2DRenderable*> mSelections;
//���峡����ͼ�ζ���ѡ����س�Ա����
public:
	//����ѡ�����ʰȡ����ɹ������滻ѡ�񼯣�����ʰȡ�Ķ���
	CG2DRenderable* UpdatePicked(const Vec2d& p, double radius); //��ѡ
	CG2DRenderable* UpdatePicked(const ABox2d& box, bool inner = true); //��ѡ��������ѡ�У���
	//���ѡ�����ʰȡ����ɹ��������ѡ�񼯣�����ʰȡ�Ķ���
	CG2DRenderable* AppendPicked(const Vec2d& p, double radius); //��ѡ
	CG2DRenderable* AppendPicked(const ABox2d& box, bool inner = true); //��ѡ��������ѡ�У���
	//��ͼ�ζ�������ѡȡ�����иö��������ѡ�񼯣�����ѡȡ�Ķ���
	CG2DRenderable* Selected(const CString& name);
	bool Unselect(const CString& name); //����ָ������ѡ��״̬
	bool Unselect(CG2DRenderable* r); //����ָ������ѡ��״̬
	bool UnselectAll(); //�������ж���ѡ��״̬
	bool SelectAll(); //���ж�����Ϊѡ��
public:
	//ͼ�μ��α任
	bool Translate(double tx, double ty); //ƽ��
	bool Rotate(double angle, double cx, double cy); //��ת����ʱ��Ϊ�����ȣ�
	bool Scale(double sx, double sy); //���ţ���������ԭ�����ţ�
	bool Scale(double sx, double sy, double cx, double cy); //���ţ�����ָ���ο������ţ�
	bool MirrorXAxis(); //����X��Գƣ���ά��
	bool MirrorYAxis(); //����Y��Գƣ���ά��
	bool MirrorYeqPosX(); //����y=x�Գƣ���ά��
	bool MirrorYeNegPX(); //����y=-x�Գƣ���ά��
	bool MirrorOrigin(); //����ԭ��Գƣ���ά��
	bool Mirror(const Vec2d& vs, const Vec2d& ve); //�����߶�se�Գƣ���ά��
	bool ShearXAxis(double shx); //��X�����
	bool ShearYAxis(double shy); //��Y�����
	bool ShearXYAxis(double shx, double shy); //��X��Y�����
	bool Transform(const Mat3d& mat); //���α任����˸�������
public: //ʵ��ο�6
	//��ʱ�ص�������ʵ�ֶ����� 
	bool TimerCallback();
public:
	bool addParticleSystem(ParticleSystem2D*);
	bool delParticleSystem(ParticleSystem2D*);
	void removeAllParticleSystem();
protected:
	CTypedPtrArray<CObArray, ParticleSystem2D*> mParticleSystems;
};
#endif //_CG2DScene_H_INCLUDED
