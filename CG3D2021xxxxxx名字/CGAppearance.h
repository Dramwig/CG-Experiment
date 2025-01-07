#ifndef _CGAppearance_H_INCLUDED 
#define _CGAppearance_H_INCLUDED 

#include "CGRenderState.h" 
#include "CGColorMaterial.h" 

class CGAppearance : public CGRenderState
{
    DECLARE_SERIAL(CGAppearance)
public:
    CGAppearance();
    virtual ~CGAppearance() = default;
    //序列化 
    virtual void Serialize(CArchive& ar);
    virtual ERenderState type() const { return ERenderState::RS_Material; }
    //应用，需要在派生类中重写实现多态 
    virtual void apply(int index, const CG3DCamera* camera, CG3DRenderContext* ctx) const;
    //外观 
    CGColorMaterial& Material() { return mMaterial; }
    const CGColorMaterial& Material() const { return mMaterial; }

protected:
    //颜色或材质 
    CGColorMaterial mMaterial;
    //其他属性，如纹理，顶点属性等 

};

#endif //_CGAppearance_H_INCLUDED
