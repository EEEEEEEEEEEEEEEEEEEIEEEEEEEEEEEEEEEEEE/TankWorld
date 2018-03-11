//�߶�ͼ����������
class ground
{
#define  MAP_SIZE 1024   // ���ø߶�ͼ�����ݣ����߶�
#define  STEP_SIZE 16    // ���ڶ���ľ���
#define  HEIGHT_RATIO 0.5   //���Ƹ߶ȱ任����
public:
	ground(int z);//����
	~ground(void);//����
	void LoadRawFile(LPSTR strName, int nSize);// ��*.raw�ļ��м��ظ߶�����
	void InitGL();//��ʼ�������ɸ߶�����
	int Height(int X, int Y);   // ����ĺ�������(x,y)��ĸ߶�
	float terrainHeight(float x,float y,float terrain_to_heightmap_ratio);//˫���Բ�ֵ��������һ��ĸ߶�ֵ
	void SetVertexColor(int x, int y) ;  // ���߶����ö������ɫ��Խ�ߵĵط�Խ��	 
	void RenderHeightMap() ;   // ���ݸ߶�ͼ��Ⱦ�������
private:
	BYTE g_HeightMap[MAP_SIZE*MAP_SIZE];    //����1024*1024�ĸ߶�ͼ��g_HeightMap���飬����߶�����
	int w; //�������
	AUX_RGBImageRec *Img;//ͼƬ���ͱ���
	GLuint texId[1];//glu�ض�����������飬�洢����id
	texture g_texture;//��������Ա
};

