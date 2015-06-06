/*
*		Filename:   CubeRotate.cpp
*		Function:   控制魔方旋转
*		Author:	    李开希  U201414093
*				    华中科技大学 集成1401
*		Time:	    2015-5
*/

#include "Magic3D.h"

static stPoint CubePoint[8] =
{
	{ -1.0f, -1.0f, 1.0f },		//0   
	{ 1.0f, -1.0f, 1.0f },		//1 
	{ 1.0f, 1.0f, 1.0f },		//2   
	{ -1.0f, 1.0f, 1.0f },      //3

	{ -1.0f, -1.0f, -1.0f },	//4    
	{ -1.0f, 1.0f, -1.0f },		//5
	{ 1.0f, 1.0f, -1.0f },		//6    
	{ 1.0f, -1.0f, -1.0f },		//7
};

stCube  Cube[27];
stCube  Static_Cube[27];

/*旋转控制*/
int     rotFace = -1;		//	指定旋转轴
int     rotAngle = 1;		//	每次旋转角度
int     rotCount;			//	一次旋转周期中的旋转次数
int     rotDirection = 1;	//	正反向旋转

const BYTE   Static_Index[3 * 3][3 * 3] = {// 创建并储存初始值用于比较
	{  0, 1,  2,  3,  4,  5,  6,  7,  8  }, //Z1
	{  6, 7,  8,  15, 16, 17, 24, 25, 26 },//Y1
	{  2, 5,  8,  11, 14, 17, 20, 23, 26 },//X1
	{  9, 10, 11, 12, 13, 14, 15, 16, 17 },//Z2
	{  3, 4,  5,  12, 13, 14, 21, 22, 23 },//Y2
	{  1, 4,  7,  10, 13, 16, 19, 22, 25 },//X2
	{ 18, 19, 20, 21, 22, 23, 24, 25, 26 },//Z3
	{  0, 1,  2,  9,  10, 11, 18, 19, 20 },//Y3
	{  0, 3,  6,  9,  12, 15, 18, 21, 24 },//X3
};
BYTE   Index[3 * 3][3 * 3];

