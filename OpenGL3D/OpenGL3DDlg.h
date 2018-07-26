
// OpenGL3DDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "OGLObject.h"
class CRenderDlg;
#include "Scene.h"
// COpenGL3DDlg �Ի���
class COpenGL3DDlg : public CDialogEx
{
// ����
public:
	COpenGL3DDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENGL3D_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	// ���˵�
	CMenu m_appMainMenu;
	CRenderDlg* m_pRenderDlg; //��Ⱦ���򴰿�
	CScene m_scene;//����������
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
