//纹理
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
AUX_RGBImageRec类型是一个RGB图像结构类型。该结构定义了三个成员：
sizeX —— 图像的宽度；
sizeY —— 图像的高度；
data; —— 图形所包含的数据，其实也就是该图形在内存中的像素数据的一个指针。
*/
//获取图片格式
void texture::setImg(AUX_RGBImageRec *Img)
{
	img=Img;
}
//获取图片id
void texture::setTexId(GLuint *texId)
{
	texID=texId;
}
//加载纹理,通过图片路径以及其id
void texture::loadTexture(LPCTSTR filename,int i)
{
	img = auxDIBImageLoad(filename);//读取图片信息
	glGenTextures(1, &texID[i]);//创建纹理，每次只分配一个纹理对象的编号
	glBindTexture(GL_TEXTURE_2D, texID[i]);//绑定纹理数据
	//载入二维纹理信息
	glTexImage2D(
		GL_TEXTURE_2D,//指定二维纹理
		0, //不考虑多重细节，设置为0
		GL_RGBA, //采用RGBA模式，红、绿、蓝、alpha四个值
		//二维纹理像素的宽和高（图片像素尺寸）
		img->sizeX,
		img->sizeY,
		0,//纹理边框设为0
		GL_RGB, 
		GL_UNSIGNED_BYTE,
		img->data//图片数据
	);
    //设置纹理过滤
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}
//纹理贴图封装
void texture::Tex(int ID,int * p,GLfloat  box[][3])
{
	Apply(ID);
	//四边形纹理
	glBegin(GL_QUADS);
		glTexCoord2f(0,0);	glVertex3fv(box[p[0]]);//左下
		glTexCoord2f(0,1);	glVertex3fv(box[p[1]]);//左上
		glTexCoord2f(1,1);	glVertex3fv(box[p[2]]);//右上
		glTexCoord2f(1,0);	glVertex3fv(box[p[3]]);//右下
	glEnd();
}
//申请纹理的编号（id）
void texture::Apply(int i)
{
	glBindTexture(GL_TEXTURE_2D, texID[i]);
}