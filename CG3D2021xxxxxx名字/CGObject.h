#ifndef _CGObject_H_INCLUDED
#define _CGObject_H_INCLUDED
#include <afx.h>
#include "CGBase.h"
/// CGObject
/// ʹ��MFC ��CObject��Ϊ���࣬����֧������ʱ����Ϣ����̬���������л�������������
/// �������ܣ���֧������ʱ����Ϣ�����л�������������ڴ����
/// �������ܼ��϶�����ʱ����Ϣ��֧�֡���DECLARE_DYNAMIC����IMPLEMENT_DYNAMIC�������ʵ���ļ� (.CPP) �У�
/// �������ܼ��϶�����ʱ����Ϣ�Ͷ�̬������֧�֡���DECLARE_DYNCREATE����IMPLEMENT_DYNCREATE �������ʵ���ļ�(.CPP) �У�
/// �������ܼ��϶�����ʱ����Ϣ����̬���������л���֧�֡���DECLARE_SERIAL����IMPLEMENT_SERIAL�������ʵ���ļ�(.CPP) �У�
/// 
class CGObject : public CObject
{
	DECLARE_SERIAL(CGObject) //������ʱ����Ϣ����̬���������л���֧�֣�IMPLEMENT_SERIAL�������ʵ���ļ�(.CPP) �У�
public:
	CGObject();
	CGObject(const CString& name);
	CGObject(const CGObject& other);
	virtual ~CGObject() = default; //����������
	//���л���������Ӧ��д���麯����
	virtual void Serialize(CArchive& ar) override;
	const CString& Name() const { return mName; }
	CString& Name() { return mName; }
protected:
	CString mName; //�������ƣ�Ĭ���ɡ�����+��š����ɣ�������ʾ
	static long sID; //����ID�������ڸ�����������������Ψһ��ʶ
};
#endif //_CGObject_H_INCLUDED
