#ifndef _CGLight_H_INCLUDED 
#define _CGLight_H_INCLUDED
#include "CGRenderState.h" 
#include "Vector4.h" 
#include "Matrix44.h" 

class CGLight : public CGRenderState
{
    DECLARE_SERIAL(CGLight)
public:
    CGLight();
    //CGLight(const CString& name); 
    CGLight(const CGLight& other);
    virtual ~CGLight() = default;
    //���л� 
    virtual void Serialize(CArchive& ar);

    //���������������в��� 
    void setAsDirectionalLight() {
        mPosition = Vec4f(mPosition.x(), mPosition.y(), mPosition.z(), 0.0f);
    }
    void setAsPointLight() {
        mPosition = Vec4f(mPosition.x(), mPosition.y(), mPosition.z(), 1.0f);
        mSpotCutoff = 180.0f;
    }
    void setAsSpotLight() {
        mPosition = Vec4f(mPosition.x(), mPosition.y(), mPosition.z(), 1.0f);
        if(mSpotCutoff>90.0f) mSpotCutoff = 45.0f;
    }
    void setAmbient(const Vec4f& ambient) { mAmbient = ambient; }
    void setDiffuse(const Vec4f& diffuse) { mDiffuse = diffuse; }
    void setSpecular(const Vec4f& specular) { mSpecular = specular; }
    void setPosition(const Vec4f& pos) { mPosition = Vec4f(pos.x(), pos.y(), pos.z(), pos.w()); }
    void setPosition(const Vec3f& pos) {mPosition = Vec4f(pos.x(), pos.y(), pos.z(), mPosition.w());}
    void setSpotlightExponent(float exponent) { mSpotExponent = exponent; }
    void setSpotlightCutoff(float cutoff) { mSpotCutoff = cutoff; }
    void setSpotlightParameters(const Vec3f& direction, float exponent, float cutoff) {
        mSpotDirection = direction;   // ���þ۹�Ʒ���
        mSpotExponent = exponent;     // ���þ۹�Ƶľ۹�ָ��
        mSpotCutoff = cutoff;         // ���þ۹�Ƶ����ɢ�Ƕ�
    }
    void setAttenuation(float constant, float linear, float quadratic) {
        mConstantAttenuation = constant;      // ����˥��
        mLinearAttenuation = linear;          // һ��˥��
        mQuadraticAttenuation = quadratic;    // ����˥��
    }

    // ԭʼ
    void setEnabled(bool enabled) { mEnabled = enabled; }
    bool enabled() const { return mEnabled; }

    //Ӧ�ã���дʵ�ֶ�̬ 
    virtual void apply(int index, const CG3DCamera* camera, CG3DRenderContext* ctx, bool ena = true) const;

protected:
    Vec4f mAmbient;     //��������ɣ�����ȡֵ0~1�� 
    Vec4f mDiffuse;     //��������ɣ�����ȡֵ0~1�� 
    Vec4f mSpecular;    //���������ɣ�����ȡֵ0~1�� 
    Vec4f mPosition;    //λ�ã���ʵ��λ�ù�Դ�������Դ��  //1=���Դ��0=�����Դ 
    Vec3f mSpotDirection;   //�۹ⷽ�� 
    float mSpotExponent;    //�۹�̶ȣ�0~128�� 
    float mSpotCutoff;      //��ɢ�Ƕȣ�0~180�� 
    float mConstantAttenuation; //˥����ϵ�������ڵ���0�� 
    float mLinearAttenuation;   //˥��һ��ϵ�������ڵ���0�� 
    float mQuadraticAttenuation;    //˥������ϵ�������ڵ���0�� 
    bool mEnabled;  //������Դ��Ҫ�򿪹��գ� 
};
#endif //_CGLight_H_INCLUDED
