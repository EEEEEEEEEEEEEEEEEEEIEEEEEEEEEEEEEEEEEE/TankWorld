//创建地形
#include <stdio.h>
#include <stdlib.h>
#include <gl/glut.h>
#include <gl/glu.h>
#include <gl/glaux.h>
#include <math.h>
#include "texture.h"
#include "ground.h"
ground::ground(int z)
{
	w=z;//16
}
// 从*.raw文件（图片）中加载高度数据
void ground::LoadRawFile(LPSTR strName, int nSize)//LPSTR路径类型
{
	FILE *pFile = NULL;
	 // 打开文件
	pFile = fopen( strName, "rb" );
	// 如果文件不能打开
	if ( pFile == NULL )
	{
		 // 提示错误，退出
		printf("不能打开高度图文件\n");
		return;
	}
	else
		printf("打开高度图形文件正常\n");
	 // 读取文件数据到pHeightMap数组中
	fread( g_HeightMap, 1, nSize, pFile );
	 // 读取是否成功
	int result = ferror( pFile );
	 // 如果不成功，提示错误退出
	if (result)
	{
		printf("读取数据失败\n");
	}
	else
		printf("读取数据正常\n");
	 // 关闭文件
	fclose(pFile);
}
//初始化,生成高度数组
void ground::InitGL()
{
	LoadRawFile("Terrain.raw", MAP_SIZE * MAP_SIZE);// 载入1024*1024的高度图道g_HeightMap数组中
	g_texture.setImg(Img);//设置图片类型
	g_texture.setTexId(texId);//设置图片id
	g_texture.loadTexture("skybox\\tex3.bmp",0);//加载设置的地面图片,id为0
}
//从高程图中返回(x,z)点的高度
int ground::Height(int X, int Y)   
{
	//检测想x,y的范围
	int x = X % MAP_SIZE;    // 限制X的值在0-1024之间
	int y = Y % MAP_SIZE;    // 限制Y的值在0-1024之间
	if(!g_HeightMap) 
		return 0;    // 检测高度图是否存在，不存在则返回0
	return g_HeightMap[x + (y * MAP_SIZE)];   // 返回（x,y)的高度
}
//双线性插值，调用返回高度函数，返回任一点的高度值y，y其实为z
float ground::terrainHeight(float x,float y,float terrain_to_heightmap_ratio)
{
	int X=x/terrain_to_heightmap_ratio;
	int Y=y/terrain_to_heightmap_ratio;
	float xs=x/terrain_to_heightmap_ratio-X;
	float ys=y/terrain_to_heightmap_ratio-Y;
	float h00=Height(X,Y);//左下
	float h10=Height(X+1,Y);//右下
	float h11=Height(X+1,Y+1);//右上
	float h01=Height(X,Y+1);//左上
	return (1-ys)*(xs*h10+(1-xs)*h00)+ys*(xs*h11+(1-xs)*h01);

}
// 按高度设置顶点的颜色，越高的地方越亮
void ground::SetVertexColor(int x, int y)  
{        
	if(!g_HeightMap) return; // 检测高度图是否存在    
	float fColor = -0.15f + (Height( x, y ) / 256.0f);
	// 设置顶点的颜色
	glColor3f(fColor+0.1, fColor+0.1, fColor+0.1 );
}
// 根据高度图渲染输出地形
void ground::RenderHeightMap()
{
	int X = 0, Y = 0;      // 设置循环变量
	float x, y, z;   
	float TextureSize=1;//纹理尺寸
	int heightMapSize=MAP_SIZE;//高度图尺寸
	float groundMapSize=2*w;//地面贴图尺寸
	int heightMapStepSize=STEP_SIZE;//高度图步长
	float tex_height_ratio=TextureSize/(float)heightMapSize;//纹理高度比率
	float ground_height_ratio=groundMapSize/(float)heightMapSize;//地面高度比率
	if(!g_HeightMap) return;     // 确认高度图存在
	for ( X = 0; X < (heightMapSize); X += heightMapStepSize )//-heightMapStepSize
		for ( Y = 0; Y < (heightMapSize); Y += heightMapStepSize )//-heightMapStepSize
		{
			g_texture.Apply(0);
			glBegin(GL_QUADS);  // 渲染为四边形
			glDisable(GL_ALPHA_TEST);// 此处需要禁用Alpha测试
			/**如果启动了Alpha测试，OpenGL会检查像素的Alpha值，
			只有Alpha值满足条件的像素才会进行绘制
			（严格的说，满足条件的像素会通过本项测试，进行下一种测试，只有所有测试都通过，才能进行绘制），
			不满足条件的则不进行绘制。*/

			//绘制(x,y)处的顶点
			// 获得(x,y,z)坐标
			x = X*ground_height_ratio-w;//由灰度图转换为实际地面地图
			y = (Height( X, Y )-Height(0,0 ))*ground_height_ratio*HEIGHT_RATIO;
			z = Y*ground_height_ratio-w;
			y=y-0.85*w;//地面需要从0位置向下平移w
			SetVertexColor(X, Y);// 设置顶点颜色
			glTexCoord2f(X*tex_height_ratio,Y*tex_height_ratio);//由灰度图的遍历转换进而遍历纹理图
			/*
			glTexCoord2f(GLfloat s, GLfloat t)，s和t 代表坐标 s为 X轴坐标，t为Y轴坐标，用于绘制图形时指定纹理的坐标。
            glTexCoord2f(0,0)左下
			glTexCoord2f(0,1)左上
			glTexCoord2f(1,0)右下
			glTexCoord2f(1,1)右上
			*/
			glVertex3f(x, y, z); // 调用OpenGL绘制顶点的命令

			// 绘制(x,y+1)处的顶点
			x = X*ground_height_ratio-w;
			y = (Height(X, Y + heightMapStepSize)-Height(0,0))*ground_height_ratio*HEIGHT_RATIO;
			y=y-0.85*w;//地面需要从0位置向下平移w
			z = (Y + heightMapStepSize)*ground_height_ratio-w ;
			SetVertexColor(X, (Y + heightMapStepSize));
			glTexCoord2f(X*tex_height_ratio,(Y + heightMapStepSize)*tex_height_ratio);
			glVertex3f(x, y, z);  

			// 绘制(x+1,y+1)处的顶点
			x = (X + heightMapStepSize)*ground_height_ratio-w;
			y = (Height(X + heightMapStepSize, Y +heightMapStepSize )-Height( 0,0 ))*ground_height_ratio*HEIGHT_RATIO;
			y=y-0.85*w;//地面需要从0位置向下平移0.9w
			z = (Y + heightMapStepSize)*ground_height_ratio-w;
			SetVertexColor((X + heightMapStepSize),(Y + heightMapStepSize));
			glTexCoord2f((X + heightMapStepSize)*tex_height_ratio,(Y + heightMapStepSize)*tex_height_ratio);
			glVertex3f(x, y, z);   

			// 绘制(x+1,y)处的顶点
			x = (X + heightMapStepSize)*ground_height_ratio-w;
			y = (Height(X + heightMapStepSize, Y )-Height(0,0 ))*ground_height_ratio*HEIGHT_RATIO;
			y=y-0.85*w;//地面需要从0位置向下平移w
			z = Y*ground_height_ratio-w;
			SetVertexColor((X + heightMapStepSize), Y);
			glTexCoord2f((X + heightMapStepSize)*tex_height_ratio,(Y)*tex_height_ratio);
			glVertex3f(x, y, z);  

			glEnd();
		}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f); 
}
ground::~ground(void)
{
}
