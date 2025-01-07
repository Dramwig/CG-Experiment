#include "pch.h" 
#include "CGPolygonMode.h"
#include "CG3DCamera.h" 
#include "CG3DRenderContext.h" 
 
IMPLEMENT_SERIAL(CGPolygonMode, CGRenderState, 1) //1���Կ��������ݰ汾�ţ����ڼ����������������ݳ�Ա�� 
 
CGPolygonMode::CGPolygonMode(EPolygonMode frontface/* = EPolygonMode::PM_FILL*/, EPolygonMode 
backface/* = EPolygonMode::PM_FILL*/) 
 :CGRenderState(CString("CGShadeModel")) 
 , mFrontFace(frontface), mBackFace(backface) 
{ 
} 
 
//���л� 
void CGPolygonMode::Serialize(CArchive& ar) 
{ 
 CGRenderState::Serialize(ar); //�ȵ��û�������л������������л��Լ��ĳ�Ա��������Ҫ�� 
 if (ar.IsStoring())  //���� 
 { 
  ar << (GLenum)mFrontFace << (GLenum)mBackFace; 
 } 
 else //��ȡ 
 { 
  GLenum x, y; 
  ar >> x >> y; 
  mFrontFace = (EPolygonMode)x; 
  mBackFace = (EPolygonMode)y; 
 } 
} 
 
//Ӧ�ã���Ҫ������������дʵ�ֶ�̬ 
void CGPolygonMode::apply(int index, const CG3DCamera* camera, CG3DRenderContext* ctx) const 
{ 
 if (mFrontFace == mBackFace) 
 { 
  glPolygonMode(GL_FRONT_AND_BACK, (GLenum)mFrontFace); 
 }
 else
 {
	 glPolygonMode(GL_FRONT, (GLenum)mFrontFace);
	 glPolygonMode(GL_BACK, (GLenum)mBackFace);
 }
}
