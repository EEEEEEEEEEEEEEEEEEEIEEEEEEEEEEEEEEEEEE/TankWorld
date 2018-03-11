//高度图，创建地形
class ground
{
#define  MAP_SIZE 1024   // 设置高度图的数据，最大高度
#define  STEP_SIZE 16    // 相邻顶点的距离
#define  HEIGHT_RATIO 0.5   //地势高度变换比率
public:
	ground(int z);//构造
	~ground(void);//析构
	void LoadRawFile(LPSTR strName, int nSize);// 从*.raw文件中加载高度数据
	void InitGL();//初始化，生成高度数组
	int Height(int X, int Y);   // 下面的函数返回(x,y)点的高度
	float terrainHeight(float x,float y,float terrain_to_heightmap_ratio);//双线性插值，返回任一点的高度值
	void SetVertexColor(int x, int y) ;  // 按高度设置顶点的颜色，越高的地方越亮	 
	void RenderHeightMap() ;   // 根据高度图渲染输出地形
private:
	BYTE g_HeightMap[MAP_SIZE*MAP_SIZE];    //设置1024*1024的高度图道g_HeightMap数组，保存高度数据
	int w; //构造地势
	AUX_RGBImageRec *Img;//图片类型变量
	GLuint texId[1];//glu重定义的整型数组，存储纹理id
	texture g_texture;//纹理对象成员
};

