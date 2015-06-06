#ifndef _MO_FANG_H_
#define _MO_FANG_H_
 
#include <windows.h>		
#include <stdio.h>	
#include <gl/gl.h>			
#include <gl/glu.h>			
#include <gl/glaux.h>		
#include <math.h>
#include <mmsystem.h>		// ���ڲ�������
#pragma comment(lib, "WINMM.LIB")

#define  PI2 6.2831853f 
#define  PI  3.1415926f 
#define  RIGHTANGLE 90

#define KEY_S 83
#define KEY_A 65
#define KEY_D 68
#define KEY_W 87

#define  Z1 0
#define  Y1 1
#define  X1 2
#define  Z2 3
#define  Y2 4
#define  X2 5
#define  Z3 6
#define  Y3 7
#define  X3 8


//���ڴ洢����
#define  MAXSTEP 1000

#define MAX_CHAR	128		// ASCII�ַ��ܹ�ֻ��0��127��һ��128���ַ�

//����
typedef struct 
{
	GLfloat  vx,vy,vz;
}CubeVertex;
//��
typedef struct 
{
	GLfloat p[3];
}stPoint;
//������
typedef struct 
{
	stPoint CubePoint[8];
}stCube;
 

void Init_model(); 

void Rotate_Surface();
void Restore_Surface();
void Enable_Roatate(int surface, int derection, int angle);

extern int		step[MAXSTEP][2];
extern int		step_count ;
extern int		randomshuffle;

extern int      rotFace;
extern stCube   Cube[27];

// װ��Bmp�ļ�
AUX_RGBImageRec *LoadBMP(char *Filename);
// ��*LoadBMP()��Bmp�������
int  LoadGLTextures(char *file, int index);
//��������
extern GLuint texture[55];
//��������ͼƬ
extern int LoadAllTextures();


//���ڻ�������
extern GLuint lists;
extern int InitENstring();
void selectFont(int size, int charset, const char* face);
void drawCNString(const char* str);
void drawENString(const char* str);
#endif