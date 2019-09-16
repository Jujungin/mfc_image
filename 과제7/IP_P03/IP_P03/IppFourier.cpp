#include "StdAfx.h"
#include "IppFourier.h"

#include  <math.h>

const double PI = 3.14159265358979323846;

void DFT1d(double* re, double* im, int N, int dir)
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

	if (dir == -1) // IDFT
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
void FFT1d(double * re, double * im, int N, int dir)
{
}
bool IsPowerOf2(int n)
{
	return false;
}
IppFourier::IppFourier(void)
	: width(0), height(0)
{
}

void IppFourier::SetImage(IppByteImage& img)
{
	width = img.GetWidth();
	height = img.GetHeight();

	real.Convert(img);               // 실수부에 영상의 그레이스케일 값 복사

	imag.CreateImage(width, height); // 허수부는 모두 0으로 초기화
}

void IppFourier::GetImage(IppByteImage& img)
{
	if (!real.IsValid())
		return;

	// 실수부의 값을 이용하여 출력 영상을 생성
	img.CreateImage(width, height);

	double* pRe = real.GetPixels();
	BYTE* ptr = img.GetPixels();

	int size = real.GetSize();
	for (int i = 0; i < size; i++)
		ptr[i] = static_cast<BYTE>(limit(pRe[i] + 0.5));
}

void IppFourier::GetSpectrumImage(IppByteImage& img)
{
	register int i, j;

	img.CreateImage(width, height);
	BYTE** ptr = img.GetPixels2D();

	double** pRe = real.GetPixels2D();
	double** pIm = imag.GetPixels2D();

	// 스펙트럼 값을 저장할 임시 버퍼
	IppDoubleImage spectrum(width, height);
	double** pSpec = spectrum.GetPixels2D();

	//-------------------------------------------------------------------------
	// 복소수 값의 절댓값을 로그 변환하여 저장.
	// 정규화된 결과 이미지 생성을 위하여 스펙트럼의 최댓값 계산.
	//-------------------------------------------------------------------------

	double mag, max_value = 0;
	for (j = 0; j < height; j++)
		for (i = 0; i < width; i++)
		{
			mag = sqrt(pRe[j][i] * pRe[j][i] + pIm[j][i] * pIm[j][i]);
			pSpec[j][i] = log(mag + 1);

			if (pSpec[j][i] > max_value)
				max_value = pSpec[j][i];
		}

	//-------------------------------------------------------------------------
	// 출력 영상 생성. 푸리에 변환 결과를 SHIFT 하고,
	// 출력 영상의 최댓값이 255가 되도록 그레이스케일 값을 정규화.
	//-------------------------------------------------------------------------

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

void IppFourier::GetPhaseImage(IppByteImage& img)
{
	register int i, j;

	img.CreateImage(width, height);
	BYTE** ptr = img.GetPixels2D();

	double** pRe = real.GetPixels2D();
	double** pIm = imag.GetPixels2D();

	// 위상각을 저장할 임시 버퍼
	IppDoubleImage phase(width, height);
	double** pPhase = phase.GetPixels2D();

	//-------------------------------------------------------------------------
	// 복소수 값의 위상각을 저장. atan2 함수의 반환 값은 -PI ~ PI 이다.
	//-------------------------------------------------------------------------

	for (j = 0; j < height; j++)
		for (i = 0; i < width; i++)
		{
			pPhase[j][i] = atan2(pIm[j][i], pRe[j][i]); // 래디언 단위
		}

	//-------------------------------------------------------------------------
	// 출력 영상 생성. 푸리에 변환 결과를 SHIFT하고,
	// 출력 영상의 최댓값이 255가 되도록 그레이스케일 값을 정규화.
	//-------------------------------------------------------------------------

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

void IppFourier::DFT(int dir)
{
	if (!real.IsValid())
		return;

	//-------------------------------------------------------------------------
	// real, imag 복사본 생성
	//-------------------------------------------------------------------------

	IppDoubleImage real_cpy = real;
	IppDoubleImage imag_cpy = imag;

	double** pRe = real.GetPixels2D();
	double** pIm = imag.GetPixels2D();

	double** pReCpy = real_cpy.GetPixels2D();
	double** pImCpy = imag_cpy.GetPixels2D();

	//-------------------------------------------------------------------------
	// 이산 푸리에 변환 (또는 역변환)
	//-------------------------------------------------------------------------

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

			if (dir == -1) // 역변환인 경우
			{
				pRe[j][i] /= (width * height);
				pIm[j][i] /= (width * height);
			}
		}
}

void IppFourier::DFTRC(int dir)
{
	if (!real.IsValid())
		return;

	//-------------------------------------------------------------------------
	// 행(Row) 단위 이산 푸리에 변환 (또는 역변환)
	//-------------------------------------------------------------------------

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

		DFT1d(re, im, width, dir);

		for (i = 0; i < width; i++)
		{
			pRe[j][i] = re[i];
			pIm[j][i] = im[i];
		}
	}

	//-------------------------------------------------------------------------
	// 열(Column) 단위 이산 푸리에 변환 (또는 역변환)
	//-------------------------------------------------------------------------

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

		DFT1d(re, im, height, dir);

		for (j = 0; j < height; j++)
		{
			pRe[j][i] = re[j];
			pIm[j][i] = im[j];
		}
	}
}

void IppFourier::FFT(int dir)
{
}

void IppFourier::LowPassIdeal(int cutoff)
{
}

void IppFourier::HighPassIdeal(int cutoff)
{
}

void IppFourier::LowPassGaussian(int cutoff)
{
}

void IppFourier::HighPassGaussian(int cutoff)
{
}

