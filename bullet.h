//�ӵ�����
class bullet
{
public:
	bullet(void);//Ĭ�Ϲ��캯��,�����ӵ��뾶��С
	bullet(float size);//���캯����
	void bulletInit();//��ʼ���ӵ�
	void bulletMove();//�ӵ��ƶ�
	void setBulletX(float X);
	void setBulletY(float Y);
	void setBulletZ(float Z);
	void setBulletTheta(float Theta);//������ת�Ƕ�
	void setBulletBeta(float Beta);//������б�Ƕ�
	float getBulletX();
	float getBulletY();
	float getBulletZ();
	float getBulletTheta();//ˮƽ��ת�Ƕ�
	float getBulletBeta();//��ֱ�������
	~bullet(void);//�����ͷŻ���
private:
	float bulletSize; //�뾶
	//�ӵ�����
	float x;
	float y;
	float z;
	float theta;//��ת�Ƕ�
	float beta;//��ת�Ƕ�
};

