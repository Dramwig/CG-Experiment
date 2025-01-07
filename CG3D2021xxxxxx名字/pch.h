// pch.h: ����Ԥ�����ͷ�ļ���
// �·��г����ļ�������һ�Σ�����˽������ɵ��������ܡ�
// �⻹��Ӱ�� IntelliSense ���ܣ�����������ɺ�������������ܡ�
// ���ǣ�����˴��г����ļ��е��κ�һ��������֮���и��£�����ȫ�����������±��롣
// �����ڴ˴����ҪƵ�����µ��ļ����⽫ʹ������������Ч��

#ifndef PCH_H 
#define PCH_H 
// ���Ҫ�ڴ˴�Ԥ����ı�ͷ 
#include "framework.h" 
#include <gl/gl.h> 
#include <gl/glu.h> 
//#include "glad.h" 
//#include "glfw3.h" 
#include "glut.h" 

#pragma comment(lib, "opengl32.lib")  
#pragma comment(lib, "glu32.lib")  

// 32λ���� 
#ifdef _M_IX86 
#pragma comment(lib, "glut32.lib")  
#endif // _M_IX86 
// 64λ���� 
#ifdef _M_X64 
#pragma comment(lib, "glut64.lib")  
#endif // _M_X64 

#endif //PCH_H 
