/*
*		Filename:   Image.cpp
*		Function:    Load BMP And Transform to Textures
*					用于载入图片, 转化为纹理
*		Author:	    李开希  U201414093
*				    华中科技大学 集成1401
*		Time:	    2015-5
*		License:	LGPL
*/

#include "Magic2D.h"


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
	if (!LoadGLTextures("Data/Image/backgroud_0.bmp", 0))								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	if (!LoadGLTextures("Data/1/1.bmp", 1))								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	if (!LoadGLTextures("Data/1/2.bmp", 2))								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}

	if (!LoadGLTextures("Data/1/3.bmp", 3))								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	if (!LoadGLTextures("Data/1/4.bmp", 4))								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	if (!LoadGLTextures("Data/1/5.bmp", 5))								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	if (!LoadGLTextures("Data/1/6.bmp", 6))								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	if (!LoadGLTextures("Data/1/7.bmp", 7))								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	if (!LoadGLTextures("Data/1/8.bmp", 8))								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	if (!LoadGLTextures("Data/1/9.bmp", 9))								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	if (!LoadGLTextures("Data/1/10.bmp", 10))								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	if (!LoadGLTextures("Data/1/11.bmp", 11))								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	if (!LoadGLTextures("Data/1/12.bmp", 12))								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	if (!LoadGLTextures("Data/1/13.bmp", 13))								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	if (!LoadGLTextures("Data/1/14.bmp", 14))								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	if (!LoadGLTextures("Data/1/15.bmp", 15))								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	if (!LoadGLTextures("Data/1/16.bmp", 16))								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	if (!LoadGLTextures("Data/1/17.bmp", 17))								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	if (!LoadGLTextures("Data/1/18.bmp", 18))								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	if (!LoadGLTextures("Data/1/19.bmp", 19))								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	if (!LoadGLTextures("Data/1/20.bmp", 20))								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	if (!LoadGLTextures("Data/1/21.bmp", 21))								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	if (!LoadGLTextures("Data/1/22.bmp", 22))								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	if (!LoadGLTextures("Data/1/23.bmp", 23))								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	if (!LoadGLTextures("Data/1/24.bmp", 24))								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	if (!LoadGLTextures("Data/1/25.bmp", 25))								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	if (!LoadGLTextures("Data/1/26.bmp", 26))								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	if (!LoadGLTextures("Data/1/27.bmp", 27))								// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	return TRUE;
}