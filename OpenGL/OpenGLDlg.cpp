
// OpenGLDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGL.h"
#include "OpenGLDlg.h"
#include "afxdialogex.h"
#include "SaveLoadFile.h"

#include <fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// COpenGLDlg dialog



COpenGLDlg::COpenGLDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_OPENGL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpenGLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COpenGLDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//	ON_NOTIFY(UDN_DELTAPOS, IDC_MOVEX, &COpenGLDlg::OnDeltaposMovex)
	//ON_NOTIFY(UDN_DELTAPOS, IDC_MOVEX, &COpenGLDlg::OnDeltaposMovex)
	ON_NOTIFY(UDN_DELTAPOS, IDC_MOVE_X, &COpenGLDlg::OnDeltaposMoveX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_MOVE_Y2, &COpenGLDlg::OnDeltaposMoveY2)
	ON_BN_CLICKED(IDC_LOAD, &COpenGLDlg::OnBnClickedLoad)
	ON_BN_CLICKED(IDC_SAVE, &COpenGLDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_RESET, &COpenGLDlg::OnBnClickedReset)
	ON_NOTIFY(UDN_DELTAPOS, IDC_MOVE_Z, &COpenGLDlg::OnDeltaposMoveZ)
	ON_NOTIFY(UDN_DELTAPOS, IDC_MOVE_LEFT_HAND, &COpenGLDlg::OnDeltaposMoveLeftHand)
	ON_NOTIFY(UDN_DELTAPOS, IDC_MOVE_RIGHT_HAND, &COpenGLDlg::OnDeltaposMoveRightHand)
	ON_NOTIFY(UDN_DELTAPOS, IDC_MOVE_PROFILE, &COpenGLDlg::OnDeltaposMoveProfile)
	ON_NOTIFY(UDN_DELTAPOS, IDC_MOVE_RIGHT_FOOT, &COpenGLDlg::OnDeltaposMoveRightFoot)
	ON_NOTIFY(UDN_DELTAPOS, IDC_MOVE_ROTATE_X, &COpenGLDlg::OnDeltaposMoveRotateX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_MOVE_ROTATE_Z, &COpenGLDlg::OnDeltaposMoveRotateZ)
	ON_NOTIFY(UDN_DELTAPOS, IDC_MOVE_LEFT_FOOT, &COpenGLDlg::OnDeltaposMoveLeftFoot)
	ON_BN_CLICKED(IDC_WINK, &COpenGLDlg::OnBnClickedWink)
	ON_BN_CLICKED(IDC_WALK, &COpenGLDlg::OnBnClickedWalk)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// COpenGLDlg message handlers

BOOL COpenGLDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//ptrView = new CGlView(this);
	CWnd* wnd = GetDlgItem(IDC_PICTURE);
	ptrView = new CGlView(wnd);

	moveON = false;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COpenGLDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COpenGLDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();

		ptrView->vDrawGLScene();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COpenGLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void COpenGLDlg::OnDeltaposMoveX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	// TODO: Add your control notification handler code here
	ptrView->setMoveX(ptrView->getMoveX() - 0.5*pNMUpDown->iDelta);
	ptrView->vDrawGLScene();

	*pResult = 0;
}


void COpenGLDlg::OnDeltaposMoveY2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	ptrView->setMoveY(ptrView->getMoveY() - 0.5*pNMUpDown->iDelta);
	ptrView->vDrawGLScene();

	*pResult = 0;
}


void COpenGLDlg::OnDeltaposMoveZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	ptrView->setMoveZ(ptrView->getMoveZ() - 0.5*pNMUpDown->iDelta);
	ptrView->vDrawGLScene();

	*pResult = 0;
}

void COpenGLDlg::loadContent()
{
	CFileDialog dlg(true);
	//dlg.DoModal();

	ifstream inFile("SavedCoords.txt");

	//float temp;
	//inFile >> temp;
	//ptrView->setMoveX(temp);
	//inFile >> temp;
	//ptrView->setMoveY(temp);

	/*
	float temp;
	inFile.read((char*)(&temp), sizeof(float));
	ptrView->setMoveX(temp);
	inFile.read((char*)(&temp), sizeof(float));
	ptrView->setRotY(temp);
	*/

	SaveLoadFile loadFile;
	inFile.read((char*)(&loadFile), sizeof(SaveLoadFile));
	ptrView->setMoveX(loadFile.moveX);
	ptrView->setMoveY(loadFile.moveY);
	ptrView->setMoveZ(loadFile.moveZ);
	ptrView->setMoveLeftHand(loadFile.moveLeftHand);
	ptrView->setMoveRightHand(loadFile.moveRightHand);
	ptrView->setMoveLeftFoot(loadFile.moveLeftFoot);
	ptrView->setMoveRightFoot(loadFile.moveRightFoot);
	ptrView->setMoveProfile(loadFile.moveProfile);
	ptrView->setMoveRotX(loadFile.moveRotX);
	ptrView->setMoveRotZ(loadFile.moveRotZ);

	inFile.close();
	ptrView->vDrawGLScene();
}
void COpenGLDlg::saveContent()
{
	// dlg(false);
	//dlg.DoModal();

	ofstream outFile("SavedCoords.txt");

	/*outFile << ptrView->getMoveX() << "\n";
	outFile << ptrView->getMoveY();*/

	/*
	float temp = ptrView->getMoveX();
	outFile.write((char*)(&temp), sizeof(float));
	temp = ptrView->getRotY();
	outFile.write((char*)(&temp), sizeof(float));
	*/

	SaveLoadFile saveFile;
	saveFile.moveX = ptrView->getMoveX();
	saveFile.moveY = ptrView->getMoveY();
	saveFile.moveZ = ptrView->getMoveZ();
	saveFile.moveLeftHand = ptrView->getMoveLeftHand();
	saveFile.moveRightHand = ptrView->getMoveRightHand();
	saveFile.moveLeftFoot = ptrView->getMoveLeftFoot();
	saveFile.moveRightFoot = ptrView->getMoveRightFoot();
	saveFile.moveProfile = ptrView->getMoveProfile();
	saveFile.moveRotX = ptrView->getMoveRotX();
	saveFile.moveRotZ = ptrView->getMoveRotZ();
	outFile.write((char*)(&saveFile), sizeof(SaveLoadFile));

	outFile.close();
}


