//��
#include <stdlib.h>
#include <gl/glut.h>
#include <gl/glu.h>
#include <gl/glaux.h>
#include <math.h>
#include"texture.h"
#include "tree.h"
#define PI 3.1415926535897932384626433832795
tree::tree(void)
{
	treeX=0;
	treeY=0;
	treeZ=0;
	treeTheta=0;
	treeBeta=0;
}
//��������ر����ĺ���
void tree::setTreeX(float x)
{
	treeX=x;
}
void tree::setTreeY(float y)
{
	treeY=y;
}
void tree::setTreeZ(float z)
{
	treeZ=z;
}
void tree::setTreeTheta(float theta)
{
	treeTheta=theta;
}
void tree::setTreeBeta(float beta)
{
	treeBeta=beta;
}
float tree::getTreeX()
{
	return treeX;
}
float tree::getTreeY()
{
	return treeY;
}
float tree::getTreeZ()
{
	return treeZ;
}
//�����µĽǶ�
float tree::getTreeTheta()
{
	return treeTheta;
}
//ʹ����һֱ�������
float tree::getTreeBeta()
{
	return treeBeta;
}
//��RGBģʽ��ΪRGBAģʽ,Alpha����,Color Key����������ͼƬ�Ĳ�����͸���ȴ���
//���������ص�RGBֵ�����ָ��rgb������absolute����Alpha����Ϊ0.0����������Ϊ1.0 
void tree::texture_colorkey(GLubyte r, GLubyte g, GLubyte b, GLubyte absolute)
{	
    GLint w, h;
    GLubyte* pixels = 0;

    // �������Ĵ�С��Ϣ
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);

    pixels = (GLubyte*)malloc(w*h*4); // ����ռ䲢�����������
    if( pixels == 0 ) return;

    glGetTexImage(GL_TEXTURE_2D, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, pixels);  // �����������

    // �޸������е�Alphaֵ
	// ����pixels[i*4], pixels[i*4+1], pixels[i*4+2], pixels[i*4+3]  
    // �ֱ��ʾ��i�����ص������̡��졢Alpha���ַ�����0��ʾ��С��255��ʾ���
    GLint count = w * h;
    for(GLint  i=0; i<count; ++i)
	{
		//printf("abs(pixels[i*4] - b)=%d,abs(pixels[i*4+1] - g)=%d,abs(pixels[i*4+2] - r)=%d\n",abs(pixels[i*4] - b),abs(pixels[i*4+1] - g),abs(pixels[i*4+2] - r));
        if( abs(pixels[i*4] - b) <= absolute
            && abs(pixels[i*4+1] - g) <= absolute
            && abs(pixels[i*4+2] - r) <= absolute )
			pixels[i*4+3] = 0;
		else
			pixels[i*4+3] = 255;
	}

    // ���޸ĺ�������������õ������У��ͷ��ڴ�
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,w,h,0,GL_BGRA_EXT,GL_UNSIGNED_BYTE, pixels);
    free(pixels);
}
void tree::initTreeImg()
{
	tree_texture.setImg(treeimg);
	tree_texture.setTexId(treeTexId);
	tree_texture.loadTexture("skybox\\tree.bmp", 0);
	texture_colorkey(255, 255, 255, 10);
}
void tree::drawTree(float size)
{
	tree_texture.Apply(0);
	glEnable(GL_ALPHA_TEST);//���alpha����
	glAlphaFunc(GL_GREATER,0.5); //��������"����0.5ʱͨ��
	glPushMatrix();
		glTranslatef(treeX,treeY,treeZ);
		glRotatef(treeTheta,sin(treeBeta*PI/180),0,cos(treeBeta*PI/180));//���ĵ���
		glRotatef(treeBeta,0,1,0);//����������ʼ�ն�׼���

		glBegin(GL_QUADS);//����ı���
		glTexCoord2d(0,0); glVertex3f(0-size/2,0,0);
		glTexCoord2d(0,1); glVertex3f(0-size/2,0+size,0);
		glTexCoord2d(1,1); glVertex3f(0+size/2,0+size,0);
		glTexCoord2d(1,0); glVertex3f(0+size/2,0,0);
		glEnd();
	glPopMatrix();
}
tree::~tree(void)
{
}
