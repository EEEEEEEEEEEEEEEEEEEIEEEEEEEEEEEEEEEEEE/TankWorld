//坦克
class tank
{
#define PI 3.1415926535897932384626433832795
public:
	tank(float size,int mapsize);//构造函数
	~tank(void);//析构
	void tankTexInit();//设置坦克纹理图片
	//设置坦克坐标
	void setTankX(float x);
	void setTankY(float y);
	void setTankZ(float z);
	//设置坦克角度
	void setTankTheta(float theta);
	void setTankBeta(float beta);
	//设置炮台角度以及方向
	void setBatteryTheta(float btheta);
	void setBatteryBeta(float bbeta);
	void setTankDirection(float direction);
	//获取坐标，角度，方向
	float getTankX();
	float getTankY();
	float getTankZ();
	float getTankTheta();
	float getTankBeta();
	float getBatteryTheta();
	float getBatteryBeta();
	float getTankDirection();

	float getTankSize();//返回坦克大小
	void tankModel();//绘制坦克
	void tankMove();//坦克的移动
	void collideDetect();//碰撞检验
private:
	float tankSize;//坦克大小
    float tankX,tankY,tankZ;
    int tankDirection;//坦克方向
    float tankTheta,tankBeta;//tankTheta定义坦克水平转角，tankBeta定义竖直方向倾角
    float tankBatteryTheta,tankBatteryBeta;//tankBatteryBeta定义坦克炮台转角,tankBatteryTheta定义炮台倾角
    int w;
    texture t_texture;//纹理对象成员
    AUX_RGBImageRec * img;//图片类型
    GLuint t_texID[1];
};

