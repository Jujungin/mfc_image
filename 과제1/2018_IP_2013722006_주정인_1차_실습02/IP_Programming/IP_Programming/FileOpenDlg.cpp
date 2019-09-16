// FileOpenDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "IP_Programming.h"
#include "FileOpenDlg.h"
#include "afxdialogex.h"


// CFileOpenDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CFileOpenDlg, CDialogEx)

CFileOpenDlg::CFileOpenDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFileOpenDlg::IDD, pParent)
	, m_DlgWidth(0)
	, m_DlgHeight(0)
{

}

CFileOpenDlg::~CFileOpenDlg()
{
}

void CFileOpenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_DlgWidth);
	DDX_Text(pDX, IDC_EDIT2, m_DlgHeight);
}


BEGIN_MESSAGE_MAP(CFileOpenDlg, CDialogEx)
END_MESSAGE_MAP()


// CFileOpenDlg 메시지 처리기입니다.
