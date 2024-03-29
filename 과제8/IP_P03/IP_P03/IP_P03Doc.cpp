
// IP_P03Doc.cpp: CIPP03Doc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "IP_P03.h"
#endif

#include "IP_P03Doc.h"
#include "FileNewDlg.h"
#include <propkey.h>
#include "HistogramDlg.h"
#include ".\IppImage\IppImage.h"
#include ".\IppImage\IppConvert.h"
#include ".\IppImage\IppEnhance.h"
#include "IppFourier.h"
#include "IppFeature.h"
#include "IppFilter.h"
#include <mmsystem.h>
#include <algorithm>
#include <functional>
#include "IppSegment.h"

#pragma comment(lib, "winmm.lib")

#define SHOW_SPECTRUM_PHASE_IMAGE

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img) \
    IppByteImage img; \
    IppDibToImage(m_Dib, img);

#define CONVERT_IMAGE_TO_DIB(img, dib) \
    IppDib dib; \
    IppImageToDib(img, dib);

// CIPP03Doc

IMPLEMENT_DYNCREATE(CIPP03Doc, CDocument)

BEGIN_MESSAGE_MAP(CIPP03Doc, CDocument)
	ON_COMMAND(ID_VIEW_HISTOGRAM, &CIPP03Doc::OnViewHistogram)
	ON_COMMAND(ID_HISTO_STRETCHING, &CIPP03Doc::OnHistoStretching)
	ON_COMMAND(ID_HISTO_EQUALIZATION, &CIPP03Doc::OnHistoEqualization)
	ON_COMMAND(ID_HISTO_LSHIFT, &CIPP03Doc::OnHistoLshift)
	ON_COMMAND(ID_HISTO_RSHIFT, &CIPP03Doc::OnHistoRshift)
	ON_COMMAND(ID_FOURIER_DFT, &CIPP03Doc::OnFourierDft)
	ON_COMMAND(ID_FOURIER_DFTRC, &CIPP03Doc::OnFourierDftrc)
	ON_COMMAND(ID_EDGE_SOBEL, &CIPP03Doc::OnEdgeSobel)
	ON_COMMAND(ID_GAUSSIAN, &CIPP03Doc::OnGaussian)
	ON_COMMAND(ID_FILTER_LAPLACIAN, &CIPP03Doc::OnFilterLaplacian)
	ON_COMMAND(ID_FILTER_LOG, &CIPP03Doc::OnFilterLog)
	ON_COMMAND(ID_FILTER_GOS, &CIPP03Doc::OnFilterGos)
	ON_COMMAND(ID_EDGE_CANNY, &CIPP03Doc::OnEdgeCanny)
	ON_COMMAND(ID_HOUGH_LINE, &CIPP03Doc::OnHoughLine)
	ON_COMMAND(ID_SEGMENT_BINARIZATION, &CIPP03Doc::OnSegmentBinarization)
	ON_COMMAND(ID_MORPHOLOGY_EROSION, &CIPP03Doc::OnMorphologyErosion)
	ON_COMMAND(ID_MORPHOLOGY_DILATION, &CIPP03Doc::OnMorphologyDilation)
	ON_COMMAND(ID_MORPHOLOGY_OPENING, &CIPP03Doc::OnMorphologyOpening)
	ON_COMMAND(ID_MORPHOLOGY_CLOSING, &CIPP03Doc::OnMorphologyClosing)
	ON_COMMAND(ID_GRAYMORPH_EROSION, &CIPP03Doc::OnGraymorphErosion)
	ON_COMMAND(ID_GRAYMORPH_DILATION, &CIPP03Doc::OnGraymorphDilation)
	ON_COMMAND(ID_GRAYMORPH_OPENING, &CIPP03Doc::OnGraymorphOpening)
	ON_COMMAND(ID_GRAYMORPH_CLOSING, &CIPP03Doc::OnGraymorphClosing)
END_MESSAGE_MAP()


// CIPP03Doc 생성/소멸

CIPP03Doc::CIPP03Doc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CIPP03Doc::~CIPP03Doc()
{
}

BOOL CIPP03Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	BOOL ret = TRUE;

	if (theApp.m_pNewDib == NULL)
	{

		CFileNewDlg dlg;
		if (dlg.DoModal() == IDOK)
		{
			if (dlg.m_nType == 0) // 그레이스케일 비트맵
				ret = m_Dib.CreateGrayBitmap(dlg.m_nWidth, dlg.m_nHeight);
			else // 트루컬러 비트맵
				ret = m_Dib.CreateRgbBitmap(dlg.m_nWidth, dlg.m_nHeight);
		}
		else
		{
			ret = FALSE;
		}
	}
	else
	{
		m_Dib = *(theApp.m_pNewDib);
		theApp.m_pNewDib = NULL;
	}

	return ret;

}




