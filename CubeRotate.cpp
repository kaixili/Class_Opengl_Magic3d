/*
*		Filename:   CubeRotate.cpp
*		Function:   控制魔方旋转
*		Author:	    李开希  U201414093
*				    华中科技大学 集成1401
*		Time:	    2015-5
*		License:	LGPL
*/

#include "Magic2D.h"

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
int     rotAngle = 1;	//	每次旋转角度
int     rotCount;		//	一次旋转周期中的旋转次数
int     rotX1, rotY1, rotZ1, rotX2, rotY2, rotZ2, rotX3, rotY3, rotZ3; //	指定旋转轴
int     rotDirect = 1;	//	正反向旋转


const BYTE   SZ1[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8};	 // 创建并储存初始值用于比较
const BYTE   SZ2[9] = { 9,10,11,12,13,14,15,16,17};	 // 各轴正负方向(上下)的面
const BYTE   SZ3[9] = {18,19,20,21,22,23,24,25,26};	

const BYTE   SY1[9] = { 6, 7, 8,15,16,17,24,25,26};
const BYTE   SY2[9] = { 3, 4, 5,12,13,14,21,22,23};
const BYTE   SY3[9] = { 0, 1, 2, 9,10,11,18,19,20};

const BYTE   SX1[9] = { 2, 5, 8,11,14,17,20,23,26};
const BYTE   SX2[9] = { 1, 4, 7,10,13,16,19,22,25};
const BYTE   SX3[9] = { 0, 3, 6, 9,12,15,18,21,24};

BYTE   Z1[9], Z2[9], Z3[9], Y1[9], Y2[9], Y3[9], X1[9], X2[9], X3[9];