// 初始化魔方建立点
void Init_model()
{
	memcpy(Index, Static_Index, sizeof(Static_Index));
	
	step_count = 0;										// 初始化栈
	step[step_count][0] = 0;

	int i;
	for (i = 0; i<8; i++)
	{
		Cube[0].CubePoint[i].p[0] = CubePoint[i].p[0] - 2.0f;
		Cube[0].CubePoint[i].p[1] = CubePoint[i].p[1] - 2.0f;
		Cube[0].CubePoint[i].p[2] = CubePoint[i].p[2] + 2.0f;

		Cube[1].CubePoint[i].p[0] = CubePoint[i].p[0] + 0.0f;
		Cube[1].CubePoint[i].p[1] = CubePoint[i].p[1] - 2.0f;
		Cube[1].CubePoint[i].p[2] = CubePoint[i].p[2] + 2.0f;

		Cube[2].CubePoint[i].p[0] = CubePoint[i].p[0] + 2.0f;
		Cube[2].CubePoint[i].p[1] = CubePoint[i].p[1] - 2.0f;
		Cube[2].CubePoint[i].p[2] = CubePoint[i].p[2] + 2.0f;

		Cube[3].CubePoint[i].p[0] = CubePoint[i].p[0] - 2.0f;
		Cube[3].CubePoint[i].p[1] = CubePoint[i].p[1] + 0.0f;
		Cube[3].CubePoint[i].p[2] = CubePoint[i].p[2] + 2.0f;

		Cube[4].CubePoint[i].p[0] = CubePoint[i].p[0] + 0.0f;
		Cube[4].CubePoint[i].p[1] = CubePoint[i].p[1] + 0.0f;
		Cube[4].CubePoint[i].p[2] = CubePoint[i].p[2] + 2.0f;

		Cube[5].CubePoint[i].p[0] = CubePoint[i].p[0] + 2.0f;
		Cube[5].CubePoint[i].p[1] = CubePoint[i].p[1] + 0.0f;
		Cube[5].CubePoint[i].p[2] = CubePoint[i].p[2] + 2.0f;

		Cube[6].CubePoint[i].p[0] = CubePoint[i].p[0] - 2.0f;
		Cube[6].CubePoint[i].p[1] = CubePoint[i].p[1] + 2.0f;
		Cube[6].CubePoint[i].p[2] = CubePoint[i].p[2] + 2.0f;

		Cube[7].CubePoint[i].p[0] = CubePoint[i].p[0] + 0.0f;
		Cube[7].CubePoint[i].p[1] = CubePoint[i].p[1] + 2.0f;
		Cube[7].CubePoint[i].p[2] = CubePoint[i].p[2] + 2.0f;

		Cube[8].CubePoint[i].p[0] = CubePoint[i].p[0] + 2.0f;
		Cube[8].CubePoint[i].p[1] = CubePoint[i].p[1] + 2.0f;
		Cube[8].CubePoint[i].p[2] = CubePoint[i].p[2] + 2.0f;

		Cube[9].CubePoint[i].p[0] = CubePoint[i].p[0] - 2.0f;
		Cube[9].CubePoint[i].p[1] = CubePoint[i].p[1] - 2.0f;
		Cube[9].CubePoint[i].p[2] = CubePoint[i].p[2] + 0.0f;

		Cube[10].CubePoint[i].p[0] = CubePoint[i].p[0] + 0.0f;
		Cube[10].CubePoint[i].p[1] = CubePoint[i].p[1] - 2.0f;
		Cube[10].CubePoint[i].p[2] = CubePoint[i].p[2] + 0.0f;

		Cube[11].CubePoint[i].p[0] = CubePoint[i].p[0] + 2.0f;
		Cube[11].CubePoint[i].p[1] = CubePoint[i].p[1] - 2.0f;
		Cube[11].CubePoint[i].p[2] = CubePoint[i].p[2] + 0.0f;

		Cube[12].CubePoint[i].p[0] = CubePoint[i].p[0] - 2.0f;
		Cube[12].CubePoint[i].p[1] = CubePoint[i].p[1] + 0.0f;
		Cube[12].CubePoint[i].p[2] = CubePoint[i].p[2] + 0.0f;

		Cube[13].CubePoint[i].p[0] = CubePoint[i].p[0] + 0.0f;
		Cube[13].CubePoint[i].p[1] = CubePoint[i].p[1] + 0.0f;
		Cube[13].CubePoint[i].p[2] = CubePoint[i].p[2] + 0.0f;

		Cube[14].CubePoint[i].p[0] = CubePoint[i].p[0] + 2.0f;
		Cube[14].CubePoint[i].p[1] = CubePoint[i].p[1] + 0.0f;
		Cube[14].CubePoint[i].p[2] = CubePoint[i].p[2] + 0.0f;

		Cube[15].CubePoint[i].p[0] = CubePoint[i].p[0] - 2.0f;
		Cube[15].CubePoint[i].p[1] = CubePoint[i].p[1] + 2.0f;
		Cube[15].CubePoint[i].p[2] = CubePoint[i].p[2] + 0.0f;

		Cube[16].CubePoint[i].p[0] = CubePoint[i].p[0] + 0.0f;
		Cube[16].CubePoint[i].p[1] = CubePoint[i].p[1] + 2.0f;
		Cube[16].CubePoint[i].p[2] = CubePoint[i].p[2] + 0.0f;

		Cube[17].CubePoint[i].p[0] = CubePoint[i].p[0] + 2.0f;
		Cube[17].CubePoint[i].p[1] = CubePoint[i].p[1] + 2.0f;
		Cube[17].CubePoint[i].p[2] = CubePoint[i].p[2] + 0.0f;

		Cube[18].CubePoint[i].p[0] = CubePoint[i].p[0] - 2.0f;
		Cube[18].CubePoint[i].p[1] = CubePoint[i].p[1] - 2.0f;
		Cube[18].CubePoint[i].p[2] = CubePoint[i].p[2] - 2.0f;

		Cube[19].CubePoint[i].p[0] = CubePoint[i].p[0] + 0.0f;
		Cube[19].CubePoint[i].p[1] = CubePoint[i].p[1] - 2.0f;
		Cube[19].CubePoint[i].p[2] = CubePoint[i].p[2] - 2.0f;

		Cube[20].CubePoint[i].p[0] = CubePoint[i].p[0] + 2.0f;
		Cube[20].CubePoint[i].p[1] = CubePoint[i].p[1] - 2.0f;
		Cube[20].CubePoint[i].p[2] = CubePoint[i].p[2] - 2.0f;

		Cube[21].CubePoint[i].p[0] = CubePoint[i].p[0] - 2.0f;
		Cube[21].CubePoint[i].p[1] = CubePoint[i].p[1] + 0.0f;
		Cube[21].CubePoint[i].p[2] = CubePoint[i].p[2] - 2.0f;

		Cube[22].CubePoint[i].p[0] = CubePoint[i].p[0] + 0.0f;
		Cube[22].CubePoint[i].p[1] = CubePoint[i].p[1] + 0.0f;
		Cube[22].CubePoint[i].p[2] = CubePoint[i].p[2] - 2.0f;

		Cube[23].CubePoint[i].p[0] = CubePoint[i].p[0] + 2.0f;
		Cube[23].CubePoint[i].p[1] = CubePoint[i].p[1] + 0.0f;
		Cube[23].CubePoint[i].p[2] = CubePoint[i].p[2] - 2.0f;

		Cube[24].CubePoint[i].p[0] = CubePoint[i].p[0] - 2.0f;
		Cube[24].CubePoint[i].p[1] = CubePoint[i].p[1] + 2.0f;
		Cube[24].CubePoint[i].p[2] = CubePoint[i].p[2] - 2.0f;

		Cube[25].CubePoint[i].p[0] = CubePoint[i].p[0] + 0.0f;
		Cube[25].CubePoint[i].p[1] = CubePoint[i].p[1] + 2.0f;
		Cube[25].CubePoint[i].p[2] = CubePoint[i].p[2] - 2.0f;

		Cube[26].CubePoint[i].p[0] = CubePoint[i].p[0] + 2.0f;
		Cube[26].CubePoint[i].p[1] = CubePoint[i].p[1] + 2.0f;
		Cube[26].CubePoint[i].p[2] = CubePoint[i].p[2] - 2.0f;
	}

	for (i = 0; i<27; i++)
		Static_Cube[i] = Cube[i];
}

