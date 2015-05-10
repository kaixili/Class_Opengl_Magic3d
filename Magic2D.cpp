/*
*		Filename:   Magic2D.cpp
*		Function:   Init and Creat Window and GL Program
*				    ��ʼ��������Windows���ںͻ���GLͼ��
*		Author:	    �ϣ  U201414093
*				    ���пƼ���ѧ ����1401
*		Time:	    2015-5
*		Remarks:	Thanks to Jeff Molofee and his Tutorial.This Code Was First Created By Him In 2000 (Visit his Site At nehe.gamedev.net)
*					And I Used His Code For Creating Magic2D Main Window.
*		License:	LGPL
*/

#include "Magic2D.h"

HDC			hDC = NULL;			// Private GDI Device Context
HGLRC		hRC = NULL;			// Permanent Rendering Context
HWND		hWnd = NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;			// Holds The Instance Of The Application

bool		keys[256];			// �洢���̰���״̬
bool		active = TRUE;		// ���ڼ���״̬
bool		fullscreen = FALSE;	// ȫ��״̬

GLfloat		xrot;				// /
GLfloat		yrot;				// /
GLfloat		zrot;				// ����ͷ��תƫ����

GLboolean	ROT = TRUE;			// ��ͷ��ת״̬
GLint		RandomShuffle = TRUE;	// ����/��ԭ״̬
int			step[MAXSTEP];		// �洢���Ҳ������ڻ�ԭ
int			step_count ;		// ���Ҳ���

//GLUquadricObj *g_text;			

GLfloat RX;						// /
GLfloat RY;						// ����ͷƽ��ƫ����

GLuint	texture[30];			// �洢����

GLfloat XPos;		
GLfloat YPos;
GLfloat XPosMove;
GLfloat YPosMove;
GLboolean Lbutton = 0;
GLboolean Rbutton = 0;

LRESULT	 CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
GLvoid	 ReSizeGLScene(GLsizei width, GLsizei height);
GLvoid	 KillGLWindow(GLvoid);
BOOL	 CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag);

// ��ʼ��GL>�������� ���� ͼƬ ����
int InitGL(GLvoid)
{
	if (!LoadAllTextures()) return FALSE;
	InitENstring();
	Init_model();
	char buffer10[50];
	step_count = 0;
	step[step_count] = 0;

	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);	 			// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	return TRUE;										
}

