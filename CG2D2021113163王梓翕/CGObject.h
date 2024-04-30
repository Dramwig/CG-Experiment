#ifndef _CGObject_H_INCLUDED
#define _CGObject_H_INCLUDED
#include <afx.h>
#include "CGBase.h"
/// CGObject
/// 使用MFC 的CObject作为基类，用于支持运行时类信息、动态创建、串行化、对象诊断输出
/// 基本功能：不支持运行时类信息或序列化，但包括诊断内存管理。
/// 基本功能加上对运行时类信息的支持。（DECLARE_DYNAMIC）（IMPLEMENT_DYNAMIC放在类的实现文件 (.CPP) 中）
/// 基本功能加上对运行时类信息和动态创建的支持。（DECLARE_DYNCREATE）（IMPLEMENT_DYNCREATE 放在类的实现文件(.CPP) 中）
/// 基本功能加上对运行时类信息、动态创建和序列化的支持。（DECLARE_SERIAL）（IMPLEMENT_SERIAL放在类的实现文件(.CPP) 中）
/// 
class CGObject : public CObject
{
	DECLARE_SERIAL(CGObject) //对运行时类信息、动态创建和序列化的支持（IMPLEMENT_SERIAL放在类的实现文件(.CPP) 中）
public:
	CGObject();
	CGObject(const CString& name);
	CGObject(const CGObject& other);
	virtual ~CGObject() = default; //虚析构函数
	//序列化（派生类应重写该虚函数）
	virtual void Serialize(CArchive& ar) override;
	const CString& Name() const { return mName; }
	CString& Name() { return mName; }
protected:
	CString mName; //对象名称，默认由“类名+序号”构成，用于显示
	static long sID; //对象ID，仅用于辅助对象命名，不能唯一标识
};
#endif //_CGObject_H_INCLUDED
