#include "pch.h"
#include "CG2DRenderContext.h"
#include <utility>
#include <cassert>
#include <algorithm>
#include <cmath>
#include <vector>
#include <stack>

#define PI acos(-1)

CG2DRenderContext::CG2DRenderContext()
{
}
CG2DRenderContext::~CG2DRenderContext()
{
	if (mMemHBMP != nullptr)
	{
		::DeleteObject(mMemHBMP);
		mMemHBMP = nullptr;
	}
	if (mMemHDC != nullptr)
	{
		::DeleteDC(mMemHDC);
		mMemHDC = nullptr;
	}
}
//绘制的开始与结束（支持双缓冲用）
void CG2DRenderContext::Ready(bool erasebkgnd) //每一次批量绘制前调用
{
	if (erasebkgnd)
	{
		if (mMemHBMP != nullptr)
		{
			::DeleteObject(mMemHBMP);
			mMemHBMP = nullptr;
		}
		if (mMemHDC != nullptr)
		{
			::DeleteDC(mMemHDC);
			mMemHDC = nullptr;

		}
	}
}

void CG2DRenderContext::Finish()//每一次批量绘制后调用（显示）
{
	assert(mMemHDC != nullptr);
}

//直线段绘制算法（起点坐标x、y，终点坐标x、y，颜色）
void CG2DRenderContext::DDALine(int x0, int y0, int x1, int y1, unsigned long color)
{
	// 计算delta_x, delta_y, 确定steps，并计算dx, dy
	int delta_x = x1 - x0, delta_y = y1 - y0,
		steps = max(abs(delta_x), abs(delta_y));
	double x = x0, y = y0,
		dx = (double)delta_x / steps, dy = (double)delta_y / steps;
	for (int i = 1; i <= steps + 1; i++)
	{
		putpixel((int)(x + 0.5), (int)(y + 0.5), color); // 四舍五入生成像素点
		x += dx, y += dy;
	}
}

void CG2DRenderContext::MidPointLine(int x0, int y0, int x1, int y1, unsigned long color)
{
	if (x0 > x1) // 保证x0 <= x1
		std::swap(x0, x1), std::swap(y0, y1);
	int a = y0 - y1, b = x1 - x0,   // 直线L的参数（c因为没有用到不用计算）
		d,                          // 决策变量d
		dd_L, dd_G,                 // 决策变量d的增量(L代表小于0的情况，G代表大于0的情况)
		x = x0, y = y0,             // 初始P坐标
		dPx_L, dPy_L, dPx_G, dPy_G; // P坐标的增量(L代表小于0的情况，G代表大于0的情况)
	// 根据k值分情况生成决策变量和增量
	if (-b <= a && a <= 0) // k ∈ [0, 1]
	{
		d = 2 * a + b;                            // d0 = 2a + b
		dPx_L = 1, dPy_L = 1, dd_L = 2 * (a + b); // d < 0情况
		dPx_G = 1, dPy_G = 0, dd_G = 2 * a;       // d >= 0 情况
	}
	else if (a < -b) // k ∈ (1, +∞)
	{
		d = a + 2 * b;                            // d0 = a + 2b
		dPx_L = 0, dPy_L = 1, dd_L = 2 * b;       // d < 0情况
		dPx_G = 1, dPy_G = 1, dd_G = 2 * (a + b); // d >= 0 情况
	}
	else if (0 < a && a <= b) // k ∈ [-1, 0)
	{
		d = 2 * a - b;                             // d0 = 2a - b
		dPx_L = 1, dPy_L = 0, dd_L = 2 * a;        // d < 0情况
		dPx_G = 1, dPy_G = -1, dd_G = 2 * (a - b); // d >= 0 情况
	}
	else // k ∈ (-∞, -1)
	{
		d = a - 2 * b;                             // d0 = a - 2b
		dPx_L = 1, dPy_L = -1, dd_L = 2 * (a - b); // d < 0情况
		dPx_G = 0, dPy_G = -1, dd_G = -2 * b;      // d >= 0 情况
	}
	// 迭代生成直线
	while (x != x1 || y != y1)
	{
		putpixel(x, y, color);
		if (d < 0)
			x += dPx_L, y += dPy_L, d += dd_L;
		else
			x += dPx_G, y += dPy_G, d += dd_G;
	}
	putpixel(x, y, color);
}

