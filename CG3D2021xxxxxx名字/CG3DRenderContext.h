#ifndef _CG3DRenderContext_H_INCLUDED 
#define _CG3DRenderContext_H_INCLUDED 

#include "CGRenderState.h"

class CG3DCamera;
class CG3DRenderContext
{
public:
	CG3DRenderContext();
	virtual ~CG3DRenderContext();

	//���ƿͻ����Ŀ�ȡ��߶ȣ���������������ʵ�֣� 
	virtual void GetClientWidthHeight(int& w, int& h) = 0;
	virtual bool SetupRenderContext() = 0;
	virtual void Ready(CG3DCamera*) = 0;
	virtual void Finish(CG3DCamera*) = 0;
protected:
	virtual bool SetupPixelFormat(void) = 0;

protected:
	COLORREF mBkgndColor = RGB(0, 0, 0); //������ɫ 
	double mBkgndDepth = 1000.0; //������ȣ�Ĭ����Ȼ�����ȣ� 
	CG3DCamera* mCamera = nullptr; //��ǰʹ�õ��������ȡ�ӿ�λ�á����� 

	HWND mHWnd = 0;  //ͨ������������ 
	HDC  mHDC = 0;  //ͨ������������ 
	HGLRC mHGLRC = 0; //ͨ������������ 
	HPALETTE mPalette = 0; //OpenGL��ɫ�� 
public: //ʵ��7
	//���ر��� 
	bool Enable(EEnable capability);
	bool Disable(EEnable capability);
	//�������� 
	bool IsShading() { return bShading; }
	bool IsLighting();
	void Shading(bool shading);
	void Lighting(bool lighting);
protected:
	//���ղ��� 
	bool bShading = false; //�Ƿ�ʹ�ò������� 
	bool bLighting = false; //�Ƿ����ù��չ���
};

#endif //_CG3DRenderContext_H_INCLUDED
