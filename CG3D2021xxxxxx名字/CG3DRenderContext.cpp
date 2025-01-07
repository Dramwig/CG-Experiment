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
		::ReleaseDC(mHWnd, mHDC); //�ͷ�DC 
		mHDC = 0;
	}
}

//���ر��� 
bool CG3DRenderContext::Enable(EEnable capability)
{
	GLboolean enable = glIsEnabled((GLenum)capability);
	glEnable((GLenum)capability);
	return enable;
}
bool CG3DRenderContext::Disable(EEnable capability)
{
	GLboolean enable = glIsEnabled((GLenum)capability);
	glDisable((GLenum)capability);
	return enable;
}
//�������� 
bool CG3DRenderContext::IsLighting()
{
	GLboolean bLighting;
	glGetBooleanv(GL_LIGHTING, &bLighting);
	return bLighting;
}
void CG3DRenderContext::Shading(bool shading)
{
	bShading = shading;
	if (bShading) {
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		//glPolygonMode��һ����������GL_FRONT��GL_BACK��GL_FRONT_AND_BACK 
		//glPolygonMode�ڶ�����������GL_POINT��GL_LINE��GL_FILL 
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else {
		glDisable(GL_LIGHTING);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
}
void CG3DRenderContext::Lighting(bool lighting)
{
	if (bLighting)
		glEnable(GL_LIGHTING);
	else
		glDisable(GL_LIGHTING);
}
