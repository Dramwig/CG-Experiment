#include "pch.h" 
#include "CGShadeModel.h" 
#include "CG3DCamera.h" 
#include "CG3DRenderContext.h" 

IMPLEMENT_SERIAL(CGShadeModel, CGRenderState, 1) //1可以看作是数据版本号，用于兼容升级（增加数据成员）

CGShadeModel::CGShadeModel(EShadeModel shademodel/* = EShadeModel::SM_SMOOTH*/)
	:CGRenderState(CString("CGShadeModel"))
	, mShadeModel(shademodel)
{
}

//序列化 
void CGShadeModel::Serialize(CArchive& ar)
{
	CGRenderState::Serialize(ar); //先调用基类的序列化函数，再序列化自己的成员（根据需要） 
	if (ar.IsStoring())  //保存 
	{
		ar << (GLenum)mShadeModel;
	}
	else //读取 
	{
		GLenum t;
		ar >> t;
		mShadeModel = (EShadeModel)t;
	}
}

//应用，需要在派生类中重写实现多态 
void CGShadeModel::apply(int index, const CG3DCamera* camera, CG3DRenderContext* ctx) const
{
	glShadeModel((GLenum)mShadeModel);
}
