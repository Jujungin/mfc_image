
// IP_Programming.h : IP_Programming ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CIP_ProgrammingApp:
// �� Ŭ������ ������ ���ؼ��� IP_Programming.cpp�� �����Ͻʽÿ�.
//

class CIP_ProgrammingApp : public CWinApp
{
public:
	CIP_ProgrammingApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CIP_ProgrammingApp theApp;
