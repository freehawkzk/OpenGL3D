
// OpenGL3DDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "OGLObject.h"
class CRenderDlg;
#include "Scene.h"
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
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
//	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);


	afx_msg void OnSetting();
	afx_msg void OnExit();
	
public:
	// 主菜单
	CMenu m_appMainMenu;
	CRenderDlg* m_pRenderDlg; //渲染区域窗口
	CScene m_scene;//场景管理器
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
