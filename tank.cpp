//坦克
#include <stdlib.h>
#include <stdio.h>
#include <gl/glut.h>
#include <gl/glu.h>
#include <gl/glaux.h>
#include <math.h>
#include "texture.h"
#include "tank.h"
//构造函数，初始化
tank::tank(float size,int mapsize)
{
	tankSize=size;//0.3
	w=mapsize;//1/2地图大小 16
	//获取图片
	t_texture.setImg(img);
	t_texture.setTexId(t_texID);

	//初始化坦克坐标
	tankX=0;
	tankY=0;
	tankZ=0;

	tankTheta=0;//θtankTheta定义坦克水平转角
	tankBeta=0;//βtankBeta定义竖直方向倾角
	tankDirection=0;//坦克方向
	tankBatteryBeta=0;//定义坦克炮台转角
	tankBatteryTheta=0;//定义坦克炮台倾角	
}
//设置坦克纹理图片
void tank::tankTexInit()
{
	t_texture.loadTexture("skybox\\tex2.bmp", 0);
}
//返回坦克尺寸数据
float tank::getTankSize()
{
	return tankSize;//0.3
}
//设置坐标
void tank::setTankX(float x)
{
	tankX=x;
}
void tank::setTankY(float y)
{
	tankY=y;
}
void tank::setTankZ(float z)
{
	tankZ=z;
}
//设置角度
void tank::setTankTheta(float theta)
{
	tankTheta=theta;
}
void tank::setTankBeta(float beta)
{
	tankBeta=beta;
}
//炮台角度，方向
void tank::setBatteryTheta(float btheta)
{
	tankBatteryTheta=btheta;
}
void tank::setBatteryBeta(float bbeta)
{
	tankBatteryBeta=bbeta;
}
void tank::setTankDirection(float direction)
{
	tankDirection=direction;
}
//返回一系列坦克信息
float tank::getTankX()
{
	return tankX;
}
float tank::getTankY()
{
	return tankY;
}
float tank::getTankZ()
{
	return tankZ;
}
float tank::getTankTheta()
{
	return tankTheta;
}
float tank::getTankBeta()
{
	return tankBeta;
}
float tank::getBatteryTheta()
{
	return tankBatteryTheta;
}
float tank::getBatteryBeta()
{
	return tankBatteryBeta;
}
float tank::getTankDirection()
{
	return tankDirection;
}
//坦克的绘制，并添加纹理
void tank::tankModel()//size指定大小
{
	//坦克中心坐标
	float centerx=0;
	float centery=0;
	float centerz=0;
	float size=tankSize;//0.3
	//坦克盒，构建坦克大小
	GLfloat tankbox[][3] = 
	{
		//坦克为梯台
		//坦克底
		{centerx+size/2,centery,centerz+size/2},      // 0# {0.15,0.0,0.15}
		{centerx+size/2,centery,centerz-size/2},     // 1# {0.15,0.0,-0.15}
		{centerx-size/2,centery,centerz-size/2},      // 2# {-0.15,0.0,-0.15}
		{centerx-size/2,centery,centerz+size/2},       // 3# {-0.15,0.0,0.15}
        //坦克顶
		{centerx+size/4, centery+size/2, centerz+size/4},    // 4# 
		{centerx+size/4, centery+size/2, centerz-size/4},   // 5#
		{centerx-size/4, centery+size/2, centerz-size/4},     //6#
		{centerx-size/4, centery+size/2, centerz+size/4},      // 7#
		//炮台为方体
        //炮台底
		{centerx+size/8, centery+size/2, centerz+size/8},    // 8#
		{centerx+size/8, centery+size/2, centerz-size/8},   // 9#
		{centerx-size/8, centery+size/2, centerz-size/8},     //10#
		{centerx-size/8, centery+size/2, centerz+size/8},  //11#
        //炮台顶
		{centerx+size/8, centery+size/2+size/5, centerz+size/8},    // 12#
		{centerx+size/8, centery+size/2+size/5, centerz-size/8},   // 13#
		{centerx-size/8, centery+size/2+size/5, centerz-size/8},     //14#
		{centerx-size/8, centery+size/2+size/5, centerz+size/8},  //15#
        //坦克炮管前
		{centerx+size/25,centery+5*size/8-size/25,centerz-size/8},//16
		{centerx+size/25,centery+5*size/8+size/25,centerz-size/8},//17
		{centerx-size/25,centery+5*size/8+size/25,centerz-size/8},//18
		{centerx-size/25,centery+5*size/8-size/25,centerz-size/8},//19	
        //坦克炮管后
		{centerx+size/25,centery+5*size/8-size/25,centerz-size/8-size*0.7},//20
		{centerx+size/25,centery+5*size/8+size/25,centerz-size/8-size*0.7},//21
		{centerx-size/25,centery+5*size/8+size/25,centerz-size/8-size*0.7},//22
		{centerx-size/25,centery+5*size/8-size/25,centerz-size/8-size*0.7},//23	
	};
	//根据坦克序列组建坦克
	int tankboxId[][4]=
	{
		//坦克
		//底，右，前，上，左，后
		{0,1,2,3},{0,1,5,4},{1,2,6,5},{4,5,6,7},{2,6,7,3},{3,0,4,7},
		//炮台
		//底，右，前，上，左，后
		{8,9,10,11},{8,9,13,12},{9,10,14,13},{12,13,14,15},{10,14,15,11},{11,8,12,15},
		//炮管
		//后，右，上，前，左，下
		{16,17,18,19},{16,17,21,20},{17,18,22,21},{20,21,22,23},{18,22,23,19},{19,16,20,23}
	};
	//绘制坦克纹理
	glDisable(GL_ALPHA_TEST);//禁止ALPHA测试
	t_texture.Tex(0,tankboxId[0],tankbox);
	t_texture.Tex(0,tankboxId[1],tankbox);
	t_texture.Tex(0,tankboxId[2],tankbox);
	t_texture.Tex(0,tankboxId[3],tankbox);
	t_texture.Tex(0,tankboxId[4],tankbox);
	t_texture.Tex(0,tankboxId[5],tankbox);
	glPushMatrix();
	//炮台
		glRotatef(tankBatteryBeta,0,1,0);
		t_texture.Tex(0,tankboxId[6],tankbox);
		t_texture.Tex(0,tankboxId[7],tankbox);
		t_texture.Tex(0,tankboxId[8],tankbox);
		t_texture.Tex(0,tankboxId[9],tankbox);
		t_texture.Tex(0,tankboxId[10],tankbox);
		t_texture.Tex(0,tankboxId[11],tankbox);
    //炮管
		t_texture.Tex(0,tankboxId[12],tankbox);
		t_texture.Tex(0,tankboxId[13],tankbox);
		t_texture.Tex(0,tankboxId[14],tankbox);
		t_texture.Tex(0,tankboxId[15],tankbox);
		t_texture.Tex(0,tankboxId[16],tankbox);
		t_texture.Tex(0,tankboxId[17],tankbox);
	glPopMatrix();
}
//坦克的移动
void tank::tankMove()
{
	glPushMatrix();
		glTranslatef(tankX,tankY,tankZ);//平移
		glRotatef(tankTheta,cos(tankBeta*PI/180),0,-sin(tankBeta*PI/180));//
		glRotatef(tankBeta,0,1,0);//沿y轴旋转，即限定坦克只能在地面左右方向移动，而不能跳起
		tankModel();
	glPopMatrix();
}
//碰撞检验,与天空盒的碰撞检测
void tank::collideDetect()
{
    //(0.97*w-tankSize/2)=15.37<16
	//与x,z方向的碰撞检，包围盒AABB
	if(tankX*tankX>=(0.97*w-tankSize/2)*(0.97*w-tankSize/2)||tankZ*tankZ>=(0.97*w-tankSize/2)*(0.97*w-tankSize/2))
	{
		if(tankDirection)
		{
			tankX+=0.05*sin(tankBeta*PI/180)*cos(tankTheta*PI/180);
			tankY-=0.05*sin(tankTheta*PI/180);
			tankZ+=0.05*cos(tankBeta*PI/180)*cos(tankTheta*PI/180);	
		}
		else
		{
			tankX-=0.05*sin(tankBeta*PI/180)*cos(tankTheta*PI/180);
			tankY+=0.05*sin(tankTheta*PI/180);
			tankZ-=0.05*cos(tankBeta*PI/180)*cos(tankTheta*PI/180);
		}
	}
}
tank::~tank(void)
{
}




