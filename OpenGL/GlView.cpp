// GlView.cpp: implementation of the CGlView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GlView.h"

#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGlView::CGlView(CWnd *pclWnd)
	: moveX(0)
	, moveY(0)
	, moveZ(0)
	, moveLeftHand(-90)
	, moveRightHand(90)
	, moveProfile(0)
	, moveRotX(0)
	, moveRotZ(0)
	, moveRightFoot(90)
	, moveLeftFoot(90)
	, wink(1)
{
	m_pclWnd = pclWnd;
	m_hDC = GetDC(pclWnd->m_hWnd);
	BOOL bSuccess;

	RECT rect;
	m_pclWnd->GetClientRect(&rect);
	int iWidth = rect.right - rect.left;
	int iHeight = rect.bottom - rect.top;

	bSuccess = bSetWindowPixelFormat(m_hDC);
	ASSERT(&bSuccess);

	bSuccess = bCreateViewGLContext(m_hDC);
	ASSERT(&bSuccess);

	vInitGl(iWidth, iHeight);
}

// +
// *****************************************************************************
//   Module      :  CGlView::~CGlView()
//   Access      :  Public
//   Input       :  None
//   Output      :  None
//   Return Val  :  None
//   Exceptions  :  None
//   Desc        :  This function is the one and only destructor. It provides
//									clean up and performs any needed shutdown procedures
//
//   Notes       :  None
// *****************************************************************************
// -
CGlView::~CGlView()
{
	// make the rendering context not current
	if (wglGetCurrentContext() != NULL)
		wglMakeCurrent(NULL, NULL);

	// delete the Context
	if (m_hGLContext != NULL)
	{
		wglDeleteContext(m_hGLContext);
		m_hGLContext = NULL;
	}
}


