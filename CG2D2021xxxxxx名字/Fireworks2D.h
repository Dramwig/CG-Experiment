#pragma once
#include "CG2DCircle.h" 
#include "ParticleSystem2D.h"

enum class ParticleType {
	Ascending,
	Exploding,
	Trailing
};

//以圆形作为一个粒子形状，定义圆形粒子用于烟花 
class FireworksParticle : public CG2DCircle, public Particle2D
{
	friend class Fireworks2D;
	CG2DScene* mScene;
protected:
	//其他自定义的喷泉粒子属性 
	//粒子的生命期，粒子的初速度、加速度、颜色、大小等 
	//double mBlastY = 100;
	ParticleType mType = ParticleType::Ascending;
	double mSpeed = 0.0; //粒子初速度 
	double mAccSpeed = 0.9; //速度阻力
	double mAcc = 0.0; //粒子加速度 
	COLORREF mColor = RGB(255, 0, 0); // Example: Red color; //粒子颜色 
	double mRadiusDec = 0.0; //粒子大小递减速度 
	BYTE mAlphaDec = 0; //粒子透明度递减速度 
	BYTE mAlpha = 255; //粒子透明度 
	int expParNum = 20;
public:
	FireworksParticle(CG2DScene* scene, const Vec2d& c, double r) : CG2DCircle(c, r), mScene(scene)
	{
		mTimerCallbackEnabled = true; //启用定时器回调
	}
	//定时器回调，重写基类虚函数实现多态 
	virtual bool TimerCallback() override; //更新粒子
	void Render(CG2DRenderContext* pRC, CG2DCamera* pCamera) override;
	//其他自定义的粒子属性 
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
	virtual void Run() override; //不断产生新粒子，粒子的更新由其定时回调处理 

protected:
	//烟花系统的一些自定义属性， 
	//比如粒子半径、粒子初速度等（可加一定随机因子），粒子产生速度（粒子规模） 
	//逐渐变暗、变小，直到消亡 

};

