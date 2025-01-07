#ifndef _CGColorMeterial_H_INCLUDED 
#define _CGColorMeterial_H_INCLUDED 
#include "CGRenderState.h" 
#include "Vector4.h" 

class CGColorMaterial : public CGRenderState
{
    DECLARE_SERIAL(CGColorMaterial)
public:
    CGColorMaterial();
    virtual ~CGColorMaterial() = default;
    //序列化 
    virtual void Serialize(CArchive& ar);
    virtual ERenderState type() const { return ERenderState::RS_Material; }
    //应用，重写基类虚函数实现多态 
    virtual void apply(int index, const CG3DCamera* camera, CG3DRenderContext* ctx) const;

    //其他数据成员访问设置辅助函数自行补充 
    void setFlatColor(Vec4f color) {
        //setFrontAmbient(color);
        //setFrontDiffuse(color);
        //setFrontSpecular(color);
        setFrontEmission(color);
        //setBackAmbient(color);
        //setBackDiffuse(color);
        //setBackSpecular(color);
        setBackEmission(color);
    }
    void setShininess(float hininoss) { mFrontShininess = mBackShininess; }

    void setFrontAmbient(const Vec4f& color) { mFrontAmbient = color; }
    void setFrontDiffuse(const Vec4f& color) { mFrontDiffuse = color; }
    void setFrontSpecular(const Vec4f& color) {mFrontSpecular = color;}
    void setFrontEmission(const Vec4f& color) {mFrontEmission = color;}
    void setFrontShininess(float shininess) {mFrontShininess = shininess;}
    void setBackAmbient(const Vec4f& color) { mBackAmbient = color; }
    void setBackDiffuse(const Vec4f& color) { mBackDiffuse = color; }
    void setBackSpecular(const Vec4f& color) { mBackSpecular = color; }
    void setBackEmission(const Vec4f& color) { mBackEmission = color; }
    void setBackShininess(float shininess) { mBackShininess = shininess; }
     
    const Vec4f& frontAmbient() const {return mFrontAmbient; }
    const Vec4f& frontDiffuse() const {return mFrontDiffuse; }
    const Vec4f& frontSpecular()const { return mFrontSpecular;}
    const Vec4f& frontEmission() const { return mFrontEmission; }
    float frontShininess() const {  return mFrontShininess; }

    void setTransparency(float alpha);
    void setFrontTransparency(float alpha);
    void setBackTransparency(float alpha);

    // 材质设置
    //金属材质
    void setMetallicMaterial(Vec4f color = Vec4f(1,1,1,1)) {
        setFrontAmbient(Vec4f(0.25f, 0.25f, 0.25f, 1.0f) * color); // 微弱的环境光
        setFrontDiffuse(Vec4f(0.3f, 0.3f, 0.3f, 1.0f) * color);    // 低漫反射
        setFrontSpecular(Vec4f(0.9f, 0.9f, 0.9f, 1.0f) * color); // 强镜面反射
        setFrontShininess(76.8f); // 高光滑度
        setFrontEmission(Vec4f(0.0f, 0.0f, 0.0f, 1.0f) * color);  // 无自发光
    }
    //塑料材质
    void setPlasticMaterial(Vec4f color = Vec4f(1, 1, 1, 1)) {
        setFrontAmbient(Vec4f(0.2f, 0.2f, 0.2f, 1.0f) * color); // 无环境光
        setFrontDiffuse(Vec4f(0.8f, 0.8f, 0.8f, 1.0f) * color); // 高漫反射
        setFrontSpecular(Vec4f(0.40f, 0.40f, 0.40f, 1.0f) * color); // 适中的镜面反射
        setFrontShininess(32.0f); // 中等光滑度
        setFrontEmission(Vec4f(0.0f, 0.0f, 0.0f, 1.0f) * color); // 无自发光
    }
    //玻璃材质
    void setGlassMaterial(Vec4f color = Vec4f(1, 1, 1, 1)) {
        setFrontAmbient(Vec4f(0.1f, 0.1f, 0.1f, 1.0f) * color);  // 轻微环境光，模拟周围环境对玻璃的轻微影响
        setFrontDiffuse(Vec4f(0.6f, 0.6f, 0.6f, 0.5f) * color);  // 高漫反射，但透明度减半以允许光线穿透
        setFrontSpecular(Vec4f(0.98f, 0.98f, 0.98f, 1.0f) * color); // 极强镜面反射
        setFrontShininess(125.0f); // 高光滑度保持不变
        setFrontEmission(Vec4f(0.0f, 0.0f, 0.0f, 1.0f) * color);    // 无自发光

        // 假设存在以下方法来设置透明度和折射率
        setFrontTransparency(0.9f);       // 设置高透明度
        //setFrontRefractionIndex(1.5f);    // 玻璃的典型折射率约为1.5
    }
    // 木质材质
    void setWoodenMaterial(Vec4f color = Vec4f(0.6f, 0.4f, 0.1f, 1.0f)) {
        setFrontAmbient(Vec4f(0.15f, 0.1f, 0.05f, 1.0f) * color); // 柔和环境光
        setFrontDiffuse(Vec4f(0.6f, 0.4f, 0.1f, 1.0f) * color);   // 温暖的漫反射
        setFrontSpecular(Vec4f(0.2f, 0.2f, 0.2f, 1.0f) * color); // 较弱的镜面反射，模拟木质光泽
        setFrontShininess(10.0f); // 较低光滑度，木头表面较粗糙
        setFrontEmission(Vec4f(0.0f, 0.0f, 0.0f, 1.0f));         // 无自发光
    }
    // 陶瓷材质
    void setCeramicMaterial(Vec4f color = Vec4f(1.0f, 1.0f, 1.0f, 1.0f)) {
        setFrontAmbient(Vec4f(0.1f, 0.1f, 0.1f, 1.0f) * color); // 环境光影响较小
        setFrontDiffuse(Vec4f(0.8f, 0.8f, 0.8f, 1.0f) * color); // 高漫反射，表现陶瓷的白净
        setFrontSpecular(Vec4f(0.9f, 0.9f, 0.9f, 1.0f) * color); // 强镜面反射，陶瓷的光泽感
        setFrontShininess(120.0f); // 非常高的光滑度，陶瓷表面光滑
        setFrontEmission(Vec4f(0.0f, 0.0f, 0.0f, 1.0f));         // 无自发光
    }

