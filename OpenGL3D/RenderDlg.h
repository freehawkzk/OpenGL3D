#pragma once


// CRenderDlg 对话框
class CScene;
class CRenderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRenderDlg)

public:
	CRenderDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRenderDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RENDERDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:


	HGLRC m_hRC;    //RC 绘图上下文
	CDC* m_pDC;        //DC 设备上下文
	CScene* m_pSence;
public:
	BOOL InitOpenGL(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	BOOL SetupPixelFormat();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
};
