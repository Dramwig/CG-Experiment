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
    //���л� 
    virtual void Serialize(CArchive& ar);
    virtual ERenderState type() const { return ERenderState::RS_Material; }
    //Ӧ�ã���Ҫ������������дʵ�ֶ�̬ 
    virtual void apply(int index, const CG3DCamera* camera, CG3DRenderContext* ctx) const;
    //��� 
    CGColorMaterial& Material() { return mMaterial; }
    const CGColorMaterial& Material() const { return mMaterial; }

protected:
    //��ɫ����� 
    CGColorMaterial mMaterial;
    //�������ԣ��������������Ե� 

};

#endif //_CGAppearance_H_INCLUDED
