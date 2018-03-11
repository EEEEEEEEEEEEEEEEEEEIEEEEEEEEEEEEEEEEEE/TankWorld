//树
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
//访问树相关变量的函数
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
//树倒下的角度
float tree::getTreeTheta()
{
	return treeTheta;
}
//使得树一直对着相机
float tree::getTreeBeta()
{
	return treeBeta;
}
//将RGB模式改为RGBA模式,Alpha测试,Color Key技术。对树图片的部分做透明度处理
//纹理中像素的RGB值如果与指定rgb相差不超过absolute，则将Alpha设置为0.0，否则设置为1.0 
void tree::texture_colorkey(GLubyte r, GLubyte g, GLubyte b, GLubyte absolute)
{	
    GLint w, h;
    GLubyte* pixels = 0;

    // 获得纹理的大小信息
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);

    pixels = (GLubyte*)malloc(w*h*4); // 分配空间并获得纹理像素
    if( pixels == 0 ) return;

    glGetTexImage(GL_TEXTURE_2D, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, pixels);  // 获得纹理像素

    // 修改像素中的Alpha值
	// 其中pixels[i*4], pixels[i*4+1], pixels[i*4+2], pixels[i*4+3]  
    // 分别表示第i个像素的蓝、绿、红、Alpha四种分量，0表示最小，255表示最大
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

    // 将修改后的像素重新设置到纹理中，释放内存
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
	glEnable(GL_ALPHA_TEST);//完成alpha测试
	glAlphaFunc(GL_GREATER,0.5); //测试条件"大于0.5时通过
	glPushMatrix();
		glTranslatef(treeX,treeY,treeZ);
		glRotatef(treeTheta,sin(treeBeta*PI/180),0,cos(treeBeta*PI/180));//树的倒下
		glRotatef(treeBeta,0,1,0);//设置树正面始终对准相机

		glBegin(GL_QUADS);//填充四边形
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
