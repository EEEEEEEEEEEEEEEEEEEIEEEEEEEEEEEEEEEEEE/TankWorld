//天空盒
#include <stdlib.h>
#include <gl/glut.h>
#include <gl/glu.h>
#include <gl/glaux.h>
#include <math.h>
#include "texture.h"
#include "SkyBox.h"
//设置天空盒大小（尺寸）
SkyBox::SkyBox(int size)
{
	w=size;
}
//制作天空盒，即给天空盒贴图
void SkyBox::initSkyBox()
{
	skybox_texture.setImg(img);
	skybox_texture.setTexId(skybox_texID);//存储天空盒序列（6个面）数组
	skybox_texture.loadTexture("skybox\\neg_x.bmp",0);//右
	skybox_texture.loadTexture("skybox\\pos_x.bmp", 1);//左
	skybox_texture.loadTexture("skybox\\tex3.bmp", 2);//地面
	skybox_texture.loadTexture("skybox\\pos_y.bmp", 3);//上
	skybox_texture.loadTexture("skybox\\neg_z.bmp", 4);//前
	skybox_texture.loadTexture("skybox\\pos_z.bmp", 5);//后
	
}
//天空盒，纹理封装
void SkyBox::drawSkyBox(int boxId[][4],GLfloat skybox[][3])
{
	glDisable(GL_ALPHA_TEST);//禁用Alpha测试，该测试有限制
	//给boxid对应的面贴上纹理
	skybox_texture.Tex(4,boxId[0],skybox);// 前
	skybox_texture.Tex(0,boxId[1],skybox);// 右
	skybox_texture.Tex(1,boxId[2],skybox);// 左
	skybox_texture.Tex(5,boxId[3],skybox);// 后
	skybox_texture.Tex(3,boxId[4],skybox);// 上
	//ground 用算法绘制了地形
}
SkyBox::~SkyBox(void)
{
}
