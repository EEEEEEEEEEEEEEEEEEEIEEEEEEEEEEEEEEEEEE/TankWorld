#include <windows.h>
#include <mmsystem.h>//控制多媒体的头文件
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gl\glut.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include "bullet.h"//子弹
#include "texture.h"//纹理
#include "SkyBox.h"//天空盒
#include "ground.h"//地面
#include "tank.h"//坦克
#include "tree.h"//树
//链接静态库
#pragma comment(lib,"glaux.lib")//引用glaux.h头文件，必须加入该句，否则编译时出错
#pragma comment(lib, "winmm.lib")//导入winmm.lib库才可以支持对windows多媒体的编程

float eyeflag;
int w = 16;//1/2地图大小，地图为2w=32
//float t=0.3;
//float treez;

//高度场相关变量定义
/**************************************************************************************/
#define  HEIGHT_RATIO 0.5   //地形高度变换比例,越接近0地势越平坦
ground m_ground(w);//构造地势
/**************************************************************************************/


//天空盒相关变量定义
/**************************************************************************************/
float transformRatio=(float)2*w/MAP_SIZE;//MAP_SIZE=1024，"ground.h"中，
SkyBox m_skybox(w);//构造天空盒
//根据天空盒序列组建天空盒
int boxId[][4]=
{
	{6,2,3,7},//前
	{7,3,0,4},//右
	{5,1,2,6},//左
	{4,0,1,5},//后
	{1,0,3,2},//天
	{5,6,7,4}//地
};//设置天空盒的序列
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


//坦克相关变量定义
/**************************************************************************************/
#define PI 3.1415926535897932384626433832795
tank m_tank(0.3,w);//构造坦克
float eyeToTankDistance=1;//眼睛到坦克距离
bullet tankBullets[30];//30发子弹
int bulletCount;//子弹用量计数
/**************************************************************************************/


