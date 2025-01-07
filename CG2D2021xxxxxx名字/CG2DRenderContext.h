#ifndef _CG2DRenderContext_H_INCLUDED
#define _CG2DRenderContext_H_INCLUDED

#include <vector>

#define PI acos(-1)

enum class LineAlgorithm //线画图形绘制算法
{
	CDC = 0, //使用CDC类的绘制函数
	MidPoint = 1, //使用自定义的中点绘制算法
	Bresenham = 2, //使用自定义的Bresenham绘制算法
	DDA = 3, //使用自定义的DDA绘制算法（用于直线段）
	//PolygonApproximation = 3//使用自定义的多边形逼近算法（用于圆轮廓）
};
enum class FillAlgorithm //区域图形绘制算法
{
	CDC = 0, //使用CDC类的绘制函数
	SeedBound4 = 1, //边界表示的点阵区域四连通种子填充算法
	SeedFlood4 = 2, //内点表示的点阵区域四连通种子填充算法
	SeedBound8 = 3, //边界表示的点阵区域八连通种子填充算法
	SeedFlood8 = 4, //内点表示的点阵区域八连通种子填充算法
	AETFill = 1, //多边形扫描线填充算法（有序边表算法）
	EdgeBase = 2, //边缘填充
	EdgeFence = 3, //栅栏填充
	EdgeFlag = 4, //边标记填充
	SeedScanline = 5, //多边形扫描线种子填充算法
};

class CG2DCamera;

//使用Windows图形绘制接口GDI进行绘制的绘制环境（相当于画布、绘制工具、绘制算法）
class CG2DRenderContext
{
public:
	CG2DRenderContext();
	virtual ~CG2DRenderContext();
	virtual void EraseBkgnd() = 0; //使用背景色清除客户区背景
	virtual HWND GetHWnd() const = 0; //获取当前客户区的窗口句柄，可用于获取客户区DC
	HDC GetMemHDC() const { return mMemHDC; } //图形对象绘制时调用，返回非空则可绘制
	void SetBkgndColor(COLORREF color) { mBkgndColor = color; } //设置背景色
	COLORREF GetBkgndColor() const { return mBkgndColor; }

	//绘制的开始与结束（支持双缓冲用），全部客户区绘制。
	virtual void Ready(bool erasebkgnd = true); //每一次批量绘制前调用
	virtual void Finish();//每一次批量绘制后调用（显示）

	//自定义绘制算法相关函数（根据需要补充）
	void putpixel(int x, int y, unsigned long color);

	//直线段绘制算法（起点坐标x、y，终点坐标x、y，颜色）
	void DDALine(int xStart, int yStart, int xEnd, int yEnd, unsigned long color);
	void MidPointLine(int xStart, int yStart, int xEnd, int yEnd, unsigned long color);
	void BresenhamLine(int xStart, int yStart, int xEnd, int yEnd, unsigned long color);

	//圆绘制算法（中心坐标x、y，半径，颜色）
	void DrawCirclePoints(int xc, int yc, int x, int y, unsigned long color, float startAngle, float sweepAngle);
	void MidPointCircle(int xc, int yc, int R, unsigned long color);
	//圆弧绘制算法（中心坐标x、y，半径，颜色，相对于X轴的开始角度弧度，相对于开始角度的逆时针扫描角度弧度）
	void MidPointCircleArc(int xc, int yc, int R, unsigned long color, float startAngle, float sweepAngle);

	//有效边表多边形扫描线填充算法（多边形顶点数组、填充颜色）
	void ScanLinePolygonFill(const std::vector<CPoint>& pnts, unsigned long fillColor);
	//边界表示的种子填充算法（种子点坐标x、y，边界颜色，填充颜色）
	void BoundFill4(int xSeed, int ySeed, unsigned long boundColor, unsigned long fillColor);
	//内点表示的种子填充算法（种子点坐标x、y，区域原颜色，区域新颜色）
	void FloodFill4(int xSeed, int ySeed, unsigned long oldColor, unsigned long newColor);

protected:
	bool mReady = false; //调用Ready成功则为true
	HDC mMemHDC = nullptr; //支持双缓存，用于实际绘图
	HBITMAP mMemHBMP = nullptr; //支持双缓存
	COLORREF mBkgndColor = RGB(255, 255, 255); //客户区背景颜色

public:
	//绘制客户区的宽度、高度（必须在派生类中实现）
	virtual void GetClientWidthHeight(int& w, int& h) { }
	//绘制算法选择
	virtual int LineAlgorithm() const { return 0; }
	virtual int CircleAlgorithm() const { return 0; }
	virtual int FillAlgorithm() const { return 0; }
	virtual int SeedAlgorithm() const { return 0; }
	//使用相机，在指定视口中绘制
	virtual void Ready(CG2DCamera*); //每一次批量绘制前调用。生成填充视口背景，需要重新绘制图形。
	virtual void Finish(CG2DCamera*); //每一次批量绘制后调用（显示）
protected:
	CG2DCamera* mCamera = nullptr; //当前使用的相机，获取视口位置、长宽。

};
#endif //_CG2DRenderContext_H_INCLUDED
