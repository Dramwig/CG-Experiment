#include "pch.h" 
#include "CGLightModel.h" 
#include "CG3DCamera.h" 
#include "CG3DRenderContext.h" 

IMPLEMENT_SERIAL(CGLightModel, CGRenderState, 1) //1���Կ��������ݰ汾�ţ����ڼ����������������ݳ�Ա��

CGLightModel::CGLightModel()
	:CGRenderState(CString("CGRenderState"))
	, mAmbientColor(0.2f, 0.2f, 0.2f, 1.0f), mLocalViewer(false), mTwoSide(false)
{
}
//���л� 
void CGLightModel::Serialize(CArchive& ar)
{
	CGRenderState::Serialize(ar); //�ȵ��û�������л������������л��Լ��ĳ�Ա��������Ҫ�� 
	if (ar.IsStoring())  //���棬���в��� 
	{
	}
	else //��ȡ 
	{
	}
}

//Ӧ�ã���Ҫ������������дʵ�ֶ�̬ 
void CGLightModel::apply(int index, const CG3DCamera* camera, CG3DRenderContext* ctx) const
{
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, mLocalViewer ? 1.0f : 0.0f);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, mAmbientColor.ptr());
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, mTwoSide ? 1.0f : 0.0f);
}
