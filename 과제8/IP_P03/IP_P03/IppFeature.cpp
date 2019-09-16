#include "stdafx.h"
#include "IppFeature.h"
#include "IppFilter.h"
#include <vector>

const double PI = 3.14159265358979323846;
const float PI_F = 3.14159265358979323846f;

#define CHECK_WEAK_EDGE(x, y) \
    if (pEdge[y][x] == WEAK_EDGE) { \
        pEdge[y][x] = STRONG_EDGE; \
        strong_edges.push_back(IppPoint(x, y)); \
    }

void IppEdgeCanny(IppByteImage& imgSrc, IppByteImage& imgEdge, float sigma, float th_low, float th_high)
{
	register int i, j;

	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	IppFloatImage imgGaussian(w, h);
	IppFilterGaussian(imgSrc, imgGaussian, sigma);


	IppFloatImage imgGx(w, h);
	IppFloatImage imgGy(w, h);
	IppFloatImage imgMag(w, h);

	float** pGauss = imgGaussian.GetPixels2D();
	float** pGx = imgGx.GetPixels2D();
	float** pGy = imgGy.GetPixels2D();
	float** pMag = imgMag.GetPixels2D();

	for (j = 1; j < h - 1; j++)
		for (i = 1; i < w - 1; i++)
		{
			pGx[j][i] = -pGauss[j - 1][i - 1] - 2 * pGauss[j][i - 1] - pGauss[j + 1][i - 1]
				+ pGauss[j - 1][i + 1] + 2 * pGauss[j][i + 1] + pGauss[j + 1][i + 1];
			pGy[j][i] = -pGauss[j - 1][i - 1] - 2 * pGauss[j - 1][i] - pGauss[j - 1][i + 1]
				+ pGauss[j + 1][i - 1] + 2 * pGauss[j + 1][i] + pGauss[j + 1][i + 1];

			pMag[j][i] = sqrt(pGx[j][i] * pGx[j][i] + pGy[j][i] * pGy[j][i]);
		}


	imgEdge.CreateImage(w, h);
	BYTE** pEdge = imgEdge.GetPixels2D();

	enum DISTRICT { AREA0 = 0, AREA45, AREA90, AREA135, NOAREA };

	const BYTE STRONG_EDGE = 255;
	const BYTE WEAK_EDGE = 128;

	std::vector<IppPoint> strong_edges;

	float ang;
	int district;
	bool local_max;
	for (j = 1; j < h - 1; j++)
		for (i = 1; i < w - 1; i++)
		{
			if (pMag[j][i] > th_low)
			{
				if (pGx[j][i] != 0.f)
				{
					ang = atan2(pGy[j][i], pGx[j][i]) * 180 / PI_F;
					if (((ang >= -22.5f) && (ang < 22.5f)) || (ang >= 157.5f) || (ang < -157.5f))
						district = AREA0;
					else if (((ang >= 22.5f) && (ang < 67.5f)) || ((ang >= -157.5f) && (ang <
						-112.5f)))
						district = AREA45;
					else if (((ang >= 67.5) && (ang < 112.5)) || ((ang >= -112.5) && (ang < -67.5)))
						district = AREA90;
					else
						district = AREA135;
				}
				else
					district = AREA90;

				local_max = false;
				switch (district)
				{
				case AREA0:
					if ((pMag[j][i] >= pMag[j][i - 1]) && (pMag[j][i] > pMag[j][i + 1]))
						local_max = true;
					break;
				case AREA45:
					if ((pMag[j][i] >= pMag[j - 1][i - 1]) && (pMag[j][i] > pMag[j + 1][i + 1]))
						local_max = true;
					break;
				case AREA90:
					if ((pMag[j][i] >= pMag[j - 1][i]) && (pMag[j][i] > pMag[j + 1][i]))
						local_max = true;
					break;
				case AREA135:
				default:
					if ((pMag[j][i] >= pMag[j - 1][i + 1]) && (pMag[j][i] > pMag[j + 1][i - 1]))
						local_max = true;
					break;
				}

				if (local_max)
				{
					if (pMag[j][i] > th_high)
					{
						pEdge[j][i] = STRONG_EDGE;
						strong_edges.push_back(IppPoint(i, j));
					}
					else
						pEdge[j][i] = WEAK_EDGE;
				}
			}
		}


	while (!strong_edges.empty())
	{
		IppPoint p = strong_edges.back();
		strong_edges.pop_back();

		int x = p.x, y = p.y;

			CHECK_WEAK_EDGE(x + 1, y)
			CHECK_WEAK_EDGE(x + 1, y + 1)
			CHECK_WEAK_EDGE(x, y + 1)
			CHECK_WEAK_EDGE(x - 1, y + 1)
			CHECK_WEAK_EDGE(x - 1, y)
			CHECK_WEAK_EDGE(x - 1, y - 1)
			CHECK_WEAK_EDGE(x, y - 1)
			CHECK_WEAK_EDGE(x + 1, y - 1)
	}

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			if (pEdge[j][i] == WEAK_EDGE) pEdge[j][i] = 0;
		}
}