// CIPP03Doc serialization

void CIPP03Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CIPP03Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CIPP03Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CIPP03Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CIPP03Doc 진단

#ifdef _DEBUG
void CIPP03Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CIPP03Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CIPP03Doc 명령


BOOL CIPP03Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	return m_Dib.Save(CT2A(lpszPathName));
}


BOOL CIPP03Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	return m_Dib.Load(CT2A(lpszPathName));
}


void CIPP03Doc::OnViewHistogram()
{
	CHistogramDlg dlg;
	dlg.SetImage(&m_Dib);
	dlg.DoModal();
}


void CIPP03Doc::OnHistoStretching()
{
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
		IppHistogramStretching(img);
	CONVERT_IMAGE_TO_DIB(img, dib)
	AfxNewBitmap(dib);

}


void CIPP03Doc::OnHistoEqualization()
{
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
		IppHistogramEqualization(img);
	CONVERT_IMAGE_TO_DIB(img, dib)
	AfxNewBitmap(dib);
}


void CIPP03Doc::OnHistoLshift()
{
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
		IppHistogramLShift(img);
	CONVERT_IMAGE_TO_DIB(img, dib)

	AfxNewBitmap(dib);

}


void CIPP03Doc::OnHistoRshift()
{
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
		IppHistogramRShift(img);
	CONVERT_IMAGE_TO_DIB(img, dib)

		AfxNewBitmap(dib);
}


void CIPP03Doc::OnFourierDft()
{
	int w = m_Dib.GetWidth();
	int h = m_Dib.GetHeight();

	if (w * h > 128 * 128)
	{
		CString msg = _T("영상의 크기가 커서 시간이 오래 걸릴 수 있습니다.\n계속 하시겠습니까?");
		if (AfxMessageBox(msg, MB_OKCANCEL) != IDOK)
			return;
	}

	CWaitCursor wait;

	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)

		IppFourier fourier;
	fourier.SetImage(img);

	DWORD t1 = timeGetTime();
	fourier.DFT(1);

#ifdef SHOW_SPECTRUM_PHASE_IMAGE
	IppByteImage imgSpec;
	fourier.GetSpectrumImage(imgSpec);

	CONVERT_IMAGE_TO_DIB(imgSpec, dibSpec)
		AfxNewBitmap(dibSpec);

	IppByteImage imgPhase;
	fourier.GetPhaseImage(imgPhase);

	CONVERT_IMAGE_TO_DIB(imgPhase, dibPhase)
		AfxNewBitmap(dibPhase);
#endif

	fourier.DFT(-1);
	DWORD t2 = timeGetTime();

	IppByteImage img2;
	fourier.GetImage(img2);

	CONVERT_IMAGE_TO_DIB(img2, dib)
	AfxNewBitmap(dib);

}


void CIPP03Doc::OnFourierDftrc()
{
	int w = m_Dib.GetWidth();
	int h = m_Dib.GetHeight();

	if (w * h > 256 * 256)
	{
		CString msg = _T("영상의 크기가 커서 시간이 오래 걸릴 수 있습니다.\n계속 하시겠습니까?");
		if (AfxMessageBox(msg, MB_OKCANCEL) != IDOK)
			return;
	}

	CWaitCursor wait;

	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)

		IppFourier fourier;
	fourier.SetImage(img);

	DWORD t1 = timeGetTime();
	fourier.DFTRC(1);

#ifdef SHOW_SPECTRUM_PHASE_IMAGE
	IppByteImage imgSpec;
	fourier.GetSpectrumImage(imgSpec);

	CONVERT_IMAGE_TO_DIB(imgSpec, dibSpec)
		AfxNewBitmap(dibSpec);

	IppByteImage imgPhase;
	fourier.GetPhaseImage(imgPhase);

	CONVERT_IMAGE_TO_DIB(imgPhase, dibPhase)
		AfxNewBitmap(dibPhase);
#endif

	fourier.DFTRC(-1);
	DWORD t2 = timeGetTime();

	IppByteImage img2;
	fourier.GetImage(img2);

	CONVERT_IMAGE_TO_DIB(img2, dib)
	AfxNewBitmap(dib);
}


void CIPP03Doc::OnEdgeSobel()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
		IppByteImage imgEdge;
	Sobel(img, imgEdge);
	CONVERT_IMAGE_TO_DIB(imgEdge, dib)
	AfxNewBitmap(dib);

}


