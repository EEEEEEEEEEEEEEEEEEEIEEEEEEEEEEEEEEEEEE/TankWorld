//����
class texture
{
public:
	texture(void);//����
	~texture(void);//����
	void setImg(AUX_RGBImageRec *Img);
	void setTexId(GLuint *texId);
	void loadTexture(LPCTSTR  filename,int i);
	void Tex(int ID,int * p,GLfloat  box[][3]);//������ͼ��װ
	void Apply(int i);
private:
	AUX_RGBImageRec * img;//ͼƬ����
	GLuint *texID;
};

