/***********************************************************************************************************************
*		Filename:   Magic3D.cpp
					改自Magic2D.cpp
*		Function:   Init and Creat Window and GL Program
*				    初始化并创建Windows窗口和绘制GL图像
*		Author:	    李开希  U201414093
*				    华中科技大学 集成1401
*		Time:	    2015-5
*		Remarks:	Thanks to Jeff Molofee and his Tutorial.This Code Was First Created By Him In 2000 (Visit his Site At nehe.gamedev.net)
*					And I Used His Code For Creating Magic2D Main Window.
************************************************************************************************************************/

#include "Magic3D.h"

HDC			hDC = NULL;			// Private GDI Device Context
HGLRC		hRC = NULL;			// Permanent Rendering Context
HWND		hWnd = NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;			// Holds The Instance Of The Application

bool		keys[256];			// 存储键盘按键状态
bool		active = TRUE;		// 窗口激活状态
bool		fullscreen = FALSE;	// 全屏状态

GLfloat		xrot;				// /
GLfloat		yrot;				// /
GLfloat		zrot;				// 摄像头旋转偏移量

GLboolean	ROT = TRUE;			// 镜头旋转状态
GLint		RandomShuffle = 1;	// 打乱/还原状态
int			step[MAXSTEP][2];	// 存储打乱步骤用于还原
int			step_count ;		// 打乱步数		

GLfloat RX;						// /
GLfloat RY;						// 摄像头平移偏移量

GLuint	texture[55];			// 存储纹理

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


// 初始化GL>载入声音 文字 图片 纹理
int InitGL(GLvoid)
{
	if (!LoadAllTextures()) return FALSE;
	InitENstring();										// 初始化字符显示 Text.cpp

	glEnable(GL_TEXTURE_2D);							// 启用2D纹理贴图
	glShadeModel(GL_SMOOTH);							// 颜色光滑过渡
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);	 			// 清空绘图区域
	glClearDepth(1.0f);									// 设置深度
	glEnable(GL_DEPTH_TEST);							// 深度测试
	glDepthFunc(GL_LEQUAL);								// 深度测试方式
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// 最佳质量
	return TRUE;										
}

