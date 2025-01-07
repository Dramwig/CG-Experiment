#include "pch.h" 
#include "CGLight.h" 

IMPLEMENT_SERIAL(CGLight, CGRenderState, 1) //1可以看作是数据版本号，用于兼容升级（增加数据成员） 

CGLight::CGLight()
	:CGRenderState(CString("CGLight"))
{
	mAmbient = Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
	mDiffuse = Vec4f(0.6f, 0.6f, 0.6f, 1.0f);
	mSpecular = Vec4f(1.0f, 0.6f, 0.6f, 1.0f);
	mPosition = Vec4f(0.0f, 0.0f, 10.0f, 1.0f); //1=点光源，0=方向光源 
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

//序列化 
void CGLight::Serialize(CArchive& ar)
{
	CGRenderState::Serialize(ar); //先调用基类的序列化函数，再序列化自己的成员（根据需要） 
	if (ar.IsStoring())  //保存 
	{
		ar << mAmbient.r() << mAmbient.g() << mAmbient.b() << mAmbient.a();
		ar << mDiffuse.r() << mDiffuse.g() << mDiffuse.b() << mDiffuse.a();
		ar << mSpecular.r() << mSpecular.g() << mSpecular.b() << mSpecular.a();
		ar << mPosition.r() << mPosition.g() << mPosition.b() << mPosition.a();
		ar << mSpotDirection.x() << mSpotDirection.y() << mSpotDirection.z();
		ar << mSpotExponent << mSpotCutoff << mConstantAttenuation << mLinearAttenuation << mQuadraticAttenuation;
		ar << mEnabled;
	}
	else //读取 
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

//应用，重写实现多态 
void CGLight::apply(int index, const CG3DCamera* camera, CG3DRenderContext* ctx, bool ena) const
{
	if (enabled() && ena)
	{
		glEnable(GL_LIGHT0 + index);
		glEnable(GL_DEPTH_TEST);    // 开启深度测试，避免光照导致的渲染顺序问题
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		//glLoadIdentity();

		glLightfv(GL_LIGHT0 + index, GL_AMBIENT, mAmbient.ptr());
		glLightfv(GL_LIGHT0 + index, GL_DIFFUSE, mDiffuse.ptr());
		glLightfv(GL_LIGHT0 + index, GL_SPECULAR, mSpecular.ptr());
		glLightfv(GL_LIGHT0 + index, GL_POSITION, mPosition.ptr());

		// 如果是点光源
		if(mPosition.w() != 0)
		{ 
			
			// 如果是聚光灯
			if (mSpotCutoff >= 0.0f && mSpotCutoff <= 90.0f)
			{
				glLightf(GL_LIGHT0 + index, GL_SPOT_CUTOFF, mSpotCutoff);
				glLightfv(GL_LIGHT0 + index, GL_SPOT_DIRECTION, mSpotDirection.ptr());
				glLightf(GL_LIGHT0 + index, GL_SPOT_EXPONENT, mSpotExponent);
			}
		
			// 如果是点光源或聚光灯，计算衰减因子
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
