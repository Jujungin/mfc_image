#include "stdafx.h"
#include "IP_ProgrammingMyClass.h"


CIP_ProgrammingMyClass::CIP_ProgrammingMyClass(void)
	: m_pucBMP(NULL)
	, m_pucImgbuf(NULL)
	, m_uiWidth(0)
	, m_uiHeight(0)
{
	//	set the BMP header information
	m_BMPheader.biSize			=	sizeof(BITMAPINFOHEADER);
	m_BMPheader.biPlanes		=	1;
	m_BMPheader.biBitCount		=	24;
	m_BMPheader.biCompression	=	BI_RGB;
	m_BMPheader.biSizeImage		=	0;
	m_BMPheader.biXPelsPerMeter	=	0;
	m_BMPheader.biYPelsPerMeter	=	0;
	m_BMPheader.biClrUsed		=	0;
	m_BMPheader.biClrImportant	=	0;
}
CIP_ProgrammingMyClass::~CIP_ProgrammingMyClass(void)
{
}