//Bresenham直线段绘制算法（起点坐标x、y，终点坐标x、y，颜色）
void CG2DRenderContext::BresenhamLine(int x0, int y0, int x1, int y1, unsigned long color)
{
	if (x0 > x1) // 保证x0 <= x1
		std::swap(x0, x1), std::swap(y0, y1);
	int Delta_x = x1 - x0, Delta_y = y1 - y0,
		d,                          // 决策变量d
		dd_L, dd_G,                 // 决策变量d的增量(L代表小于0的情况，G代表大于0的情况)
		x = x0, y = y0,             // 初始P坐标
		dPx_L, dPy_L, dPx_G, dPy_G; // P坐标的增量(L代表小于0的情况，G代表大于0的情况)
	// 根据k值分情况生成决策变量和增量
	if (0 <= Delta_y && Delta_y <= Delta_x) // k ∈ [0, 1]
	{
		d = 2 * Delta_y - Delta_x;                            // d0 = 2Δy - Δx
		dPx_L = 1, dPy_L = 0, dd_L = 2 * Delta_y;             // d < 0情况
		dPx_G = 1, dPy_G = 1, dd_G = 2 * (Delta_y - Delta_x); // d >= 0 情况
	}
	else if (Delta_x < Delta_y) // k ∈ (1, +∞)
	{
		d = 2 * Delta_x - Delta_y;                            // d0 = 2Δx - Δy
		dPx_L = 0, dPy_L = 1, dd_L = 2 * Delta_x;             // d < 0情况
		dPx_G = 1, dPy_G = 1, dd_G = 2 * (Delta_x - Delta_y); // d >= 0 情况
	}
	else if (-Delta_x <= Delta_y && Delta_y < 0) // k ∈ [-1, 0)
	{
		d = -2 * Delta_y - Delta_x;                             // d0 = -2Δy - Δx
		dPx_L = 1, dPy_L = 0, dd_L = -2 * Delta_y;              // d < 0情况
		dPx_G = 1, dPy_G = -1, dd_G = -2 * (Delta_y + Delta_x); // d >= 0 情况
	}
	else // k ∈ (-∞, -1)
	{
		d = 2 * Delta_x + Delta_y;                             // d0 = 2Δx + Δy
		dPx_L = 0, dPy_L = -1, dd_L = 2 * Delta_x;             // d < 0情况
		dPx_G = 1, dPy_G = -1, dd_G = 2 * (Delta_x + Delta_y); // d >= 0 情况
	}
	// 迭代生成直线
	while (x != x1 || y != y1)
	{
		putpixel(x, y, color);
		if (d < 0)
			x += dPx_L, y += dPy_L, d += dd_L;
		else
			x += dPx_G, y += dPy_G, d += dd_G;
	}
	putpixel(x, y, color);
}

void CG2DRenderContext::putpixel(int x, int y, unsigned long color)
{
	if (mMemHDC == nullptr)
		return;
	HDC hDC = mMemHDC;
	::SetPixel(hDC, x, y, color);
}

