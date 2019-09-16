#pragma once

class CIP_ProgrammingMyClass
{
public:
	BITMAPINFOHEADER	m_BMPheader;

	UCHAR*				m_pucBMP;
	UCHAR**				m_pucImgbuf;

	UINT				m_uiHeight;
	UINT				m_uiWidth;

public:
public:
	CIP_ProgrammingMyClass(void);
	~CIP_ProgrammingMyClass(void);
};
