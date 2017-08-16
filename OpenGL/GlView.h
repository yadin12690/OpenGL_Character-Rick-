// GlView.h: interface for the CGlView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLVIEW_H__6EDA23AE_B764_11D5_8D52_0004AC3DB799__INCLUDED_)
#define AFX_GLVIEW_H__6EDA23AE_B764_11D5_8D52_0004AC3DB799__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <gl/GLAUX.H> 
//#include <GLAUX.H> //Header File For The glaux Library

#define SIZE 2

class CGlView
{
public:
	CGlView(CWnd *pclWnd);
	~CGlView();

	void vDrawGLScene();

protected:
private:
	void vInitGl(int iWidth, int iHeigth);
	BOOL bSetWindowPixelFormat(HDC hDC);
	BOOL bCreateViewGLContext(HDC hDC);

	// members //////////////////////////////////////////////////////////
public:
protected:
private:
	HGLRC	m_hGLContext;	// required GLContext
	CWnd *m_pclWnd;			// window inwhich opengl will be drawn
	HDC		m_hDC;			// handle to m_pclWnds device context
	float moveX, moveY, moveZ, moveLeftHand, moveRightHand, moveProfile, moveRightFoot, moveLeftFoot, moveRotX, moveRotZ,wink;
	bool addMoves;
public:
	UINT_PTR myTimer = 0;

	float getMoveX();
	float getMoveY();
	float getMoveZ();
	float getMoveLeftHand();
	float getMoveRightHand();
	float getMoveProfile();
	float getMoveRightFoot();
	float getMoveLeftFoot();
	float getMoveRotX();
	float getMoveRotZ();
	float getWink();
	bool getAddMoves();

	void setAddMoves(bool addMoves);
	void setWink(float wink);
	void setMoveRotZ(float moveRotZ);
	void setMoveRotX(float moveRotX);
	void setMoveRightFoot(float moveRightFoot);
	void setMoveLeftFoot(float moveLeftFoot);
	void setMoveProfile(float moveProfile);
	void setMoveLeftHand(float moveLeftHand);
	void setMoveRightHand(float moveRightHand);
	void setMoveX(float moveX);
	void setMoveY(float moveY);
	void setMoveZ(float moveZ);
	void generateTextureFromImageFile();
private:
	GLuint idTexture[SIZE];
	AUX_RGBImageRec* texture;
};

#endif