// ��ID�Ż�������
void DrawCube(int ID, int face1, int face2, int face3, int face4, int face5, int face6)
{
	stPoint *CubePoint = Cube[ID].CubePoint;
	/*
	*				  * * * * * * * *
	*				*	��  	  * *
	*			  *				*	*
	*			* * * * * * * *		*
	*			*			  *	��  *
	*			*			  *		*
	*		 /\	*			  *		*
	*	    *	*			  *	  *	
	*	  *		*    ǰ 	  *	*
	*	*		* * * * * * * *
	*
	*/
	// �����
	glBindTexture(GL_TEXTURE_2D, texture[face1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(CubePoint[0].p);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(CubePoint[1].p);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(CubePoint[2].p);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(CubePoint[3].p);
	glEnd();
	// ǰ����
	face2 ? (glBindTexture(GL_TEXTURE_2D, texture[face2])) : (glBindTexture(GL_TEXTURE_2D, texture[0]));
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(CubePoint[4].p);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(CubePoint[5].p);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(CubePoint[6].p);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(CubePoint[7].p);
	glEnd();
	// �ϱ���
	face3? (glBindTexture(GL_TEXTURE_2D, texture[face3])) : (glBindTexture(GL_TEXTURE_2D, texture[0]));
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(CubePoint[5].p);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(CubePoint[3].p);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(CubePoint[2].p);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(CubePoint[6].p);
	glEnd();
	// �±���	
	face4?glBindTexture(GL_TEXTURE_2D, texture[face4]) :(glBindTexture(GL_TEXTURE_2D, texture[0]));
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(CubePoint[4].p);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(CubePoint[7].p);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(CubePoint[1].p);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(CubePoint[0].p);
	glEnd();
	// �����
	face5 ? glBindTexture(GL_TEXTURE_2D, texture[face5]) : (glBindTexture(GL_TEXTURE_2D, texture[0]));;
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(CubePoint[7].p);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(CubePoint[6].p);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(CubePoint[2].p);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(CubePoint[1].p);
	glEnd();
	// �ұ���
	face6 ? glBindTexture(GL_TEXTURE_2D, texture[face6]) : (glBindTexture(GL_TEXTURE_2D, texture[0]));;
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(CubePoint[4].p);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(CubePoint[0].p);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(CubePoint[3].p);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(CubePoint[5].p);
	glEnd();
}

void DrawBackground()
{
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-18.6f, -18.6f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(18.6f, -18.6f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(18.6f, 18.6f);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(-18.6f, 18.6f);
	glEnd();
	//
}

// ����GL������
int DrawGLScene(GLvoid)				
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glLoadIdentity();										//������Ұλ��
	glTranslatef(0.0f, 0.0f, -12.0f);
//
	selectFont(36, ANSI_CHARSET, "MS Gothic");
	glColor3f(0.914f, 0.251f, 0.365f);
	glRasterPos2f(-6.4f, 3.2f);
	drawCNString("����OpenGL��2dħ��");
	selectFont(32, ANSI_CHARSET, "DFKai-SB");
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(-6.2f, 2.75f);
	drawCNString("���ߣ��ϣ U201414093");
	glRasterPos2f(-6.2f, 2.40f);
	drawCNString("      ����1401");
	glRasterPos2f(-6.2f, 2.0f);
	drawCNString("ʱ�䣺2015-5");

	selectFont(36, ANSI_CHARSET, "Trebuchet MS"); 
	glRasterPos2f(-5.2f, 1.60f);
	if (RandomShuffle == 1)  drawCNString("���������");
	if (RandomShuffle == 0)  drawCNString("���ڻ�ԭ");
	if (RandomShuffle == -1) drawCNString("��F3������ת");
	
	/*		// ����DeBug
	char buffer1[50], buffer2[50], buffer3[50], buffer4[50], buffer5[50], buffer6[50], buffer7[50], buffer8[70], buffer9[50], buffer10[50];
	glRasterPos2f(-5.2f,-2.00f); drawCNString(buffer9);*/
	
//
	glColor3f(1, 1, 1);										// �ر�glClolor����ɫ״̬
	
	glTranslatef(0.0f, 0.0f, -12.0f);

	glTranslatef(0.0f, 0.0f, -6.0f);
	DrawBackground();
	glTranslatef(0.0f, 0.0f, 6.0f);

	glTranslatef(RX, 0.0f, 0.0f);							// ��תƽ���ӽ�
	glTranslatef(0.0, RY, 0.0);

	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glRotatef(zrot, 0.0f, 0.0f, 1.0f);
	
								// ����ħ����
	
	DrawCube( 0, 0, 7, 0, 1, 27, 27);
	DrawCube( 1, 0, 8, 0, 2, 1, 1);
	DrawCube( 2, 0, 9, 0, 3, 2, 2);
	DrawCube( 3, 0, 5, 0, 0, 3, 3);
	DrawCube( 4, 0, 6, 0, 0, 4, 4);
	DrawCube( 5, 0, 7, 0, 0, 5, 5);
	DrawCube( 6, 0, 1, 7, 0, 3, 3);
	DrawCube( 7, 0, 2, 8, 0, 7, 7);
	DrawCube( 8, 0, 3, 9, 0, 8, 8);

	DrawCube( 9, 0, 0, 0, 4, 9, 9);
	DrawCube(10, 0, 0, 0, 5,10,10);
	DrawCube(11, 0, 0, 0, 6,11,11);
	DrawCube(12, 0, 0, 0, 0,12,12);
	DrawCube(13, 0, 0, 0, 0,13,13);
	DrawCube(14, 0, 0, 0, 0,14,14);
	DrawCube(15, 0, 0, 4, 0, 2, 2);
	DrawCube(16, 0, 0, 5, 0,16,16);
	DrawCube(17, 0, 0, 6, 0,17,17);

	DrawCube(18, 9, 0, 0, 7,18,18);
	DrawCube(19, 8, 0, 0, 8,19,19);
	DrawCube(20, 7, 0, 0, 9,20,20);
	DrawCube(21, 6, 0, 0, 0,21,21);
	DrawCube(22, 5, 0, 0, 0,22,22);
	DrawCube(23, 4, 0, 0, 0,23,23);
	DrawCube(24, 3, 0, 1, 0, 1, 1);
	DrawCube(25, 2, 0, 2, 0,25,25);
	DrawCube(26, 1, 0, 3, 0,26,26);
	
	
	//
	

	if (ROT)
	{
		xrot += 0.20f;
		yrot += 0.10f;
		zrot += 0.20f;
	}
	return TRUE;										
}

// GL���ڳ���>�رմ���
GLvoid KillGLWindow(GLvoid)								// ��ȷ�رմ���
{
	if (fullscreen)										// ȫ��״̬ʱ
	{
		ChangeDisplaySettings(NULL, 0);					// ��������
		ShowCursor(TRUE);								// ��ʾ���
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))				// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;									// Set hInstance To NULL
	}
}

