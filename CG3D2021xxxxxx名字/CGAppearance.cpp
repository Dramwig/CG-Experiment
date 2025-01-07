#include "pch.h" 
#include "CGAppearance.h" 
#include "CG3DCamera.h" 
#include "CG3DRenderContext.h" 

IMPLEMENT_SERIAL(CGAppearance, CGRenderState, 1) //1可以看作是数据版本号，用于兼容升级（增加数据成员）

CGAppearance::CGAppearance()
	:CGRenderState(CString("CGAppearance"))
{
}

//序列化 
void CGAppearance::Serialize(CArchive& ar)
{
	CGRenderState::Serialize(ar); //先调用基类的序列化函数，再序列化自己的成员（根据需要） 
	mMaterial.Serialize(ar);
	if (ar.IsStoring())  //保存 
	{
	}
	else //读取 
	{
	}
}
//应用，需要在派生类中重写实现多态 
void CGAppearance::apply(int index, const CG3DCamera* camera, CG3DRenderContext* ctx) const
{
	mMaterial.apply(0, camera, ctx);
}
