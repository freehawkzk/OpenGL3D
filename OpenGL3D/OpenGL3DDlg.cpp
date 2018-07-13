
// OpenGL3DDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OpenGL3D.h"
#include "OpenGL3DDlg.h"
#include "afxdialogex.h"

#include "OGLObject.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

OGLObject g_oglobj;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// COpenGL3DDlg �Ի���



COpenGL3DDlg::COpenGL3DDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_OPENGL3D_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpenGL3DDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COpenGL3DDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// COpenGL3DDlg ��Ϣ�������

BOOL COpenGL3DDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	g_oglobj.SetUp();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void COpenGL3DDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void COpenGL3DDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//CDialogEx::OnPaint();


		// �����ɫ����Ȼ���
		::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//���������Ⱦ����
		g_oglobj.Render();
		// Flush����Ⱦ��ˮ��
		::glFinish();
		// ����ǰ�󻺴���
		::SwapBuffers(m_pDC->GetSafeHdc());
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR COpenGL3DDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int COpenGL3DDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	InitializeOpenGL();
	return 0;
}


void COpenGL3DDlg::OnDestroy()
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
		delete m_pDC;
	}
	//Set it to NULL
	m_pDC = NULL;
}


void COpenGL3DDlg::OnSize(UINT nType, int cx, int cy)
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
}


BOOL COpenGL3DDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;
//	return CDialogEx::OnEraseBkgnd(pDC);
}


BOOL COpenGL3DDlg::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ����ר�ô����/����û���
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CDialogEx::PreCreateWindow(cs);
}

BOOL COpenGL3DDlg::InitializeOpenGL()
{
	//�ͻ������DC
	m_pDC = new CClientDC(this);
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

BOOL  COpenGL3DDlg::SetupPixelFormat()
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
	int m_nPixelFormat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);
	if (m_nPixelFormat == 0)
	{
		return FALSE;
	}
	if (::SetPixelFormat(m_pDC->GetSafeHdc(), m_nPixelFormat, &pfd) == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}