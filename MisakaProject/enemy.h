#pragma once
#include "gameNode.h"
#define ENEMYMAX 15

//#define FENCEMAX 8

enum ENEMYDIRECTION
{
	LEFT,
	RIGHT
};

class enemy : public gameNode
{
protected:
	image* _enemyImg;			//�̹���
	RECT _rc;					//��Ʈ
	float _x, _y;				//���� ��ġ
	ENEMYDIRECTION _direction;  //�𷺼�

	int _index;				//������ �ε���
	int _count;				//������ ī��Ʈ ��

	//���� �̵� ���� ������
	int _initX, _initY;
	bool _isRight;
	bool _isLeft;

	////���� �̵� ���� ������ ��Ʈ
	//RECT _fence[FENCEMAX];
	////��Ʈ�� ������
	//POINT _fencePoint[FENCEMAX] = {
	//	{200, WINSIZEY - 100}, {1000, WINSIZEY - 100}, {1400, WINSIZEY - 100}, {2000, WINSIZEY - 100},
	//	{3000, WINSIZEY - 100}, {4000, WINSIZEY - 100}, {4100, WINSIZEY - 150}, {4500, WINSIZEY - 150}
	//};

public:
	enemy();
	~enemy();

	HRESULT init(POINT respawnPos);			//�ʱ�ȭ��
	void release();
	void update();
	void render();
	void move();			//������

	//void enemyDirection(int num) { _direction = (ENEMYDIRECTION)num; }
	
	//��Ʈ ������
	inline RECT getRect() { return _rc; }
};