// +
// *****************************************************************************
//   Module      :  void CGlView::DrawGLScene()	
//   Access      :  Public
//   Input       :  None
//   Output      :  None
//   Return Val  :  None
//   Exceptions  :  None
//   Desc        :  This function is called contiously to provide realtime OpenGl
//									drawing
//
//   Notes       :  Place all reatime rendering code here
// *****************************************************************************
// -
void CGlView::vDrawGLScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(0, 0.0f, -10.02f); //הזזת תמונת רקע--טקסטורה
	//glTranslatef(0.0f, 0.0f, -10.02f);//מרחק של הדמות מהמסך
	


	//For Texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, idTexture[0]);
	glBegin(GL_QUADS);
	//glColor3f(1, 1, 1);

	//פינה שמאלית תחתונה 
	glTexCoord2f(0, 0);//מאיזה נקודה בתמונת המקור
	glVertex3f(-6, -4.5, 0);//ומאיפה להתחיל להדביק בתמונת היעד
							//פינה שמאלית עליונה
	glTexCoord2f(0, 1);
	glVertex3f(-6, 4.5, 0);
	//פינה ימנית עליונה
	glTexCoord2f(1, 1);
	glVertex3f(6, 4.5, 0);
	//פינה ימנית תחתונה
	glTexCoord2f(1, 0);
	glVertex3f(6, -4.5, 0);
	glEnd();
	//End texture
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	glTranslatef(1, 0.0f, -10.02f);//הזזת מרחק הדמות מהמסך

	//Enable color and light effects
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);


	//Profile View ---Rotate Y
	glRotatef(moveProfile, 0, 1, 0);

	//Rotate X
	glRotatef(moveRotX, 1, 0, 0);

	//Rotate Z
	glRotatef(moveRotZ, 0, 0, 1);

	//הזזת צירים
	glTranslatef(moveX, moveY, moveZ);

	////Axes
	//glBegin(GL_LINES);
	////x  RED
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glVertex3f(-3.0f, 0.0f, 0.0f);
	//glVertex3f(3.0f, 0.0f, 0.0f);
	////y  GREEN 
	//glColor3f(0.0f, 1.0f, 0.0f);
	//glVertex3f(0.0f, -3.0f, 0.0f);
	//glVertex3f(0.0f, 3.0f, 0.0f);
	////z  BLUE
	//glColor3f(0.0f, 0.0f, 1.0f);
	//glVertex3f(0.0f, 0.0f, -3.0f);
	//glVertex3f(0.0f, 0.0f, 3.0f);
	//glEnd();


	GLUquadricObj* obj;
	obj = gluNewQuadric();

	gluQuadricTexture(obj, true);
	glRotatef(-90, 1, 0, 0);//axis(0,0,0) z up

	glColor3f(0.2f, 0.8f, 0.0f);
	glRotatef(90, 1, 0, 0);//axis(0,0,0) z toward us
	glColor3f(0.623529, 0.623529, 0.372549);

	glPushMatrix();
	gluSphere(obj, 1.1, 32, 32);//ראש

	glColor3f(0, 0, 0);
	glScalef(1, 0.5, 1);//כיווץ עבור האף על ציר ואי
	glTranslatef(-0.1, -0.8, 1.0);
	gluPartialDisk(obj, 0.15f, 0.25f, 64, 64, 0, 180);//ציור האף

	glPopMatrix();


	//Eyebrow --- Middle head
	glPushMatrix();
	glTranslatef(0.0f, 0.35f, 0.75f);
	//glRotatef(-90,0, 1, 0);//axis(0,0,0) z down
	glScalef(1.5, 0.2, 1.0);//כיווץ
	glColor3f(0.2f, 0.8f, 0.8f);
	gluSphere(obj, 0.4, 15, 5);//שיער
	glPopMatrix();


	//Right Eye
	glPushMatrix();
	glTranslatef(0.45f, -0.2f, 0.85f);
	glColor3f(1, 1, 1);// White
	glScalef(1, wink, 1);
	gluSphere(obj, 0.32, 32, 32);//עין ימין

	glColor3f(0, 0, 0);
	glTranslatef(0, 0, 0.25f);
	gluPartialDisk(obj, 0.25, 0.27, 64, 64, 0, 360);
	glPopMatrix();


	//Inside Right Eye
	glPushMatrix();
	glTranslatef(0.45f, -0.2f, 1.0f);
	glColor3f(0, 0, 0); //Black
	glScalef(1, wink, 1);
	gluSphere(obj, 0.20, 32, 32);//עין ימין
	glPopMatrix();

	//Left Eye
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-0.45f, -0.2f, 0.85f);
	gluSphere(obj, 0.32, 32, 32);//עין שמאל
	//Left eye frame
	glColor3f(0, 0, 0);
	glTranslatef(0, 0, 0.25f);
	gluPartialDisk(obj, 0.25, 0.27, 64, 64, 0, 360);
	glPopMatrix();//axis(0,0,0) z toward us

	//Inside Left Eye
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(-0.45f, -0.2f, 1.0f);
	gluSphere(obj, 0.20, 32, 32);//עין שמאל
	glPopMatrix();//axis(0,0,0) z toward us


	//Smile - OLD
	//glPushMatrix();
	//glScalef(4.2, 0.5, 1);//כיווץ
	//glTranslatef(0.0f, -1.4f, 0.96f);
	//glColor3f(0, 0, 0); //Black Color
	//gluSphere(obj, 0.065, 16, 16);//עין שמאל
	//glPopMatrix();

	//Smile - (Partial Disk)
	glPushMatrix();
	glTranslatef(0.0f, -0.69f, 0.92f);
	glColor3f(0, 0, 0); //Black Color
	glScalef(2, 0.4, 1);//כשיש גרפס 0.4 משתנה ל-0.7
	gluDisk(obj, 0.09, 0.18, 32, 32);
	glPopMatrix();


	//Body
	glPushMatrix();
	glRotatef(90, 1, 0, 0);//axis(0,0,0) z down
	glColor3f(1, 1, 1);
	gluCylinder(obj, 0.5, 0.8, 2.7, 64, 64);//גוף
	glRotatef(-90, 1, 0, 0);//axis(0,0,0) z toward us
	glPopMatrix();

	//חלוק
	glPushMatrix();
	glTranslatef(0.0f, -0.90, 0.43f);//location
	glRotatef(90, 1, 0, 0);//axis(0,0,0) z down
	glColor3f(0, 1, 1);
	gluCylinder(obj, 0.29, 0.45, 1.8, 16, 16);//חלוק
	glPopMatrix();

	//Hair--Right
	glPushMatrix();
	glScalef(1.0, 0.5, 1);//כיווץ
	glRotatef(90, 1, 5, 0);//axis(0,0,0) z down
	glColor3f(0.2f, 0.8f, 0.8f);
	gluCylinder(obj, 1, 0, 2, 10, 10);
	glRotatef(-90, 0, 0, 0);//axis(0,0,0) z toward us
	glPopMatrix();

	//hair (Right)
	glPushMatrix();
	glScalef(1.0, 0.5, 1);//כיווץ
	glRotatef(90, 1, 1, 0);//axis(0,0,0) z down
	glColor3f(0.2f, 0.8f, 0.8f);
	gluCylinder(obj, 1, 0, 2, 10, 10);
	glRotatef(-90, 0, 0, 0);//axis(0,0,0) z toward us
	glPopMatrix();

	//Left Hair
	glPushMatrix();
	glScalef(1.0, 0.5, 1);//כיווץ
	glRotatef(-85, 1, 5, 0);//axis(0,0,0) z down
	glColor3f(0.2f, 0.8f, 0.8f);
	gluCylinder(obj, 1, 0, 2, 10, 10);
	glRotatef(-90, 0, 0, 0);//axis(0,0,0) z toward us
	glPopMatrix();

	//More Hair --left
	glPushMatrix();
	glTranslatef(0.2, 0.4, 0); //מיקום על המסך
	glRotatef(83, 0, 1, 0);//axis(0,0,0) z down
	glColor3f(0.2f, 0.8f, 0.8f);
	gluCylinder(obj, 0.5, 0, 1.4, 10, 10);
	glPopMatrix();

	//Hair
	glPushMatrix();
	glScalef(1.0, 0.5, 1);//כיווץ
	glRotatef(-80, 5, 5, 0);//axis(0,0,0) z down
	glColor3f(0.2f, 0.8f, 0.8f);
	gluCylinder(obj, 1, 0, 2, 10, 10);
	glRotatef(-90, 0, 0, 0);//axis(0,0,0) z toward us
	glPopMatrix();

	//hair2
	glPushMatrix();
	glScalef(1.0, 0.3, 1);//כיווץ
	glTranslatef(0, 1.5, 0); //מיקום על המסך
	glRotatef(-80, 5, 5, 0);//axis(0,0,0) z down
	glColor3f(0.2f, 0.8f, 0.8f);
	gluCylinder(obj, 1, 0, 2, 10, 10);
	glPopMatrix();


	//hair3
	glPushMatrix();
	glTranslatef(0.5, 0.9, 0); //מיקום על המסך
	glRotatef(-90, 1, 0, 0.3);//axis(0,0,0) z down
	glColor3f(0.2f, 0.8f, 0.8f);
	gluCylinder(obj, 0.3, 0, 1, 10, 10);
	glPopMatrix();

	//Middle Hair
	glPushMatrix();
	glTranslatef(0, 0.9, 0); //מיקום על המסך
	glRotatef(-90, 1, 0, 0);//axis(0,0,0) z down
	glColor3f(0.2f, 0.8f, 0.8f);
	gluCylinder(obj, 0.3, 0, 1, 10, 10);
	glPopMatrix();

	//Hand1(Right) --WITH MOVE 
	glPushMatrix();
	glScalef(1.0, 0.5, 1);//כיווץ
	glTranslatef(0.35, -2.3, 0.1); //מיקום על המסך
	glRotatef(moveRightHand, 9, 45, 0);//זווית
	glColor3f(1, 1, 1);
	gluCylinder(obj, 0.3, 0.3, 2, 7, 7);//יד
	glTranslatef(0, 0, 1.7); //מיקום על המסך
	glRotatef(moveRightHand, 1, 1, 0);//זווית
	glColor3f(0.623529, 0.623529, 0.372549);
	gluSphere(obj, 0.5, 10, 10);//עיגול של היד
	glPopMatrix();


	//Hand2(Left) -- WITH MOVE
	glPushMatrix();
	glScalef(1.0, 0.5, 1);//כיווץ
	/////LEFT(-)RIGTH(+)//LOW(-)HEIGH(+)//FAR(-)CLOSE(+)
	glTranslatef(-0.3, -2.3, 0.1); //מיקום על המסך
	glRotatef(moveLeftHand, 9, 19, 0);//axis(0,0,0) z down //זווית
	glColor3f(1, 1, 1);
	gluCylinder(obj, 0.3, 0.3, 2, 7, 7);//יד			
	glTranslatef(0, 0, 2); //מיקום על המסך
	glRotatef(moveLeftHand, 9, 19, 0);//axis(0,0,0) z down //זווית
	glColor3f(0.623529, 0.623529, 0.372549);
	gluSphere(obj, 0.5, 10, 10);//עיגול של היד
	glPopMatrix();


	//Foot(right)--WITH MOVE
	glPushMatrix();
	glScalef(0.8, 0.5, 1);//כיווץ
	glTranslatef(0.55, -5.1, 0); //מיקום על המסך
	glRotatef(moveRightFoot, 1, 0, 0);//axis(0,0,0) z down //זווית
	glColor3f(0.55f, 0.47f, 0.14f);
	gluCylinder(obj, 0.3, 0.3, 2, 7, 7);//רגל
	glColor3f(1, 1, 1);
	glTranslatef(0, 0, 2.15); //מיקום על המסך
	//glRotatef(-moveRightFoot, 1, 0, 0);//axis(0,0,0) z down //זווית
	gluSphere(obj, 0.5, 10, 10);//עיגול של הרגל
	glPopMatrix();


	//Foot(left)-- WORKED WITH MOVE 
	glPushMatrix();
	glScalef(0.8, 0.5, 1);//כיווץ
	glTranslatef(-0.49, -5.1, 0); //מיקום על המסך
	glRotatef(moveLeftFoot, 1, 0, 0);//axis(0,0,0) z down //זווית
	glColor3f(0.55f, 0.47f, 0.14f);
	gluCylinder(obj, 0.3, 0.3, 2, 7, 7);//רגל
	glColor3f(1, 1, 1);
	glTranslatef(0, 0, 2.15); //מיקום על המסך
	gluSphere(obj, 0.5, 10, 10);//עיגול של הרגל
	glPopMatrix();


	//Disable color and light effects
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	gluDeleteQuadric(obj);

	//swap the buffer
	SwapBuffers(m_hDC);
}

