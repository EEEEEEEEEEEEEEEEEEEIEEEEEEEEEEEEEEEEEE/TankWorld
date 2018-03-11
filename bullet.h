//子弹函数
class bullet
{
public:
	bullet(void);//默认构造函数,设置子弹半径大小
	bullet(float size);//构造函数，
	void bulletInit();//初始化子弹
	void bulletMove();//子弹移动
	void setBulletX(float X);
	void setBulletY(float Y);
	void setBulletZ(float Z);
	void setBulletTheta(float Theta);//设置旋转角度
	void setBulletBeta(float Beta);//设置倾斜角度
	float getBulletX();
	float getBulletY();
	float getBulletZ();
	float getBulletTheta();//水平旋转角度
	float getBulletBeta();//竖直方向倾角
	~bullet(void);//析构释放缓存
private:
	float bulletSize; //半径
	//子弹坐标
	float x;
	float y;
	float z;
	float theta;//旋转角度
	float beta;//旋转角度
};

