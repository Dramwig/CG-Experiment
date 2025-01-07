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
    //���л� 
    virtual void Serialize(CArchive& ar);
    virtual ERenderState type() const { return ERenderState::RS_LightModel; }

    //Ӧ�ã���дʵ�ֶ�̬ 
    virtual void apply(int index, const CG3DCamera* camera, CG3DRenderContext* ctx) const;

    //����������������ʵ�� 

    const Vec4f& ambientColor() const { return mAmbientColor; }

protected:
    Vec4f mAmbientColor;    //ȫ�ֻ����� 
    bool mLocalViewer;      //����Զ��ֲ��۲� 
    bool mTwoSide;          //˫����� 
};

#endif //_CGLightModel_H_INCLUDED 
