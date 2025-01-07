#ifndef _CGBase_H_INCLUDED
#define _CGBase_H_INCLUDED
// �������翼��ͨ���ԣ��ɶ���һЩ���ͱ���
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
// Բ���ʡ����뻡�ȵ��໥ת��
const double dPi = 3.141592653589793238462643383279;
const double dDEG_TO_RAD = dPi / 180.0;
const double dRAD_TO_DEG = 180.0 / dPi;
const float fPi = (float)3.141592653589793238462643;
const float fDEG_TO_RAD = float(dPi / 180.0);
const float fRAD_TO_DEG = float(180.0 / dPi);
// ����ת��
class Radian
{
public:
	Radian(double val) : mValue(val) {}
	double value() { return mValue; }
	double degree() { return (double)(mValue * dRAD_TO_DEG); }
private:
	double mValue;
};
// ��ת����
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
