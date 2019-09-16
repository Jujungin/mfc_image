
// IP_ProgrammingDoc.h : CIP_ProgrammingDoc Ŭ������ �������̽�
//


#pragma once

#include "FileOpenDlg.h"
#include "IP_ProgrammingMyClass.h"

class CIP_ProgrammingDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CIP_ProgrammingDoc();
	DECLARE_DYNCREATE(CIP_ProgrammingDoc)

// Ư���Դϴ�.
public:
	CIP_ProgrammingMyClass Image;
// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CIP_ProgrammingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
};