void CG2DRenderContext::DrawCirclePoints(int xc, int yc, int x, int y, unsigned long color, float startAngle = -PI, float sweepAngle = 2 * PI)
{
	if (sweepAngle >= 2 * PI) {
		putpixel(xc + x, yc + y, color);
		putpixel(xc - x, yc + y, color);
		putpixel(xc + x, yc - y, color);
		putpixel(xc - x, yc - y, color);
		putpixel(xc + y, yc + x, color);
		putpixel(xc + y, yc - x, color);
		putpixel(xc - y, yc + x, color);
		putpixel(xc - y, yc - x, color);
	}
	else {
		double angle = atan2(y, x);
		startAngle = (float)fmod(startAngle, 2.0 * PI);
		if (startAngle >= PI)startAngle -= float(2.0 * PI);
		if(startAngle < -PI)startAngle += float(2.0 * PI);
		float endAngle = startAngle + sweepAngle;
		if (endAngle >= PI)endAngle -= float(2.0 * PI);

		if((startAngle < endAngle && angle >= startAngle && angle <= endAngle) || (startAngle > endAngle && (angle >= startAngle || angle <= endAngle)))
		{
			putpixel(xc + x, yc + y, color);
		}
		angle = atan2(y, -x);
		if((startAngle < endAngle && angle >= startAngle && angle <= endAngle) || (startAngle > endAngle && (angle >= startAngle || angle <= endAngle)))
		{
			putpixel(xc - x, yc + y, color);
		}
		angle = atan2(-y, x);
		if((startAngle < endAngle && angle >= startAngle && angle <= endAngle) || (startAngle > endAngle && (angle >= startAngle || angle <= endAngle)))
		{
			putpixel(xc + x, yc - y, color);
		}
		angle = atan2(-y, -x);
		if((startAngle < endAngle && angle >= startAngle && angle <= endAngle) || (startAngle > endAngle && (angle >= startAngle || angle <= endAngle)))
		{
			putpixel(xc - x, yc - y, color);
		}
		angle = atan2(x, y);
		if((startAngle < endAngle && angle >= startAngle && angle <= endAngle) || (startAngle > endAngle && (angle >= startAngle || angle <= endAngle)))
		{
			putpixel(xc + y, yc + x, color);
		}
		angle = atan2(-x, y);
		if((startAngle < endAngle && angle >= startAngle && angle <= endAngle) || (startAngle > endAngle && (angle >= startAngle || angle <= endAngle)))
		{
			putpixel(xc + y, yc - x, color);
		}
		angle = atan2(x, -y);
		if((startAngle < endAngle && angle >= startAngle && angle <= endAngle) || (startAngle > endAngle && (angle >= startAngle || angle <= endAngle)))
		{
			putpixel(xc - y, yc + x, color);
		}
		angle = atan2(-x, -y);
		if((startAngle < endAngle && angle >= startAngle && angle <= endAngle) || (startAngle > endAngle && (angle >= startAngle || angle <= endAngle)))
		{
			putpixel(xc - y, yc - x, color);
		}
	}
}

//圆绘制算法（中心坐标x、y，半径，颜色）
void CG2DRenderContext::MidPointCircle(int xc, int yc, int R, unsigned long color)
{
	int x = 0, y = R, // 初始P坐标
		d = 1 - R;    // 决策变量d
	while (x < y)
	{
		DrawCirclePoints(xc, yc, x, y, color);
		if (d < 0)
			d += 2 * x + 3, x++;
		else
			d += 2 * (x - y) + 5, x++, y--;
	}
	DrawCirclePoints(xc, yc, x, y, color);
}

//圆弧绘制算法（中心坐标x、y，半径，颜色，相对于X轴的开始角度弧度，相对于开始角度的逆时针扫描角度弧度）
void CG2DRenderContext::MidPointCircleArc(int xc, int yc, int R, unsigned long color, float startAngle, float sweepAngle)
{
	int x = 0, y = R, // 初始P坐标
		d = 1 - R;    // 决策变量d
	while (x < y)
	{
		DrawCirclePoints(xc, yc, x, y, color, startAngle, sweepAngle);
		if (d < 0)
			d += 2 * x + 3, x++;
		else
			d += 2 * (x - y) + 5, x++, y--;
	}
	DrawCirclePoints(xc, yc, x, y, color, startAngle, sweepAngle);
}

//扫描线种子填充算法（种子点坐标x、y，边界颜色，填充颜色）
void CG2DRenderContext::ScanLinePolygonFill(const std::vector<CPoint>&pnts, unsigned long fillColor)
{
	if (mMemHDC == nullptr)
		return;
	if (pnts.empty())
		return;

	// 查找最小和最大 Y 值以确定扫描线范围
	int minY = pnts[0].y, maxY = pnts[0].y;
	for (const auto& point : pnts) {
		minY = min(minY, point.y);
		maxY = max(maxY, point.y);
	}

	// 活性边表 (AET)
	std::vector<std::vector<CPoint>> edgeTable(maxY - minY + 1);

	// 制作边表
	CPoint prev = pnts.back();
	for (const auto& current : pnts) {
		if (current.y != prev.y) {
			CPoint top = (current.y < prev.y) ? current : prev;
			CPoint bottom = (current.y > prev.y) ? current : prev;
			for (int y = top.y; y < bottom.y; ++y) {
				int x = top.x + (y - top.y) * (bottom.x - top.x) / (bottom.y - top.y);
				edgeTable[y - minY].push_back(CPoint(x, y));
			}
		}
		prev = current;
	}

	// 使用活动边缘表进行填充
	for (int y = minY; y <= maxY; ++y) {
		if (edgeTable[y - minY].empty()) continue;

		// 按 x 坐标对边排序
		std::sort(edgeTable[y - minY].begin(), edgeTable[y - minY].end(), [](const CPoint& a, const CPoint& b) {
			return a.x < b.x;
			});

		// 在两对交叉点之间填充
		for (size_t i = 0; i < edgeTable[y - minY].size(); i += 2) {
			if (i + 1 >= edgeTable[y - minY].size()) break;
			int startX = edgeTable[y - minY][i].x;
			int endX = edgeTable[y - minY][i + 1].x;
			for (int x = startX; x <= endX; x++) {
				putpixel(x, y, fillColor);
			}
		}
	}
}

