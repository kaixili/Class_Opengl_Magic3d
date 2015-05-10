#ifndef _MO_FANG_H_
#define _MO_FANG_H_
 
#include <windows.h>		
#include <stdio.h>	
#include <gl/gl.h>			
#include <gl/glu.h>			
#include <gl/glaux.h>		
#include <math.h>
#include <mmsystem.h>		// 用于播放声音
#pragma comment(lib, "WINMM.LIB")

#define MAX_CHAR	128		// ASCII字符总共只有0到127，一共128种字符

#define  PI2 6.2831853f 
#define  PI  3.1415926f 
#define  CYCLE_COUNT 90

#define KEY_S 83
#define KEY_A 65
#define KEY_D 68
#define KEY_W 87

#define  TEXTLOCATION_X	 
#define  TEXTLOCATION_Y		

#define  FRONT   0
#define  BACK    1
#define  LEFT    2
#define  RIGHT   3
#define  TOP     4
#define  BOTTOM  5

//用于存储步骤
#define  MAXSTEP 1000
#define  X1_ROTATE_L 1
#define  X1_ROTATE_R -1
#define  Y1_ROTATE_L 2
#define  Y1_ROTATE_R -2
#define  Z1_ROTATE_L 3
#define  Z1_ROTATE_R -3
#define  X2_ROTATE_L 4
#define  X2_ROTATE_R -4
#define  Y2_ROTATE_L 5
#define  Y2_ROTATE_R -5
#define  Z2_ROTATE_L 6
#define  Z2_ROTATE_R -6
#define  X3_ROTATE_L 7
#define  X3_ROTATE_R -7
#define  Y3_ROTATE_L 8
#define  Y3_ROTATE_R -8
#define  Z3_ROTATE_L 9
#define  Z3_ROTATE_R -9

//坐标
typedef struct 
{
	GLfloat  vx,vy,vz;
}CubeVertex;
//点
typedef struct 
{
	GLfloat p[3];
}stPoint;
//正方体
typedef struct 
{
	stPoint CubePoint[8];
}stCube;
 

void Init_model(); 

void Rotate_Z1();
void Rotate_X1();
void Rotate_Y1();
void Rotate_Z2();
void Rotate_X2();
void Rotate_Y2();
void Rotate_Z3();
void Rotate_X3();
void Rotate_Y3();

void enable_X1_roatate(int direction);
void enable_Y1_roatate(int direction);
void enable_Z1_roatate(int direction);
void enable_X2_roatate(int direction);
void enable_Y2_roatate(int direction);
void enable_Z2_roatate(int direction);
void enable_X3_roatate(int direction);
void enable_Y3_roatate(int direction);
void enable_Z3_roatate(int direction);

extern int		step[MAXSTEP];
extern int		step_count ;
extern int		randomshuffle;

void Restore_Z1();
void Restore_X1();
void Restore_Y1();
void Restore_Z2();
void Restore_X2();
void Restore_Y2(); 
void Restore_Z3();
void Restore_X3();
void Restore_Y3();


extern stCube  Cube[27];
extern int     rotAngle;
extern int     rotCount;
extern int     rotX1, rotY1, rotZ1, rotX2, rotY2, rotZ2, rotX3, rotY3, rotZ3;
extern BYTE   Z1[9], Z2[9], Z3[9], Y1[9], Y2[9], Y3[9], X1[9], X2[9], X3[9];
extern stCube  Static_Cube[27];

// 装载Bmp文件
AUX_RGBImageRec *LoadBMP(char *Filename);
// 用*LoadBMP()将Bmp变成纹理
int  LoadGLTextures(char *file, int index);
//储存纹理
extern GLuint texture[30];
//载入所有图片
extern int LoadAllTextures();

//用于绘制文字
extern GLuint lists;
extern int InitENstring();
void selectFont(int size, int charset, const char* face);
void drawCNString(const char* str);
void drawENString(const char* str);
#endif