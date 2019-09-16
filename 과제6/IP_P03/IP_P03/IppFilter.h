#pragma once

#include "./IppImage/IppImage.h"

void IppFilterGaussian(IppByteImage& imgSrc, IppFloatImage& imgDst, float sigma);
void IppFilterLaplacian(IppByteImage& imgSrc, IppByteImage& imgDst);
void IppFilterLoG(IppByteImage& imgSrc, IppFloatImage& imgDst, float sigma);
void IppFilterGoS(IppByteImage& imgSrc, IppFloatImage& imgDst, float sigma);