// 用ID号画正方体
void DrawCube(int ID, int face1, int face2, int face3, int face4, int face5, int face6)
{
	stPoint *CubePoint = Cube[ID].CubePoint;
	/*
	*				  * * * * * * * *
	*				*	上  	  * *
	*			  *				*	*
	*			* * * * * * * *		*
	*			*			  *	右  *
	*			*			  *		*
	*		 /\	*			  *		*
	*	    *	*			  *	  *	
	*	  *		*    前 	  *	*
	*	*		* * * * * * * *
	*
	*/
	// 后表面
	glBindTexture(GL_TEXTURE_2D, texture[face1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(CubePoint[0].p);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(CubePoint[1].p);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(CubePoint[2].p);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(CubePoint[3].p);
	glEnd();
	// 前表面
	face2 ? (glBindTexture(GL_TEXTURE_2D, texture[9 + face2])) : (glBindTexture(GL_TEXTURE_2D, texture[0]));
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(CubePoint[4].p);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(CubePoint[5].p);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(CubePoint[6].p);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(CubePoint[7].p);
	glEnd();
	// 上表面
	face3? (glBindTexture(GL_TEXTURE_2D, texture[18 + face3])) : (glBindTexture(GL_TEXTURE_2D, texture[0]));
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(CubePoint[5].p);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(CubePoint[3].p);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(CubePoint[2].p);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(CubePoint[6].p);
	glEnd();
	// 下表面	
	face4?glBindTexture(GL_TEXTURE_2D, texture[27 + face4]) :(glBindTexture(GL_TEXTURE_2D, texture[0]));
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(CubePoint[4].p);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(CubePoint[7].p);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(CubePoint[1].p);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(CubePoint[0].p);
	glEnd();
	// 左表面
	face5 ? glBindTexture(GL_TEXTURE_2D, texture[36 + face5]) : (glBindTexture(GL_TEXTURE_2D, texture[0]));;
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(CubePoint[7].p);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(CubePoint[6].p);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(CubePoint[2].p);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(CubePoint[1].p);
	glEnd();
	// 右表面
	face6 ? glBindTexture(GL_TEXTURE_2D, texture[45 + face6]) : (glBindTexture(GL_TEXTURE_2D, texture[0]));;
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
	glTranslatef(0.0f, 0.0f, -18.0f);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-18.6f, -18.6f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(18.6f, -18.6f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(18.6f, 18.6f);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(-18.6f, 18.6f);
	glEnd();

	glTranslatef(0.0f, 0.0f, 18.0f);
}

// 绘制GL主程序
int DrawGLScene(GLvoid)				
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glLoadIdentity();										//重置视野位置
	glTranslatef(0.0f, 0.0f, -12.0f);
//
	glBindTexture(GL_TEXTURE_2D, texture[1]);				//关闭纹理的状态

	selectFont(36, ANSI_CHARSET, "MS Gothic");
	glColor3f(0.914f, 0.251f, 0.365f);
	glRasterPos2f(-6.4f, 3.2f);
	drawCNString("基于OpenGL的3d魔方");
	selectFont(32, ANSI_CHARSET, "DFKai-SB");
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(-6.2f, 2.75f);
	drawCNString("作者：李开希 U201414093");
	glRasterPos2f(-6.2f, 2.40f);
	drawCNString("      集成1401");
	glRasterPos2f(-6.2f, 2.0f);
	drawCNString("时间：2015-5");

	selectFont(36, ANSI_CHARSET, "Trebuchet MS"); 
	glRasterPos2f(-5.2f, 1.60f);
	if (RandomShuffle == 1)  drawCNString("随机打乱中 按F2还原");
	if (RandomShuffle == 0)  drawCNString("正在还原");
	if (RandomShuffle == -1) drawCNString("按F3继续旋转");
	
	glColor3f(1, 1, 1);										// 关闭glClolor的颜色状态

	/*														// 用作DeBug
	glRasterPos2f(-5.2f, 1.20f);
	char buffer[50];										
	sprintf(buffer, "%d,%d,%d", rotAngle, RandomShuffle, rotYP || rotZP || rotXM || rotYM || rotZM || rotXP);
	drawCNString(buffer);*/

	DrawBackground();
	
	glTranslatef(0.0f, 0.0f, -12.0f);
	glTranslatef(RX, RY, 0.0f);							// 旋转平移视角
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glRotatef(zrot, 0.0f, 0.0f, 1.0f);

	DrawCube( 0, 7, 0, 0, 9, 0,  9);
	DrawCube( 1, 8, 0, 0, 8, 0,  0);
	DrawCube( 2, 9, 0, 0, 7, 7,  0);
	DrawCube( 3, 4, 0, 0, 0, 0,  6);
	DrawCube( 4, 5, 0, 0, 0, 0,  0);
	DrawCube( 5, 6, 0, 0, 0, 4,  0);
	DrawCube( 6, 1, 0, 7, 0, 0,  3);
	DrawCube( 7, 2, 0, 8, 0, 0,  0);
	DrawCube( 8, 3, 0, 9, 0, 1,  0);

	DrawCube( 9, 0, 0, 0, 6,  0, 8);
	DrawCube(10, 0, 0, 0, 5,  0, 0);
	DrawCube(11, 0, 0, 0, 4,  8, 0);
	DrawCube(12, 0, 0, 0, 0,  0, 5);
	DrawCube(13, 0, 0, 0, 0,  0, 0);
	DrawCube(14, 0, 0, 0, 0,  5, 0);
	DrawCube(15, 0, 0, 4, 0,  0, 2);
	DrawCube(16, 0, 0, 5, 0,  0, 0);
	DrawCube(17, 0, 0, 6, 0,  2, 0);

	DrawCube(18, 0, 9, 0, 3,  0, 7);
	DrawCube(19, 0, 8, 0, 2,  0, 0);
	DrawCube(20, 0, 7, 0, 1,  9, 0);
	DrawCube(21, 0, 6, 0, 0,  0, 4);
	DrawCube(22, 0, 5, 0, 0,  0, 0);
	DrawCube(23, 0, 4, 0, 0,  6, 0);
	DrawCube(24, 0, 3, 1, 0,  0, 1);
	DrawCube(25, 0, 2, 2, 0,  0, 0);
	DrawCube(26, 0, 1, 3, 0,  3, 0);
	


	if (ROT)
	{
		xrot += 0.40f;
		yrot += 0.35f;
		zrot += 0.35f;
	}
	return TRUE;										
}

// GL窗口程序>关闭窗口
GLvoid KillGLWindow(GLvoid)								// 正确关闭窗口
{
	if (fullscreen)										// 全屏状态时
	{
		ChangeDisplaySettings(NULL, 0);					// 返回桌面
		ShowCursor(TRUE);								// 显示鼠标
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

// 调整GL窗口尺寸
GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		
{
	if (height == 0)									// 防止高度被设为0
	{
		height = 1;										
	}
	glViewport(0, 0, width, height);					// 设置当前视角范围

	glMatrixMode(GL_PROJECTION);						// 设置投影视角
	glLoadIdentity();									

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f); // 透视视角缩放(视景体)

	glMatrixMode(GL_MODELVIEW);							// 设置视景体后设置矩阵
	glLoadIdentity();									// 单位化位置矩阵
}

// GL窗口程序>创建窗口 Created By NeHe
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

	if (!InitGL())
	{
		KillGLWindow();
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	return TRUE;									// Success
}


// 回调函数》监控WIN事件；产生旋转状态；rotX；rotY；rotZ; 监控按键
LRESULT CALLBACK WndProc(
	HWND	hWnd,			// 窗口句柄
	UINT	uMsg,			// 窗口响应信息
	WPARAM	wParam,			// 按键信息
	LPARAM	lParam			// 鼠标信息
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

	/*打算做鼠标拖动视野*/
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


// 回调函数>计时器>随机产生旋转事件
VOID CALLBACK TimerShuffle(
	HWND hwnd,			 // Windows Timer Message 句柄
	UINT uMsg,			 // 接受的 WM_TIMER message
	UINT idEvent,		 // 定时器编号
	DWORD dwTime		 // 当前时间
	)
{
	if ((idEvent == 2) && (RandomShuffle == 1))
	{
		srand(dwTime);
		Enable_Roatate(rand() % 9,		//随机旋转面
			(rand() % 2) * 2 - 1,		//随机方向(-1或1)
			1);							//每次旋转角度为1度
	}
}


// 回调函数>计时器>快速还原魔方
VOID CALLBACK TimeRestore(
	HWND	hwnd,		 // Windows Timer Message 句柄
	UINT	uMsg,		 // 接受的 WM_TIMER message
	UINT	idEvent,	 // 定时器编号
	DWORD	dwTime		 // 当前时间
	)
{
	if (RandomShuffle == 1) return;
	if ((idEvent == 3) && (RandomShuffle == 0))
	{
		switch (step[step_count - 1][0])
		{
		case Z1:case Z2:case Z3:case Y1:case Y2:case Y3: case X1:case X2:case X3:
			Enable_Roatate(step[step_count - 1][0], - step[step_count - 1][1], 3); break;//根据栈中的步骤反向转动模仿
		default:
			if (RandomShuffle == 0)
			{
				RandomShuffle = -1;
				if (!fullscreen)			//全屏不启用对话框
				{
					if (MessageBox(NULL, TEXT("魔方已成功还原\n是否继续旋转?"), TEXT("Magic 2D Info"), MB_ICONINFORMATION | MB_YESNO) == IDYES)
					{
						RandomShuffle = 1;
					}
					else
					{
						MessageBox(NULL, TEXT("按F3继续旋转"), TEXT("Magic 2D Info"), MB_OK);
						RandomShuffle = -1;
					}
				}
				break;
			}
		}
	}
}


//主函数>定义所有的按键 时间响应
int WINAPI WinMain( 
	HINSTANCE	hInstance,				// 窗口标识符(当前实例的句柄)
	HINSTANCE	hPrevInstance,			//		   (前一个实例的句柄)
	LPSTR		lpCmdLine,				// 命令行参数
	int			nCmdShow				// 窗口显示参数
	)				
{
	MSG		msg;									// Windows Message 结构
	BOOL	done = FALSE;							// 运行状态
	
	MessageBox(NULL, 
		TEXT("题目：基于OpenGL的3D旋转魔方实现\n作者：李开希U201414093\n班级：集成1401\n\n按F1启动帮助\n按F2启动还原\n按F11在窗口全屏中切换\n按F4开启关闭旋转镜头\n按上下左右移动魔方\n使用WASD移动镜头角度"),
		TEXT("Magic 3D Info"), MB_ICONINFORMATION | MB_OK);
	
	Init_model();									// 初始化魔方坐标 CubeRotate.cpp
	if (!CreateGLWindow("3D MagicCube By 李开希", 1024, 768, 32, fullscreen))
	{
		return 0;									
	}

	::SetTimer(hWnd, 2, 1500, TimerShuffle);		// 定时器 > 中速打乱

	::SetTimer(hWnd, 3, 100, TimeRestore);			// 定时器 > 快速复原

	PlaySound("Data/Sound/BackgroudMusic.wav", NULL, SND_LOOP|SND_ASYNC);

	while (!done)									
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// Windows Message 处理
		{
			if (msg.message == WM_QUIT)	
			{
				done = TRUE;						// 结束
			}
			else									
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										
		{
			if ((active && !DrawGLScene()) || keys[VK_ESCAPE])	// 开始绘制
			{
				done = TRUE;						// 结束
			}
			else									
			{
				SwapBuffers(hDC);					// 绘制到屏幕
			}

			if (keys[VK_LEFT])	{ RX -= 0.05f; }
			if (keys[VK_RIGHT])	{ RX += 0.05f; }
			if (keys[VK_UP])	{ RY += 0.05f; }
			if (keys[VK_DOWN])	{ RY -= 0.05f; }
			if (keys[KEY_W])	{ ROT = FALSE; zrot *= 0.95f; xrot += 0.75f; }
			if (keys[KEY_S])	{ ROT = FALSE; zrot *= 0.95f; xrot -= 0.75f; }
			if (keys[KEY_A])	{ ROT = FALSE; zrot *= 0.95f; yrot -= 0.75f; }
			if (keys[KEY_D])	{ ROT = FALSE; zrot *= 0.95f; yrot += 0.75f; }

			if (keys[VK_F1] && !fullscreen)
			{
				MessageBox(NULL, 
					TEXT("题目：基于OpenGL的3D旋转魔方实现\n作者：李开希U201414093\n班级：集成1401\n\n按F1启动帮助\n按F2启动还原\n按F11在窗口全屏中切换\n按F4开启关闭旋转镜头\n按上下左右移动魔方\n使用WASD移动镜头角度"),
					TEXT("About"), MB_ICONINFORMATION | MB_OK);
				keys[VK_F1] = FALSE;
			}

			if (keys[VK_F2] && (RandomShuffle == 1))		// 关闭自动打乱,启动还原
			{
				keys[VK_F2] = FALSE;
				if (rotFace == -1)//判断是否还在旋转
					RandomShuffle = FALSE;
			}

			if (keys[VK_F3] && ( RandomShuffle == -1))		// 启动自动打乱
			{
				keys[VK_F3] = FALSE;
				RandomShuffle = 1;
			}

			if (keys[VK_F4])								// 关闭自动旋转视野
			{
				keys[VK_F4] = FALSE;
				ROT ? (ROT = FALSE) : (ROT = TRUE);
			}
			
			if (keys[VK_F11])								// 改变全屏/窗口显示
			{
				keys[VK_F11] = FALSE;
				KillGLWindow();
				fullscreen = !fullscreen;
				if (!CreateGLWindow("3D MagicCube By 李开希",
					fullscreen?(::GetSystemMetrics(SM_CXSCREEN)):(1024), fullscreen?(::GetSystemMetrics(SM_CYSCREEN)):(768), 32, fullscreen))
				{
					return 0;
				}
				InitGL();
				::SetTimer(hWnd, 2, 1500, TimerShuffle);
				::SetTimer(hWnd, 3, 100, TimeRestore);
			}
		}
		
		if (rotFace != -1)													// 根据选装状态,绘制旋转动画
		{
			if (RandomShuffle)
				Rotate_Surface();
			else
				Restore_Surface();
		}
	}

	// Shutdown
	KillGLWindow();															// 关闭窗口
	return (msg.wParam);							
}