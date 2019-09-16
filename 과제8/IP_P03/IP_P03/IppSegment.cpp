#include "stdafx.h"
#include "IppSegment.h"
#include "./IppImage/IppEnhance.h"
#include <map>

void IppBinarization(IppByteImage& imgSrc, IppByteImage& imgDst, int threshold)
{
	imgDst.CreateImage(imgSrc.GetWidth(), imgSrc.GetHeight());

	int size = imgSrc.GetSize();
	BYTE* pSrc = imgSrc.GetPixels();
	BYTE* pDst = imgDst.GetPixels();

	for (int i = 0; i < size; i++)
	{
		pDst[i] = (pSrc[i] <= threshold) ? 0 : 255;
	}
}

int IppBinarizationIterative(IppByteImage& imgSrc)
{
	float hist[256] = { 0, };
	IppHistogram(imgSrc, hist);

	int i, T, Told;

	float sum = 0.f;
	for (i = 0; i < 256; i++)
		sum += (i * hist[i]);

	T = static_cast<int>(sum + .5f);

	float a1, b1, u1, a2, b2, u2;
	do {
		Told = T;

		a1 = b1 = u1 = 0.f;
		for (i = 0; i <= Told; i++)
		{
			a1 += (i*hist[i]);
			b1 += hist[i];
		}

		if (b1 != 0.f)
			u1 = a1 / b1;

		a2 = b2 = u2 = 0.f;
		for (i = Told + 1; i < 256; i++)
		{
			a2 += (i*hist[i]);
			b2 += hist[i];
		}

		if (b2 != 0.f)
			u2 = a2 / b2;

		T = static_cast<int>((u1 + u2) / 2 + 0.5f);
	} while (T != Told);

	return T;
}


void IppMorphologyErosion(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	int i, j;
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst = imgSrc;

	BYTE** pDst = imgDst.GetPixels2D();
	BYTE** pSrc = imgSrc.GetPixels2D();

	for (j = 1; j < h - 1; j++)
		for (i = 1; i < w - 1; i++)
		{
			if (pSrc[j][i] != 0)
			{
				if (pSrc[j - 1][i] == 0 || pSrc[j - 1][i + 1] == 0 ||
					pSrc[j][i - 1] == 0 || pSrc[j][i + 1] == 0 ||
					pSrc[j + 1][i - 1] == 0 || pSrc[j + 1][i] == 0 ||
					pSrc[j + 1][i + 1] == 0 || pSrc[j - 1][i - 1] == 0)
				{
					pDst[j][i] = 0;
				}
			}
		}
}

void IppMorphologyDilation(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	int i, j;
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst = imgSrc;

	BYTE** pDst = imgDst.GetPixels2D();
	BYTE** pSrc = imgSrc.GetPixels2D();

	for (j = 1; j < h - 1; j++)
		for (i = 1; i < w - 1; i++)
		{
			if (pSrc[j][i] == 0)
			{
				if (pSrc[j - 1][i] != 0 || pSrc[j - 1][i + 1] != 0 ||
					pSrc[j][i - 1] != 0 || pSrc[j][i + 1] != 0 ||
					pSrc[j + 1][i - 1] != 0 || pSrc[j + 1][i] != 0 ||
					pSrc[j + 1][i + 1] != 0 || pSrc[j - 1][i - 1] != 0)
				{
					pDst[j][i] = 255;
				}
			}
		}
}

void IppMorphologyOpening(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	IppByteImage imgTmp;
	IppMorphologyErosion(imgSrc, imgTmp);
	IppMorphologyDilation(imgTmp, imgDst);
}

void IppMorphologyClosing(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	IppByteImage imgTmp;
	IppMorphologyDilation(imgSrc, imgTmp);
	IppMorphologyErosion(imgTmp, imgDst);
}

void IppMorphologyGrayErosion(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	int i, j, m, n, x, y, pmin;
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst = imgSrc;

	BYTE** pDst = imgDst.GetPixels2D();
	BYTE** pSrc = imgSrc.GetPixels2D();

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			pmin = 255;

			for (n = -1; n <= 1; n++)
				for (m = -1; m <= 1; m++)
				{
					x = i + m;
					y = j + n;

					if (x >= 0 && x < w && y >= 0 && y < h)
					{
						if (pSrc[y][x] < pmin)
							pmin = pSrc[y][x];
					}
				}

			pDst[j][i] = pmin;
		}
}

void IppMorphologyGrayDilation(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	int i, j, m, n, x, y, pmax;
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst = imgSrc;

	BYTE** pDst = imgDst.GetPixels2D();
	BYTE** pSrc = imgSrc.GetPixels2D();

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			pmax = 0;

			for (n = -1; n <= 1; n++)
				for (m = -1; m <= 1; m++)
				{
					x = i + m;
					y = j + n;

					if (x >= 0 && x < w && y >= 0 && y < h)
					{
						if (pSrc[y][x] > pmax)
							pmax = pSrc[y][x];
					}
				}

			pDst[j][i] = pmax;
		}
}

void IppMorphologyGrayOpening(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	IppByteImage imgTmp;
	IppMorphologyGrayErosion(imgSrc, imgTmp);
	IppMorphologyGrayDilation(imgTmp, imgDst);
}

void IppMorphologyGrayClosing(IppByteImage& imgSrc, IppByteImage& imgDst)
{
	IppByteImage imgTmp;
	IppMorphologyGrayDilation(imgSrc, imgTmp);
	IppMorphologyGrayErosion(imgTmp, imgDst);
}

