#include "textures.h"
void COGLTexture::LoadFromFile(char *filename)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1,&ID); 
	glBindTexture( GL_TEXTURE_2D, ID);
	//����λͼ
	Image = auxDIBImageLoadA( (const char*) filename );
	Width = Image->sizeX;
	Height = Image->sizeY;

	//gluBuild2DMipmaps()�÷�������
	//	gluBuild2DMipmaps(GL_TEXTURE_2D,����//��������һ��2D����
	// 3, �������������������� //��ɫ�ɷ�R(��ɫ����)��G(��ɫ����)��B(��ɫ����)�����֣���Ϊ4����R(��ɫ����)��G(��ɫ����)��B(��ɫ����)��Alpha
	// TextureImage[0]->sizeX,����//����Ŀ��
	// TextureImage[0]->sizeY,����//����ĸ߶�
	// GL_RGB,������������ //����OpenGLͼ�������ɺ졢�̡�����ɫ�������
	// GL_UNSIGNED_BYTE,������ //���ͼ����������޷����ֽ�����
	// TextureImage[0]->data);�� //����OpenGL�������ݵ���Դ,������ָ������TextureImage[0]��¼�е�����

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
	//��һ������������󶨵�һ������Ŀ����
	glBindTexture( GL_TEXTURE_2D, ID);
}

unsigned int COGLTexture::GetID()
{
	return ID;
}

