// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H 
#define PCH_H 
// 添加要在此处预编译的标头 
#include "framework.h" 
#include <gl/gl.h> 
#include <gl/glu.h> 
//#include "glad.h" 
//#include "glfw3.h" 
#include "glut.h" 

#pragma comment(lib, "opengl32.lib")  
#pragma comment(lib, "glu32.lib")  

// 32位编译 
#ifdef _M_IX86 
#pragma comment(lib, "glut32.lib")  
#endif // _M_IX86 
// 64位编译 
#ifdef _M_X64 
#pragma comment(lib, "glut64.lib")  
#endif // _M_X64 

#endif //PCH_H 