// ����GL���ڳߴ�
GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		
{
	if (height == 0)									// ��ֹ�߶ȱ���Ϊ0
	{
		height = 1;										
	}
	glViewport(0, 0, width, height);					// ���õ�ǰ�ӽǷ�Χ

	glMatrixMode(GL_PROJECTION);						// ����ͶӰ�ӽ�
	glLoadIdentity();									

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f); // ͸���ӽ�����(�Ӿ���)

	glMatrixMode(GL_MODELVIEW);							// �����Ӿ�������þ���
	glLoadIdentity();									// ��λ��λ�þ���
}

// GL���ڳ���>�������� Created By NeHe
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;			// Set Left Value To 0
	WindowRect.right = (long)width;		// Set Right Value To Requested Width
	WindowRect.top = (long)0;				// Set Top Value To 0
	WindowRect.bottom = (long)height;		// Set Bottom Value To Requested Height

	fullscreen = fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = hInstance;							// Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground = NULL;									// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu
	wc.lpszClassName = "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight = height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "Magic 2D Info", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle = WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
		"OpenGL",							// Class Name
		title,								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		WindowRect.right - WindowRect.left,	// Calculate Window Width
		WindowRect.bottom - WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen



	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}


// �ص����������WIN�¼���������ת״̬��rotX��rotY��rotZ; ��ذ���
LRESULT CALLBACK WndProc(
	HWND	hWnd,			// ���ھ��
	UINT	uMsg,			// ������Ӧ��Ϣ
	WPARAM	wParam,			// ������Ϣ
	LPARAM	lParam			// �����Ϣ
	)			
{
	switch (uMsg)								// Check For Windows Messages
	{
	case WM_ACTIVATE:							// Watch For Window Activate Message
	{
		if (!HIWORD(wParam))					// Check Minimization State
		{
			active = TRUE;						// Program Is Active
		}
		else
		{
			active = FALSE;						// Program Is No Longer Active
		}

		return 0;								// Return To The Message Loop
	}

	case WM_SYSCOMMAND:							// Intercept System Commands
	{
		switch (wParam)							// Check System Calls
		{
		case SC_SCREENSAVE:						// Screensaver Trying To Start?
		case SC_MONITORPOWER:					// Monitor Trying To Enter Powersave?
			return 0;							// Prevent From Happening
		}
		break;									// Exit
	}
	
	

	/*����������϶���Ұ*/
	/*case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	{
		
	}
	case WM_MOUSEMOVE:
		if (wParam & MK_LBUTTON && iCount < MAXPOINTS)
		{
		pt[iCount].x = LOWORD(lParam);
		pt[iCount++].y = HIWORD(lParam);
		hdc = GetDC(hwnd);
		SetPixel(hdc, LOWORD(lParam), HIWORD(lParam), 0);
		ReleaseDC(hwnd, hdc);
		}
	{
		if (wParam & MK_LBUTTON)
		{
			if (Lbutton == 1)
			{
				XPosMove -= LOWORD(lParam);
				YPosMove -= HIWORD(lParam);
			}
		}
		
		int angle, elev;
		angle = (GLdouble)LOWORD(lParam) / 1280.0*2.0*3.14;
		elev = (GLdouble)HIWORD(lParam) / 800.0*3.14 - 3.14 / 2.0;
		if (LOWORD(lParam) >= 1279)
			SetCursorPos(2, HIWORD(lParam));
		else if (LOWORD(lParam) <= 1)
			SetCursorPos(1278, HIWORD(lParam));
		return 0;
	return 0;

	}*/
		

	case WM_CLOSE:								
	{
		PostQuitMessage(0);						
		return 0;								
	}

	case WM_KEYDOWN:							
	{
		keys[wParam] = TRUE;					
		return 0;								
	}

	case WM_KEYUP:								
	{
		keys[wParam] = FALSE;					
		return 0;								
	}

	case WM_SIZE:								
	{
		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
		return 0;								
	}
	//case WM_TIMER:
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);  // Pass All Unhandled Messages To DefWindowProc
}


