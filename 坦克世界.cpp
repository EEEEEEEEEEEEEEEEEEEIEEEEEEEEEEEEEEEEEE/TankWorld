#include <windows.h>
#include <mmsystem.h>//���ƶ�ý���ͷ�ļ�
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gl\glut.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include "bullet.h"//�ӵ�
#include "texture.h"//����
#include "SkyBox.h"//��պ�
#include "ground.h"//����
#include "tank.h"//̹��
#include "tree.h"//��
//���Ӿ�̬��
#pragma comment(lib,"glaux.lib")//����glaux.hͷ�ļ����������þ䣬�������ʱ����
#pragma comment(lib, "winmm.lib")//����winmm.lib��ſ���֧�ֶ�windows��ý��ı��

float eyeflag;
int w = 16;//1/2��ͼ��С����ͼΪ2w=32
//float t=0.3;
//float treez;

//�߶ȳ���ر�������
/**************************************************************************************/
#define  HEIGHT_RATIO 0.5   //���θ߶ȱ任����,Խ�ӽ�0����Խƽ̹
ground m_ground(w);//�������
/**************************************************************************************/


//��պ���ر�������
/**************************************************************************************/
float transformRatio=(float)2*w/MAP_SIZE;//MAP_SIZE=1024��"ground.h"�У�
SkyBox m_skybox(w);//������պ�
//������պ������齨��պ�
int boxId[][4]=
{
	{6,2,3,7},//ǰ
	{7,3,0,4},//��
	{5,1,2,6},//��
	{4,0,1,5},//��
	{1,0,3,2},//��
	{5,6,7,4}//��
};//������պе�����
GLfloat skybox[][3] = 
{
		{w, w, w},      // 0# 
		{-w, w, w},     // 1#
		{-w, w, -w},      // 2#
		{w, w, -w},       // 3#
		{w, -w, w},    // 4#
		{-w, -w, w},   // 5#
		{-w, -w, -w},     //6#
		{w, -w, -w}       // 7#
};
/*************************************************************************************/


//̹����ر�������
/**************************************************************************************/
#define PI 3.1415926535897932384626433832795
tank m_tank(0.3,w);//����̹��
float eyeToTankDistance=1;//�۾���̹�˾���
bullet tankBullets[30];//30���ӵ�
int bulletCount;//�ӵ���������
/**************************************************************************************/


