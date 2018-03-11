//̹��
class tank
{
#define PI 3.1415926535897932384626433832795
public:
	tank(float size,int mapsize);//���캯��
	~tank(void);//����
	void tankTexInit();//����̹������ͼƬ
	//����̹������
	void setTankX(float x);
	void setTankY(float y);
	void setTankZ(float z);
	//����̹�˽Ƕ�
	void setTankTheta(float theta);
	void setTankBeta(float beta);
	//������̨�Ƕ��Լ�����
	void setBatteryTheta(float btheta);
	void setBatteryBeta(float bbeta);
	void setTankDirection(float direction);
	//��ȡ���꣬�Ƕȣ�����
	float getTankX();
	float getTankY();
	float getTankZ();
	float getTankTheta();
	float getTankBeta();
	float getBatteryTheta();
	float getBatteryBeta();
	float getTankDirection();

	float getTankSize();//����̹�˴�С
	void tankModel();//����̹��
	void tankMove();//̹�˵��ƶ�
	void collideDetect();//��ײ����
private:
	float tankSize;//̹�˴�С
    float tankX,tankY,tankZ;
    int tankDirection;//̹�˷���
    float tankTheta,tankBeta;//tankTheta����̹��ˮƽת�ǣ�tankBeta������ֱ�������
    float tankBatteryTheta,tankBatteryBeta;//tankBatteryBeta����̹����̨ת��,tankBatteryTheta������̨���
    int w;
    texture t_texture;//��������Ա
    AUX_RGBImageRec * img;//ͼƬ����
    GLuint t_texID[1];
};