// +
// *****************************************************************************
//   Module      :  BOOL CGlView::SetWindowPixelFormat(HDC hDC)
//   Access      :  Private
//   Input       :  hDC - Handle to the GL windwos device context
//   Output      :  None
//   Return Val  :  TRUE  - success
//									FALSE - failure
//   Exceptions  :  None
//   Desc        :  This function sets up the required pixelformat descriptor
//
//   Notes       :  None
// *****************************************************************************
// -
BOOL CGlView::bSetWindowPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc;

	pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion = 1;

	pixelDesc.dwFlags =

		PFD_DRAW_TO_WINDOW |// Format Must Support Window
		PFD_SUPPORT_OPENGL |// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,	// Must Support Double Buffering
		PFD_TYPE_RGBA,		// Request An RGBA Format
		32,					// Select A 16Bit Color Depth
		0, 0, 0, 0, 0, 0,	// Color Bits Ignored (?)
		0,					// No Alpha Buffer
		0,					// Shift Bit Ignored (?)
		0,					// No Accumulation Buffer
		0, 0, 0, 0,			// Accumulation Bits Ignored (?)
		16,					// 16Bit Z-Buffer (Depth Buffer)  
		0,					// No Stencil Buffer
		0,					// No Auxiliary Buffer (?)
		PFD_MAIN_PLANE,		// Main Drawing Layer
		0,					// Reserved (?)
		0, 0, 0;			// Layer Masks Ignored (?)

	int iGLPixelIndex = ChoosePixelFormat(hDC, &pixelDesc);
	ASSERT(&iGLPixelIndex);

	if (SetPixelFormat(hDC, iGLPixelIndex, &pixelDesc))
		return false;

	return TRUE;
}

