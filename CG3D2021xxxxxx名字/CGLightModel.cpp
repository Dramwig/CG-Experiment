#include "pch.h" 
#include "CGLightModel.h" 
#include "CG3DCamera.h" 
#include "CG3DRenderContext.h" 

IMPLEMENT_SERIAL(CGLightModel, CGRenderState, 1) //1可以看作是数据版本号，用于兼容升级（增加数据成员）

CGLightModel::CGLightModel()
	:CGRenderState(CString("CGRenderState"))
	, mAmbientColor(0.2f, 0.2f, 0.2f, 1.0f), mLocalViewer(false), mTwoSide(false)
{
}
//序列化 
void CGLightModel::Serialize(CArchive& ar)
{
	CGRenderState::Serialize(ar); //先调用基类的序列化函数，再序列化自己的成员（根据需要） 
	if (ar.IsStoring())  //保存，自行补充 
	{
	}
	else //读取 
	{
	}
}

//应用，需要在派生类中重写实现多态 
void CGLightModel::apply(int index, const CG3DCamera* camera, CG3DRenderContext* ctx) const
{
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, mLocalViewer ? 1.0f : 0.0f);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, mAmbientColor.ptr());
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, mTwoSide ? 1.0f : 0.0f);
}
