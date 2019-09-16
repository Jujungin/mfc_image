#include "stdafx.h"
#include "IppFilter.h"

const float PI_F = 3.14159265358979323846f;

void IppFilterGaussian(IppByteImage & imgSrc, IppFloatImage & imgDst, float sigma)
{
	sigma = 1.0;
	register int i, j, k, x;

	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst.CreateImage(w, h);

	BYTE** pSrc = imgSrc.GetPixels2D();
	float** pDst = imgDst.GetPixels2D();

	int dim = static_cast<int>(2 * 4 * sigma + 1.0);
	if (dim < 3) dim = 3;
	if (dim % 2 == 0) dim++;
	int dim2 = dim / 2;

	IppFloatImage imgMask(dim, 1);
	float* pMask = imgMask.GetPixels();

	for (i = 0; i < dim; i++)
	{
		x = i - dim2;
		pMask[i] = exp(-(x * x) / (2 * sigma * sigma)) / (sqrt(2 * PI_F) * sigma);
	}

	IppFloatImage imgBuf(w, h);
	float** pBuf = imgBuf.GetPixels2D();

	float sum1, sum2;
	for (i = 0; i < w; i++)
		for (j = 0; j < h; j++)
		{
			sum1 = sum2 = 0.f;

			for (k = 0; k < dim; k++)
			{
				x = k - dim2 + j;

				if (x >= 0 && x < h)
				{
					sum1 += pMask[k];
					sum2 += (pMask[k] * pSrc[x][i]);
				}
			}

			pBuf[j][i] = sum2 / sum1;
		}

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			sum1 = sum2 = 0.f;

			for (k = 0; k < dim; k++)
			{
				x = k - dim2 + i;

				if (x >= 0 && x < w)
				{
					sum1 += pMask[k];
					sum2 += (pMask[k] * pBuf[j][x]);
				}
			}

			pDst[j][i] = sum2 / sum1;
		}

}

void IppFilterLaplacian(IppByteImage & imgSrc, IppByteImage & imgDst)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst.CreateImage(w, h);

	BYTE** pSrc = imgSrc.GetPixels2D();
	BYTE** pDst = imgDst.GetPixels2D();

	int i, j, sum;
	for (j = 1; j < h - 1; j++)
		for (i = 1; i < w - 1; i++)
		{
			sum = pSrc[j - 1][i] + pSrc[j][i - 1] + pSrc[j + 1][i] + pSrc[j][i + 1]
				- 4 * pSrc[j][i];

			pDst[j][i] = static_cast<BYTE>(limit(sum + 128));
		}

}

void IppFilterLoG(IppByteImage & imgSrc, IppFloatImage & imgDst, float sigma)
{
	sigma = 1.0;
	register int i, j, k, x;

	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst.CreateImage(w, h);

	BYTE** pSrc = imgSrc.GetPixels2D();
	float** pDst = imgDst.GetPixels2D();

	int dim = static_cast<int>(2 * 4 * sigma + 1.0);
	if (dim < 3) dim = 3;
	if (dim % 2 == 0) dim++;
	int dim2 = dim / 2;

	IppFloatImage imgMask(dim, 1);
	float* pMask = imgMask.GetPixels();

	for (i = 0; i < dim; i++)
	{
		x = i - dim2;
		pMask[i] = exp(-(x * x) / (2 * sigma * sigma)) / (sqrt(2 * PI_F) * sigma);
	}

	IppFloatImage imgBuf(w, h);
	float** pBuf = imgBuf.GetPixels2D();

	float sum1, sum2;
	for (i = 0; i < w; i++)
		for (j = 0; j < h; j++)
		{
			sum1 = sum2 = 0.f;

			for (k = 0; k < dim; k++)
			{
				x = k - dim2 + j;

				if (x >= 0 && x < h)
				{
					sum1 += pMask[k];
					sum2 += (pMask[k] * pSrc[x][i]);
				}
			}

			pBuf[j][i] = sum2 / sum1;
		}

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			sum1 = sum2 = 0.f;

			for (k = 0; k < dim; k++)
			{
				x = k - dim2 + i;

				if (x >= 0 && x < w)
				{
					sum1 += pMask[k];
					sum2 += (pMask[k] * pBuf[j][x]);
				}
			}

			pDst[j][i] = sum2 / sum1;
		}



	int sum;
	for (j = 1; j < h - 1; j++)
		for (i = 1; i < w - 1; i++)
		{
			sum = pBuf[j - 1][i] + pBuf[j][i - 1] + pBuf[j + 1][i] + pBuf[j][i + 1]
				- 4 * pBuf[j][i];

			pDst[j][i] = static_cast<BYTE>(limit(sum + 128));
		}
}
