//����
#include <stdlib.h>
#include <gl/glut.h>
#include <gl/glu.h>
#include <gl/glaux.h>
#include <math.h>
#include "texture.h"
texture::texture(void)
{
}
texture::~texture(void)
{
}
/*
AUX_RGBImageRec������һ��RGBͼ��ṹ���͡��ýṹ������������Ա��
sizeX ���� ͼ��Ŀ�ȣ�
sizeY ���� ͼ��ĸ߶ȣ�
data; ���� ͼ�������������ݣ���ʵҲ���Ǹ�ͼ�����ڴ��е��������ݵ�һ��ָ�롣
*/
//��ȡͼƬ��ʽ
void texture::setImg(AUX_RGBImageRec *Img)
{
	img=Img;
}
//��ȡͼƬid
void texture::setTexId(GLuint *texId)
{
	texID=texId;
}
//��������,ͨ��ͼƬ·���Լ���id
void texture::loadTexture(LPCTSTR filename,int i)
{
	img = auxDIBImageLoad(filename);//��ȡͼƬ��Ϣ
	glGenTextures(1, &texID[i]);//��������ÿ��ֻ����һ���������ı��
	glBindTexture(GL_TEXTURE_2D, texID[i]);//����������
	//�����ά������Ϣ
	glTexImage2D(
		GL_TEXTURE_2D,//ָ����ά����
		0, //�����Ƕ���ϸ�ڣ�����Ϊ0
		GL_RGBA, //����RGBAģʽ���졢�̡�����alpha�ĸ�ֵ
		//��ά�������صĿ�͸ߣ�ͼƬ���سߴ磩
		img->sizeX,
		img->sizeY,
		0,//����߿���Ϊ0
		GL_RGB, 
		GL_UNSIGNED_BYTE,
		img->data//ͼƬ����
	);
    //�����������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}
//������ͼ��װ
void texture::Tex(int ID,int * p,GLfloat  box[][3])
{
	Apply(ID);
	//�ı�������
	glBegin(GL_QUADS);
		glTexCoord2f(0,0);	glVertex3fv(box[p[0]]);//����
		glTexCoord2f(0,1);	glVertex3fv(box[p[1]]);//����
		glTexCoord2f(1,1);	glVertex3fv(box[p[2]]);//����
		glTexCoord2f(1,0);	glVertex3fv(box[p[3]]);//����
	glEnd();
}
//��������ı�ţ�id��
void texture::Apply(int i)
{
	glBindTexture(GL_TEXTURE_2D, texID[i]);
}