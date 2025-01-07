#include "pch.h" 
#include "CGColorMaterial.h" 
#include <limits> 
#include "CG3DCamera.h" 
#include "CG3DRenderContext.h" 

IMPLEMENT_SERIAL(CGColorMaterial, CGRenderState, 1) //1���Կ��������ݰ汾�ţ����ڼ����������������ݳ�Ա�� 
 
CGColorMaterial::CGColorMaterial()
	:CGRenderState(CString("CGRenderState"))
{
	mFrontAmbient = Vec4f(0.2f, 0.2f, 0.2f, 1.0f);
	mFrontDiffuse = Vec4f(0.8f, 0.8f, 0.8f, 1.0f);
	mFrontSpecular = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
	mFrontEmission = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
	mFrontShininess = 0;

	mBackAmbient = Vec4f(0.2f, 0.2f, 0.2f, 1.0f);
	mBackDiffuse = Vec4f(0.8f, 0.8f, 0.8f, 1.0f);
	mBackSpecular = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
	mBackEmission = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
	mBackShininess = 0;

	mColorMaterialEnabled = false;
	mColorMaterialFace = EPolygonFace::PF_FRONT_AND_BACK;
	mColorMaterial = EColorMaterial::CM_AMBIENT_AND_DIFFUSE;
}
//���л� 
void CGColorMaterial::Serialize(CArchive& ar)
{
	CGRenderState::Serialize(ar); //�ȵ��û�������л������������л��Լ��ĳ�Ա��������Ҫ�� 
	if (ar.IsStoring())  //���棬�Լ����� 
	{
	}
	else //��ȡ 
	{
	}
}

//Ӧ�ã���дʵ�ֶ�̬ 
void CGColorMaterial::apply(int index, const CG3DCamera* camera, CG3DRenderContext* ctx) const
{
	if (mColorMaterialEnabled)
	{
		glColorMaterial((GLenum)colorMaterialFace(), (GLenum)colorMaterial());
		glEnable(GL_COLOR_MATERIAL);
	}
	else
	{
		glDisable(GL_COLOR_MATERIAL);
	}

	if (mFrontAmbient == mBackAmbient)
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mFrontAmbient.ptr());
	}
	else
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, mFrontAmbient.ptr());
		glMaterialfv(GL_BACK, GL_AMBIENT, mBackAmbient.ptr());
	}

	if (mFrontDiffuse == mBackDiffuse)
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mFrontDiffuse.ptr());
	}
	else
	{
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mFrontDiffuse.ptr());
		glMaterialfv(GL_BACK, GL_DIFFUSE, mBackDiffuse.ptr());
	}

	if (mFrontSpecular == mBackSpecular)
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mFrontSpecular.ptr());
	}
	else
	{
		glMaterialfv(GL_FRONT, GL_SPECULAR, mFrontSpecular.ptr());
		glMaterialfv(GL_BACK, GL_SPECULAR, mBackSpecular.ptr());
	}

	if (mFrontEmission == mBackEmission)
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mFrontEmission.ptr());
	}
	else
	{
		glMaterialfv(GL_FRONT, GL_EMISSION, mFrontEmission.ptr());
		glMaterialfv(GL_BACK, GL_EMISSION, mBackEmission.ptr());
	}

	if (mFrontShininess == mBackShininess)
	{
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mFrontShininess);
	}
	else
	{
		glMaterialf(GL_FRONT, GL_SHININESS, mFrontShininess);
		glMaterialf(GL_BACK, GL_SHININESS, mBackShininess);
	}
}

void CGColorMaterial::setTransparency(float alpha) {
	mFrontAmbient.a()= alpha;
	mFrontDiffuse.a() = alpha;
	mFrontSpecular.a() = alpha;
	mFrontEmission.a() = alpha;
	mBackAmbient.a() = alpha;
	mBackDiffuse.a() = alpha;
	mBackSpecular.a() = alpha;
	mBackEmission.a() = alpha;
}
void CGColorMaterial::setFrontTransparency(float alpha) {
	mFrontAmbient.a() = alpha;
	mFrontDiffuse.a() = alpha;
	mFrontSpecular.a() = alpha;
	mFrontEmission.a() = alpha;
}
void CGColorMaterial::setBackTransparency(float alpha) {
	mBackAmbient.a() = alpha;
	mBackDiffuse.a() = alpha;
	mBackSpecular.a() = alpha;
	mBackEmission.a() = alpha;
}