// �ص�����>��ʱ��>���������ת�¼�
VOID CALLBACK TimerShuffle(
	HWND hwnd,			 // Windows Timer Message ���
	UINT uMsg,			 // ���ܵ� WM_TIMER message
	UINT idEvent,		 // ��ʱ�����
	DWORD dwTime		 // ��ǰʱ��
	)
{
	if ((idEvent == 2) && (RandomShuffle == 1))
	{
		srand(dwTime);
		int  r = rand();

		if (r % 18 == 0)
		{
			enable_X1_roatate(1);
		}
		else if (r % 18 == 1)
		{
			enable_Y1_roatate(1);
		}
		else if (r % 18 == 2)
		{
			enable_Z1_roatate(1);
		}
		else if (r % 18 == 3)
		{
			enable_X1_roatate(-1);
		}
		else if (r % 18 == 4)
		{
			enable_Y1_roatate(-1);
		}
		else if (r % 18 == 5)
		{
			enable_Z1_roatate(-1);
		}
		else if (r % 18 == 6)
		{
			enable_X2_roatate(1);
		}
		else if (r % 18 == 7)
		{
			enable_Y2_roatate(1);
		}
		else if (r % 18 == 8)
		{
			enable_Z2_roatate(1);
		}
		else if (r % 18 == 9)
		{
			enable_X2_roatate(-1);
		}
		else if (r % 18 == 10)
		{
			enable_Y2_roatate(-1);
		}
		else if (r % 18== 11)
		{
			enable_Z2_roatate(-1);
		}
		else if (r % 18 == 12)
		{
			enable_X3_roatate(1);
		}
		else if (r % 18 == 13)
		{
			enable_Y3_roatate(1);
		}
		else if (r % 18 == 14)
		{
			enable_Z3_roatate(1);
		}
		else if (r % 18 == 15)
		{
			enable_X3_roatate(-1);
		}
		else if (r % 18 == 16)
		{
			enable_Y3_roatate(-1);
		}
		else if (r % 18== 17)
		{
			enable_Z3_roatate(-1);
		}
	}
}


