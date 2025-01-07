#ifndef _CGShadeModel_H_INCLUDED 
#define _CGShadeModel_H_INCLUDED 
#include "CGRenderState.h" 

class CGShadeModel : public CGRenderState
{
    DECLARE_SERIAL(CGShadeModel)
public:
    CGShadeModel(EShadeModel shademodel = EShadeModel::SM_SMOOTH);
    virtual ~CGShadeModel() = default;
    //���л� 
    virtual void Serialize(CArchive& ar);
    virtual ERenderState type() const { return ERenderState::RS_ShadeModel; }

    //Ӧ�ã���дʵ�ֶ�̬ 
    virtual void apply(int index, const CG3DCamera* camera, CG3DRenderContext* ctx) const;

    void set(EShadeModel shademodel) { mShadeModel = shademodel; }
    EShadeModel shadeModel() const { return mShadeModel; }

protected:
    EShadeModel mShadeModel;
};

#endif //_CGShadeModel_H_INCLUDED