// 判断重合并消除误差
int  is_equal(stCube *pC1, stCube *pC2)
{
	float x1, x2, y1, y2, z1, z2;

	int isFind = 0;

	for (int i = 0; i<8; i++)
	{
		x1 = pC1->CubePoint[i].p[0];
		y1 = pC1->CubePoint[i].p[1];
		z1 = pC1->CubePoint[i].p[2];

		isFind = 0;

		for (int j = 0; j<8; j++)
		{
			x2 = pC2->CubePoint[j].p[0];
			y2 = pC2->CubePoint[j].p[1];
			z2 = pC2->CubePoint[j].p[2];

			if (fabs(x1 - x2)<0.5 && fabs(y1 - y2)<0.5 && fabs(z1 - z2)<0.5)
			{
				pC1->CubePoint[i].p[0] = pC2->CubePoint[j].p[0]; //消除累计误差
				pC1->CubePoint[i].p[1] = pC2->CubePoint[j].p[1];
				pC1->CubePoint[i].p[2] = pC2->CubePoint[j].p[2];

				isFind = 1;
				break;
			}
		}

		if (isFind == 0) return 0;
	}

	return 1;
}

// 旋转后更新角点索引
void Update_Index()
{
	int i, j, k, face;
	for (face = 0; face < 9; face++)
	{
		for (k = 0, i = 0; i < 27; i++)
		{

			for (j = 0; j < 9; j++)
				if (is_equal(&Cube[i], &Static_Cube[Static_Index[face][j]]))
				{
					Index[face][k++] = i;
				}
		}
	}
}

// 旋转魔方
void Rotate(stCube *pCube, int angle)
{

	int i;
	double a = PI2*(float)angle / 360.0;

	double cosa = cos(a), sina = sin(a);//旋转90°0.0, 1.0

	if (rotFace == X1 || rotFace == X2 || rotFace == X3)
	{
		for (i = 0; i<8; i++)
		{
			float y, z;

			y = pCube->CubePoint[i].p[1];
			z = pCube->CubePoint[i].p[2];

			pCube->CubePoint[i].p[1] = y*cosa - z*sina;
			pCube->CubePoint[i].p[2] = y*sina + z*cosa;
		}
	}

	if (rotFace == Y1 || rotFace == Y2 || rotFace == Y3)
	{
		for (i = 0; i<8; i++)
		{
			float  x, z;

			x = pCube->CubePoint[i].p[0];
			z = pCube->CubePoint[i].p[2];

			pCube->CubePoint[i].p[0] = x*cosa - z*sina;
			pCube->CubePoint[i].p[2] = x*sina + z*cosa;

		}
	}

	if (rotFace == Z1 || rotFace == Z2 || rotFace == Z3)
	{
		for (i = 0; i<8; i++)
		{
			float x, y;

			x = pCube->CubePoint[i].p[0];
			y = pCube->CubePoint[i].p[1];

			pCube->CubePoint[i].p[0] = x*cosa - y*sina;
			pCube->CubePoint[i].p[1] = x*sina + y*cosa;
		}
	}
}

void Enable_Roatate(int surface, int direction, int angle)
{
	if (rotFace == -1)
	{
		mciSendString("play data/Sound/click.wav","",0,NULL);
		rotFace = surface;
		rotDirection = direction;
		rotAngle = angle;
	}
}

void Rotate_Surface()
{
	for (int i = 0; i<9; i++)
	{
		Rotate(&Cube[Index[rotFace][i]], rotAngle*rotDirection);
	}

	if (rotCount++ == RIGHTANGLE / rotAngle)
	{
		step[step_count][0] = rotFace;
		step[step_count][1] = rotDirection;
		step_count++;
		

		Update_Index();
		rotFace = -1;
		rotCount = 0;
	}
}

void Restore_Surface()
{
	for (int i = 0; i<9; i++)
	{
		Rotate(&Cube[Index[rotFace][i]], rotAngle*rotDirection);
	}

	if (rotCount++ == RIGHTANGLE / rotAngle)
	{
		--step_count;

		Update_Index();
		rotFace = -1;
		rotCount = 0;
	}
}