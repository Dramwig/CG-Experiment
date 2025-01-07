#ifndef _CGBase_H_INCLUDED
#define _CGBase_H_INCLUDED
// 程序中如考虑通用性，可定义一些类型别名
typedef signed char Int8;
typedef short Int16;
typedef int Int32;
typedef long long Int64;
typedef unsigned char UInt8;
typedef unsigned short UInt16;
typedef unsigned int UInt32;
typedef unsigned long long UInt64;
typedef float Real32;
typedef double Real64;
// 圆周率、度与弧度的相互转换
const double dPi = 3.141592653589793238462643383279;
const double dDEG_TO_RAD = dPi / 180.0;
const double dRAD_TO_DEG = 180.0 / dPi;
const float fPi = (float)3.141592653589793238462643;
const float fDEG_TO_RAD = float(dPi / 180.0);
const float fRAD_TO_DEG = float(180.0 / dPi);
// 弧度转度
class Radian
{
public:
	Radian(double val) : mValue(val) {}
	double value() { return mValue; }
	double degree() { return (double)(mValue * dRAD_TO_DEG); }
private:
	double mValue;
};
// 度转弧度
class Degree
{
public:
	Degree(double val) : mValue(val) {}
	double value() { return mValue; }
	double radian() { return (double)(mValue * dDEG_TO_RAD); }
private:
	double mValue;
};
#endif //_CGBase_H_INCLUDED
