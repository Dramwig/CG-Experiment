#include "pch.h" 
#include "Sparkler2D.h" 
#include "CG2DScene.h" 

IMPLEMENT_SERIAL(Sparkler2D, ParticleSystem2D, 1)

bool SparklerParticle::TimerCallback() //�������� 
{
	mCenter.x() += mSpeedX;
	mCenter.y() += mSpeedY;
	mLifeSpan += 50;
	return true;
}

void Sparkler2D::Run() //���ϲ��������ӣ����ӵĸ������䶨ʱ�ص����� 
{
	for (int i = 0; i < mParticlesGen; i++)
	{
		SparklerParticle* sp = new SparklerParticle(mPos, 5 + rand() % 10);
		sp->setBrushColor(RGB(255, 0, 0));
		sp->setPenColor(RGB(255, 0, 0));
		sp->mSpeedX = rand() % 20 - 10;
		sp->mSpeedY = rand() % 20 - 10;
		sp->mLife = 1000;
		mScene->addRenderable(sp);
	}
}
