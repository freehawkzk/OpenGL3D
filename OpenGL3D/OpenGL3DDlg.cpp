
// OpenGL3DDlg.cpp : 实现文件
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

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// COpenGL3DDlg 对话框



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


// COpenGL3DDlg 消息处理程序

BOOL COpenGL3DDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void COpenGL3DDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR COpenGL3DDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void COpenGL3DDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	//// TODO: 在此处添加消息处理程序代码

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
	// TODO: 在此添加命令处理程序代码
}


void COpenGL3DDlg::OnExit()
{
	// TODO: 在此添加命令处理程序代码
	OnCancel();
}


void COpenGL3DDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
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
