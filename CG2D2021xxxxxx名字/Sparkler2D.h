#pragma once
#include "CG2DCircle.h" 
#include "ParticleSystem2D.h"

//��Բ����Ϊһ��������״������Բ�����������̻� 
class SparklerParticle : public CG2DCircle, public Particle2D
{
	friend class Sparkler2D;
public:
	SparklerParticle(const Vec2d& c, double r) : CG2DCircle(c, r)
	{
		mTimerCallbackEnabled = true;
	}
	//��ʱ���ص�����д�����麯��ʵ�ֶ�̬ 
	virtual bool TimerCallback() override; //��������
	//�����Զ������Ȫ�������� 

};

class Sparkler2D : public ParticleSystem2D
{
	DECLARE_SERIAL(Sparkler2D)
public:
	Sparkler2D(CG2DScene* scene = nullptr) : ParticleSystem2D(scene)
	{
	}
	virtual void Run() override; //���ϲ��������ӣ����ӵĸ������䶨ʱ�ص����� 

protected:
	//�̻�ϵͳ��һЩ�Զ������ԣ� 
	//�������Ӱ뾶�����ӳ��ٶȵȣ��ɼ�һ��������ӣ������Ӳ����ٶȣ����ӹ�ģ�� 
	//�𽥱䰵����С��ֱ������ 

};

