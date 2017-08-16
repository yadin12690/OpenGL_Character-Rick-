
// OpenGLDlg.h : header file
//

#pragma once

#include "GlView.h"


// COpenGLDlg dialog
class COpenGLDlg : public CDialogEx
{
// Construction
public:
	COpenGLDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENGL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CGlView* ptrView;
	
public:
	afx_msg void OnDeltaposMoveX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposMoveY2(NMHDR *pNMHDR, LRESULT *pResult);
	void loadContent();
	void saveContent();
	UINT_PTR moveTimer;
	bool moveON;


	afx_msg void OnBnClickedLoad();
	afx_msg void OnBnClickedSave();
	afx_msg void OnFileSave();
	afx_msg void OnFileLoad();
	afx_msg void OnBnClickedReset();
	afx_msg void OnDeltaposMoveZ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposMoveLeftHand(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposMoveRightHand(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposMoveProfile(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposMoveRightFoot(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposMoveRotateX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposMoveRotateZ(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposMoveLeftFoot(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedWink();
	afx_msg void OnBnClickedWalk();
	//afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