// 初始化魔方建立点
void Init_model()
{
	int i, k;
	for (i = 0; i < 9; i++)
	{
		Z1[i] = SZ1[i]; 
		Z2[i] = SZ2[i];
		Z3[i] = SZ3[i];  

		Y1[i] = SY1[i];
		Y2[i] = SY2[i];
		Y3[i] = SY3[i]; 

		X1[i] = SX1[i];
		X2[i] = SX2[i]; 
		X3[i] = SX3[i]; 

	}
	//

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
int  is_equal(stCube *pc1, stCube *pc2)
{
	float x1, x2, y1, y2, z1, z2;

	int isFind = 0;

	for (int i = 0; i<8; i++)
	{
		x1 = pc1->CubePoint[i].p[0];
		y1 = pc1->CubePoint[i].p[1];
		z1 = pc1->CubePoint[i].p[2];

		isFind = 0;

		for (int j = 0; j<8; j++)
		{
			x2 = pc2->CubePoint[j].p[0];
			y2 = pc2->CubePoint[j].p[1];
			z2 = pc2->CubePoint[j].p[2];

			if (fabs(x1 - x2)<1e-1 && fabs(y1 - y2)<1e-1 && fabs(z1 - z2)<1e-1)
			{
				pc1->CubePoint[i].p[0] = pc2->CubePoint[j].p[0]; //消除累计误差
				pc1->CubePoint[i].p[1] = pc2->CubePoint[j].p[1];
				pc1->CubePoint[i].p[2] = pc2->CubePoint[j].p[2];

				isFind = 1;
				break;
			}
		}

		if (isFind == 0) return 0;
	}

	return 1;
}

// 旋转后更新角点索引
void Update_Cube_index()
{
	int i, j, k = 0;
	/**/
	k = 0;
	for (i = 0; i<27; i++)
	{

		for (j = 0; j<9; j++)
			if (is_equal(&Cube[i], &Static_Cube[SZ1[j]]))
			{
				Z1[k++] = i;
			}
	}

	k = 0;
	for (i = 0; i<27; i++)
	{

		for (j = 0; j<9; j++)
			if (is_equal(&Cube[i], &Static_Cube[SZ2[j]]))
			{
				Z2[k++] = i;
			}
	}
	k = 0;
	for (i = 0; i<27; i++)
	{

		for (j = 0; j<9; j++)
			if (is_equal(&Cube[i], &Static_Cube[SZ3[j]]))
			{
				Z3[k++] = i;
			}
	}
	k = 0;
	for (i = 0; i<27; i++)
	{

		for (j = 0; j<9; j++)
			if (is_equal(&Cube[i], &Static_Cube[SX1[j]]))
			{
				X1[k++] = i;
			}
	}
	k = 0;
	for (i = 0; i<27; i++)
	{

		for (j = 0; j<9; j++)
			if (is_equal(&Cube[i], &Static_Cube[SX2[j]]))
			{
				X2[k++] = i;
			}
	}
	k = 0;
	for (i = 0; i<27; i++)
	{

		for (j = 0; j<9; j++)
			if (is_equal(&Cube[i], &Static_Cube[SX3[j]]))
			{
				X3[k++] = i;
			}
	}
	k = 0;
	for (i = 0; i<27; i++)
	{
		for (j = 0; j<9; j++)
			if (is_equal(&Cube[i], &Static_Cube[SY1[j]]))
			{
				Y1[k++] = i;
			}
	}
	k = 0;
	for (i = 0; i<27; i++)
	{
		for (j = 0; j<9; j++)
			if (is_equal(&Cube[i], &Static_Cube[SY2[j]]))
			{
				Y2[k++] = i;
			}
	}
	k = 0;
	for (i = 0; i<27; i++)
	{
		for (j = 0; j<9; j++)
			if (is_equal(&Cube[i], &Static_Cube[SY3[j]]))
			{
				
				Y3[k++] = i;
			}

	}

}

// 旋转魔方
void Rotate(stCube *pCube, float angle, int x, int y, int z)
{

	int i;
	double a = PI2*angle / 360.0;

	double cosa = cos(a), sina = sin(a);//旋转90°0.0, 1.0

	if (x)
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

	if (y)
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

	if (z)
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

// 旋转一个面的9个魔方体
void Rotate_Z1()
{
	for (int i = 0; i<9; i++)
	{
		Rotate(&Cube[Z1[i]], rotAngle*rotDirect, 0, 0, 1);
	}

	if (rotCount++ == CYCLE_COUNT)
	{
		Update_Cube_index();

		rotAngle = 0;

		rotZ1 = 0;
		step[step_count++] = Z1_ROTATE_L * rotDirect;
	}

}
void Rotate_X1()
{
	for (int i = 0; i<9; i++)
	{
		Rotate(&Cube[X1[i]], rotAngle*rotDirect, 1, 0, 0);
	}

	if (rotCount++ == CYCLE_COUNT)
	{
		Update_Cube_index();

		rotAngle = 0;

		rotX1 = 0;
		step[step_count++] = X1_ROTATE_L * rotDirect;
	}

}
void Rotate_Y1()
{
	for (int i = 0; i<9; i++)
	{
		Rotate(&Cube[Y1[i]], rotAngle*rotDirect, 0, 1, 0);
	}

	if (rotCount++ == CYCLE_COUNT)
	{
		Update_Cube_index();

		rotAngle = 0;
		rotY1 = 0;
		step[step_count++] = Y1_ROTATE_L * rotDirect;
	}

}
void Rotate_Z2()
{
	for (int i = 0; i<9; i++)
	{
		Rotate(&Cube[Z2[i]], rotAngle*rotDirect, 0, 0, 1);
	}

	if (rotCount++ == CYCLE_COUNT)
	{
		Update_Cube_index();

		rotAngle = 0;

		rotZ2 = 0;
		step[step_count++] = Z2_ROTATE_L * rotDirect;
	}

}
void Rotate_X2()
{
	for (int i = 0; i<9; i++)
	{
		Rotate(&Cube[X2[i]], rotAngle*rotDirect, 1, 0, 0);
	}

	if (rotCount++ == CYCLE_COUNT)
	{
		Update_Cube_index();

		rotAngle = 0;
		rotX2 = 0;
		step[step_count++] = X2_ROTATE_L * rotDirect;
	}

}
void Rotate_Y2()
{
	for (int i = 0; i<9; i++)
	{
		Rotate(&Cube[Y2[i]], rotAngle*rotDirect, 0, 1, 0);
	}

	if (rotCount++ == CYCLE_COUNT)
	{
		Update_Cube_index();

		rotAngle = 0;
		rotY2 = 0;
		step[step_count++] = Y2_ROTATE_L * rotDirect;
	}
	
}
void Rotate_Z3()
{
	for (int i = 0; i<9; i++)
	{
		Rotate(&Cube[Z3[i]], rotAngle*rotDirect, 0, 0, 1);
	}

	if (rotCount++ == CYCLE_COUNT)
	{
		Update_Cube_index();

		rotAngle = 0;

		rotZ3 = 0;
		step[step_count++] = Z3_ROTATE_L * rotDirect;
	}

}
void Rotate_X3()
{
	for (int i = 0; i<9; i++)
	{
		Rotate(&Cube[X3[i]], rotAngle*rotDirect, 1, 0, 0);
	}

	if (rotCount++ == CYCLE_COUNT)
	{
		Update_Cube_index();

		rotAngle = 0;
		rotX3 = 0;
		step[step_count++] = X3_ROTATE_L * rotDirect;
	}

}
void Rotate_Y3()
{
	for (int i = 0; i<9; i++)
	{
		Rotate(&Cube[Y3[i]], rotAngle*rotDirect, 0, 1, 0);
	}

	if (rotCount++ == CYCLE_COUNT)
	{
		Update_Cube_index();

		rotAngle = 0;
		rotY3 = 0;
		step[step_count++] = Y3_ROTATE_L * rotDirect;
	}
	
}

// 激活旋转状态
void enable_X1_roatate(int direction)
{
	if (rotX1 == 0)
	{
		if (rotY1 || rotZ1 || rotX2 || rotY2 || rotZ2 || rotX3 || rotY3 || rotZ3)
		{
			rotX1 = 0;
		}
		else
		{	
			PlaySound("data/Sound/click.wav", NULL, SND_ASYNC);
			rotAngle = 1;
			rotCount = 0;
			rotX1 = 1;
			rotDirect = direction;
		}
	}

}
void enable_Y1_roatate(int direction)
{
	if (rotY1 == 0)
	{
		if (rotX1 || rotZ1 || rotX2 || rotY2 || rotZ2 || rotX3 || rotY3 || rotZ3)
		{
			rotY1 = 0;
		}
		else
		{
			PlaySound("data/Sound/click.wav", NULL, SND_ASYNC);
			rotAngle = 1;
			rotCount = 0;
			rotY1 = 1;
			rotDirect = direction;
		}
	}
}
void enable_Z1_roatate(int direction)
{
	if (rotZ1 == 0)
	{

		if (rotX1 || rotY1 || rotX2 || rotY2 || rotZ2 || rotX3 || rotY3 || rotZ3)
		{
			rotZ1 = 0;
		}
		else
		{
			PlaySound("data/Sound/click.wav", NULL, SND_ASYNC);
			rotAngle = 1;
			rotCount = 0;
			rotZ1 = 1;
			rotDirect = direction;
		}
	}
}
void enable_X2_roatate(int direction)
{
	if (rotX2 == 0)
	{
		if (rotX1 || rotY1 || rotZ1 || rotY2 || rotZ2 || rotX3 || rotY3 || rotZ3)
		{
			rotX2 = 0;
		}
		else
		{
			PlaySound("data/Sound/click.wav", NULL, SND_ASYNC);
			rotAngle = 1;
			rotCount = 0;
			rotX2 = 1;
			rotDirect = direction;
		}
	}

}
void enable_Y2_roatate(int direction)
{
	if (rotY2 == 0)
	{
		if (rotX1 || rotY1 || rotZ1 || rotX2 || rotZ2 || rotX3 || rotY3 || rotZ3)
		{
			rotY2 = 0;
		}
		else
		{
			PlaySound("data/Sound/click.wav", NULL, SND_ASYNC);
			rotAngle = 1;
			rotCount = 0;
			rotY2 = 1;
			rotDirect = direction;
		}
	}
}
void enable_Z2_roatate(int direction)
{
	if (rotZ2 == 0)
	{

		if (rotX1 || rotY1 || rotZ1 || rotX2 || rotY2 || rotX3 || rotY3 || rotZ3)
		{
			rotZ2 = 0;
		}
		else
		{
			PlaySound("data/Sound/click.wav", NULL, SND_ASYNC);
			rotAngle = 1;
			rotCount = 0;
			rotZ2 = 1;
			rotDirect = direction;
		}
	}
}
void enable_X3_roatate(int direction)
{
	if (rotX3 == 0)
	{
		if (rotX1 || rotY1 || rotZ1 || rotX2 || rotY2 || rotZ2 || rotY3 || rotZ3)
		{
			rotX3 = 0;
		}
		else
		{
			PlaySound("data/Sound/click.wav", NULL, SND_ASYNC);
			rotAngle = 1;
			rotCount = 0;
			rotX3 = 1;
			rotDirect = direction;
		}
	}

}
void enable_Y3_roatate(int direction)
{
	if (rotY3 == 0)
	{
		if (rotX1 || rotY1 || rotZ1 || rotX2 || rotY2 || rotZ2 || rotX3 || rotZ3)
		{
			rotY2 = 0;
		}
		else
		{
			PlaySound("data/Sound/click.wav", NULL, SND_ASYNC);
			rotAngle = 1;
			rotCount = 0;
			rotY3 = 1;
			rotDirect = direction;
		}
	}
}
void enable_Z3_roatate(int direction)
{
	if (rotZ3 == 0)
	{

		if (rotX1 || rotY1 || rotZ1 || rotX2 || rotY2 || rotZ2 || rotX3 || rotY3)
		{
			rotZ3 = 0;
		}
		else
		{
			PlaySound("data/Sound/click.wav", NULL, SND_ASYNC);
			rotAngle = 1;
			rotCount = 0;
			rotZ3 = 1;
			rotDirect = direction;
		}
	}
}
// 还原魔方
void Restore_Z1()
{
	for (int i = 0; i<9; i++)
	{
		Rotate(&Cube[Z1[i]], rotAngle*rotDirect, 0.0, 0.0, 1.0);
	}

	if (rotCount++ == CYCLE_COUNT)
	{
		Update_Cube_index();

		rotAngle = 0;

		rotZ1 = 0;

		--step_count;


	}

}
void Restore_X1()
{
	for (int i = 0; i<9; i++)
	{
		Rotate(&Cube[X1[i]], rotAngle*rotDirect, 1.0, 0.0, 0.0);
	}

	if (rotCount++ == CYCLE_COUNT)
	{
		Update_Cube_index();

		rotAngle = 0;

		rotX1 = 0;
		--step_count;
	}

}
void Restore_Y1()
{
	for (int i = 0; i<9; i++)
	{
		Rotate(&Cube[Y1[i]], rotAngle*rotDirect, 0.0, 1.0, 0.0);
	}

	if (rotCount++ == CYCLE_COUNT)
	{
		Update_Cube_index();

		rotAngle = 0;
		rotY1 = 0;
		--step_count;
	}

}
void Restore_Z2()
{
	for (int i = 0; i<9; i++)
	{
		Rotate(&Cube[Z2[i]], rotAngle*rotDirect, 0.0, 0.0, 1.0);
	}

	if (rotCount++ == CYCLE_COUNT)
	{
		Update_Cube_index();

		rotAngle = 0;

		rotZ2 = 0;
		--step_count;
	}

}
void Restore_X2()
{
	for (int i = 0; i<9; i++)
	{
		Rotate(&Cube[X2[i]], rotAngle*rotDirect, 1.0, 0.0, 0.0);
	}

	if (rotCount++ == CYCLE_COUNT)
	{
		Update_Cube_index();

		rotAngle = 0;
		rotX2 = 0;
		--step_count;
	}

}
void Restore_Y2()
{
	for (int i = 0; i<9; i++)
	{
		Rotate(&Cube[Y2[i]], rotAngle*rotDirect, 0.0, 1.0, 0.0);
	}

	if (rotCount++ == CYCLE_COUNT)
	{
		Update_Cube_index();

		rotAngle = 0;
		rotY2 = 0;
		--step_count;
	}

}
void Restore_Z3()
{
	for (int i = 0; i<9; i++)
	{
		Rotate(&Cube[Z3[i]], rotAngle*rotDirect, 0.0, 0.0, 1.0);
	}

	if (rotCount++ == CYCLE_COUNT)
	{
		Update_Cube_index();

		rotAngle = 0;

		rotZ3 = 0;
		--step_count;
	}

}
void Restore_X3()
{
	for (int i = 0; i<9; i++)
	{
		Rotate(&Cube[X3[i]], rotAngle*rotDirect, 1.0, 0.0, 0.0);
	}

	if (rotCount++ == CYCLE_COUNT)
	{
		Update_Cube_index();

		rotAngle = 0;
		rotX3 = 0;
		--step_count;
	}

}
void Restore_Y3()
{
	for (int i = 0; i<9; i++)
	{
		Rotate(&Cube[Y3[i]], rotAngle*rotDirect, 0.0, 1.0, 0.0);
	}

	if (rotCount++ == CYCLE_COUNT)
	{
		Update_Cube_index();

		rotAngle = 0;
		rotY3 = 0;
		--step_count;
	}

}