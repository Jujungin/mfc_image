#pragma once

#include ".\IppImage\IppImage.h"

class IppTranse
{
public:
	int width;
	int height;
	IppDoubleImage real; 
	IppDoubleImage imag; 

public:
	IppTranse();

	void SetImage(IppByteImage& img);
	void GetImage(IppByteImage& img);
	void GetSpectrumImage(IppByteImage& img);
	void GetPhaseImage(IppByteImage& img);

	void DCT(int dir);
	void DST(int dir);
	void DSTRC(int dir);


};

void DST1d(double* re, double* im, int N, int dir);
