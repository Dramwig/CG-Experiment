#include "pch.h" 
#include "CGRenderState.h" 

IMPLEMENT_SERIAL(CGRenderState, CGObject, 1) //1可以看作是数据版本号，用于兼容升级（增加数据成员） 

CGRenderState::CGRenderState()
	:CGObject(CString("CGRenderState"))
{
}

CGRenderState::CGRenderState(const CString& name)
	: CGObject(CString(name))
{
}

//序列化 
void CGRenderState::Serialize(CArchive& ar)
{
	CGObject::Serialize(ar); //先调用基类的序列化函数，再序列化自己的成员（根据需要） 
	if (ar.IsStoring())  //保存 
	{
	}
	else //读取 
	{
	}
}

//应用，需要在派生类中重写实现多态 
void CGRenderState::apply(int index, const CG3DCamera* camera, CG3DRenderContext* ctx) const
{

}
