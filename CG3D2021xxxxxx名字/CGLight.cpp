#include "pch.h" 
#include "CGLight.h" 

IMPLEMENT_SERIAL(CGLight, CGRenderState, 1) //1���Կ��������ݰ汾�ţ����ڼ����������������ݳ�Ա�� 

CGLight::CGLight()
	:CGRenderState(CString("CGLight"))
{
	mAmbient = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
	mDiffuse = Vec4f(0.6f, 0.6f, 0.6f, 1.0f);
	mSpecular = Vec4f(1.0f, 0.6f, 0.6f, 1.0f);
	mPosition = Vec4f(0.0f, 0.0f, 10.0f, 1.0f); //1=���Դ��0=�����Դ 
	mSpotDirection = Vec3f(0.0f, -0.0f, -1.0f);
	mSpotExponent = 10.0f;
	mSpotCutoff = 30.0f;
	mConstantAttenuation = 0.5f;
	mLinearAttenuation = 0.0f;
	mQuadraticAttenuation = 0.0f;
	//mTransform = Mat4d(); 
	mEnabled = true;
}

CGLight::CGLight(const CGLight& other)
	: CGRenderState(other.Name())
{
	mAmbient = other.mAmbient;
	mDiffuse = other.mDiffuse;
	mSpecular = other.mSpecular;
	mPosition = other.mPosition;
	mSpotDirection = other.mSpotDirection;
	mSpotExponent = other.mSpotExponent;
	mSpotCutoff = other.mSpotCutoff;
	mConstantAttenuation = other.mConstantAttenuation;
	mLinearAttenuation = other.mLinearAttenuation;
	mQuadraticAttenuation = other.mQuadraticAttenuation;
	//mTransform = other.mTransform; 
	mEnabled = other.mEnabled;
	mCallback = other.mCallback;
}

//���л� 
void CGLight::Serialize(CArchive& ar)
{
	CGRenderState::Serialize(ar); //�ȵ��û�������л������������л��Լ��ĳ�Ա��������Ҫ�� 
	if (ar.IsStoring())  //���� 
	{
		ar << mAmbient.r() << mAmbient.g() << mAmbient.b() << mAmbient.a();
		ar << mDiffuse.r() << mDiffuse.g() << mDiffuse.b() << mDiffuse.a();
		ar << mSpecular.r() << mSpecular.g() << mSpecular.b() << mSpecular.a();
		ar << mPosition.r() << mPosition.g() << mPosition.b() << mPosition.a();
		ar << mSpotDirection.x() << mSpotDirection.y() << mSpotDirection.z();
		ar << mSpotExponent << mSpotCutoff << mConstantAttenuation << mLinearAttenuation << mQuadraticAttenuation;
		ar << mEnabled;
	}
	else //��ȡ 
	{
		ar >> mAmbient.r() >> mAmbient.g() >> mAmbient.b() >> mAmbient.a();
		ar >> mDiffuse.r() >> mDiffuse.g() >> mDiffuse.b() >> mDiffuse.a();
		ar >> mSpecular.r() >> mSpecular.g() >> mSpecular.b() >> mSpecular.a();
		ar >> mPosition.r() >> mPosition.g() >> mPosition.b() >> mPosition.a();
		ar >> mSpotDirection.x() >> mSpotDirection.y() >> mSpotDirection.z();
		ar >> mSpotExponent >> mSpotCutoff >> mConstantAttenuation >> mLinearAttenuation >>
			mQuadraticAttenuation;
		ar >> mEnabled;
	}
}

//Ӧ�ã���дʵ�ֶ�̬ 
void CGLight::apply(int index, const CG3DCamera* camera, CG3DRenderContext* ctx, bool ena) const
{
	if (enabled() && ena)
	{
		glEnable(GL_LIGHT0 + index);
		glEnable(GL_DEPTH_TEST);    // ������Ȳ��ԣ�������յ��µ���Ⱦ˳������
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		//glLoadIdentity();

		glLightfv(GL_LIGHT0 + index, GL_AMBIENT, mAmbient.ptr());
		glLightfv(GL_LIGHT0 + index, GL_DIFFUSE, mDiffuse.ptr());
		glLightfv(GL_LIGHT0 + index, GL_SPECULAR, mSpecular.ptr());
		glLightfv(GL_LIGHT0 + index, GL_POSITION, mPosition.ptr());

		// ����ǵ��Դ
		if(mPosition.w() != 0)
		{ 
			
			// ����Ǿ۹��
			if (mSpotCutoff >= 0.0f && mSpotCutoff <= 90.0f)
			{
				glLightf(GL_LIGHT0 + index, GL_SPOT_CUTOFF, mSpotCutoff);
				glLightfv(GL_LIGHT0 + index, GL_SPOT_DIRECTION, mSpotDirection.ptr());
				glLightf(GL_LIGHT0 + index, GL_SPOT_EXPONENT, mSpotExponent);
			}
		
			// ����ǵ��Դ��۹�ƣ�����˥������
			if (mConstantAttenuation + mLinearAttenuation + mQuadraticAttenuation > 0) {
				glLightf(GL_LIGHT0 + index, GL_CONSTANT_ATTENUATION, mConstantAttenuation);
				glLightf(GL_LIGHT0 + index, GL_LINEAR_ATTENUATION, mLinearAttenuation);
				glLightf(GL_LIGHT0 + index, GL_QUADRATIC_ATTENUATION, mQuadraticAttenuation);
			}
			
		}

		glPopMatrix();

	}
	else
	{
		glDisable(GL_LIGHT0 + index);
	}
}
