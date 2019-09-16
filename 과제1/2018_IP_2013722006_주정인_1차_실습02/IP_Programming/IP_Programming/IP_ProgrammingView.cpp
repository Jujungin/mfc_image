
// IP_ProgrammingView.cpp : CIP_ProgrammingView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CIP_ProgrammingView ����/�Ҹ�

CIP_ProgrammingView::CIP_ProgrammingView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CIP_ProgrammingView::~CIP_ProgrammingView()
{
}

BOOL CIP_ProgrammingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CScrollView::PreCreateWindow(cs);
}

// CIP_ProgrammingView �׸���

void CIP_ProgrammingView::OnDraw(CDC* pDC)
{
	CIP_ProgrammingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
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
	// TODO: �� ���� ��ü ũ�⸦ ����մϴ�.
	
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


// CIP_ProgrammingView �μ�

BOOL CIP_ProgrammingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CIP_ProgrammingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CIP_ProgrammingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CIP_ProgrammingView ����

#ifdef _DEBUG
void CIP_ProgrammingView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CIP_ProgrammingView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CIP_ProgrammingDoc* CIP_ProgrammingView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIP_ProgrammingDoc)));
	return (CIP_ProgrammingDoc*)m_pDocument;
}
#endif //_DEBUG


// CIP_ProgrammingView �޽��� ó����
