//��պ�
class SkyBox
{
public:
	SkyBox(int size);//��ʼ����պ�,���ô�С
	~SkyBox(void);//�����ͷŻ���
	void initSkyBox();//������պ�
	void drawSkyBox(int boxId[][4],GLfloat skybox[][3]);//��պ�
private:
	texture skybox_texture;//������������Ա
	GLuint skybox_texID[6];//����һ��ȫ�ֵ��������飬�����洢��λͼת��֮��õ���������Ӧ���������6����
	AUX_RGBImageRec * img;//ͼƬ����
	/*AUX_RGBImageRec������һ��RGBͼ��ṹ���͡�������һ��ͼ����������ýṹ������������Ա��
	  sizeX ���� ͼ��Ŀ�ȣ�
	  sizeY ���� ͼ��ĸ߶ȣ�
	  data; ���� ͼ�������������ݣ���ʵҲ���Ǹ�ͼ�����ڴ��е��������ݵ�һ��ָ�롣
    */
	int w;
};