void COpenGLDlg::OnBnClickedLoad()
{
	loadContent();
}


void COpenGLDlg::OnBnClickedSave()
{
	saveContent();
}

void COpenGLDlg::OnFileSave()
{
	saveContent();
}


void COpenGLDlg::OnFileLoad()
{
	loadContent();
}


void COpenGLDlg::OnBnClickedReset()
{
	ptrView->setMoveX(0);
	ptrView->setMoveY(0);
	ptrView->setMoveZ(0);
	ptrView->setMoveLeftHand(-90);
	ptrView->setMoveRightHand(90);
	ptrView->setMoveRightFoot(90);
	ptrView->setMoveLeftFoot(90);
	ptrView->setMoveProfile(0);
	ptrView->setMoveRotX(0);
	ptrView->setMoveRotZ(0);
	KillTimer(moveTimer);
	PlaySoundA((LPCSTR)NULL, NULL, SND_ASYNC);//הפסקת מוזיקה
	getchar();
	ptrView->vDrawGLScene();
}


void COpenGLDlg::OnDeltaposMoveLeftHand(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	ptrView->setMoveLeftHand(ptrView->getMoveLeftHand() - 0.5*pNMUpDown->iDelta);
	ptrView->vDrawGLScene();

	*pResult = 0;
}


void COpenGLDlg::OnDeltaposMoveRightHand(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	ptrView->setMoveRightHand(ptrView->getMoveRightHand() - 0.5*pNMUpDown->iDelta);
	ptrView->vDrawGLScene();

	*pResult = 0;
}


void COpenGLDlg::OnDeltaposMoveProfile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	ptrView->setMoveProfile(ptrView->getMoveProfile() - 0.5*pNMUpDown->iDelta);
	ptrView->vDrawGLScene();

	*pResult = 0;
}


void COpenGLDlg::OnDeltaposMoveRightFoot(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	ptrView->setMoveRightFoot(ptrView->getMoveRightFoot() - 0.5*pNMUpDown->iDelta);
	ptrView->vDrawGLScene();

	*pResult = 0;
}


void COpenGLDlg::OnDeltaposMoveRotateX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	ptrView->setMoveRotX(ptrView->getMoveRotX() - 0.5*pNMUpDown->iDelta);
	ptrView->vDrawGLScene();

	*pResult = 0;
}


void COpenGLDlg::OnDeltaposMoveRotateZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	ptrView->setMoveRotZ(ptrView->getMoveRotZ() - 0.5*pNMUpDown->iDelta);
	ptrView->vDrawGLScene();

	*pResult = 0;
}


void COpenGLDlg::OnDeltaposMoveLeftFoot(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	ptrView->setMoveLeftFoot(ptrView->getMoveLeftFoot() - 0.5*pNMUpDown->iDelta);
	ptrView->vDrawGLScene();

	*pResult = 0;
}


void COpenGLDlg::OnBnClickedWink()
{

	PlaySoundA((LPCSTR)"\Cartoon_Ding_Sound_Effect.wav", NULL, SND_ASYNC);//הפעלת מוזיקה
	getchar();

	ptrView->setWink(0.45f);
	ptrView->vDrawGLScene();
	Sleep(500);
	ptrView->setWink(1);
	ptrView->vDrawGLScene();
}


void COpenGLDlg::OnBnClickedWalk()
{
	if (!(moveON))
	{
		PlaySoundA((LPCSTR)"\Footsteps_Sound_Effect_Royalty_Free_.wav", NULL, SND_ASYNC);//הפעלת סאונד
		getchar();

		moveTimer = SetTimer(1, 200, NULL);
		moveON = true;
	}
	else
	{
		PlaySoundA((LPCSTR)NULL, NULL, SND_ASYNC);//הפסקת סאונד
		getchar();


		KillTimer(moveTimer);
		moveON = false;
	}
}


void COpenGLDlg::OnTimer(UINT_PTR nIDEvent)
{
	CDialogEx::OnTimer(nIDEvent);
	if (nIDEvent == moveTimer)
	{
		if (ptrView->getAddMoves())
		{
			ptrView->setMoveRightFoot(ptrView->getMoveRightFoot() + 5);
			ptrView->setMoveLeftFoot(ptrView->getMoveLeftFoot() - 5);
			ptrView->vDrawGLScene();
			ptrView->setAddMoves(false);
		}
		else
		{
			ptrView->setMoveLeftFoot(ptrView->getMoveLeftFoot() + 5);
			ptrView->setMoveRightFoot(ptrView->getMoveRightFoot() - 5);
			ptrView->vDrawGLScene();
		}
	}
}
