#pragma once


// CFileOpenDlg ��ȭ �����Դϴ�.

class CFileOpenDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFileOpenDlg)

public:
	CFileOpenDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CFileOpenDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };

	UINT GetWidth() { return m_DlgWidth; };
	UINT GetHeight() { return m_DlgHeight; };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
private:
	UINT m_DlgWidth;
	UINT m_DlgHeight;
};
