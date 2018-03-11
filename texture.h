//纹理
class texture
{
public:
	texture(void);//构造
	~texture(void);//析构
	void setImg(AUX_RGBImageRec *Img);
	void setTexId(GLuint *texId);
	void loadTexture(LPCTSTR  filename,int i);
	void Tex(int ID,int * p,GLfloat  box[][3]);//纹理贴图封装
	void Apply(int i);
private:
	AUX_RGBImageRec * img;//图片类型
	GLuint *texID;
};