void Sobel(IppByteImage& img, IppByteImage& imgEdge)
{
	int w = img.GetWidth();
	int h = img.GetHeight();

	imgEdge.CreateImage(w, h);

	BYTE** p1 = img.GetPixels2D();
	BYTE** p2 = imgEdge.GetPixels2D();

	int i, j, h1, h2;
	double hval;
	for (j = 1; j < h - 1; j++)
		for (i = 1; i < w - 1; i++)
		{
			h1 = -p1[j - 1][i - 1] - 2 * p1[j - 1][i] - p1[j - 1][i + 1]
				+ p1[j + 1][i - 1] + 2 * p1[j + 1][i] + p1[j + 1][i + 1];
			h2 = -p1[j - 1][i - 1] - 2 * p1[j][i - 1] - p1[j + 1][i - 1]
				+ p1[j - 1][i + 1] + 2 * p1[j][i + 1] + p1[j + 1][i + 1];

			hval = sqrt(static_cast<double>(h1 * h1 + h2 * h2));

			p2[j][i] = static_cast<BYTE>(limit(hval + 0.5));
		}
}

void IppDrawLine(IppByteImage & img, IppLineParam line, BYTE c)
{
	int w = img.GetWidth();
	int h = img.GetHeight();

	int x1, y1, x2, y2;
	if ((line.ang >= 0 && line.ang < PI / 4) || (line.ang >= 3 * PI / 4 && line.ang < PI))
	{
		x1 = 0;
		y1 = static_cast<int>(floor(line.rho / cos(line.ang) + 0.5));
		x2 = w - 1;
		y2 = static_cast<int>(floor((line.rho - x2 * sin(line.ang)) / cos(line.ang) + 0.5));
	}
	else
	{
		y1 = 0;
		x1 = static_cast<int>(floor(line.rho / sin(line.ang) + 0.5));
		y2 = h - 1;
		x2 = static_cast<int>(floor((line.rho - y2 * cos(line.ang)) / sin(line.ang) + 0.5));
	}

	IppDrawLine(img, x1, y1, x2, y2, c);
}

void IppDrawLine(IppByteImage & img, int x1, int y1, int x2, int y2, BYTE c)
{
	int w = img.GetWidth();
	int h = img.GetHeight();
	BYTE** ptr = img.GetPixels2D();

	int dx, dy, inc_x, inc_y, fraction;

	dx = x2 - x1;
	inc_x = (dx > 0) ? 1 : -1;
	dx = abs(dx) << 1;

	dy = y2 - y1;
	inc_y = (dy > 0) ? 1 : -1;
	dy = abs(dy) << 1;

	if (x1 >= 0 && x1 < w && y1 >= 0 && y1 < h)
		ptr[y1][x1] = c;

	if (dx >= dy)
	{
		fraction = dy - (dx >> 1);

		while (x1 != x2)
		{
			if ((fraction >= 0) && (fraction || (inc_x > 0)))
			{
				fraction -= dx;
				y1 += inc_y;
			}

			fraction += dy;
			x1 += inc_x;

			if (x1 >= 0 && x1 < w && y1 >= 0 && y1 < h)
				ptr[y1][x1] = c;
		}
	}
	else
	{
		fraction = dx - (dy >> 1);

		while (y1 != y2)
		{
			if ((fraction >= 0) && (fraction || (inc_y > 0)))
			{
				fraction -= dy;
				x1 += inc_x;
			}

			fraction += dx;
			y1 += inc_y;

			if (x1 >= 0 && x1 < w && y1 >= 0 && y1 < h)
				ptr[y1][x1] = c;
		}
	}

}

void IppHoughLine(IppByteImage & img, std::vector<IppLineParam>& lines, int threshold)
{
	register int i, j;

	int w = img.GetWidth();
	int h = img.GetHeight();

	BYTE** ptr = img.GetPixels2D();
	int num_rho = static_cast<int>(sqrt((double)w*w + h * h) * 2);
	int num_ang = 360;

	float* sin_tbl = new float[num_ang];
	float* cos_tbl = new float[num_ang];

	for (i = 0; i < num_ang; i++)
	{
		sin_tbl[i] = sin(i * PI_F / num_ang);
		cos_tbl[i] = cos(i * PI_F / num_ang);
	}

	IppIntImage imgAcc(num_ang, num_rho);
	int** pAcc = imgAcc.GetPixels2D();

	int m, n;
	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			if (ptr[j][i] > 128)
			{
				for (n = 0; n < num_ang; n++)
				{
					m = static_cast<int>(floor(i * sin_tbl[n] + j * cos_tbl[n] + 0.5f));
					m += (num_rho / 2);

					pAcc[m][n]++;
				}
			}
		}

	lines.clear();
	int temp;
	for (m = 0; m < num_rho; m++)
		for (n = 0; n < num_ang; n++)

		{
			temp = pAcc[m][n];
			if (temp > threshold)
			{
				if (temp > pAcc[m - 1][n] && temp > pAcc[m - 1][n + 1] &&
					temp > pAcc[m][n + 1] && temp > pAcc[m + 1][n + 1] &&
					temp > pAcc[m + 1][n] && temp > pAcc[m + 1][n - 1] &&
					temp > pAcc[m][n - 1] && temp > pAcc[m - 1][n - 1])
				{
					lines.push_back(IppLineParam(m - (num_rho / 2), n * PI / num_ang, pAcc[m][n]));
				}
			}
		}

	delete[] sin_tbl;
	delete[] cos_tbl;

}
