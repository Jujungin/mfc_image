#pragma once

#include "./IppImage/IppImage.h"
#include "IppFeature.h"
#include <vector>

class IppLabelInfo
{
public:
	std::vector<IppPoint> pixels;
	int cx, cy;
	int minx, miny, maxx, maxy;

public:
	IppLabelInfo() : cx(0), cy(0), minx(9999), miny(9999), maxx(0), maxy(0)
	{
		pixels.clear();
	}
};

void IppBinarization(IppByteImage& imgSrc, IppByteImage& imgDst, int threshold);
int  IppBinarizationIterative(IppByteImage& imgSrc);

void IppMorphologyErosion(IppByteImage& imgSrc, IppByteImage& imgDst);
void IppMorphologyDilation(IppByteImage& imgSrc, IppByteImage& imgDst);
void IppMorphologyOpening(IppByteImage& imgSrc, IppByteImage& imgDst);
void IppMorphologyClosing(IppByteImage& imgSrc, IppByteImage& imgDst);

void IppMorphologyGrayErosion(IppByteImage& imgSrc, IppByteImage& imgDst);
void IppMorphologyGrayDilation(IppByteImage& imgSrc, IppByteImage& imgDst);
void IppMorphologyGrayOpening(IppByteImage& imgSrc, IppByteImage& imgDst);
void IppMorphologyGrayClosing(IppByteImage& imgSrc, IppByteImage& imgDst);