//边界表示的种子填充算法（种子点坐标x、y，边界颜色，填充颜色）
void CG2DRenderContext::BoundFill4(int xSeed, int ySeed, unsigned long boundColor, unsigned long fillColor)
{
	if (mMemHDC == nullptr)
		return;
	//以下是算法代码，根据算法自行补充
	//::GetPixel(mMemHDC, xSeed, ySeed)可返回种子像素颜色
	//::SetPixel(mMemHDC, xSeed, ySeed, fillColor);可设置种子像素颜色

	// 检查种子像素是否具有边界颜色或填充颜色
	if (::GetPixel(mMemHDC, xSeed, ySeed) == boundColor || ::GetPixel(mMemHDC, xSeed, ySeed) == fillColor)
		return;

	std::stack<std::pair<int, int>> pixelStack;
	pixelStack.push(std::make_pair(xSeed, ySeed));

	while (!pixelStack.empty()) {
		std::pair<int, int> current = pixelStack.top();
		pixelStack.pop();
		int x = current.first;
		int y = current.second;

		// 获取当前像素的颜色
		COLORREF color = ::GetPixel(mMemHDC, x, y);

		// 如果颜色既不是边界颜色也不是填充颜色，则填充像素
		if (color != boundColor && color != fillColor) {
			::SetPixel(mMemHDC, x, y, fillColor);

			// 将4个相邻像素推入堆栈
			pixelStack.push(std::make_pair(x + 1, y));    // 右
			pixelStack.push(std::make_pair(x - 1, y));    // 左
			pixelStack.push(std::make_pair(x, y + 1));    // 上
			pixelStack.push(std::make_pair(x, y - 1));    // 下
		}
	}
}

// 内点表示的种子填充算法（种子点坐标x、y，区域原颜色，区域新颜色）
void CG2DRenderContext::FloodFill4(int xSeed, int ySeed, unsigned long oldColor, unsigned long newColor)
{
	if (mMemHDC == nullptr)
		return;

	// 获取种子点的颜色
	COLORREF seedColor = ::GetPixel(mMemHDC, xSeed, ySeed);

	// 检查种子点是否需要填充
	if (seedColor != oldColor)
		return;

	std::stack<std::pair<int, int>> pixelStack;
	pixelStack.push(std::make_pair(xSeed, ySeed));

	while (!pixelStack.empty()) {
		std::pair<int, int> current = pixelStack.top();
		pixelStack.pop();
		int x = current.first;
		int y = current.second;

		// 获取当前像素的颜色
		COLORREF color = ::GetPixel(mMemHDC, x, y);

		// 如果像素颜色与原颜色相同，则进行填充
		if (color == oldColor) {
			::SetPixel(mMemHDC, x, y, newColor);

			// 推入相邻的四个像素
			pixelStack.push(std::make_pair(x + 1, y));    // 右
			pixelStack.push(std::make_pair(x - 1, y));    // 左
			pixelStack.push(std::make_pair(x, y + 1));    // 上
			pixelStack.push(std::make_pair(x, y - 1));    // 下
		}
	}
}

//使用相机，在指定视口中绘制
void CG2DRenderContext::Ready(CG2DCamera* camera) //每一次批量绘制前调用。生成填充视口背景，需要重新绘制图形。
{
if (mMemHBMP != nullptr)
{
::DeleteObject(mMemHBMP);
mMemHBMP = nullptr;
}
if (mMemHDC != nullptr)
{
	::DeleteDC(mMemHDC);
	mMemHDC = nullptr;
}
mCamera = camera;
}
void CG2DRenderContext::Finish(CG2DCamera* camera) //每一次批量绘制前调用
{
	assert(mMemHDC != nullptr);
	if (mMemHDC == nullptr)
		return;
}
