//��պ�
#include <stdlib.h>
#include <gl/glut.h>
#include <gl/glu.h>
#include <gl/glaux.h>
#include <math.h>
#include "texture.h"
#include "SkyBox.h"
//������պд�С���ߴ磩
SkyBox::SkyBox(int size)
{
	w=size;
}
//������պУ�������պ���ͼ
void SkyBox::initSkyBox()
{
	skybox_texture.setImg(img);
	skybox_texture.setTexId(skybox_texID);//�洢��պ����У�6���棩����
	skybox_texture.loadTexture("skybox\\neg_x.bmp",0);//��
	skybox_texture.loadTexture("skybox\\pos_x.bmp", 1);//��
	skybox_texture.loadTexture("skybox\\tex3.bmp", 2);//����
	skybox_texture.loadTexture("skybox\\pos_y.bmp", 3);//��
	skybox_texture.loadTexture("skybox\\neg_z.bmp", 4);//ǰ
	skybox_texture.loadTexture("skybox\\pos_z.bmp", 5);//��
	
}
//��պУ������װ
void SkyBox::drawSkyBox(int boxId[][4],GLfloat skybox[][3])
{
	glDisable(GL_ALPHA_TEST);//����Alpha���ԣ��ò���������
	//��boxid��Ӧ������������
	skybox_texture.Tex(4,boxId[0],skybox);// ǰ
	skybox_texture.Tex(0,boxId[1],skybox);// ��
	skybox_texture.Tex(1,boxId[2],skybox);// ��
	skybox_texture.Tex(5,boxId[3],skybox);// ��
	skybox_texture.Tex(3,boxId[4],skybox);// ��
	//ground ���㷨�����˵���
}
SkyBox::~SkyBox(void)
{
}
