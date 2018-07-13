
// OpenGL3DDlg.h : 头文件
//

#pragma once


// COpenGL3DDlg 对话框
class COpenGL3DDlg : public CDialogEx
{
// 构造
public:
	COpenGL3DDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENGL3D_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	HGLRC m_hRC;    //RC 绘图上下文
	CDC* m_pDC;        //DC 设备上下文
	BOOL InitializeOpenGL();    //初始化 OpenGL
	BOOL SetupPixelFormat();    //为 DC 建立像素格式
};