// �ص�����>��ʱ��>���ٻ�ԭħ��
VOID CALLBACK TimeRestore(
	HWND	hwnd,		 // Windows Timer Message ���
	UINT	uMsg,		 // ���ܵ� WM_TIMER message
	UINT	idEvent,	 // ��ʱ�����
	DWORD	dwTime		 // ��ǰʱ��
	)
{
	if (RandomShuffle == 1) return;
	if ((idEvent == 3) && (RandomShuffle == 0))
	{
		switch (step[step_count - 1])
		{

		case X1_ROTATE_L:
			enable_X1_roatate(-1);
			break;
		case X1_ROTATE_R:
			enable_X1_roatate(1);
			break;
		case Y1_ROTATE_L:
			enable_Y1_roatate(-1);
			break;
		case Y1_ROTATE_R:
			enable_Y1_roatate(1);
			break;
		case Z1_ROTATE_L:
			enable_Z1_roatate(-1);
			break;
		case Z1_ROTATE_R:
			enable_Z1_roatate(1);
			break;
		case X2_ROTATE_L:
			enable_X2_roatate(-1);
			break;
		case X2_ROTATE_R:
			enable_X2_roatate(1);
			break;
		case Y2_ROTATE_L:
			enable_Y2_roatate(-1);
			break;
		case Y2_ROTATE_R:
			enable_Y2_roatate(1);
			break;
		case Z2_ROTATE_L:
			enable_Z2_roatate(-1);
			break;
		case Z2_ROTATE_R:
			enable_Z2_roatate(1);
			break;
		case X3_ROTATE_L:
			enable_X3_roatate(-1);
			break;
		case X3_ROTATE_R:
			enable_X3_roatate(1);
			break;
		case Y3_ROTATE_L:
			enable_Y3_roatate(-1);
			break;
		case Y3_ROTATE_R:
			enable_Y3_roatate(1);
			break;
		case Z3_ROTATE_L:
			enable_Z3_roatate(-1);
			break;
		case Z3_ROTATE_R:
			enable_Z3_roatate(1);
			break;
		default:
			if (RandomShuffle == 0)
			{
				RandomShuffle = -1;
				if (!fullscreen)
				{
					if (MessageBox(NULL, TEXT("ħ���ѳɹ���ԭ\n�Ƿ������ת?"), TEXT("Magic 2D Info"), MB_ICONINFORMATION | MB_YESNO) == IDYES)
					{
						RandomShuffle = 1;
					}
					else
					{
						MessageBox(NULL, TEXT("��F3������ת"), TEXT("Magic 2D Info"), MB_OK);
						RandomShuffle = -1;
					}
				}
				break;
			}
		}
	}
}


