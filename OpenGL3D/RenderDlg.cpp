// RenderDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OpenGL3D.h"
#include "RenderDlg.h"
#include "afxdialogex.h"
#include "Scene.h"

// CRenderDlg �Ի���

IMPLEMENT_DYNAMIC(CRenderDlg, CDialogEx)

CRenderDlg::CRenderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RENDERDLG, pParent),m_pDC(NULL),m_pSence(NULL)
{

}

CRenderDlg::~CRenderDlg()
{
}

void CRenderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRenderDlg, CDialogEx)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CRenderDlg ��Ϣ�������


BOOL CRenderDlg::InitOpenGL(CDC* pDC)
{
	m_pDC = pDC;// CClientDC(this);
								 //Failure to Get DC
	if (m_pDC == NULL)
	{
		MessageBox(L"Error Obtaining DC");
		return FALSE;
	}
	//ΪDC�������ظ�ʽ
	if (!SetupPixelFormat())
	{
		return FALSE;
	}
	//���� RC
	m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc());
	//Failure to Create Rendering Context
	if (m_hRC == 0)
	{
		MessageBox(L"Error Creating RC");
		return FALSE;
	}
	//�趨OpenGL��ǰ�̵߳���Ⱦ������
	//�Ժ�����߳����е�OpenGL���ö��������hdc��ʶ���豸�ϻ��ơ�
	if (::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC) == FALSE)
	{
		MessageBox(L"Error making RC Current");
		return FALSE;
	}

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}

	//������ɫ
	::glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//��Ȼ��� 1������κζ�����ʾ����
	::glClearDepth(1.0f);
	//���ͨ���ȽϺ����ֵ�����仯�ˣ�����и�����Ȼ������Ĳ���
	::glEnable(GL_DEPTH_TEST);
	return TRUE;
}

int CRenderDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	m_pDC = GetDC();
	if (m_pDC)
	{
		BOOL hr = InitOpenGL(m_pDC);
		if (!hr)
		{
			ReleaseDC(m_pDC);
			m_pDC = NULL;
		}
	}
	
	return 0;
}


void CRenderDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	if (::wglMakeCurrent(0, 0) == FALSE)
	{
		MessageBox(L"Could not make RC non-current");
	}

	//Delete the rendering context
	if (::wglDeleteContext(m_hRC) == FALSE)
	{
		MessageBox(L"Could not delete RC");
	}
	//Delete the DC
	if (m_pDC)
	{
		ReleaseDC(m_pDC);
	}
	//Set it to NULL
	m_pDC = NULL;
}


void CRenderDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	GLdouble aspect_ratio; // width/height ratio

	if (0 >= cx || 0 >= cy)
	{
		return;
	}
	// select the full client area
	::glViewport(0, 0, cx, cy);
	// compute the aspect ratio
	// this will keep all dimension scales equal
	aspect_ratio = (GLdouble)cx / (GLdouble)cy;
	// select the projection matrix and clear it
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	// select the viewing volume
	::gluPerspective(45.0f, aspect_ratio, .01f, 200.0f);

	// switch back to the modelview matrix and clear it
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();

	Invalidate();
}


BOOL CRenderDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return TRUE;//CDialogEx::OnEraseBkgnd(pDC);
}


BOOL CRenderDlg::SetupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
		1,                              // version number
		PFD_DRAW_TO_WINDOW |            // support window
		PFD_SUPPORT_OPENGL |            // support OpenGL
		PFD_DOUBLEBUFFER,                // double buffered
		PFD_TYPE_RGBA,                  // RGBA type
		24,                             // 24-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // no alpha buffer
		0,                              // shift bit ignored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ignored
		16,                             // 16-bit z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	};
	int nPixelFormat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);
	if (nPixelFormat == 0)
	{
		return FALSE;
	}
	if (::SetPixelFormat(m_pDC->GetSafeHdc(), nPixelFormat, &pfd) == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}


BOOL CRenderDlg::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ����ר�ô����/����û���
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CDialogEx::PreCreateWindow(cs);
}


void CRenderDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
					   // �����ɫ����Ȼ���
	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//���������Ⱦ����
	if (m_pSence)
	{
		m_pSence->Render();
	}
	//g_oglobj.Render();
	// Flush����Ⱦ��ˮ��
	::glFinish();
	// ����ǰ�󻺴���
	::SwapBuffers(m_pDC->GetSafeHdc());
}


void CRenderDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case 0:
		//Invalidate();
		break;
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


BOOL CRenderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//SetTimer(0, 50, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CRenderDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnClose();
}
