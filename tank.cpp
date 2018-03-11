//̹��
#include <stdlib.h>
#include <stdio.h>
#include <gl/glut.h>
#include <gl/glu.h>
#include <gl/glaux.h>
#include <math.h>
#include "texture.h"
#include "tank.h"
//���캯������ʼ��
tank::tank(float size,int mapsize)
{
	tankSize=size;//0.3
	w=mapsize;//1/2��ͼ��С 16
	//��ȡͼƬ
	t_texture.setImg(img);
	t_texture.setTexId(t_texID);

	//��ʼ��̹������
	tankX=0;
	tankY=0;
	tankZ=0;

	tankTheta=0;//��tankTheta����̹��ˮƽת��
	tankBeta=0;//��tankBeta������ֱ�������
	tankDirection=0;//̹�˷���
	tankBatteryBeta=0;//����̹����̨ת��
	tankBatteryTheta=0;//����̹����̨���	
}
//����̹������ͼƬ
void tank::tankTexInit()
{
	t_texture.loadTexture("skybox\\tex2.bmp", 0);
}
//����̹�˳ߴ�����
float tank::getTankSize()
{
	return tankSize;//0.3
}
//��������
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
//���ýǶ�
void tank::setTankTheta(float theta)
{
	tankTheta=theta;
}
void tank::setTankBeta(float beta)
{
	tankBeta=beta;
}
//��̨�Ƕȣ�����
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
//����һϵ��̹����Ϣ
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
//̹�˵Ļ��ƣ����������
void tank::tankModel()//sizeָ����С
{
	//̹����������
	float centerx=0;
	float centery=0;
	float centerz=0;
	float size=tankSize;//0.3
	//̹�˺У�����̹�˴�С
	GLfloat tankbox[][3] = 
	{
		//̹��Ϊ��̨
		//̹�˵�
		{centerx+size/2,centery,centerz+size/2},      // 0# {0.15,0.0,0.15}
		{centerx+size/2,centery,centerz-size/2},     // 1# {0.15,0.0,-0.15}
		{centerx-size/2,centery,centerz-size/2},      // 2# {-0.15,0.0,-0.15}
		{centerx-size/2,centery,centerz+size/2},       // 3# {-0.15,0.0,0.15}
        //̹�˶�
		{centerx+size/4, centery+size/2, centerz+size/4},    // 4# 
		{centerx+size/4, centery+size/2, centerz-size/4},   // 5#
		{centerx-size/4, centery+size/2, centerz-size/4},     //6#
		{centerx-size/4, centery+size/2, centerz+size/4},      // 7#
		//��̨Ϊ����
        //��̨��
		{centerx+size/8, centery+size/2, centerz+size/8},    // 8#
		{centerx+size/8, centery+size/2, centerz-size/8},   // 9#
		{centerx-size/8, centery+size/2, centerz-size/8},     //10#
		{centerx-size/8, centery+size/2, centerz+size/8},  //11#
        //��̨��
		{centerx+size/8, centery+size/2+size/5, centerz+size/8},    // 12#
		{centerx+size/8, centery+size/2+size/5, centerz-size/8},   // 13#
		{centerx-size/8, centery+size/2+size/5, centerz-size/8},     //14#
		{centerx-size/8, centery+size/2+size/5, centerz+size/8},  //15#
        //̹���ڹ�ǰ
		{centerx+size/25,centery+5*size/8-size/25,centerz-size/8},//16
		{centerx+size/25,centery+5*size/8+size/25,centerz-size/8},//17
		{centerx-size/25,centery+5*size/8+size/25,centerz-size/8},//18
		{centerx-size/25,centery+5*size/8-size/25,centerz-size/8},//19	
        //̹���ڹܺ�
		{centerx+size/25,centery+5*size/8-size/25,centerz-size/8-size*0.7},//20
		{centerx+size/25,centery+5*size/8+size/25,centerz-size/8-size*0.7},//21
		{centerx-size/25,centery+5*size/8+size/25,centerz-size/8-size*0.7},//22
		{centerx-size/25,centery+5*size/8-size/25,centerz-size/8-size*0.7},//23	
	};
	//����̹�������齨̹��
	int tankboxId[][4]=
	{
		//̹��
		//�ף��ң�ǰ���ϣ��󣬺�
		{0,1,2,3},{0,1,5,4},{1,2,6,5},{4,5,6,7},{2,6,7,3},{3,0,4,7},
		//��̨
		//�ף��ң�ǰ���ϣ��󣬺�
		{8,9,10,11},{8,9,13,12},{9,10,14,13},{12,13,14,15},{10,14,15,11},{11,8,12,15},
		//�ڹ�
		//���ң��ϣ�ǰ������
		{16,17,18,19},{16,17,21,20},{17,18,22,21},{20,21,22,23},{18,22,23,19},{19,16,20,23}
	};
	//����̹������
	glDisable(GL_ALPHA_TEST);//��ֹALPHA����
	t_texture.Tex(0,tankboxId[0],tankbox);
	t_texture.Tex(0,tankboxId[1],tankbox);
	t_texture.Tex(0,tankboxId[2],tankbox);
	t_texture.Tex(0,tankboxId[3],tankbox);
	t_texture.Tex(0,tankboxId[4],tankbox);
	t_texture.Tex(0,tankboxId[5],tankbox);
	glPushMatrix();
	//��̨
		glRotatef(tankBatteryBeta,0,1,0);
		t_texture.Tex(0,tankboxId[6],tankbox);
		t_texture.Tex(0,tankboxId[7],tankbox);
		t_texture.Tex(0,tankboxId[8],tankbox);
		t_texture.Tex(0,tankboxId[9],tankbox);
		t_texture.Tex(0,tankboxId[10],tankbox);
		t_texture.Tex(0,tankboxId[11],tankbox);
    //�ڹ�
		t_texture.Tex(0,tankboxId[12],tankbox);
		t_texture.Tex(0,tankboxId[13],tankbox);
		t_texture.Tex(0,tankboxId[14],tankbox);
		t_texture.Tex(0,tankboxId[15],tankbox);
		t_texture.Tex(0,tankboxId[16],tankbox);
		t_texture.Tex(0,tankboxId[17],tankbox);
	glPopMatrix();
}
//̹�˵��ƶ�
void tank::tankMove()
{
	glPushMatrix();
		glTranslatef(tankX,tankY,tankZ);//ƽ��
		glRotatef(tankTheta,cos(tankBeta*PI/180),0,-sin(tankBeta*PI/180));//
		glRotatef(tankBeta,0,1,0);//��y����ת�����޶�̹��ֻ���ڵ������ҷ����ƶ�������������
		tankModel();
	glPopMatrix();
}
//��ײ����,����պе���ײ���
void tank::collideDetect()
{
    //(0.97*w-tankSize/2)=15.37<16
	//��x,z�������ײ�죬��Χ��AABB
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




