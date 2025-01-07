#pragma once
#include "CG2DCircle.h" 
#include "ParticleSystem2D.h"

enum class ParticleType {
	Ascending,
	Exploding,
	Trailing
};

//��Բ����Ϊһ��������״������Բ�����������̻� 
class FireworksParticle : public CG2DCircle, public Particle2D
{
	friend class Fireworks2D;
	CG2DScene* mScene;
protected:
	//�����Զ������Ȫ�������� 
	//���ӵ������ڣ����ӵĳ��ٶȡ����ٶȡ���ɫ����С�� 
	//double mBlastY = 100;
	ParticleType mType = ParticleType::Ascending;
	double mSpeed = 0.0; //���ӳ��ٶ� 
	double mAccSpeed = 0.9; //�ٶ�����
	double mAcc = 0.0; //���Ӽ��ٶ� 
	COLORREF mColor = RGB(255, 0, 0); // Example: Red color; //������ɫ 
	double mRadiusDec = 0.0; //���Ӵ�С�ݼ��ٶ� 
	BYTE mAlphaDec = 0; //����͸���ȵݼ��ٶ� 
	BYTE mAlpha = 255; //����͸���� 
	int expParNum = 20;
public:
	FireworksParticle(CG2DScene* scene, const Vec2d& c, double r) : CG2DCircle(c, r), mScene(scene)
	{
		mTimerCallbackEnabled = true; //���ö�ʱ���ص�
	}
	//��ʱ���ص�����д�����麯��ʵ�ֶ�̬ 
	virtual bool TimerCallback() override; //��������
	void Render(CG2DRenderContext* pRC, CG2DCamera* pCamera) override;
	//�����Զ������������ 
	bool isDead() {
		return mLifeSpan > mLife || mRadius <=0 || mAlpha<=0;
	}
};

class Fireworks2D : public ParticleSystem2D
{
	DECLARE_SERIAL(Fireworks2D)
public:
	Fireworks2D(CG2DScene* scene = nullptr) : ParticleSystem2D(scene)
	{
	}
	virtual void Run() override; //���ϲ��������ӣ����ӵĸ������䶨ʱ�ص����� 

protected:
	//�̻�ϵͳ��һЩ�Զ������ԣ� 
	//�������Ӱ뾶�����ӳ��ٶȵȣ��ɼ�һ��������ӣ������Ӳ����ٶȣ����ӹ�ģ�� 
	//�𽥱䰵����С��ֱ������ 

};

