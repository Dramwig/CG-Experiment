#include "pch.h" 
#include "Fireworks2D.h" 
#include "CG2DScene.h" 
#include "CG2DRenderContext.h"
#include <gdiplus.h>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

using namespace Gdiplus;

IMPLEMENT_SERIAL(Fireworks2D, ParticleSystem2D, 1)

bool FireworksParticle::TimerCallback() //更新粒子 
{
    if (mType == ParticleType::Exploding) //阻力
    {
        mSpeedY *= mAccSpeed;
        mSpeedX *= mAccSpeed;
    }
	mCenter.x() += mSpeedX;
	mCenter.y() += mSpeedY;
    mSpeedY += mGAccY;
    mRadius = std::max(0.0, mRadius - mRadiusDec);
    mAlpha = std::max(0, mAlpha - mAlphaDec);
	mLifeSpan += 50;
    setBoundsDirty(true);
    if (mType != ParticleType::Trailing) {
        FireworksParticle* sp = new FireworksParticle(mScene, mCenter, mRadius);
        sp->mColor = mColor;
        sp->setBrushColor(mColor);
        sp->setPenColor(mColor);
        sp->mLife = mLife- mLifeSpan;
        sp->mAlpha = 128;
        sp->mAlphaDec = 16;
        sp->mRadiusDec = 1;
        if (mType == ParticleType::Exploding) {
            sp->mAlphaDec = 8;
            sp->mRadiusDec = 0.5;
        }
        sp->mType = ParticleType::Trailing;
        sp->setBoundsDirty(true);
        mScene->addRenderable(sp);
    }
    if (mType == ParticleType::Ascending && isDead()) {
        for (int i = 0; i < expParNum; i++)
        {
            FireworksParticle* sp = new FireworksParticle(mScene, mCenter, mRadius);
            sp->mColor = mColor;
            sp->setBrushColor(mColor);
            sp->setPenColor(mColor);
            double theta = static_cast<double>(rand()) / RAND_MAX * 2 * PI;
            int maxSpeed = rand() % 20 + 20;
            int biaSpeed = rand() % 5 - 2;
            sp->mSpeedX = cos(theta) * (maxSpeed + biaSpeed - double(maxSpeed) / 2);
            sp->mSpeedY = sin(theta) * (maxSpeed + biaSpeed - double(maxSpeed) / 2);
            sp->mGAccY = -0.2;
            sp->mLife = 5000;
            sp->mAlphaDec = 8;
            sp->mRadiusDec = 0.1;
            sp->mType = ParticleType::Exploding;
            sp->setBoundsDirty(true);
            mScene->addRenderable(sp);

        }
    }
	return true;
}

void FireworksParticle::Render(CG2DRenderContext* pRC, CG2DCamera* pCamera)
{
    if (pRC == nullptr || pCamera == nullptr) {
        return;
    }
    HDC hDC = pRC->GetMemHDC();
    if (hDC == nullptr) {
        return;
    }

    // Initialize GDI+ if it hasn't been done elsewhere in your application
    static GdiplusStartupInput gdiplusStartupInput;
    static ULONG_PTR gdiplusToken;
    static bool gdiPlusInitialized = false;
    if (!gdiPlusInitialized) {
        GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
        gdiPlusInitialized = true;
    }

    Graphics graphics(hDC);

    Vec3d s = mMat * Vec3d(mCenter); // Calculate actual start point
    Vec2i v1 = pCamera->WorldtoViewPort(Vec2d(s.x(), s.y()));
    double r1 = mRadius * mMat.scalex(); // Calculate actual radius
    double r2 = mRadius * mMat.scaley();
    // Define the pen and brush with transparency (alpha value)
    Color tpenColor(mAlpha, GetRValue(penColor()), GetGValue(penColor()), GetBValue(penColor()));
    Color tbrushColor(mAlpha, GetRValue(brushColor()), GetGValue(brushColor()), GetBValue(brushColor()));
    Pen pen(tpenColor, static_cast<REAL>(penWidth()));
    SolidBrush brush(tbrushColor);

    // Draw the filled circle with transparency
    graphics.SetSmoothingMode(SmoothingMode::SmoothingModeHighQuality);
    graphics.FillEllipse(&brush, int(v1.x() - r1), int(v1.y() - r2), int(2 * r1), int(2 * r2));
    graphics.DrawEllipse(&pen, int(v1.x() - r1), int(v1.y() - r2), int(2 * r1), int(2 * r2));

    // Draw the selected bounding box if needed
    DrawSelectedBoundingBox(hDC, this, pCamera);
}


COLORREF getRandomVibrantColor() {
    // Seed the random number generator if it hasn't been done yet
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(nullptr)));
        seeded = true;
    }

    // Generate three random values between 0 and 255
    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;

    // Ensure at least one component is at maximum value to ensure vibrancy
    int maxComponent = rand() % 3;
    switch (maxComponent) {
    case 0: r = 255; break;
    case 1: g = 255; break;
    case 2: b = 255; break;
    }

    return RGB(r, g, b);
}

void Fireworks2D::Run() //不断产生新粒子，粒子的更新由其定时回调处理 
{
	for (int i = 0; i < mParticlesGen; i++)
	{
        if(rand()%100 <1)
        { 
		    FireworksParticle* sp = new FireworksParticle(mScene, mPos + Vec2d(-1000 + rand() % 2000, -1000), 5 + rand() % 10);
            COLORREF vibrantColor = getRandomVibrantColor();
            sp->mColor = vibrantColor;
		    sp->setBrushColor(vibrantColor);
		    sp->setPenColor(vibrantColor);
		    sp->mSpeedX = (rand() % 5) - 2;
		    sp->mSpeedY = rand() % 10 + 10;
            sp->mGAccY = -0.007;
		    sp->mLife = 4500+rand()%1000;
            sp->mType = ParticleType::Ascending;
            sp->mAccSpeed = 0.9 + rand() % 10;
            sp->expParNum = 20 + rand() % 100;
            sp->setBoundsDirty(true);
		    mScene->addRenderable(sp);
        }
	}
}
