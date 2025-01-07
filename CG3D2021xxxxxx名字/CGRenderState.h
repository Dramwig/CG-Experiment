#ifndef _CGRenderState_H_INCLUDED 
#define _CGRenderState_H_INCLUDED 
#include "CGObject.h" 

enum class EPolygonFace : unsigned int
{
    PF_FRONT = GL_FRONT,
    PF_BACK = GL_BACK,
    PF_FRONT_AND_BACK = GL_FRONT_AND_BACK
};

enum class EColorMaterial : unsigned int
{
    CM_EMISSION = GL_EMISSION,
    CM_AMBIENT = GL_AMBIENT,
    CM_DIFFUSE = GL_DIFFUSE,
    CM_SPECULAR = GL_SPECULAR,
    CM_AMBIENT_AND_DIFFUSE = GL_AMBIENT_AND_DIFFUSE
};

enum class EPolygonMode : unsigned int
{
    PM_FILL = GL_FILL,
    PM_LINE = GL_LINE,
    PM_POINT = GL_POINT
};

enum class EShadeModel : unsigned int
{
    SM_FLAT = GL_FLAT,
    SM_SMOOTH = GL_SMOOTH
};

enum class EFrontFace : unsigned int
{
    FF_CW = GL_CW,
    FF_CCW = GL_CCW
};

enum class EFogMode : unsigned int
{
    FM_LINEAR = GL_LINEAR,
    FM_EXP = GL_EXP,
    FM_EXP2 = GL_EXP2
};

enum class EHintMode : unsigned int
{
    HM_FASTEST = GL_FASTEST,
    HM_NICEST = GL_NICEST,
    HM_DONT_CARE = GL_DONT_CARE
};

//������ 
enum class EEnable : unsigned int
{
    // Common ones 
    EN_BLEND = GL_BLEND,
    EN_CULL_FACE = GL_CULL_FACE,
    EN_DEPTH_TEST = GL_DEPTH_TEST,
    EN_STENCIL_TEST = GL_STENCIL_TEST,
    EN_DITHER = GL_DITHER,
    EN_POLYGON_OFFSET_FILL = GL_POLYGON_OFFSET_FILL,
    EN_POLYGON_OFFSET_LINE = GL_POLYGON_OFFSET_LINE,
    EN_POLYGON_OFFSET_POINT = GL_POLYGON_OFFSET_POINT,
    EN_COLOR_LOGIC_OP = GL_COLOR_LOGIC_OP,

    EN_POINT_SMOOTH = GL_POINT_SMOOTH,
    EN_LINE_SMOOTH = GL_LINE_SMOOTH,
    EN_POLYGON_SMOOTH = GL_POLYGON_SMOOTH,

    EN_LINE_STIPPLE = GL_LINE_STIPPLE,
    EN_POLYGON_STIPPLE = GL_POLYGON_STIPPLE,

    EN_ALPHA_TEST = GL_ALPHA_TEST,
    EN_LIGHTING = GL_LIGHTING,
    EN_FOG = GL_FOG,
    EN_NORMALIZE = GL_NORMALIZE,
};

enum class ERenderState : unsigned int
{
    RS_AlphaFunc,
    RS_BlendColor,
    RS_BlendEquation,
    RS_BlendFunc,
    RS_Color,       //��ɫ 
    RS_ColorMask,
    RS_CullFace,
    RS_DepthFunc,
    RS_DepthMask,
    RS_DepthRange,
    RS_Fog,
    RS_FrontFace,   //������ 
    RS_PolygonMode, //�����ģʽ 
    RS_Hint,
    RS_LightModel,  // 
    RS_LineStipple,
    RS_LineWidth,   // 
    RS_Material,    //���� 
    RS_Normal,      //��������� 
    RS_PointSize,   //���С 
    RS_PolygonStipple,
    RS_ShadeModel,  //��ɫģʽ 

    //��Դ 
    RS_Light,
    RS_Light0 = RS_Light,   //Ĭ�Ϲ�Դ0 
    RS_Light1,
    RS_Light2,
    RS_Light3,
    RS_Light4,
    RS_Light5,
    RS_Light6,
    RS_Light7,

    RS_Unkown,
};

class CG3DCamera;
class CG3DRenderContext;
//OpenGL����״̬���� 
class CGRenderState : public CGObject
{
    DECLARE_SERIAL(CGRenderState)
    typedef bool (*CGRenderStateCallback)(CGRenderState*);   //�ص��������ͣ���Ҫһ������ָ�����������bool��
public:
    CGRenderState();
    CGRenderState(const CString& name);
    virtual ~CGRenderState() = default;
    //���л� 
    virtual void Serialize(CArchive& ar);
    virtual ERenderState type() const { return ERenderState::RS_Unkown; }

    //Ӧ�ã���Ҫ������������дʵ�ֶ�̬ 
    virtual void apply(int index, const CG3DCamera* camera, CG3DRenderContext* ctx) const;

    //ע��ص����� 
    void RegisterCallback(CGRenderStateCallback callback) { mCallback = callback; }
    void UnregisterCallback() { mCallback = nullptr; }
    CGRenderStateCallback Callback() { return mCallback; }
protected:
    CGRenderStateCallback mCallback = nullptr;   //����Ļص����� 
};

#endif //_CGRenderState_H_INCLUDED 
