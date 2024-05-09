#pragma once
#include "CGObject.h" 
#include "Vector2.h" 

class CG2DScene; //前置声明 

//粒子发射器，粒子系统。雨雪冰雹喷泉火焰落叶烟花爆炸
class ParticleSystem2D :
    public CGObject
{
    DECLARE_SERIAL(ParticleSystem2D)
public:
    ParticleSystem2D(CG2DScene* scene = nullptr) : mScene(scene) {}
    virtual ~ParticleSystem2D() = default;
    //需要在派生类中重写，实现具体的粒子发生器 
    virtual void Run() { };  //按照一定规律不断产生新粒子，粒子的更新由其定时回调处理 

    CG2DScene*& Scene() { return mScene; }
    Vec2d& Position() { return mPos; }
    bool Enabled() const { return mEnabled; }
    void Enable(bool e = true) { mEnabled = e; }
    int ParticlesGen() const { return mParticlesGen; }
    void setParticlesGen(int n) { mParticlesGen = n; }
protected:
    CG2DScene* mScene = nullptr; //新产生的粒子加入到场景中，由场景的时间回调进行粒子更新 
    Vec2d mPos;    //发生器位置（场景中） 
    bool mEnabled = true; //是否有效 
    int mParticlesGen = 1; //每次更新产生新粒子数 

    //其他属性要在派生具体粒子系统中自定义 
};

//二维粒子基类，形状等属性由二维可绘制图形对象确定 
//速度大小与方向、加速度、生命周期等性质，可根据需要自定义 
class Particle2D
{
public:
    Particle2D() = default;
    virtual ~Particle2D() = default;

    double Life() const { return mLife; }
    double LifeSpan() const { return mLifeSpan; }
protected:
    //在粒子发生器中设置。可根据需要修改补充定义 
    double mSpeedX = 0.0; //X方向速度
    double mSpeedY = 0.0; //Y方向速度 
    double mAccX = 0.0;  //X方向加速度 
    double mAccY = 0.0;  //Y方向加速度 
    double mLife = 0.0;  //生命（毫秒）。 
    double mGAccX = 0.0; //重力加速度 
    double mGAccY = 0.0; //重力加速度 
    double mLifeSpan = 0.0; //已生存时间（毫秒） 
public:
    bool isDead() {
        return mLifeSpan > mLife;
    }
};
