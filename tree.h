//��
class tree
{
public:
	tree(void);
	~tree(void);
	void setTreeX(float x);
	void setTreeY(float y);
	void setTreeZ(float z);
	void setTreeTheta(float theta);
	void setTreeBeta(float beta);
	float getTreeX();
	float getTreeY();
	float getTreeZ();
	float getTreeTheta();//�����µĽǶ�
	float getTreeBeta();//ʹ����һֱ�������
	void texture_colorkey(GLubyte r, GLubyte g, GLubyte b, GLubyte absolute);
	void initTreeImg();
	void drawTree(float size);
private:
	float treeX;
	float treeY;
	float treeZ;
	float treeTheta;
	float treeBeta;
	texture tree_texture;//������
	AUX_RGBImageRec * treeimg;
	GLuint treeTexId[1];
};