//坦克&&子弹相关函数
/*************************************************************************************/
//发射子弹
void launchBullet()
{
	if(bulletCount>0)
	{
		//未超出场景边界时|x|<|w|,|z|<|w|
		if((tankBullets[bulletCount].getBulletX()*tankBullets[bulletCount].getBulletX()<(w)*(w))&&(tankBullets[bulletCount].getBulletZ()*tankBullets[bulletCount].getBulletZ()<(w)*(w)))
		{
			//子弹未打到地面，子弹的高度大于地势的高度
			if(tankBullets[bulletCount].getBulletY()>(m_ground.terrainHeight(tankBullets[bulletCount].getBulletX()+w,tankBullets[bulletCount].getBulletZ()+w,transformRatio)-m_ground.terrainHeight(0,0,transformRatio))*transformRatio*HEIGHT_RATIO-0.85*w)
			{
				tankBullets[bulletCount].setBulletX(tankBullets[bulletCount].getBulletX()-0.06*sin(tankBullets[bulletCount].getBulletBeta()*PI/180)*cos(tankBullets[bulletCount].getBulletTheta()*PI/180));
				tankBullets[bulletCount].setBulletY(tankBullets[bulletCount].getBulletY()+0.06*sin(tankBullets[bulletCount].getBulletTheta()*PI/180));
				tankBullets[bulletCount].setBulletZ(tankBullets[bulletCount].getBulletZ()-0.06*cos(tankBullets[bulletCount].getBulletBeta()*PI/180)*cos(tankBullets[bulletCount].getBulletTheta()*PI/180));
				tankBullets[bulletCount].bulletMove();
			}
			else//子弹打到地面，把子弹放到场景外看不到的地方
			{
				tankBullets[bulletCount].setBulletX(-2*w);
				tankBullets[bulletCount].setBulletY(-2*w);
				tankBullets[bulletCount].setBulletZ(-2*w);
				PlaySound (TEXT("爆炸.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
			}
		}
		else//子弹超出边界,把子弹放在场景外的一个位置
		{
			tankBullets[bulletCount].setBulletX(2*w);
			tankBullets[bulletCount].setBulletY(2*w);
			tankBullets[bulletCount].setBulletZ(2*w);
		}		
	}
}
/*************************************************************************************/



//相机相关函数，摄像机漫游
/*************************************************************************************/
void cameraModel()
{
	//通过改变视点改变环境
	gluLookAt(
		      //眼睛位置，Beta竖直方向倾角
		      m_tank.getTankX()+eyeToTankDistance*sin(m_tank.getTankBeta()*PI/180),
		      m_tank.getTankY()+2*m_tank.getTankSize(),
			  m_tank.getTankZ()+eyeToTankDistance*cos(m_tank.getTankBeta()*PI/180),
              //看到的物体位置
	          m_tank.getTankX()-eyeToTankDistance*sin(m_tank.getTankBeta()*PI/180),
			  m_tank.getTankY()+m_tank.getTankSize(),
			  m_tank.getTankZ()-cos(m_tank.getTankBeta()*PI/180),
              //眼睛看物体的方向，沿y轴向上
			  0,1,0);
}
/*
视点转换
函数原型
void gluLookAt(GLdouble eyex,GLdouble eyey,GLdouble eyez,
               GLdouble centerx,GLdouble centery,GLdouble centerz,
			   GLdouble upx,GLdouble upy,GLdouble upz);
该函数定义一个视图矩阵，并与当前矩阵相乘。
第一组eyex, eyey,eyez 相机在世界坐标的位置
第二组centerx,centery,centerz 相机镜头对准的物体在世界坐标的位置
第三组upx,upy,upz 相机向上的方向在世界坐标中的方向

你把相机想象成为你自己的脑袋：
第一组数据就是脑袋的位置
第二组数据就是眼睛看的物体的位置
第三组就是头顶朝向的方向（因为你可以歪着头看同一个物体）。
*/
/*************************************************************************************/





//树相关变量及函数
/************************************************************************************/
#define N 20 //定义20棵树
#define treeSize 1.2
tree m_tree[N];//树的对象
float treeX[N],treeY[N],treeZ[N];
int treeFlag[N];//判断树是否要播放倒下动画
void initTreePos()//初始化树木的位置，x,y坐标由随机数指定
{
	for(int i=0;i<N;i++)
	{
		//随机生成树的位置
		treeX[i]=rand()%(w*1600)/1000.0-0.8*w;
		treeZ[i]=rand()%(w*1600)/1000.0-0.8*w;
		
		treeY[i]=(m_ground.terrainHeight(treeX[i]+w,treeZ[i]+w,transformRatio)-m_ground.terrainHeight(0,0,transformRatio))*transformRatio*HEIGHT_RATIO;
		m_tree[i].setTreeX(treeX[i]);
		m_tree[i].setTreeY(treeY[i]-0.85*w);
		m_tree[i].setTreeZ(treeZ[i]);
		m_tree[i].initTreeImg();
	}
}
//种树
void setTree()
{
	for(int j=0;j<N;j++)
	{	
		m_tree[j].setTreeBeta(m_tank.getTankBeta());
		m_tree[j].drawTree(treeSize);
	}
}
//子弹打到树的检验及效果实现
void shootTreeDetect()
{
	if(bulletCount>0)
	{
		for(int i=0;i<N;i++)
		{//若子弹打到树
			float delta=abs((tankBullets[bulletCount].getBulletX()-m_tree[i].getTreeX())*sin(m_tree[i].getTreeBeta()*PI/180)
				+(tankBullets[bulletCount].getBulletZ()-m_tree[i].getTreeZ())*cos(m_tree[i].getTreeBeta()*PI/180));//判断子弹是否与树的图片共面
		    float deltaX=abs(tankBullets[bulletCount].getBulletX()-m_tree[i].getTreeX());//判断子弹是否进入图片范围
		    float deltaZ=abs(tankBullets[bulletCount].getBulletZ()-m_tree[i].getTreeZ());//判断子弹是否进入图片范围
		    if(delta<0.08&&deltaX<abs(treeSize*cos(m_tree[i].getTreeBeta()*PI/180)/2)&&deltaZ<abs(treeSize*sin(m_tree[i].getTreeBeta()*PI/180)/2)&&abs(m_tree[i].getTreeY()-tankBullets[bulletCount].getBulletY())<treeSize)
			{
				treeFlag[i]=1;
	    	    tankBullets[bulletCount].setBulletX(2*w);
	   		    tankBullets[bulletCount].setBulletY(2*w);
		        tankBullets[bulletCount].setBulletZ(2*w);
			    PlaySound (TEXT("爆炸.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
			}
	        if(treeFlag[i]==1&&m_tree[i].getTreeTheta()<=90)//播放倒下的树的动画
			{
	    		 m_tree[i].setTreeTheta(m_tree[i].getTreeTheta()+0.8);
			}
	        else
			     treeFlag[i]=2;//使得子弹不能再作用于倒下的树
		}
	}
}
//坦克与树的碰撞检验
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





//初始化
void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);//清屏
	glEnable(GL_TEXTURE_2D);//启用二维纹理	
	m_skybox.initSkyBox();//初始化天空盒,纹理天空盒	
    m_ground.InitGL();//初始化高度场，纹理地势
	initTreePos();//生成树的位置
	m_tank.setTankY((m_ground.Height(MAP_SIZE/2,MAP_SIZE/2)-m_ground.Height(0,0))*transformRatio*HEIGHT_RATIO-0.835*w);//初始化坦克高度
	m_tank.tankTexInit();//初始化坦克,纹理坦克
	glEnable(GL_DEPTH_TEST);//启用深度测试
	glDepthFunc(GL_LESS);//深度缓冲
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
    gluPerspective(58, 1, 0.0001, 9999999);//设置视野范围
	/*
	void gluPerspective(GLdouble fovy, GLdouble aspect,GLdouble zNear,GLdouble zFar)
	fovy：指定视景体的视野的角度，以度数为单位，y轴的上下方向
　　aspect：指定你的视景体的宽高比（x 平面上）
　　zNear:指定观察者到视景体的最近的裁剪面的距离（必须为正数）
　　zFar：指定观察者到视景体的最远的裁剪面的距离（必须为正数）
	*/

}
//显示函数
void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glViewport(0,0,1000,1000);//主界面
	m_skybox.drawSkyBox(boxId,skybox);//天空盒
	glMatrixMode(GL_MODELVIEW);//对模型视景矩阵堆栈应用随后的矩阵操作
	glLoadIdentity();//将当前用户坐标系的原点移到屏幕中心
	cameraModel();//设置视角
	setTree();//生成树
	shootTreeDetect();//子弹打到树额检测及效果
	m_tank.setTankTheta(
		atan(
		(m_ground.terrainHeight(m_tank.getTankX()+w-m_tank.getTankSize()*cos(m_tank.getTankTheta()*PI/180)*sin(m_tank.getTankBeta()*PI/180)/2.5,m_tank.getTankZ()+w-m_tank.getTankSize()*cos(m_tank.getTankTheta()*PI/180)*cos(m_tank.getTankBeta()*PI/180)/2.5,transformRatio)-
		m_ground.terrainHeight(m_tank.getTankX()+w+m_tank.getTankSize()*cos(m_tank.getTankTheta()*PI/180)*sin(m_tank.getTankBeta()*PI/180)/2.5,m_tank.getTankZ()+w+m_tank.getTankSize()*cos(m_tank.getTankTheta()*PI/180)*cos(m_tank.getTankBeta()*PI/180)/2.5,transformRatio))
		*transformRatio*HEIGHT_RATIO*1.25/m_tank.getTankSize()
		)*180/PI);//计算坦克在地形图上的倾角
	m_tank.tankMove();//坦克的移动
	m_ground.RenderHeightMap();//地形图的绘制
	m_tank.collideDetect();//碰撞检验
	treeCollide();//坦克和树碰撞检测
	launchBullet();//子弹发射函数
    glutSwapBuffers();//使用双缓冲解决画面闪烁问题
}

//键盘控制回调函数
void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'w'://前进
		m_tank.setTankDirection(1);
		m_tank.setTankX(m_tank.getTankX()-0.05*sin(m_tank.getTankBeta()*PI/180)*cos(m_tank.getTankTheta()*PI/180));
		m_tank.setTankY(m_tank.getTankY()+0.05*sin(m_tank.getTankTheta()*PI/180));
		m_tank.setTankZ(m_tank.getTankZ()-0.05*cos(m_tank.getTankBeta()*PI/180)*cos(m_tank.getTankTheta()*PI/180));
		//printf("tankx=%f  tanky=%f  tankz=%f tankTheta=%f\n",m_tank.getTankX(),m_tank.getTankY(),m_tank.getTankZ(),m_tank.getTankTheta());
		break;
	case 's'://后退
		m_tank.setTankDirection(0);
		m_tank.setTankX(m_tank.getTankX()+0.05*sin(m_tank.getTankBeta()*PI/180)*cos(m_tank.getTankTheta()*PI/180));
		m_tank.setTankY(m_tank.getTankY()-0.05*sin(m_tank.getTankTheta()*PI/180));
		m_tank.setTankZ(m_tank.getTankZ()+0.05*cos(m_tank.getTankBeta()*PI/180)*cos(m_tank.getTankTheta()*PI/180));
		//printf("tankx=%f  tanky=%f  tankz=%f tankTheta=%f\n",m_tank.getTankX(),m_tank.getTankY(),m_tank.getTankZ(),m_tank.getTankTheta());
		break;
	case 'a'://左转
		m_tank.setTankBeta(m_tank.getTankBeta()+1);//
		break;
	case 'd'://右转
		m_tank.setTankBeta(m_tank.getTankBeta()-1);
		break;
	case' '://发射子弹
		if(bulletCount<=29)
		{
			bulletCount++;
	    	tankBullets[bulletCount].setBulletX(m_tank.getTankX()+m_tank.getTankSize()*0.6*sin(m_tank.getTankTheta()*PI/180)*sin(m_tank.getTankBeta()*PI/180));
	    	tankBullets[bulletCount].setBulletY(m_tank.getTankY()+m_tank.getTankSize()*0.6*cos(m_tank.getTankTheta()*PI/180));
	    	tankBullets[bulletCount].setBulletZ(m_tank.getTankZ()+m_tank.getTankSize()*0.6*sin(m_tank.getTankTheta()*PI/180)*cos(m_tank.getTankBeta()*PI/180));
	    	tankBullets[bulletCount].setBulletTheta(atan(sin(m_tank.getTankTheta()*PI/180)*cos(m_tank.getBatteryBeta()*PI/180))*180/PI);//使子弹与坦克炮筒方向一致
	    	tankBullets[bulletCount].setBulletBeta(m_tank.getTankBeta()+m_tank.getBatteryBeta());	
	    	//printf("剩余%d个子弹\n",30-bulletCount);
	    	PlaySound (TEXT("发弹.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
		}
		break;
 	}
	glutPostRedisplay();
}

//特殊键盘回调函数
void specail(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_LEFT://左转炮管
		m_tank.setBatteryBeta(m_tank.getBatteryBeta()+1);
		break;
	case GLUT_KEY_RIGHT://炮管右转
		m_tank.setBatteryBeta(m_tank.getBatteryBeta()-1);
		break;
	}
	glutPostRedisplay();
}
//主函数
int main(int argc, char** argv)
{
      glutInit(&argc, argv);
      glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
      glutInitWindowSize(1000, 1000);            
      glutInitWindowPosition(20,20);
      glutCreateWindow("坦克世界");
      glutDisplayFunc(display);                   
      glutIdleFunc(display);
	  glutSpecialFunc(specail);
      glutKeyboardFunc(keyboard);	
      init();                                                      
      glutMainLoop();	                      
	  return 0;
}