// +
// *****************************************************************************
//   Module      :  BOOL CGlView::CreateViewGLContext(HDC hDC)
//   Access      :  Private
//   Input       :  hDC - Handle to the GL windwos device context
//   Output      :  None
//   Return Val  :  TRUE  - success
//									FALSE - failure
//   Exceptions  :  None
//   Desc        :  This function sets up the required GLContext
//
//   Notes       :  None
// *****************************************************************************
// -
BOOL CGlView::bCreateViewGLContext(HDC hDC)
{
	m_hGLContext = wglCreateContext(hDC);
	if (m_hGLContext == NULL)
		return FALSE;

	if (wglMakeCurrent(hDC, m_hGLContext) == FALSE)
		return FALSE;

	return TRUE;
}

// +
// *****************************************************************************
//   Module      :  void CGlView::InitGl(int iWidth, int iHeigth)
//   Access      :  Private
//   Input       :  iWidth  - width of the window
//									iHeight - height of the window
//   Output      :  None
//   Return Val  :  None
//   Exceptions  :  None
//   Desc        :  This function initializes all OpenGL rendering specifics
//
//   Notes       :  None
// *****************************************************************************
// -
void CGlView::vInitGl(int iWidth, int iHeigth)
{
	glShadeModel(GL_SMOOTH);
	//glClearColor(0.0f, 0.0f, 0.0f, 0.5f); //Dialog Backgroung = Black
	glClearColor(1.0f, 1.0f, 1.0f, 0.5f); //Dialog Backgroung = White
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glViewport(0, 0, iWidth, iHeigth);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)iWidth / (GLfloat)iHeigth, 0.45f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	generateTextureFromImageFile();
}

