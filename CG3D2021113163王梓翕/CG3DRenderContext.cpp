#include "pch.h" 
#include "CG3DRenderContext.h" 
CG3DRenderContext::CG3DRenderContext()
{
}
CG3DRenderContext::~CG3DRenderContext()
{
	if (mPalette)
	{
		DeleteObject(mPalette);
		mPalette = 0;
	}
	::wglMakeCurrent(NULL, NULL);
	::wglDeleteContext(mHGLRC);
	if (mHDC != 0)
	{
		::ReleaseDC(mHWnd, mHDC); // Õ∑≈DC 
		mHDC = 0;
	}
}