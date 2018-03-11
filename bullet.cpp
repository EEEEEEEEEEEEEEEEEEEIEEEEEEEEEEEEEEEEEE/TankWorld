//�ӵ�
#include "bullet.h"
#include <gl\glut.h>
#include <math.h>
#define PI 3.1415926535897932384626433832795
bullet::bullet(void)
{
	bulletSize=0.01;//�뾶
}
bullet::bullet(float size)
{
	bulletSize=size;
}
void bullet::bulletInit()
{
	glColor3f(0.2,0.2,0.2);//���ɫ�ӵ�
	glutSolidSphere(bulletSize,20,20);//�����ӵ�����γ�߷ֱ�20
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);//����͸���ȣ���ֹ������ɫ
}
//�ӵ��˶�
void bullet::bulletMove()
{
	glPushMatrix();
		glTranslatef(x,y,z);//ƽ��
		glRotatef(theta,cos(beta*PI/180),0,-sin(beta*PI/180));//ˮƽ������ת
		glRotatef(beta,0,1,0);//��y�᷽����ʱ����ת��beta���ȣ���ֱ������ת
		bulletInit();
	glPopMatrix();
}
void bullet::setBulletBeta(float Beta)
{
	beta=Beta;
}
void bullet::setBulletTheta(float Theta)
{
	theta=Theta;
}
void bullet::setBulletX(float X)
{
	x=X;
}
void bullet::setBulletY(float Y)
{
	y=Y;
}
void bullet::setBulletZ(float Z)
{
	z=Z;
}
float bullet::getBulletBeta()
{
	return beta;
}
float bullet::getBulletTheta()
{
	return theta;
}
float bullet::getBulletX()
{
	return x;
}
float bullet::getBulletY()
{
	return y;
}
float bullet::getBulletZ()
{
	return z;
}
bullet::~bullet(void)
{
}
