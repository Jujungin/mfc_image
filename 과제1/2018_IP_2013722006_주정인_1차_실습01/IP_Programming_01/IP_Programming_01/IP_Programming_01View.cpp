
// IP_Programming_01View.cpp: CIPProgramming01View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "IP_Programming_01.h"
#endif

#include "IP_Programming_01Doc.h"
#include "IP_Programming_01View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIPProgramming01View

IMPLEMENT_DYNCREATE(CIPProgramming01View, CScrollView)

BEGIN_MESSAGE_MAP(CIPProgramming01View, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CIPProgramming01View 생성/소멸

CIPProgramming01View::CIPProgramming01View()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CIPProgramming01View::~CIPProgramming01View()
{
}

BOOL CIPProgramming01View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CIPProgramming01View 그리기

void CIPProgramming01View::OnDraw(CDC* /*pDC*/)
{
	CIPProgramming01Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}

void CIPProgramming01View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CIPProgramming01View 인쇄

BOOL CIPProgramming01View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CIPProgramming01View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CIPProgramming01View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CIPProgramming01View 진단

#ifdef _DEBUG
void CIPProgramming01View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CIPProgramming01View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CIPProgramming01Doc* CIPProgramming01View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIPProgramming01Doc)));
	return (CIPProgramming01Doc*)m_pDocument;
}
#endif //_DEBUG


// CIPProgramming01View 메시지 처리기
