// FileOpenDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "IP_Programming.h"
#include "FileOpenDlg.h"
#include "afxdialogex.h"


// CFileOpenDlg ��ȭ �����Դϴ�.

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


// CFileOpenDlg �޽��� ó�����Դϴ�.
