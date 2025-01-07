#ifndef _CGPolygonMode_H_INCLUDED 
#define _CGPolygonMode_H_INCLUDED 
#include "CGRenderState.h"
class CGPolygonMode : public CGRenderState
{
    DECLARE_SERIAL(CGPolygonMode)
public:
    CGPolygonMode(EPolygonMode frontface = EPolygonMode::PM_FILL, EPolygonMode backface =
        EPolygonMode::PM_FILL);
    virtual ~CGPolygonMode() = default;
    //序列化 
    virtual void Serialize(CArchive& ar);
    virtual ERenderState type() const { return ERenderState::RS_PolygonMode; }

    //应用，重写实现多态 
    virtual void apply(int index, const CG3DCamera* camera, CG3DRenderContext* ctx) const;

    void set(EPolygonMode frontface, EPolygonMode backface) {
        mFrontFace = frontface; mBackFace =
            backface;
    }

    void setFrontFace(EPolygonMode frontface) { mFrontFace = frontface; }

    void setBackFace(EPolygonMode backface) { mBackFace = backface; }

    EPolygonMode frontFace() const { return mFrontFace; }

    EPolygonMode backFace() const { return mBackFace; }

protected:
    EPolygonMode mFrontFace;
    EPolygonMode mBackFace;
};

#endif //_CGPolygonMode_H_INCLUDED
