#ifndef _CGLightModel_H_INCLUDED 
#define _CGLightModel_H_INCLUDED 
#include "CGRenderState.h" 
#include "Vector4.h" 

class CGLightModel : public CGRenderState
{
    DECLARE_SERIAL(CGLightModel)
public:
    CGLightModel();
    //CGLightModel(const CString& name); 
    virtual ~CGLightModel() = default;
    //序列化 
    virtual void Serialize(CArchive& ar);
    virtual ERenderState type() const { return ERenderState::RS_LightModel; }

    //应用，重写实现多态 
    virtual void apply(int index, const CG3DCamera* camera, CG3DRenderContext* ctx) const;

    //其他辅助函数自行实现 

    const Vec4f& ambientColor() const { return mAmbientColor; }

protected:
    Vec4f mAmbientColor;    //全局环境光 
    bool mLocalViewer;      //无限远或局部观察 
    bool mTwoSide;          //双面光照 
};

#endif //_CGLightModel_H_INCLUDED 
