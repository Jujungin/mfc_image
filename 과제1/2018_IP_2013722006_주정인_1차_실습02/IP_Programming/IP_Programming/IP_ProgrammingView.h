
// IP_ProgrammingView.h : CIP_ProgrammingView Ŭ������ �������̽�
//

#pragma once


class CIP_ProgrammingView : public CScrollView
{
protected: // serialization������ ��������ϴ�.
	CIP_ProgrammingView();
	DECLARE_DYNCREATE(CIP_ProgrammingView)

// Ư���Դϴ�.
public:
	CIP_ProgrammingDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CIP_ProgrammingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // IP_ProgrammingView.cpp�� ����� ����
inline CIP_ProgrammingDoc* CIP_ProgrammingView::GetDocument() const
   { return reinterpret_cast<CIP_ProgrammingDoc*>(m_pDocument); }
#endif

