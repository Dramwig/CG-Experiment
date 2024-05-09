#pragma once
#include "CG2DCircle.h" 
#include "ParticleSystem2D.h"

//以圆形作为一个粒子形状，定义圆形粒子用于烟花 
class SparklerParticle : public CG2DCircle, public Particle2D
{
	friend class Sparkler2D;
public:
	SparklerParticle(const Vec2d& c, double r) : CG2DCircle(c, r)
	{
		mTimerCallbackEnabled = true;
	}
	//定时器回调，重写基类虚函数实现多态 
	virtual bool TimerCallback() override; //更新粒子
	//其他自定义的喷泉粒子属性 

};

class Sparkler2D : public ParticleSystem2D
{
	DECLARE_SERIAL(Sparkler2D)
public:
	Sparkler2D(CG2DScene* scene = nullptr) : ParticleSystem2D(scene)
	{
	}
	virtual void Run() override; //不断产生新粒子，粒子的更新由其定时回调处理 

protected:
	//烟花系统的一些自定义属性， 
	//比如粒子半径、粒子初速度等（可加一定随机因子），粒子产生速度（粒子规模） 
	//逐渐变暗、变小，直到消亡 

};

