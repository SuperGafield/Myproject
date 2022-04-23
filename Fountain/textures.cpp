#include "textures.h"
void COGLTexture::LoadFromFile(char *filename)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1,&ID); 
	glBindTexture( GL_TEXTURE_2D, ID);
	//载入位图
	Image = auxDIBImageLoadA( (const char*) filename );
	Width = Image->sizeX;
	Height = Image->sizeY;

	//gluBuild2DMipmaps()用法举例：
	//	gluBuild2DMipmaps(GL_TEXTURE_2D,　　//此纹理是一个2D纹理
	// 3, 　　　　　　　　　　 //颜色成分R(红色分量)、G(绿色分量)、B(蓝色分量)三部分，若为4则是R(红色分量)、G(绿色分量)、B(蓝色分量)、Alpha
	// TextureImage[0]->sizeX,　　//纹理的宽度
	// TextureImage[0]->sizeY,　　//纹理的高度
	// GL_RGB,　　　　　　 //告诉OpenGL图像数据由红、绿、蓝三色数据组成
	// GL_UNSIGNED_BYTE,　　　 //组成图像的数据是无符号字节类型
	// TextureImage[0]->data);　 //告诉OpenGL纹理数据的来源,此例中指向存放在TextureImage[0]记录中的数据

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		3,
		Image->sizeX,
		Image->sizeY,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		Image->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


	delete Image;
}

void COGLTexture::SetActive()
{
	//将一个命名的纹理绑定到一个纹理目标上
	glBindTexture( GL_TEXTURE_2D, ID);
}

unsigned int COGLTexture::GetID()
{
	return ID;
}

