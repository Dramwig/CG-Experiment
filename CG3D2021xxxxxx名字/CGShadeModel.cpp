#include "pch.h" 
#include "CGShadeModel.h" 
#include "CG3DCamera.h" 
#include "CG3DRenderContext.h" 

IMPLEMENT_SERIAL(CGShadeModel, CGRenderState, 1) //1���Կ��������ݰ汾�ţ����ڼ����������������ݳ�Ա��

CGShadeModel::CGShadeModel(EShadeModel shademodel/* = EShadeModel::SM_SMOOTH*/)
	:CGRenderState(CString("CGShadeModel"))
	, mShadeModel(shademodel)
{
}

//���л� 
void CGShadeModel::Serialize(CArchive& ar)
{
	CGRenderState::Serialize(ar); //�ȵ��û�������л������������л��Լ��ĳ�Ա��������Ҫ�� 
	if (ar.IsStoring())  //���� 
	{
		ar << (GLenum)mShadeModel;
	}
	else //��ȡ 
	{
		GLenum t;
		ar >> t;
		mShadeModel = (EShadeModel)t;
	}
}

//Ӧ�ã���Ҫ������������дʵ�ֶ�̬ 
void CGShadeModel::apply(int index, const CG3DCamera* camera, CG3DRenderContext* ctx) const
{
	glShadeModel((GLenum)mShadeModel);
}
