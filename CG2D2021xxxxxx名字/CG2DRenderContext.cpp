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
//���ƵĿ�ʼ�������֧��˫�����ã�
void CG2DRenderContext::Ready(bool erasebkgnd) //ÿһ����������ǰ����
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

void CG2DRenderContext::Finish()//ÿһ���������ƺ���ã���ʾ��
{
	assert(mMemHDC != nullptr);
}

//ֱ�߶λ����㷨���������x��y���յ�����x��y����ɫ��
void CG2DRenderContext::DDALine(int x0, int y0, int x1, int y1, unsigned long color)
{
	// ����delta_x, delta_y, ȷ��steps��������dx, dy
	int delta_x = x1 - x0, delta_y = y1 - y0,
		steps = max(abs(delta_x), abs(delta_y));
	double x = x0, y = y0,
		dx = (double)delta_x / steps, dy = (double)delta_y / steps;
	for (int i = 1; i <= steps + 1; i++)
	{
		putpixel((int)(x + 0.5), (int)(y + 0.5), color); // ���������������ص�
		x += dx, y += dy;
	}
}

void CG2DRenderContext::MidPointLine(int x0, int y0, int x1, int y1, unsigned long color)
{
	if (x0 > x1) // ��֤x0 <= x1
		std::swap(x0, x1), std::swap(y0, y1);
	int a = y0 - y1, b = x1 - x0,   // ֱ��L�Ĳ�����c��Ϊû���õ����ü��㣩
		d,                          // ���߱���d
		dd_L, dd_G,                 // ���߱���d������(L����С��0�������G�������0�����)
		x = x0, y = y0,             // ��ʼP����
		dPx_L, dPy_L, dPx_G, dPy_G; // P���������(L����С��0�������G�������0�����)
	// ����kֵ��������ɾ��߱���������
	if (-b <= a && a <= 0) // k �� [0, 1]
	{
		d = 2 * a + b;                            // d0 = 2a + b
		dPx_L = 1, dPy_L = 1, dd_L = 2 * (a + b); // d < 0���
		dPx_G = 1, dPy_G = 0, dd_G = 2 * a;       // d >= 0 ���
	}
	else if (a < -b) // k �� (1, +��)
	{
		d = a + 2 * b;                            // d0 = a + 2b
		dPx_L = 0, dPy_L = 1, dd_L = 2 * b;       // d < 0���
		dPx_G = 1, dPy_G = 1, dd_G = 2 * (a + b); // d >= 0 ���
	}
	else if (0 < a && a <= b) // k �� [-1, 0)
	{
		d = 2 * a - b;                             // d0 = 2a - b
		dPx_L = 1, dPy_L = 0, dd_L = 2 * a;        // d < 0���
		dPx_G = 1, dPy_G = -1, dd_G = 2 * (a - b); // d >= 0 ���
	}
	else // k �� (-��, -1)
	{
		d = a - 2 * b;                             // d0 = a - 2b
		dPx_L = 1, dPy_L = -1, dd_L = 2 * (a - b); // d < 0���
		dPx_G = 0, dPy_G = -1, dd_G = -2 * b;      // d >= 0 ���
	}
	// ��������ֱ��
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

//Bresenhamֱ�߶λ����㷨���������x��y���յ�����x��y����ɫ��
void CG2DRenderContext::BresenhamLine(int x0, int y0, int x1, int y1, unsigned long color)
{
	if (x0 > x1) // ��֤x0 <= x1
		std::swap(x0, x1), std::swap(y0, y1);
	int Delta_x = x1 - x0, Delta_y = y1 - y0,
		d,                          // ���߱���d
		dd_L, dd_G,                 // ���߱���d������(L����С��0�������G�������0�����)
		x = x0, y = y0,             // ��ʼP����
		dPx_L, dPy_L, dPx_G, dPy_G; // P���������(L����С��0�������G�������0�����)
	// ����kֵ��������ɾ��߱���������
	if (0 <= Delta_y && Delta_y <= Delta_x) // k �� [0, 1]
	{
		d = 2 * Delta_y - Delta_x;                            // d0 = 2��y - ��x
		dPx_L = 1, dPy_L = 0, dd_L = 2 * Delta_y;             // d < 0���
		dPx_G = 1, dPy_G = 1, dd_G = 2 * (Delta_y - Delta_x); // d >= 0 ���
	}
	else if (Delta_x < Delta_y) // k �� (1, +��)
	{
		d = 2 * Delta_x - Delta_y;                            // d0 = 2��x - ��y
		dPx_L = 0, dPy_L = 1, dd_L = 2 * Delta_x;             // d < 0���
		dPx_G = 1, dPy_G = 1, dd_G = 2 * (Delta_x - Delta_y); // d >= 0 ���
	}
	else if (-Delta_x <= Delta_y && Delta_y < 0) // k �� [-1, 0)
	{
		d = -2 * Delta_y - Delta_x;                             // d0 = -2��y - ��x
		dPx_L = 1, dPy_L = 0, dd_L = -2 * Delta_y;              // d < 0���
		dPx_G = 1, dPy_G = -1, dd_G = -2 * (Delta_y + Delta_x); // d >= 0 ���
	}
	else // k �� (-��, -1)
	{
		d = 2 * Delta_x + Delta_y;                             // d0 = 2��x + ��y
		dPx_L = 0, dPy_L = -1, dd_L = 2 * Delta_x;             // d < 0���
		dPx_G = 1, dPy_G = -1, dd_G = 2 * (Delta_x + Delta_y); // d >= 0 ���
	}
	// ��������ֱ��
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

//Բ�����㷨����������x��y���뾶����ɫ��
void CG2DRenderContext::MidPointCircle(int xc, int yc, int R, unsigned long color)
{
	int x = 0, y = R, // ��ʼP����
		d = 1 - R;    // ���߱���d
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

//Բ�������㷨����������x��y���뾶����ɫ�������X��Ŀ�ʼ�ǶȻ��ȣ�����ڿ�ʼ�Ƕȵ���ʱ��ɨ��ǶȻ��ȣ�
void CG2DRenderContext::MidPointCircleArc(int xc, int yc, int R, unsigned long color, float startAngle, float sweepAngle)
{
	int x = 0, y = R, // ��ʼP����
		d = 1 - R;    // ���߱���d
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

//ɨ������������㷨�����ӵ�����x��y���߽���ɫ�������ɫ��
void CG2DRenderContext::ScanLinePolygonFill(const std::vector<CPoint>&pnts, unsigned long fillColor)
{
	if (mMemHDC == nullptr)
		return;
	if (pnts.empty())
		return;

	// ������С����� Y ֵ��ȷ��ɨ���߷�Χ
	int minY = pnts[0].y, maxY = pnts[0].y;
	for (const auto& point : pnts) {
		minY = min(minY, point.y);
		maxY = max(maxY, point.y);
	}

	// ���Ա߱� (AET)
	std::vector<std::vector<CPoint>> edgeTable(maxY - minY + 1);

	// �����߱�
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

	// ʹ�û��Ե��������
	for (int y = minY; y <= maxY; ++y) {
		if (edgeTable[y - minY].empty()) continue;

		// �� x ����Ա�����
		std::sort(edgeTable[y - minY].begin(), edgeTable[y - minY].end(), [](const CPoint& a, const CPoint& b) {
			return a.x < b.x;
			});

		// �����Խ����֮�����
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

//�߽��ʾ����������㷨�����ӵ�����x��y���߽���ɫ�������ɫ��
void CG2DRenderContext::BoundFill4(int xSeed, int ySeed, unsigned long boundColor, unsigned long fillColor)
{
	if (mMemHDC == nullptr)
		return;
	//�������㷨���룬�����㷨���в���
	//::GetPixel(mMemHDC, xSeed, ySeed)�ɷ�������������ɫ
	//::SetPixel(mMemHDC, xSeed, ySeed, fillColor);����������������ɫ

	// ������������Ƿ���б߽���ɫ�������ɫ
	if (::GetPixel(mMemHDC, xSeed, ySeed) == boundColor || ::GetPixel(mMemHDC, xSeed, ySeed) == fillColor)
		return;

	std::stack<std::pair<int, int>> pixelStack;
	pixelStack.push(std::make_pair(xSeed, ySeed));

	while (!pixelStack.empty()) {
		std::pair<int, int> current = pixelStack.top();
		pixelStack.pop();
		int x = current.first;
		int y = current.second;

		// ��ȡ��ǰ���ص���ɫ
		COLORREF color = ::GetPixel(mMemHDC, x, y);

		// �����ɫ�Ȳ��Ǳ߽���ɫҲ���������ɫ�����������
		if (color != boundColor && color != fillColor) {
			::SetPixel(mMemHDC, x, y, fillColor);

			// ��4���������������ջ
			pixelStack.push(std::make_pair(x + 1, y));    // ��
			pixelStack.push(std::make_pair(x - 1, y));    // ��
			pixelStack.push(std::make_pair(x, y + 1));    // ��
			pixelStack.push(std::make_pair(x, y - 1));    // ��
		}
	}
}

// �ڵ��ʾ����������㷨�����ӵ�����x��y������ԭ��ɫ����������ɫ��
void CG2DRenderContext::FloodFill4(int xSeed, int ySeed, unsigned long oldColor, unsigned long newColor)
{
	if (mMemHDC == nullptr)
		return;

	// ��ȡ���ӵ����ɫ
	COLORREF seedColor = ::GetPixel(mMemHDC, xSeed, ySeed);

	// ������ӵ��Ƿ���Ҫ���
	if (seedColor != oldColor)
		return;

	std::stack<std::pair<int, int>> pixelStack;
	pixelStack.push(std::make_pair(xSeed, ySeed));

	while (!pixelStack.empty()) {
		std::pair<int, int> current = pixelStack.top();
		pixelStack.pop();
		int x = current.first;
		int y = current.second;

		// ��ȡ��ǰ���ص���ɫ
		COLORREF color = ::GetPixel(mMemHDC, x, y);

		// ���������ɫ��ԭ��ɫ��ͬ����������
		if (color == oldColor) {
			::SetPixel(mMemHDC, x, y, newColor);

			// �������ڵ��ĸ�����
			pixelStack.push(std::make_pair(x + 1, y));    // ��
			pixelStack.push(std::make_pair(x - 1, y));    // ��
			pixelStack.push(std::make_pair(x, y + 1));    // ��
			pixelStack.push(std::make_pair(x, y - 1));    // ��
		}
	}
}

//ʹ���������ָ���ӿ��л���
void CG2DRenderContext::Ready(CG2DCamera* camera) //ÿһ����������ǰ���á���������ӿڱ�������Ҫ���»���ͼ�Ρ�
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
void CG2DRenderContext::Finish(CG2DCamera* camera) //ÿһ����������ǰ����
{
	assert(mMemHDC != nullptr);
	if (mMemHDC == nullptr)
		return;
}
