#pragma once


// CFileOpenDlg 대화 상자입니다.

class CFileOpenDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFileOpenDlg)

public:
	CFileOpenDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CFileOpenDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG1 };

	UINT GetWidth() { return m_DlgWidth; };
	UINT GetHeight() { return m_DlgHeight; };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
private:
	UINT m_DlgWidth;
	UINT m_DlgHeight;
};
