
// ɨ�׸���.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cɨ�׸���App: 
// �йش����ʵ�֣������ ɨ�׸���.cpp
//

class Cɨ�׸���App : public CWinApp
{
public:
	Cɨ�׸���App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cɨ�׸���App theApp;