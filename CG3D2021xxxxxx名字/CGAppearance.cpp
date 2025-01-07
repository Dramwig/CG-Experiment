#include "pch.h" 
#include "CGAppearance.h" 
#include "CG3DCamera.h" 
#include "CG3DRenderContext.h" 

IMPLEMENT_SERIAL(CGAppearance, CGRenderState, 1) //1���Կ��������ݰ汾�ţ����ڼ����������������ݳ�Ա��

CGAppearance::CGAppearance()
	:CGRenderState(CString("CGAppearance"))
{
}

//���л� 
void CGAppearance::Serialize(CArchive& ar)
{
	CGRenderState::Serialize(ar); //�ȵ��û�������л������������л��Լ��ĳ�Ա��������Ҫ�� 
	mMaterial.Serialize(ar);
	if (ar.IsStoring())  //���� 
	{
	}
	else //��ȡ 
	{
	}
}
//Ӧ�ã���Ҫ������������дʵ�ֶ�̬ 
void CGAppearance::apply(int index, const CG3DCamera* camera, CG3DRenderContext* ctx) const
{
	mMaterial.apply(0, camera, ctx);
}
