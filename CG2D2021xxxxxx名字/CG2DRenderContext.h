#ifndef _CG2DRenderContext_H_INCLUDED
#define _CG2DRenderContext_H_INCLUDED

#include <vector>

#define PI acos(-1)

enum class LineAlgorithm //�߻�ͼ�λ����㷨
{
	CDC = 0, //ʹ��CDC��Ļ��ƺ���
	MidPoint = 1, //ʹ���Զ�����е�����㷨
	Bresenham = 2, //ʹ���Զ����Bresenham�����㷨
	DDA = 3, //ʹ���Զ����DDA�����㷨������ֱ�߶Σ�
	//PolygonApproximation = 3//ʹ���Զ���Ķ���αƽ��㷨������Բ������
};
enum class FillAlgorithm //����ͼ�λ����㷨
{
	CDC = 0, //ʹ��CDC��Ļ��ƺ���
	SeedBound4 = 1, //�߽��ʾ�ĵ�����������ͨ��������㷨
	SeedFlood4 = 2, //�ڵ��ʾ�ĵ�����������ͨ��������㷨
	SeedBound8 = 3, //�߽��ʾ�ĵ����������ͨ��������㷨
	SeedFlood8 = 4, //�ڵ��ʾ�ĵ����������ͨ��������㷨
	AETFill = 1, //�����ɨ��������㷨������߱��㷨��
	EdgeBase = 2, //��Ե���
	EdgeFence = 3, //դ�����
	EdgeFlag = 4, //�߱�����
	SeedScanline = 5, //�����ɨ������������㷨
};

class CG2DCamera;

//ʹ��Windowsͼ�λ��ƽӿ�GDI���л��ƵĻ��ƻ������൱�ڻ��������ƹ��ߡ������㷨��
class CG2DRenderContext
{
public:
	CG2DRenderContext();
	virtual ~CG2DRenderContext();
	virtual void EraseBkgnd() = 0; //ʹ�ñ���ɫ����ͻ�������
	virtual HWND GetHWnd() const = 0; //��ȡ��ǰ�ͻ����Ĵ��ھ���������ڻ�ȡ�ͻ���DC
	HDC GetMemHDC() const { return mMemHDC; } //ͼ�ζ������ʱ���ã����طǿ���ɻ���
	void SetBkgndColor(COLORREF color) { mBkgndColor = color; } //���ñ���ɫ
	COLORREF GetBkgndColor() const { return mBkgndColor; }

	//���ƵĿ�ʼ�������֧��˫�����ã���ȫ���ͻ������ơ�
	virtual void Ready(bool erasebkgnd = true); //ÿһ����������ǰ����
	virtual void Finish();//ÿһ���������ƺ���ã���ʾ��

	//�Զ�������㷨��غ�����������Ҫ���䣩
	void putpixel(int x, int y, unsigned long color);

	//ֱ�߶λ����㷨���������x��y���յ�����x��y����ɫ��
	void DDALine(int xStart, int yStart, int xEnd, int yEnd, unsigned long color);
	void MidPointLine(int xStart, int yStart, int xEnd, int yEnd, unsigned long color);
	void BresenhamLine(int xStart, int yStart, int xEnd, int yEnd, unsigned long color);

	//Բ�����㷨����������x��y���뾶����ɫ��
	void DrawCirclePoints(int xc, int yc, int x, int y, unsigned long color, float startAngle, float sweepAngle);
	void MidPointCircle(int xc, int yc, int R, unsigned long color);
	//Բ�������㷨����������x��y���뾶����ɫ�������X��Ŀ�ʼ�ǶȻ��ȣ�����ڿ�ʼ�Ƕȵ���ʱ��ɨ��ǶȻ��ȣ�
	void MidPointCircleArc(int xc, int yc, int R, unsigned long color, float startAngle, float sweepAngle);

	//��Ч�߱�����ɨ��������㷨������ζ������顢�����ɫ��
	void ScanLinePolygonFill(const std::vector<CPoint>& pnts, unsigned long fillColor);
	//�߽��ʾ����������㷨�����ӵ�����x��y���߽���ɫ�������ɫ��
	void BoundFill4(int xSeed, int ySeed, unsigned long boundColor, unsigned long fillColor);
	//�ڵ��ʾ����������㷨�����ӵ�����x��y������ԭ��ɫ����������ɫ��
	void FloodFill4(int xSeed, int ySeed, unsigned long oldColor, unsigned long newColor);

protected:
	bool mReady = false; //����Ready�ɹ���Ϊtrue
	HDC mMemHDC = nullptr; //֧��˫���棬����ʵ�ʻ�ͼ
	HBITMAP mMemHBMP = nullptr; //֧��˫����
	COLORREF mBkgndColor = RGB(255, 255, 255); //�ͻ���������ɫ

public:
	//���ƿͻ����Ŀ�ȡ��߶ȣ���������������ʵ�֣�
	virtual void GetClientWidthHeight(int& w, int& h) { }
	//�����㷨ѡ��
	virtual int LineAlgorithm() const { return 0; }
	virtual int CircleAlgorithm() const { return 0; }
	virtual int FillAlgorithm() const { return 0; }
	virtual int SeedAlgorithm() const { return 0; }
	//ʹ���������ָ���ӿ��л���
	virtual void Ready(CG2DCamera*); //ÿһ����������ǰ���á���������ӿڱ�������Ҫ���»���ͼ�Ρ�
	virtual void Finish(CG2DCamera*); //ÿһ���������ƺ���ã���ʾ��
protected:
	CG2DCamera* mCamera = nullptr; //��ǰʹ�õ��������ȡ�ӿ�λ�á�����

};
#endif //_CG2DRenderContext_H_INCLUDED