void CIPP03Doc::OnGaussian()
{
		CONVERT_DIB_TO_BYTEIMAGE(m_Dib, imgSrc)
			IppFloatImage imgDst;
		IppFilterGaussian(imgSrc, imgDst, 1.0);
		CONVERT_IMAGE_TO_DIB(imgDst, dib)
		AfxNewBitmap(dib);

}


void CIPP03Doc::OnFilterLaplacian()
{
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, imgSrc)
		IppByteImage imgDst;
	IppFilterLaplacian(imgSrc, imgDst);
	CONVERT_IMAGE_TO_DIB(imgDst, dib)
	AfxNewBitmap(dib);

}


void CIPP03Doc::OnFilterLog()
{
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, imgSrc)
		IppFloatImage imgDst;
	IppFilterLoG(imgSrc, imgDst, 1.0);
	CONVERT_IMAGE_TO_DIB(imgDst, dib)
		AfxNewBitmap(dib);


}


void CIPP03Doc::OnFilterGos()
{
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, imgSrc)
		IppFloatImage imgDst;
	IppFilterGoS(imgSrc, imgDst, 1.0);
	CONVERT_IMAGE_TO_DIB(imgDst, dib)
		AfxNewBitmap(dib);


}


void CIPP03Doc::OnEdgeCanny()
{
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
	IppByteImage imgEdge;
	IppEdgeCanny(img, imgEdge, 1.0, 30.0, 60.0);
	CONVERT_IMAGE_TO_DIB(imgEdge, dib)
	AfxNewBitmap(dib);
}


void CIPP03Doc::OnHoughLine()
{
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
		IppByteImage imgEdge;
	IppEdgeCanny(img, imgEdge, 1.4f, 30.f, 60.f);

	std::vector<IppLineParam> lines;
	IppHoughLine(imgEdge, lines);

	if (lines.size() == 0)
	{
		return;
	}

	std::sort(lines.begin(), lines.end());

	// 최대 10개의 직선만 화면에 그려줌.
	int cnt = __min(10, lines.size());
	for (int i = 0; i < cnt; i++)
		IppDrawLine(img, lines[i], 255);

	CONVERT_IMAGE_TO_DIB(img, dib)
		AfxNewBitmap(dib);
}


void CIPP03Doc::OnSegmentBinarization()
{

	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
	IppByteImage imgRes;
	IppBinarization(img, imgRes, 127);
	CONVERT_IMAGE_TO_DIB(imgRes, dib)
	AfxNewBitmap(dib);
}


void CIPP03Doc::OnMorphologyErosion()
{
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
	IppByteImage imgDst;
	IppMorphologyErosion(img, imgDst);
	CONVERT_IMAGE_TO_DIB(imgDst, dib)
	AfxNewBitmap(dib);
}


void CIPP03Doc::OnMorphologyDilation()
{
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
	IppByteImage imgDst;
	IppMorphologyDilation(img, imgDst);
	CONVERT_IMAGE_TO_DIB(imgDst, dib)
	AfxNewBitmap(dib);
}


void CIPP03Doc::OnMorphologyOpening()
{
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
	IppByteImage imgDst;
	IppMorphologyOpening(img, imgDst);
	CONVERT_IMAGE_TO_DIB(imgDst, dib)
	AfxNewBitmap(dib);
}


void CIPP03Doc::OnMorphologyClosing()
{
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
	IppByteImage imgDst;
	IppMorphologyClosing(img, imgDst);
	CONVERT_IMAGE_TO_DIB(imgDst, dib)
	AfxNewBitmap(dib);
}


void CIPP03Doc::OnGraymorphErosion()
{
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
	IppByteImage imgDst;
	IppMorphologyGrayErosion(img, imgDst);
	CONVERT_IMAGE_TO_DIB(imgDst, dib)
	AfxNewBitmap(dib);
}


void CIPP03Doc::OnGraymorphDilation()
{
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
	IppByteImage imgDst;
	IppMorphologyGrayDilation(img, imgDst);
	CONVERT_IMAGE_TO_DIB(imgDst, dib)
	AfxNewBitmap(dib);
}


void CIPP03Doc::OnGraymorphOpening()
{
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
	IppByteImage imgDst;
	IppMorphologyGrayOpening(img, imgDst);
	CONVERT_IMAGE_TO_DIB(imgDst, dib)
	AfxNewBitmap(dib);
}


void CIPP03Doc::OnGraymorphClosing()
{
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
	IppByteImage imgDst;
	IppMorphologyGrayClosing(img, imgDst);
	CONVERT_IMAGE_TO_DIB(imgDst, dib)
	AfxNewBitmap(dib);
}
