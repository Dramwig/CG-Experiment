#ifndef _CG3DRenderContext_H_INCLUDED 
#define _CG3DRenderContext_H_INCLUDED 

#include "CGRenderState.h"

class CG3DCamera;
class CG3DRenderContext
{
public:
	CG3DRenderContext();
	virtual ~CG3DRenderContext();

	//绘制客户区的宽度、高度（必须在派生类中实现） 
	virtual void GetClientWidthHeight(int& w, int& h) = 0;
	virtual bool SetupRenderContext() = 0;
	virtual void Ready(CG3DCamera*) = 0;
	virtual void Finish(CG3DCamera*) = 0;
protected:
	virtual bool SetupPixelFormat(void) = 0;

protected:
	COLORREF mBkgndColor = RGB(0, 0, 0); //背景颜色 
	double mBkgndDepth = 1000.0; //背景深度（默认深度缓存深度） 
	CG3DCamera* mCamera = nullptr; //当前使用的相机，获取视口位置、长宽。 

	HWND mHWnd = 0;  //通过派生类设置 
	HDC  mHDC = 0;  //通过派生类设置 
	HGLRC mHGLRC = 0; //通过派生类设置 
	HPALETTE mPalette = 0; //OpenGL调色板 
public: //实验7
	//开关变量 
	bool Enable(EEnable capability);
	bool Disable(EEnable capability);
	//辅助函数 
	bool IsShading() { return bShading; }
	bool IsLighting();
	void Shading(bool shading);
	void Lighting(bool lighting);
protected:
	//光照材质 
	bool bShading = false; //是否使用材质属性 
	bool bLighting = false; //是否启用光照功能
};

#endif //_CG3DRenderContext_H_INCLUDED
