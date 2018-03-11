//子弹
#include "bullet.h"
#include <gl\glut.h>
#include <math.h>
#define PI 3.1415926535897932384626433832795
bullet::bullet(void)
{
	bulletSize=0.01;//半径
}
bullet::bullet(float size)
{
	bulletSize=size;
}
void bullet::bulletInit()
{
	glColor3f(0.2,0.2,0.2);//深灰色子弹
	glutSolidSphere(bulletSize,20,20);//球形子弹，经纬线分别20
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);//设置透明度，防止场景变色
}
//子弹运动
void bullet::bulletMove()
{
	glPushMatrix();
		glTranslatef(x,y,z);//平移
		glRotatef(theta,cos(beta*PI/180),0,-sin(beta*PI/180));//水平方向旋转
		glRotatef(beta,0,1,0);//沿y轴方向逆时针旋转“beta”度，竖直方向旋转
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