    // 橡胶材质
    void setRubberMaterial(Vec4f color = Vec4f(0.1f, 0.1f, 0.1f, 1.0f)) {
        setFrontAmbient(Vec4f(0.05f, 0.05f, 0.05f, 1.0f) * color); // 很弱的环境光，因为橡胶吸光
        setFrontDiffuse(Vec4f(0.3f, 0.3f, 0.3f, 1.0f) * color);   // 低漫反射，暗淡的表面
        setFrontSpecular(Vec4f(0.2f, 0.2f, 0.2f, 1.0f) * color); // 很弱的镜面反射，橡胶表面不反光
        setFrontShininess(5.0f); // 低光滑度，橡胶手感较粗糙
        setFrontEmission(Vec4f(0.0f, 0.0f, 0.0f, 1.0f));         // 无自发光
    }

    // 原有
    void setColorMaterial(EPolygonFace face, EColorMaterial color) {
        mColorMaterialFace = face;
        mColorMaterial = color;
    }
    EPolygonFace colorMaterialFace() const { return mColorMaterialFace; }
    EColorMaterial colorMaterial() const { return mColorMaterial; }
    void setColorMaterialEnabled(bool enabled) { mColorMaterialEnabled = enabled; }
    bool colorMaterialEnabled() const { return mColorMaterialEnabled; }

protected:
    Vec4f mFrontAmbient;    //前向面环境反射系数（0~1） 
    Vec4f mFrontDiffuse;    //前向面漫反射系数（0~1） 
    Vec4f mFrontSpecular;   //前向面镜面反射系数（0~1） 
    Vec4f mFrontEmission;   //前向面散射系数（0~1） 
    Vec4f mBackAmbient;     //背向面环境反射系数（0~1） 
    Vec4f mBackDiffuse;     //背向面漫反射系数（0~1） 
    Vec4f mBackSpecular;    //背向面镜面反射系数（0~1） 
    Vec4f mBackEmission;    //背向面散射系数（0~1） 
    float mBackShininess;   //背向面光滑系数（0~128） 
    float mFrontShininess;  //前向面光滑系数（0~128） 
    //颜色材质（设置的颜色glColor作为材质参数） 
    EPolygonFace mColorMaterialFace;    //作用于哪种面 
    EColorMaterial mColorMaterial;      //颜色作为哪种材质参数 
    bool mColorMaterialEnabled;         //启用颜色作为材质属性 
};

#endif //_CGColorMeterial_H_INCLUDED