//������>�������еİ��� ʱ����Ӧ
int WINAPI WinMain( 
	HINSTANCE	hInstance,				// ���ڱ�ʶ��(��ǰʵ���ľ��)
	HINSTANCE	hPrevInstance,			//		   (ǰһ��ʵ���ľ��)
	LPSTR		lpCmdLine,				// �����в���
	int			nCmdShow				// ������ʾ����
	)				
{
	MSG		msg;									// Windows Message �ṹ
	BOOL	done = FALSE;							// ����״̬
	
	MessageBox(NULL, TEXT("��Ŀ������OpenGL��3D��תħ��ʵ��\n���ߣ��ϣU201414093\n�༶������1401\n\n��F1��������\n��F2������ԭ\n��F11�ڴ���ȫ�����л�\n��F4�����ر���ת��ͷ\n�����������ƶ�ħ��\nʹ��WASD�ƶ���ͷ�Ƕ�"),
		TEXT("Magic 2D Info"), MB_ICONINFORMATION | MB_OK);
	

	if (!CreateGLWindow("3D MagicCube By �ϣ", 1024, 768, 16, fullscreen))
	{
		return 0;									
	}
	
	::SetTimer(hWnd, 2, 1500, TimerShuffle);		// ��ʱ�� > ���ٴ���

	::SetTimer(hWnd, 3, 100, TimeRestore);			// ��ʱ�� > ���ٸ�ԭ
	
	//::SetTimer(hWnd, 3, 5, RandomRotation);

	while (!done)									
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// Windows Message ����
		{
			if (msg.message == WM_QUIT)	
			{
				done = TRUE;						// ����
			}
			else									
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										
		{
			if ((active && !DrawGLScene()) || keys[VK_ESCAPE])	// ��ʼ����
			{
				done = TRUE;						// ����
			}
			else									
			{
				SwapBuffers(hDC);					// ���Ƶ���Ļ
			}

			if (keys[VK_LEFT])
			{

				RX -= 0.05f;
			}

			if (keys[VK_RIGHT])
			{

				RX += 0.05f;
			}
			
			if (keys[VK_F6])
			{
				enable_Z1_roatate(-1);
				
			}
			if (keys[VK_F7])
			{
				enable_Z2_roatate(-1);

			}
			if (keys[VK_F8])
			{
				enable_Z3_roatate(-1);

			}

			if (keys[VK_UP])
			{
				RY += 0.05f;
			}

			if (keys[VK_DOWN])
			{
				RY -= 0.05f;

			}

			if (keys[KEY_W])
			{
				ROT = FALSE;
				xrot += 1.00f;
			}
			if (keys[KEY_S])
			{
				ROT = FALSE;
				xrot -= 1.00f;
			}
			if (keys[KEY_A])
			{
				ROT = FALSE;
				yrot += 1.00f;
			}
			if (keys[KEY_D])
			{
				ROT = FALSE;
				xrot -= 1.00f;
			}

			if (keys[VK_F1])
			{
				MessageBox(NULL, TEXT("��Ŀ������OpenGL��3D��תħ��ʵ��\n���ߣ��ϣU201414093\n�༶������1401\n\n��F1��������\n��F2������ԭ\n��F11�ڴ���ȫ�����л�\n��F4�����ر���ת��ͷ\n�����������ƶ�ħ��\nʹ��WASD�ƶ���ͷ�Ƕ�"),
					TEXT("About"), MB_ICONINFORMATION | MB_OK);
				keys[VK_F1] = FALSE;
			}

			if (keys[VK_F2] && (RandomShuffle == 1))		// �ر��Զ�����,������ԭ
			{
				keys[VK_F2] = FALSE;
				if (!(rotAngle))//�ж��Ƿ�����ת
					RandomShuffle = 0;
			}

			if (keys[VK_F3] && ( RandomShuffle == -1))		// �����Զ�����
			{
				keys[VK_F3] = FALSE;
				RandomShuffle = 1;
			}

			if (keys[VK_F4])								// �ر��Զ���ת��Ұ
			{
				keys[VK_F4] = FALSE;

				ROT ? (ROT = FALSE) : (ROT = TRUE);
				
			}
			
			if (keys[VK_F11])								// �ı�ȫ��/������ʾ
			{
				keys[VK_F11] = FALSE;
				if (!(rotAngle))
				{
					KillGLWindow();
					fullscreen = !fullscreen;
					if (!CreateGLWindow("3D MagicCube By �ϣ", 1024, 768, 16, fullscreen))
					{
						return 0;
					}
					Init_model();
					::SetTimer(hWnd, 2, 1500, TimerShuffle);
					::SetTimer(hWnd, 3, 100, TimeRestore);
				}
			}
			
		}
		
		if (rotAngle != 0)													// ����ѡװ״̬,������ת����
		{
			if (RandomShuffle)
			{
				if (rotZ1)	Rotate_Z1();
				if (rotY1)	Rotate_Y1();
				if (rotX1)	Rotate_X1();
				if (rotZ2)	Rotate_Z2();
				if (rotY2)	Rotate_Y2();
				if (rotX2)	Rotate_X2();
				if (rotZ3)	Rotate_Z3();
				if (rotY3)	Rotate_Y3();
				if (rotX3)	Rotate_X3();
			}
			if (!RandomShuffle)
			{
				if (rotZ1)	Restore_Z1();
				if (rotY1)	Restore_Y1();
				if (rotX1)	Restore_X1();
				if (rotZ2)	Restore_Z2();
				if (rotY2)	Restore_Y2();
				if (rotX2)	Restore_X2();
				if (rotZ3)	Restore_Z3();
				if (rotY3)	Restore_Y3();
				if (rotX3)	Restore_X3();

			}
			
		}
	}

	// Shutdown
	KillGLWindow();															// �رմ���
	return (msg.wParam);							
}