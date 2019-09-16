#include "stdafx.h"
#include "IppTranse.h"
#include <math.h>

const double PI = 3.14159265358979323846;

void DST1d(double* re, double* im, int N, int dir)
{
	double* tr = new double[N];
	double* ti = new double[N];
	memcpy(tr, re, sizeof(double) * N);
	memcpy(ti, im, sizeof(double) * N);

	register int i, x;
	double sum_re, sum_im, temp;

	for (i = 0; i < N; i++)
	{
		sum_re = sum_im = 0;

		for (x = 0; x < N; x++)
		{
			temp = 2 * dir * PI * ((double)i * x / N);

			sum_re += (tr[x] * cos(temp) + ti[x] * sin(temp));
			sum_im += (ti[x] * cos(temp) - tr[x] * sin(temp));
		}

		re[i] = sum_re;
		im[i] = sum_im;
	}

	if (dir == -1) // IDST
	{
		for (i = 0; i < N; i++)
		{
			re[i] /= (double)N;
			im[i] /= (double)N;
		}
	}

	delete[] tr;
	delete[] ti;
}

IppTranse::IppTranse(void)
	: width(0), height(0)
{
}

void IppTranse::SetImage(IppByteImage& img)
{
	width = img.GetWidth();
	height = img.GetHeight();

	real.Convert(img);

	imag.CreateImage(width, height); 
}

void IppTranse::GetImage(IppByteImage& img)
{
	if (!real.IsValid())
		return;

	img.CreateImage(width, height);

	double* pRe = real.GetPixels();
	BYTE* ptr = img.GetPixels();

	int size = real.GetSize();
	for (int i = 0; i < size; i++)
		ptr[i] = static_cast<BYTE>(limit(pRe[i] + 0.5));
}

void IppTranse::GetSpectrumImage(IppByteImage& img)
{
	register int i, j;

	img.CreateImage(width, height);
	BYTE** ptr = img.GetPixels2D();

	double** pRe = real.GetPixels2D();
	double** pIm = imag.GetPixels2D();

	IppDoubleImage spectrum(width, height);
	double** pSpec = spectrum.GetPixels2D();

	double mag, max_value = 0;
	for (j = 0; j < height; j++)
		for (i = 0; i < width; i++)
		{
			mag = sqrt(pRe[j][i] * pRe[j][i] + pIm[j][i] * pIm[j][i]);
			pSpec[j][i] = log(mag + 1);

			if (pSpec[j][i] > max_value)
				max_value = pSpec[j][i];
		}

	int x, y;
	for (j = 0; j < height; j++)
		for (i = 0; i < width; i++)
		{
			x = i + width / 2;
			y = j + height / 2;

			if (x >= width) x -= width;
			if (y >= height) y -= height;

			ptr[j][i] = static_cast<BYTE>(limit(pSpec[y][x] * 255 / max_value));
		}
}

void IppTranse::GetPhaseImage(IppByteImage& img)
{
	register int i, j;

	img.CreateImage(width, height);
	BYTE** ptr = img.GetPixels2D();

	double** pRe = real.GetPixels2D();
	double** pIm = imag.GetPixels2D();

	IppDoubleImage phase(width, height);
	double** pPhase = phase.GetPixels2D();

	for (j = 0; j < height; j++)
		for (i = 0; i < width; i++)
		{
			pPhase[j][i] = atan2(pIm[j][i], pRe[j][i]);
		}

	int x, y;
	for (j = 0; j < height; j++)
		for (i = 0; i < width; i++)
		{
			x = i + width / 2;
			y = j + height / 2;

			if (x >= width) x -= width;
			if (y >= height) y -= height;

			ptr[j][i] = static_cast<BYTE>(limit(pPhase[y][x] * 128 / PI + 128));
		}
}

void IppTranse::DCT(int dir)
{
	if (!real.IsValid())
		return;

	IppDoubleImage real_cpy = real;
	IppDoubleImage imag_cpy = imag;

	double** pRe = real.GetPixels2D();
	double** pIm = imag.GetPixels2D();

	double** pReCpy = real_cpy.GetPixels2D();
	double** pImCpy = imag_cpy.GetPixels2D();

	register int i, j, x, y;
	double sum_re, sum_im, temp, temp1, temp2;

	for (j = 0; j < height; j++)
		for (i = 0; i < width; i++)
		{
			sum_re = sum_im = 0;

			for (y = 0; y < height; y++)
				for (x = 0; x < width; x++)
				{
					
					
					sum_re += (pReCpy[y][x]*cos(((2.0*x+1.0)*i*PI)/(2.0*width)));
					sum_im += (pReCpy[y][x] * cos(((2.0*x + 1.0)*i*PI) / (2.0*width)));
				}

			pRe[j][i] = sum_re;
			pIm[j][i] = sum_im;
			

			if (dir == -1)
			{
				pRe[j][i] /= (width * height) + (width * height);
				pIm[j][i] /= (width * height) + (width * height);
			}
		}
}

void IppTranse::DST(int dir)
{
	if (!real.IsValid())
		return;

	IppDoubleImage real_cpy = real;
	IppDoubleImage imag_cpy = imag;

	double** pRe = real.GetPixels2D();
	double** pIm = imag.GetPixels2D();

	double** pReCpy = real_cpy.GetPixels2D();
	double** pImCpy = imag_cpy.GetPixels2D();

	register int i, j, x, y;
	double sum_re, sum_im, temp;

	for (j = 0; j < height; j++)
		for (i = 0; i < width; i++)
		{
			sum_re = sum_im = 0;

			for (y = 0; y < height; y++)
				for (x = 0; x < width; x++)
				{
					temp = 2 * dir * PI * (static_cast<double>(i) * x / width + static_cast<double>(j) * y / height);
					sum_re += (pReCpy[y][x] * cos(temp) - pImCpy[y][x] * sin(temp));
					sum_im += (pReCpy[y][x] * sin(temp) + pImCpy[y][x] * sin(temp));
				}

			pRe[j][i] = sum_re;
			pIm[j][i] = sum_im;

			if (dir == -1)
			{
				pRe[j][i] /= (width * height);
				pIm[j][i] /= (width * height);
			}
		}
}

void IppTranse::DSTRC(int dir)
{
	if (!real.IsValid())
		return;


	// 행 변환

	IppDoubleImage real_tmp, imag_tmp;

	real_tmp.CreateImage(width, 1);
	imag_tmp.CreateImage(width, 1);

	double* re = real_tmp.GetPixels();
	double* im = imag_tmp.GetPixels();

	double** pRe = real.GetPixels2D();
	double** pIm = imag.GetPixels2D();

	register int i, j;

	for (j = 0; j < height; j++)
	{
		for (i = 0; i < width; i++)
		{
			re[i] = pRe[j][i];
			im[i] = pIm[j][i];
		}

		DST1d(re, im, width, dir);

		for (i = 0; i < width; i++)
		{
			pRe[j][i] = re[i];
			pIm[j][i] = im[i];
		}
	}


	//열 변환

	real_tmp.CreateImage(height, 1);
	imag_tmp.CreateImage(height, 1);

	re = real_tmp.GetPixels();
	im = imag_tmp.GetPixels();

	memset(re, 0, sizeof(double) * height);
	memset(im, 0, sizeof(double) * height);

	for (i = 0; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			re[j] = pRe[j][i];
			im[j] = pIm[j][i];
		}

		DST1d(re, im, height, dir);

		for (j = 0; j < height; j++)
		{
			pRe[j][i] = re[j];
			pIm[j][i] = im[j];
		}
	}
}
