#include "pch.h" 
#include "CGPolygonMode.h"
#include "CG3DCamera.h" 
#include "CG3DRenderContext.h" 
 
IMPLEMENT_SERIAL(CGPolygonMode, CGRenderState, 1) //1可以看作是数据版本号，用于兼容升级（增加数据成员） 
 
CGPolygonMode::CGPolygonMode(EPolygonMode frontface/* = EPolygonMode::PM_FILL*/, EPolygonMode 
backface/* = EPolygonMode::PM_FILL*/) 
 :CGRenderState(CString("CGShadeModel")) 
 , mFrontFace(frontface), mBackFace(backface) 
{ 
} 
 
//序列化 
void CGPolygonMode::Serialize(CArchive& ar) 
{ 
 CGRenderState::Serialize(ar); //先调用基类的序列化函数，再序列化自己的成员（根据需要） 
 if (ar.IsStoring())  //保存 
 { 
  ar << (GLenum)mFrontFace << (GLenum)mBackFace; 
 } 
 else //读取 
 { 
  GLenum x, y; 
  ar >> x >> y; 
  mFrontFace = (EPolygonMode)x; 
  mBackFace = (EPolygonMode)y; 
 } 
} 
 
//应用，需要在派生类中重写实现多态 
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