void CGlView::generateTextureFromImageFile()
{
	glGenTextures(SIZE, idTexture);

	const char* imageFileName[SIZE] = { "images\\Rick.bmp", "images\\env.bmp" };

	for (int i = 0; i < SIZE; i++)
	{
		texture = auxDIBImageLoadA(imageFileName[i]);//loads the width, height, colors from the image file (*.bmp) into opengl structure (AUX_RGBImageRec).

		if (texture)
		{
			glBindTexture(GL_TEXTURE_2D, idTexture[i]);//working on idTexture[i]
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//if the target is smaller than the source then minimize it using LINEAR algorithm.
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//if the target is bigger than the source then maximize it using LINEAR algorithm.
			glTexImage2D(GL_TEXTURE_2D, 0, 3, texture->sizeX, texture->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture->data);//save texture in memory.
			free(texture);
			texture = NULL;
		}
	}
}


float CGlView::getMoveX()
{

	return moveX;
}

float CGlView::getMoveY()
{
	return moveY;
}

float CGlView::getMoveZ()
{
	return moveZ;
}

float CGlView::getMoveLeftHand()
{
	return moveLeftHand;
}

float CGlView::getMoveRightHand()
{
	return moveRightHand;
}

float CGlView::getMoveProfile()
{
	return moveProfile;
}

float CGlView::getMoveRightFoot()
{
	return moveRightFoot;
}

float CGlView::getMoveLeftFoot()
{
	return moveLeftFoot;
}

float CGlView::getMoveRotX()
{
	return moveRotX;
}

float CGlView::getMoveRotZ()
{
	return moveRotZ;
}

float CGlView::getWink()
{
	return wink;
}

bool CGlView::getAddMoves()
{
	return addMoves;
}


void CGlView::setMoveX(float moveX)
{
	this->moveX = moveX;
}

void CGlView::setMoveY(float moveY)
{
	this->moveY = moveY;
}

void CGlView::setMoveZ(float moveZ)
{
	if (moveZ < 5 && moveZ >-1.5)
	{
		this->moveZ = moveZ;
	}
}

void CGlView::setMoveLeftHand(float moveLeftHand)
{
	if (moveLeftHand < -40 && moveLeftHand > -105)
	{
		this->moveLeftHand = moveLeftHand;
	}
}

void CGlView::setMoveRightHand(float moveRightHand)
{
	if (moveRightHand < 105 && moveRightHand >40)
	{
		this->moveRightHand = moveRightHand;
	}
}

void CGlView::setMoveProfile(float moveProfile)
{
	this->moveProfile = moveProfile;
}

void CGlView::setMoveRightFoot(float moveRightFoot)
{
	if (moveRightFoot > 30 && moveRightFoot < 100)
	{
		this->moveRightFoot = moveRightFoot;
	}
	setAddMoves(true);
}

void CGlView::setMoveLeftFoot(float moveLeftFoot)
{
	if (moveLeftFoot > 30 && moveLeftFoot < 100)
	{
		this->moveLeftFoot = moveLeftFoot;
	}
	setAddMoves(true);
}

void CGlView::setMoveRotX(float moveRotX)
{
	this->moveRotX = moveRotX;
}

void CGlView::setMoveRotZ(float moveRotZ)
{
	this->moveRotZ = moveRotZ;
}

void CGlView::setWink(float wink)
{
	this->wink = wink;
}


void CGlView::setAddMoves(bool addMoves)
{
	this->addMoves = addMoves;
}