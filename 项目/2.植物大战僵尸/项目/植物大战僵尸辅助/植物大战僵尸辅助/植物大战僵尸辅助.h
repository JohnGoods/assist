
// ֲ���ս��ʬ����.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cֲ���ս��ʬ����App: 
// �йش����ʵ�֣������ ֲ���ս��ʬ����.cpp
//

class Cֲ���ս��ʬ����App : public CWinApp
{
public:
	Cֲ���ս��ʬ����App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cֲ���ս��ʬ����App theApp;