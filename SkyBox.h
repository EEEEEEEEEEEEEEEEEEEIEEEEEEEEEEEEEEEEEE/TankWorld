//天空盒
class SkyBox
{
public:
	SkyBox(int size);//初始化天空盒,设置大小
	~SkyBox(void);//析构释放缓存
	void initSkyBox();//构建天空盒
	void drawSkyBox(int boxId[][4],GLfloat skybox[][3]);//天空盒
private:
	texture skybox_texture;//创建纹理对象成员
	GLuint skybox_texID[6];//创建一个全局的纹理数组，用来存储将位图转换之后得到的纹理，对应于立方体的6个面
	AUX_RGBImageRec * img;//图片类型
	/*AUX_RGBImageRec类型是一个RGB图像结构类型。描述了一幅图像的特征。该结构定义了三个成员：
	  sizeX —— 图像的宽度；
	  sizeY —— 图像的高度；
	  data; —— 图形所包含的数据，其实也就是该图形在内存中的像素数据的一个指针。
    */
	int w;
};

