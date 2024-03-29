
// IP_P03View.cpp: CIPP03View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "IP_P03.h"
#endif

#include "IP_P03Doc.h"
#include "IP_P03View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIPP03View

IMPLEMENT_DYNCREATE(CIPP03View, CScrollView)

BEGIN_MESSAGE_MAP(CIPP03View, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CIPP03View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CIPP03View 생성/소멸

CIPP03View::CIPP03View()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CIPP03View::~CIPP03View()
{
}

BOOL CIPP03View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CIPP03View 그리기

void CIPP03View::OnDraw(CDC* pDC)
{
	CIPP03Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (pDoc->m_Dib.IsValid())
		pDoc->m_Dib.Draw(pDC->m_hDC);
}

void CIPP03View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	CIPP03Doc* pDoc = GetDocument();
	if (pDoc->m_Dib.IsValid())
	{
		sizeTotal.cx = pDoc->m_Dib.GetWidth();
		sizeTotal.cy = pDoc->m_Dib.GetHeight();
	}
	else
	{
		sizeTotal.cx = sizeTotal.cy = 100;
	}

	SetScrollSizes(MM_TEXT, sizeTotal);

	ResizeParentToFit(TRUE);
}


// CIPP03View 인쇄


void CIPP03View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CIPP03View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CIPP03View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CIPP03View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CIPP03View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CIPP03View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CIPP03View 진단

#ifdef _DEBUG
void CIPP03View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CIPP03View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CIPP03Doc* CIPP03View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIPP03Doc)));
	return (CIPP03Doc*)m_pDocument;
}
#endif //_DEBUG


// CIPP03View 메시지 처리기
