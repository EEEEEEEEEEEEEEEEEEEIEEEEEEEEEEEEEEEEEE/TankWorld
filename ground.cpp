//��������
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
// ��*.raw�ļ���ͼƬ���м��ظ߶�����
void ground::LoadRawFile(LPSTR strName, int nSize)//LPSTR·������
{
	FILE *pFile = NULL;
	 // ���ļ�
	pFile = fopen( strName, "rb" );
	// ����ļ����ܴ�
	if ( pFile == NULL )
	{
		 // ��ʾ�����˳�
		printf("���ܴ򿪸߶�ͼ�ļ�\n");
		return;
	}
	else
		printf("�򿪸߶�ͼ���ļ�����\n");
	 // ��ȡ�ļ����ݵ�pHeightMap������
	fread( g_HeightMap, 1, nSize, pFile );
	 // ��ȡ�Ƿ�ɹ�
	int result = ferror( pFile );
	 // ������ɹ�����ʾ�����˳�
	if (result)
	{
		printf("��ȡ����ʧ��\n");
	}
	else
		printf("��ȡ��������\n");
	 // �ر��ļ�
	fclose(pFile);
}
//��ʼ��,���ɸ߶�����
void ground::InitGL()
{
	LoadRawFile("Terrain.raw", MAP_SIZE * MAP_SIZE);// ����1024*1024�ĸ߶�ͼ��g_HeightMap������
	g_texture.setImg(Img);//����ͼƬ����
	g_texture.setTexId(texId);//����ͼƬid
	g_texture.loadTexture("skybox\\tex3.bmp",0);//�������õĵ���ͼƬ,idΪ0
}
//�Ӹ߳�ͼ�з���(x,z)��ĸ߶�
int ground::Height(int X, int Y)   
{
	//�����x,y�ķ�Χ
	int x = X % MAP_SIZE;    // ����X��ֵ��0-1024֮��
	int y = Y % MAP_SIZE;    // ����Y��ֵ��0-1024֮��
	if(!g_HeightMap) 
		return 0;    // ���߶�ͼ�Ƿ���ڣ��������򷵻�0
	return g_HeightMap[x + (y * MAP_SIZE)];   // ���أ�x,y)�ĸ߶�
}
//˫���Բ�ֵ�����÷��ظ߶Ⱥ�����������һ��ĸ߶�ֵy��y��ʵΪz
float ground::terrainHeight(float x,float y,float terrain_to_heightmap_ratio)
{
	int X=x/terrain_to_heightmap_ratio;
	int Y=y/terrain_to_heightmap_ratio;
	float xs=x/terrain_to_heightmap_ratio-X;
	float ys=y/terrain_to_heightmap_ratio-Y;
	float h00=Height(X,Y);//����
	float h10=Height(X+1,Y);//����
	float h11=Height(X+1,Y+1);//����
	float h01=Height(X,Y+1);//����
	return (1-ys)*(xs*h10+(1-xs)*h00)+ys*(xs*h11+(1-xs)*h01);

}
// ���߶����ö������ɫ��Խ�ߵĵط�Խ��
void ground::SetVertexColor(int x, int y)  
{        
	if(!g_HeightMap) return; // ���߶�ͼ�Ƿ����    
	float fColor = -0.15f + (Height( x, y ) / 256.0f);
	// ���ö������ɫ
	glColor3f(fColor+0.1, fColor+0.1, fColor+0.1 );
}
// ���ݸ߶�ͼ��Ⱦ�������
void ground::RenderHeightMap()
{
	int X = 0, Y = 0;      // ����ѭ������
	float x, y, z;   
	float TextureSize=1;//����ߴ�
	int heightMapSize=MAP_SIZE;//�߶�ͼ�ߴ�
	float groundMapSize=2*w;//������ͼ�ߴ�
	int heightMapStepSize=STEP_SIZE;//�߶�ͼ����
	float tex_height_ratio=TextureSize/(float)heightMapSize;//����߶ȱ���
	float ground_height_ratio=groundMapSize/(float)heightMapSize;//����߶ȱ���
	if(!g_HeightMap) return;     // ȷ�ϸ߶�ͼ����
	for ( X = 0; X < (heightMapSize); X += heightMapStepSize )//-heightMapStepSize
		for ( Y = 0; Y < (heightMapSize); Y += heightMapStepSize )//-heightMapStepSize
		{
			g_texture.Apply(0);
			glBegin(GL_QUADS);  // ��ȾΪ�ı���
			glDisable(GL_ALPHA_TEST);// �˴���Ҫ����Alpha����
			/**���������Alpha���ԣ�OpenGL�������ص�Alphaֵ��
			ֻ��Alphaֵ�������������زŻ���л���
			���ϸ��˵���������������ػ�ͨ��������ԣ�������һ�ֲ��ԣ�ֻ�����в��Զ�ͨ�������ܽ��л��ƣ���
			�������������򲻽��л��ơ�*/

			//����(x,y)���Ķ���
			// ���(x,y,z)����
			x = X*ground_height_ratio-w;//�ɻҶ�ͼת��Ϊʵ�ʵ����ͼ
			y = (Height( X, Y )-Height(0,0 ))*ground_height_ratio*HEIGHT_RATIO;
			z = Y*ground_height_ratio-w;
			y=y-0.85*w;//������Ҫ��0λ������ƽ��w
			SetVertexColor(X, Y);// ���ö�����ɫ
			glTexCoord2f(X*tex_height_ratio,Y*tex_height_ratio);//�ɻҶ�ͼ�ı���ת��������������ͼ
			/*
			glTexCoord2f(GLfloat s, GLfloat t)��s��t �������� sΪ X�����꣬tΪY�����꣬���ڻ���ͼ��ʱָ����������ꡣ
            glTexCoord2f(0,0)����
			glTexCoord2f(0,1)����
			glTexCoord2f(1,0)����
			glTexCoord2f(1,1)����
			*/
			glVertex3f(x, y, z); // ����OpenGL���ƶ��������

			// ����(x,y+1)���Ķ���
			x = X*ground_height_ratio-w;
			y = (Height(X, Y + heightMapStepSize)-Height(0,0))*ground_height_ratio*HEIGHT_RATIO;
			y=y-0.85*w;//������Ҫ��0λ������ƽ��w
			z = (Y + heightMapStepSize)*ground_height_ratio-w ;
			SetVertexColor(X, (Y + heightMapStepSize));
			glTexCoord2f(X*tex_height_ratio,(Y + heightMapStepSize)*tex_height_ratio);
			glVertex3f(x, y, z);  

			// ����(x+1,y+1)���Ķ���
			x = (X + heightMapStepSize)*ground_height_ratio-w;
			y = (Height(X + heightMapStepSize, Y +heightMapStepSize )-Height( 0,0 ))*ground_height_ratio*HEIGHT_RATIO;
			y=y-0.85*w;//������Ҫ��0λ������ƽ��0.9w
			z = (Y + heightMapStepSize)*ground_height_ratio-w;
			SetVertexColor((X + heightMapStepSize),(Y + heightMapStepSize));
			glTexCoord2f((X + heightMapStepSize)*tex_height_ratio,(Y + heightMapStepSize)*tex_height_ratio);
			glVertex3f(x, y, z);   

			// ����(x+1,y)���Ķ���
			x = (X + heightMapStepSize)*ground_height_ratio-w;
			y = (Height(X + heightMapStepSize, Y )-Height(0,0 ))*ground_height_ratio*HEIGHT_RATIO;
			y=y-0.85*w;//������Ҫ��0λ������ƽ��w
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