//̹��&&�ӵ���غ���
/*************************************************************************************/
//�����ӵ�
void launchBullet()
{
	if(bulletCount>0)
	{
		//δ���������߽�ʱ|x|<|w|,|z|<|w|
		if((tankBullets[bulletCount].getBulletX()*tankBullets[bulletCount].getBulletX()<(w)*(w))&&(tankBullets[bulletCount].getBulletZ()*tankBullets[bulletCount].getBulletZ()<(w)*(w)))
		{
			//�ӵ�δ�򵽵��棬�ӵ��ĸ߶ȴ��ڵ��Ƶĸ߶�
			if(tankBullets[bulletCount].getBulletY()>(m_ground.terrainHeight(tankBullets[bulletCount].getBulletX()+w,tankBullets[bulletCount].getBulletZ()+w,transformRatio)-m_ground.terrainHeight(0,0,transformRatio))*transformRatio*HEIGHT_RATIO-0.85*w)
			{
				tankBullets[bulletCount].setBulletX(tankBullets[bulletCount].getBulletX()-0.06*sin(tankBullets[bulletCount].getBulletBeta()*PI/180)*cos(tankBullets[bulletCount].getBulletTheta()*PI/180));
				tankBullets[bulletCount].setBulletY(tankBullets[bulletCount].getBulletY()+0.06*sin(tankBullets[bulletCount].getBulletTheta()*PI/180));
				tankBullets[bulletCount].setBulletZ(tankBullets[bulletCount].getBulletZ()-0.06*cos(tankBullets[bulletCount].getBulletBeta()*PI/180)*cos(tankBullets[bulletCount].getBulletTheta()*PI/180));
				tankBullets[bulletCount].bulletMove();
			}
			else//�ӵ��򵽵��棬���ӵ��ŵ������⿴�����ĵط�
			{
				tankBullets[bulletCount].setBulletX(-2*w);
				tankBullets[bulletCount].setBulletY(-2*w);
				tankBullets[bulletCount].setBulletZ(-2*w);
				PlaySound (TEXT("��ը.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
			}
		}
		else//�ӵ������߽�,���ӵ����ڳ������һ��λ��
		{
			tankBullets[bulletCount].setBulletX(2*w);
			tankBullets[bulletCount].setBulletY(2*w);
			tankBullets[bulletCount].setBulletZ(2*w);
		}		
	}
}
/*************************************************************************************/



//�����غ��������������
/*************************************************************************************/
void cameraModel()
{
	//ͨ���ı��ӵ�ı价��
	gluLookAt(
		      //�۾�λ�ã�Beta��ֱ�������
		      m_tank.getTankX()+eyeToTankDistance*sin(m_tank.getTankBeta()*PI/180),
		      m_tank.getTankY()+2*m_tank.getTankSize(),
			  m_tank.getTankZ()+eyeToTankDistance*cos(m_tank.getTankBeta()*PI/180),
              //����������λ��
	          m_tank.getTankX()-eyeToTankDistance*sin(m_tank.getTankBeta()*PI/180),
			  m_tank.getTankY()+m_tank.getTankSize(),
			  m_tank.getTankZ()-cos(m_tank.getTankBeta()*PI/180),
              //�۾�������ķ�����y������
			  0,1,0);
}
/*
�ӵ�ת��
����ԭ��
void gluLookAt(GLdouble eyex,GLdouble eyey,GLdouble eyez,
               GLdouble centerx,GLdouble centery,GLdouble centerz,
			   GLdouble upx,GLdouble upy,GLdouble upz);
�ú�������һ����ͼ���󣬲��뵱ǰ������ˡ�
��һ��eyex, eyey,eyez ��������������λ��
�ڶ���centerx,centery,centerz �����ͷ��׼�����������������λ��
������upx,upy,upz ������ϵķ��������������еķ���

�����������Ϊ���Լ����Դ���
��һ�����ݾ����Դ���λ��
�ڶ������ݾ����۾����������λ��
���������ͷ������ķ�����Ϊ���������ͷ��ͬһ�����壩��
*/
/*************************************************************************************/





//����ر���������
/************************************************************************************/
#define N 20 //����20����
#define treeSize 1.2
tree m_tree[N];//���Ķ���
float treeX[N],treeY[N],treeZ[N];
int treeFlag[N];//�ж����Ƿ�Ҫ���ŵ��¶���
void initTreePos()//��ʼ����ľ��λ�ã�x,y�����������ָ��
{
	for(int i=0;i<N;i++)
	{
		//�����������λ��
		treeX[i]=rand()%(w*1600)/1000.0-0.8*w;
		treeZ[i]=rand()%(w*1600)/1000.0-0.8*w;
		
		treeY[i]=(m_ground.terrainHeight(treeX[i]+w,treeZ[i]+w,transformRatio)-m_ground.terrainHeight(0,0,transformRatio))*transformRatio*HEIGHT_RATIO;
		m_tree[i].setTreeX(treeX[i]);
		m_tree[i].setTreeY(treeY[i]-0.85*w);
		m_tree[i].setTreeZ(treeZ[i]);
		m_tree[i].initTreeImg();
	}
}
//����
void setTree()
{
	for(int j=0;j<N;j++)
	{	
		m_tree[j].setTreeBeta(m_tank.getTankBeta());
		m_tree[j].drawTree(treeSize);
	}
}
//�ӵ������ļ��鼰Ч��ʵ��
void shootTreeDetect()
{
	if(bulletCount>0)
	{
		for(int i=0;i<N;i++)
		{//���ӵ�����
			float delta=abs((tankBullets[bulletCount].getBulletX()-m_tree[i].getTreeX())*sin(m_tree[i].getTreeBeta()*PI/180)
				+(tankBullets[bulletCount].getBulletZ()-m_tree[i].getTreeZ())*cos(m_tree[i].getTreeBeta()*PI/180));//�ж��ӵ��Ƿ�������ͼƬ����
		    float deltaX=abs(tankBullets[bulletCount].getBulletX()-m_tree[i].getTreeX());//�ж��ӵ��Ƿ����ͼƬ��Χ
		    float deltaZ=abs(tankBullets[bulletCount].getBulletZ()-m_tree[i].getTreeZ());//�ж��ӵ��Ƿ����ͼƬ��Χ
		    if(delta<0.08&&deltaX<abs(treeSize*cos(m_tree[i].getTreeBeta()*PI/180)/2)&&deltaZ<abs(treeSize*sin(m_tree[i].getTreeBeta()*PI/180)/2)&&abs(m_tree[i].getTreeY()-tankBullets[bulletCount].getBulletY())<treeSize)
			{
				treeFlag[i]=1;
	    	    tankBullets[bulletCount].setBulletX(2*w);
	   		    tankBullets[bulletCount].setBulletY(2*w);
		        tankBullets[bulletCount].setBulletZ(2*w);
			    PlaySound (TEXT("��ը.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
			}
	        if(treeFlag[i]==1&&m_tree[i].getTreeTheta()<=90)//���ŵ��µ����Ķ���
			{
	    		 m_tree[i].setTreeTheta(m_tree[i].getTreeTheta()+0.8);
			}
	        else
			     treeFlag[i]=2;//ʹ���ӵ������������ڵ��µ���
		}
	}
}
//̹����������ײ����
void treeCollide()
{
	for(int i=0;i<N;i++)
	{
		float z=m_tree[i].getTreeZ()+m_tank.getTankSize()*cos(m_tree[i].getTreeBeta()*PI/180)/2;
		float x=m_tree[i].getTreeX()+m_tank.getTankSize()*sin(m_tree[i].getTreeBeta()*PI/180)/2;
		float delta=abs((m_tank.getTankX()-x)*sin(m_tree[i].getTreeBeta()*PI/180)+(m_tank.getTankZ()-z)*cos(m_tree[i].getTreeBeta()*PI/180));
		float deltaX=abs(m_tank.getTankX()-x);
		float deltaZ=abs(m_tank.getTankZ()-z);
		if(delta<0.1&&deltaX<abs(treeSize*cos(m_tree[i].getTreeBeta()*PI/180)/4)&&deltaZ<abs(treeSize*sin(m_tree[i].getTreeBeta()*PI/180)/4))
		{
			if(m_tank.getTankDirection())
			{
				m_tank.setTankX(m_tank.getTankX()+0.05*sin(m_tank.getTankBeta()*PI/180)*cos(m_tank.getTankTheta()*PI/180));
				m_tank.setTankY(m_tank.getTankY()-0.05*sin(m_tank.getTankTheta()*PI/180));
				m_tank.setTankZ(m_tank.getTankZ()+0.05*cos(m_tank.getTankBeta()*PI/180)*cos(m_tank.getTankTheta()*PI/180));
			}
			else
			{
				m_tank.setTankX(m_tank.getTankX()-0.05*sin(m_tank.getTankBeta()*PI/180)*cos(m_tank.getTankTheta()*PI/180));
				m_tank.setTankY(m_tank.getTankY()+0.05*sin(m_tank.getTankTheta()*PI/180));
				m_tank.setTankZ(m_tank.getTankZ()-0.05*cos(m_tank.getTankBeta()*PI/180)*cos(m_tank.getTankTheta()*PI/180));
			}
		}
	}
}
/************************************************************************************/





//��ʼ��
void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);//����
	glEnable(GL_TEXTURE_2D);//���ö�ά����	
	m_skybox.initSkyBox();//��ʼ����պ�,������պ�	
    m_ground.InitGL();//��ʼ���߶ȳ����������
	initTreePos();//��������λ��
	m_tank.setTankY((m_ground.Height(MAP_SIZE/2,MAP_SIZE/2)-m_ground.Height(0,0))*transformRatio*HEIGHT_RATIO-0.835*w);//��ʼ��̹�˸߶�
	m_tank.tankTexInit();//��ʼ��̹��,����̹��
	glEnable(GL_DEPTH_TEST);//������Ȳ���
	glDepthFunc(GL_LESS);//��Ȼ���
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
    gluPerspective(58, 1, 0.0001, 9999999);//������Ұ��Χ
	/*
	void gluPerspective(GLdouble fovy, GLdouble aspect,GLdouble zNear,GLdouble zFar)
	fovy��ָ���Ӿ������Ұ�ĽǶȣ��Զ���Ϊ��λ��y������·���
����aspect��ָ������Ӿ���Ŀ�߱ȣ�x ƽ���ϣ�
����zNear:ָ���۲��ߵ��Ӿ��������Ĳü���ľ��루����Ϊ������
����zFar��ָ���۲��ߵ��Ӿ������Զ�Ĳü���ľ��루����Ϊ������
	*/

}
//��ʾ����
void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glViewport(0,0,1000,1000);//������
	m_skybox.drawSkyBox(boxId,skybox);//��պ�
	glMatrixMode(GL_MODELVIEW);//��ģ���Ӿ������ջӦ�����ľ������
	glLoadIdentity();//����ǰ�û�����ϵ��ԭ���Ƶ���Ļ����
	cameraModel();//�����ӽ�
	setTree();//������
	shootTreeDetect();//�ӵ��������⼰Ч��
	m_tank.setTankTheta(
		atan(
		(m_ground.terrainHeight(m_tank.getTankX()+w-m_tank.getTankSize()*cos(m_tank.getTankTheta()*PI/180)*sin(m_tank.getTankBeta()*PI/180)/2.5,m_tank.getTankZ()+w-m_tank.getTankSize()*cos(m_tank.getTankTheta()*PI/180)*cos(m_tank.getTankBeta()*PI/180)/2.5,transformRatio)-
		m_ground.terrainHeight(m_tank.getTankX()+w+m_tank.getTankSize()*cos(m_tank.getTankTheta()*PI/180)*sin(m_tank.getTankBeta()*PI/180)/2.5,m_tank.getTankZ()+w+m_tank.getTankSize()*cos(m_tank.getTankTheta()*PI/180)*cos(m_tank.getTankBeta()*PI/180)/2.5,transformRatio))
		*transformRatio*HEIGHT_RATIO*1.25/m_tank.getTankSize()
		)*180/PI);//����̹���ڵ���ͼ�ϵ����
	m_tank.tankMove();//̹�˵��ƶ�
	m_ground.RenderHeightMap();//����ͼ�Ļ���
	m_tank.collideDetect();//��ײ����
	treeCollide();//̹�˺�����ײ���
	launchBullet();//�ӵ����亯��
    glutSwapBuffers();//ʹ��˫������������˸����
}

//���̿��ƻص�����
void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'w'://ǰ��
		m_tank.setTankDirection(1);
		m_tank.setTankX(m_tank.getTankX()-0.05*sin(m_tank.getTankBeta()*PI/180)*cos(m_tank.getTankTheta()*PI/180));
		m_tank.setTankY(m_tank.getTankY()+0.05*sin(m_tank.getTankTheta()*PI/180));
		m_tank.setTankZ(m_tank.getTankZ()-0.05*cos(m_tank.getTankBeta()*PI/180)*cos(m_tank.getTankTheta()*PI/180));
		//printf("tankx=%f  tanky=%f  tankz=%f tankTheta=%f\n",m_tank.getTankX(),m_tank.getTankY(),m_tank.getTankZ(),m_tank.getTankTheta());
		break;
	case 's'://����
		m_tank.setTankDirection(0);
		m_tank.setTankX(m_tank.getTankX()+0.05*sin(m_tank.getTankBeta()*PI/180)*cos(m_tank.getTankTheta()*PI/180));
		m_tank.setTankY(m_tank.getTankY()-0.05*sin(m_tank.getTankTheta()*PI/180));
		m_tank.setTankZ(m_tank.getTankZ()+0.05*cos(m_tank.getTankBeta()*PI/180)*cos(m_tank.getTankTheta()*PI/180));
		//printf("tankx=%f  tanky=%f  tankz=%f tankTheta=%f\n",m_tank.getTankX(),m_tank.getTankY(),m_tank.getTankZ(),m_tank.getTankTheta());
		break;
	case 'a'://��ת
		m_tank.setTankBeta(m_tank.getTankBeta()+1);//
		break;
	case 'd'://��ת
		m_tank.setTankBeta(m_tank.getTankBeta()-1);
		break;
	case' '://�����ӵ�
		if(bulletCount<=29)
		{
			bulletCount++;
	    	tankBullets[bulletCount].setBulletX(m_tank.getTankX()+m_tank.getTankSize()*0.6*sin(m_tank.getTankTheta()*PI/180)*sin(m_tank.getTankBeta()*PI/180));
	    	tankBullets[bulletCount].setBulletY(m_tank.getTankY()+m_tank.getTankSize()*0.6*cos(m_tank.getTankTheta()*PI/180));
	    	tankBullets[bulletCount].setBulletZ(m_tank.getTankZ()+m_tank.getTankSize()*0.6*sin(m_tank.getTankTheta()*PI/180)*cos(m_tank.getTankBeta()*PI/180));
	    	tankBullets[bulletCount].setBulletTheta(atan(sin(m_tank.getTankTheta()*PI/180)*cos(m_tank.getBatteryBeta()*PI/180))*180/PI);//ʹ�ӵ���̹����Ͳ����һ��
	    	tankBullets[bulletCount].setBulletBeta(m_tank.getTankBeta()+m_tank.getBatteryBeta());	
	    	//printf("ʣ��%d���ӵ�\n",30-bulletCount);
	    	PlaySound (TEXT("����.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
		}
		break;
 	}
	glutPostRedisplay();
}

//������̻ص�����
void specail(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_LEFT://��ת�ڹ�
		m_tank.setBatteryBeta(m_tank.getBatteryBeta()+1);
		break;
	case GLUT_KEY_RIGHT://�ڹ���ת
		m_tank.setBatteryBeta(m_tank.getBatteryBeta()-1);
		break;
	}
	glutPostRedisplay();
}
//������
int main(int argc, char** argv)
{
      glutInit(&argc, argv);
      glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
      glutInitWindowSize(1000, 1000);            
      glutInitWindowPosition(20,20);
      glutCreateWindow("̹������");
      glutDisplayFunc(display);                   
      glutIdleFunc(display);
	  glutSpecialFunc(specail);
      glutKeyboardFunc(keyboard);	
      init();                                                      
      glutMainLoop();	                      
	  return 0;
}