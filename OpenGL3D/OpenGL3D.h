
// OpenGL3D.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// COpenGL3DApp: 
// �йش����ʵ�֣������ OpenGL3D.cpp
//

class COpenGL3DApp : public CWinApp
{
public:
	COpenGL3DApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern COpenGL3DApp theApp;