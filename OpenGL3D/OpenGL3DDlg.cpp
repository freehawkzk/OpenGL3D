
// OpenGL3DDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OpenGL3D.h"
#include "OpenGL3DDlg.h"
#include "afxdialogex.h"
#include "RenderDlg.h"
#include "OGLObject.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//OGLObject g_oglobj;

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
	: CDialogEx(IDD_OPENGL3D_DIALOG, pParent),m_pRenderDlg(NULL)
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
//	ON_WM_CREATE()
	ON_WM_DESTROY()
//	ON_WM_SIZE()
//	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_SETTING, &COpenGL3DDlg::OnSetting)
	ON_COMMAND(ID_EXIT, &COpenGL3DDlg::OnExit)
	ON_WM_SIZE()
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
	m_appMainMenu.LoadMenuW(IDR_APP_MAIN_MENU);
	SetMenu(&m_appMainMenu);



	m_pRenderDlg = new CRenderDlg;
	m_pRenderDlg->Create(IDD_RENDERDLG, this);
	RECT rt;
	GetClientRect(&rt);
	rt.left += 5;
	rt.right -= 5;
	rt.top += 5;
	rt.bottom -= 5;
	m_pRenderDlg->m_pSence = &m_scene;
	m_pRenderDlg->MoveWindow(&rt,TRUE);
	m_pRenderDlg->ShowWindow(SW_NORMAL);

	OGLObject* pObj = new COGLPoint;
	pObj->SetUp();
	m_scene.m_vObjs.push_back(pObj);

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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR COpenGL3DDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void COpenGL3DDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	//// TODO: �ڴ˴������Ϣ����������

	m_pRenderDlg->SendMessage(WM_CLOSE, 0, 0);
	
	if (m_pRenderDlg)
	{
		delete m_pRenderDlg;
		m_pRenderDlg = NULL;
	}

	if (m_scene.m_vObjs.size() > 0)
	{
		for (int i = 0; i < m_scene.m_vObjs.size(); i++)
		{
			delete m_scene.m_vObjs[i];
			m_scene.m_vObjs[i] = NULL;
		}
		m_scene.m_vObjs.clear();
	}
}


void COpenGL3DDlg::OnSetting()
{
	// TODO: �ڴ���������������
}


void COpenGL3DDlg::OnExit()
{
	// TODO: �ڴ���������������
	OnCancel();
}


void COpenGL3DDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (m_pRenderDlg)
	{
		RECT rt;
		GetClientRect(&rt);
		rt.left += 5;
		rt.right -= 5;
		rt.top += 5;
		rt.bottom -= 5;
		m_pRenderDlg->MoveWindow(&rt, TRUE);
	}
}
