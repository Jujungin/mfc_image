
// IP_P03Doc.h: CIPP03Doc 클래스의 인터페이스
//


#pragma once
#include ".\IppImage\IppDib.h"

class CIPP03Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CIPP03Doc();
	DECLARE_DYNCREATE(CIPP03Doc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CIPP03Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	IppDib m_Dib;
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	afx_msg void OnViewHistogram();
	afx_msg void OnHistoStretching();
	afx_msg void OnHistoEqualization();
	afx_msg void OnHistoLshift();
	afx_msg void OnHistoRshift();
	afx_msg void OnFourierDft();
	afx_msg void OnFourierDftrc();
	afx_msg void OnEdgeSobel();
	afx_msg void OnGaussian();
	afx_msg void OnFilterLaplacian();
	afx_msg void OnFilterLog();
	afx_msg void OnFilterGos();
	afx_msg void OnEdgeCanny();
	afx_msg void OnHoughLine();
	afx_msg void OnSegmentBinarization();
	afx_msg void OnMorphologyErosion();
	afx_msg void OnMorphologyDilation();
	afx_msg void OnMorphologyOpening();
	afx_msg void OnMorphologyClosing();
	afx_msg void OnGraymorphErosion();
	afx_msg void OnGraymorphDilation();
	afx_msg void OnGraymorphOpening();
	afx_msg void OnGraymorphClosing();
};
