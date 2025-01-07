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
    //序列化 
    virtual void Serialize(CArchive& ar);

    //其他辅助函数自行补充 
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
        mSpotDirection = direction;   // 设置聚光灯方向
        mSpotExponent = exponent;     // 设置聚光灯的聚光指数
        mSpotCutoff = cutoff;         // 设置聚光灯的最大发散角度
    }
    void setAttenuation(float constant, float linear, float quadratic) {
        mConstantAttenuation = constant;      // 常数衰减
        mLinearAttenuation = linear;          // 一次衰减
        mQuadraticAttenuation = quadratic;    // 二次衰减
    }

    // 原始
    void setEnabled(bool enabled) { mEnabled = enabled; }
    bool enabled() const { return mEnabled; }

    //应用，重写实现多态 
    virtual void apply(int index, const CG3DCamera* camera, CG3DRenderContext* ctx, bool ena = true) const;

protected:
    Vec4f mAmbient;     //环境光组成（各项取值0~1） 
    Vec4f mDiffuse;     //漫反射组成（各项取值0~1） 
    Vec4f mSpecular;    //镜面放射组成（各项取值0~1） 
    Vec4f mPosition;    //位置（可实现位置光源、方向光源）  //1=点光源，0=方向光源 
    Vec3f mSpotDirection;   //聚光方向 
    float mSpotExponent;    //聚光程度（0~128） 
    float mSpotCutoff;      //发散角度（0~180） 
    float mConstantAttenuation; //衰减常系数（大于等于0） 
    float mLinearAttenuation;   //衰减一次系数（大于等于0） 
    float mQuadraticAttenuation;    //衰减二次系数（大于等于0） 
    bool mEnabled;  //开启光源（要打开光照） 
};
#endif //_CGLight_H_INCLUDED
