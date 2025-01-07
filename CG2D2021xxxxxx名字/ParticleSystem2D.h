#pragma once
#include "CGObject.h" 
#include "Vector2.h" 

class CG2DScene; //ǰ������ 

//���ӷ�����������ϵͳ����ѩ������Ȫ������Ҷ�̻���ը
class ParticleSystem2D :
    public CGObject
{
    DECLARE_SERIAL(ParticleSystem2D)
public:
    ParticleSystem2D(CG2DScene* scene = nullptr) : mScene(scene) {}
    virtual ~ParticleSystem2D() = default;
    //��Ҫ������������д��ʵ�־�������ӷ����� 
    virtual void Run() { };  //����һ�����ɲ��ϲ��������ӣ����ӵĸ������䶨ʱ�ص����� 

    CG2DScene*& Scene() { return mScene; }
    Vec2d& Position() { return mPos; }
    bool Enabled() const { return mEnabled; }
    void Enable(bool e = true) { mEnabled = e; }
    int ParticlesGen() const { return mParticlesGen; }
    void setParticlesGen(int n) { mParticlesGen = n; }
protected:
    CG2DScene* mScene = nullptr; //�²��������Ӽ��뵽�����У��ɳ�����ʱ��ص��������Ӹ��� 
    Vec2d mPos;    //������λ�ã������У� 
    bool mEnabled = true; //�Ƿ���Ч 
    int mParticlesGen = 1; //ÿ�θ��²����������� 

    //��������Ҫ��������������ϵͳ���Զ��� 
};

//��ά���ӻ��࣬��״�������ɶ�ά�ɻ���ͼ�ζ���ȷ�� 
//�ٶȴ�С�뷽�򡢼��ٶȡ��������ڵ����ʣ��ɸ�����Ҫ�Զ��� 
class Particle2D
{
public:
    Particle2D() = default;
    virtual ~Particle2D() = default;

    double Life() const { return mLife; }
    double LifeSpan() const { return mLifeSpan; }
protected:
    //�����ӷ����������á��ɸ�����Ҫ�޸Ĳ��䶨�� 
    double mSpeedX = 0.0; //X�����ٶ�
    double mSpeedY = 0.0; //Y�����ٶ� 
    double mAccX = 0.0;  //X������ٶ� 
    double mAccY = 0.0;  //Y������ٶ� 
    double mLife = 0.0;  //���������룩�� 
    double mGAccX = 0.0; //�������ٶ� 
    double mGAccY = 0.0; //�������ٶ� 
    double mLifeSpan = 0.0; //������ʱ�䣨���룩 
public:
    bool isDead() {
        return mLifeSpan > mLife;
    }
};
