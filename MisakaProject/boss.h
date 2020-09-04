#pragma once
#include "gameNode.h"

class player;

enum DIRECTION_A
{
	LEFT_IDLE_A = 0,
	RIGHT_IDLE_A = 1,
	LEFT_MOVE_A = 2,
	RIGHT_MOVE_A = 3,
	LEFT_PATTERN_A = 4,
	RIGHT_PATTERN_A = 5,
	LEFT_REFLECT_A = 6,
	RIGHT_REFLECT_A = 7,
	LEFT_FALLDOWN_A = 8,
	RIGHT_FALLDOWN_A = 9
};

class boss : public gameNode
{
private:
	//�̹��� 
	image* _accelImage;
	image* _blackWaveImg;
	player* _player;

	/*image* _accelIdle = IMAGEMANAGER->findImage("�׼��⺻");
	image* _accelMove = IMAGEMANAGER->findImage("�׼��̵�");
	image* _accelPattern = IMAGEMANAGER->findImage("�׼����ϰ���");
	image* _accelReflect = IMAGEMANAGER->findImage("�׼����ݹݻ�");
	image* _accelFalldown = IMAGEMANAGER->findImage("�׼�����");*/

	animation* _ani;
	DIRECTION_A _direction;

	//ĳ���� ���
	RECT _bossNPC;
	float _x, _y;
	RECT _blackWave;	//���� �߻�ü
	float _bY;			//�߻�ü�� Y�� ����
	int _bwCount;

	//ĳ���� ����
	int _bossHP;
	int _ATK;
	RECT _bossHPgauge, _bossHPFront;
	float _hpX, _hpY, _hpW;

	//�߷�ó��
	bool _isGround;
	//����
	bool _isAttack;
	//�ݻ�
	bool _isReflect;
	//�ǰ�
	bool _isDamage;

	//����ó��
	int _patternCount;



public:
	boss();
	~boss();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//�ǰ� ó��
	void collision();

	//�÷��̾� Ŭ���� ��ũ
	void setPlayerAddressLink(player* player) { _player = player; }

	//����ĳ���� ��Ʈ ������
	RECT getRect() { return _bossNPC; }
	//����ĳ�� ���� �߻�ü ��Ʈ ������
	RECT getBlackWaveRect() { return _blackWave; }

	//����ĳ���� ��Ʈ ���� ������
	int getRectHeight() { return _bossNPC.bottom - _bossNPC.top; }

	//���� ĳ�� ���� ��ǥ ������
	float getBossX() { return _x; }
	float getBossY() { return _y; }

	//���� ĳ�� ���� ��ǥ ������
	void setBossX(float x) { _x = x; }
	void setBossY(float y) { _y = y; }

	//�߷� bool ���� ���� ������
	bool getIsGround() { return _isGround; }

	//�߷� bool ���� ���� ������
	void setIsGround(bool isGround) { _isGround = isGround; }

	//���� bool ���� ���� ������
	bool getIsAttack() { return _isAttack; }
	//���� bool ���� ���� ������
	void setIsAttack(bool isAttack) { _isAttack = isAttack; }

	//�ݻ� bool ���� ���� ������
	bool getIsReflect() { return _isReflect; }
	//�ݻ� bool ���� ���� ������
	void setIsReflect(bool isReflect) { _isReflect = isReflect; }

	//�ǰ� bool ���� ���� ������
	void setIsDamage(bool isDamage) { _isDamage = isDamage; }

	//���ݷ� ������
	int getATK() { return _ATK; }

	//�������� ����ü ������
	void setDirection(int direction) { _direction = (DIRECTION_A)direction; }
};

