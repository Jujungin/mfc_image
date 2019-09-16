
// IP_ProgrammingView.cpp : CIP_ProgrammingView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "IP_Programming.h"
#endif

#include "IP_ProgrammingDoc.h"
#include "IP_ProgrammingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIP_ProgrammingView

IMPLEMENT_DYNCREATE(CIP_ProgrammingView, CScrollView)

BEGIN_MESSAGE_MAP(CIP_ProgrammingView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CIP_ProgrammingView 생성/소멸

CIP_ProgrammingView::CIP_ProgrammingView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CIP_ProgrammingView::~CIP_ProgrammingView()
{
}

BOOL CIP_ProgrammingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CIP_ProgrammingView 그리기

void CIP_ProgrammingView::OnDraw(CDC* pDC)
{
	CIP_ProgrammingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	if(pDoc->Image.m_pucBMP)
	{
		StretchDIBits(pDC->GetSafeHdc(),
			0, 0, pDoc->Image.m_uiWidth, pDoc->Image.m_uiHeight,
			0, 0, pDoc->Image.m_BMPheader.biWidth, pDoc->Image.m_BMPheader.biHeight,
			pDoc->Image.m_pucBMP, (LPBITMAPINFO)&pDoc->Image.m_BMPheader, DIB_RGB_COLORS, SRCCOPY);
	}
}

void CIP_ProgrammingView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	
	CIP_ProgrammingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) {
		sizeTotal.cx = sizeTotal.cy = 100;
	}
	else {
		sizeTotal.cx = pDoc->Image.m_uiWidth;
		sizeTotal.cy = pDoc->Image.m_uiHeight;
	}
	
	
	SetScrollSizes(MM_TEXT, sizeTotal);


	ResizeParentToFit(TRUE);
}


// CIP_ProgrammingView 인쇄

BOOL CIP_ProgrammingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CIP_ProgrammingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CIP_ProgrammingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CIP_ProgrammingView 진단

#ifdef _DEBUG
void CIP_ProgrammingView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CIP_ProgrammingView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CIP_ProgrammingDoc* CIP_ProgrammingView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIP_ProgrammingDoc)));
	return (CIP_ProgrammingDoc*)m_pDocument;
}
#endif //_DEBUG


// CIP_ProgrammingView 메시지 처리기
