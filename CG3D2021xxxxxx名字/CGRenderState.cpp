#include "pch.h" 
#include "CGRenderState.h" 

IMPLEMENT_SERIAL(CGRenderState, CGObject, 1) //1���Կ��������ݰ汾�ţ����ڼ����������������ݳ�Ա�� 

CGRenderState::CGRenderState()
	:CGObject(CString("CGRenderState"))
{
}

CGRenderState::CGRenderState(const CString& name)
	: CGObject(CString(name))
{
}

//���л� 
void CGRenderState::Serialize(CArchive& ar)
{
	CGObject::Serialize(ar); //�ȵ��û�������л������������л��Լ��ĳ�Ա��������Ҫ�� 
	if (ar.IsStoring())  //���� 
	{
	}
	else //��ȡ 
	{
	}
}

//Ӧ�ã���Ҫ������������дʵ�ֶ�̬ 
void CGRenderState::apply(int index, const CG3DCamera* camera, CG3DRenderContext* ctx) const
{

}
