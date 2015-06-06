/*
*		Filename:   Image.cpp
*		Function:    Load BMP And Transform to Textures
*					用于载入图片, 转化为纹理
*		Author:	    李开希  U201414093
*				    华中科技大学 集成1401
*		Time:	    2015-5
*/

#include "Magic3D.h"


AUX_RGBImageRec *LoadBMP(char *Filename)
{
	FILE *File = NULL;									// File Handle

	if (!Filename)										// Make Sure A Filename Was Given
	{
		return NULL;									// If Not Return NULL
	}

	File = fopen(Filename, "r");							// Check To See If The File Exists

	if (File)											// Does The File Exist?
	{
		fclose(File);									// Close The Handle
		return auxDIBImageLoad(Filename);				// Load The Bitmap And Return A Pointer
	}

	return NULL;										// If Load Failed Return NULL
}

int  LoadGLTextures(char *file, int index)		// 用*LoadBMP()将Bmp变成纹理
{
	int Status = FALSE;									// Status Indicator

	AUX_RGBImageRec *TextureImage[1];					// Create Storage Space For The Texture

	memset(TextureImage, 0, sizeof(void *) * 1);           	// Set The Pointer To NULL

	// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	if (TextureImage[0] = LoadBMP(file))
	{
		Status = TRUE;									// Set The Status To TRUE

		glGenTextures(1, &texture[index]);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texture[index]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	if (TextureImage[0])									// If Texture Exists
	{
		if (TextureImage[0]->data)							// If Texture Image Exists
		{
			free(TextureImage[0]->data);					// Free The Texture Image Memory
		}

		free(TextureImage[0]);								// Free The Image Structure
	}

	return Status;										// Return The Status
}

int LoadAllTextures()
{
	if (!LoadGLTextures("Data/Image/backgroud_0.bmp", 0))		
		return FALSE;

	int m, n, i = 1;
	for (m = 1; m <= 6; m++)
	{
		for (n = 1; n <= 9; n++, i++)
		{
			char filename[40];
			sprintf(filename, "Data/Image/%d-0%d.bmp", m, n);
			if (!LoadGLTextures(filename, i))
			{
				sprintf(filename, "无法载入Data/Image/%d-0%d.bmp", m, n);
				MessageBox(NULL, filename,TEXT("Error"), MB_ICONINFORMATION | MB_OK);
				return FALSE;
			}
		}
	}
	return TRUE;
}