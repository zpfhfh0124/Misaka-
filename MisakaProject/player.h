#pragma once
#include "gameNode.h"

class pixelCollsion;
class stage;
class fieldStage;
class boss;

enum DIRECTION
{
	LEFT_IDLE,
	RIGHT_IDLE,
	LEFT_MOVE,
	RIGHT_MOVE,
	LEFT_JUMP_START,
	LEFT_JUMP_DESCENT,
	LEFT_JUMP_LANDING,
	RIGHT_JUMP_START,
	RIGHT_JUMP_DESCENT,
	RIGHT_JUMP_LANDING,
	LEFT_ATTACK,
	RIGHT_ATTACK,
	LEFT_RAILGUN,
	RIGHT_RAILGUN,
	LEFT_FALLDOWN,
	RIGHT_FALLDOWN
};

class player : public gameNode
{
private :
	//Ŭ����
	// pixelCollsion* _pixelCollsion;
	stage* _stage;
	boss* _boss;

	//�̹���
	image* _mikotoIdle;
	image* _mikotoMove;
	image* _mikotoJump;
	image* _mikotoAttack;
	image* _mikotoFallDown;
	image* _mikotoRailgun;
	image* _railgunImg;

	//ĳ���� ���
	RECT _player;			//ĳ���� ������ ��Ʈ
	int _width, _height;	//������ ���� ����
	float _x, _y;			//������ ����
	//int frameX, frameY;	//getFrameX(), getFrameY()
	RECT _railgun;			//���ϰ� ���� �߻�ü
	float _rX, _rY, _rW, _rH; //���ϰ� ����, ���μ���
	int _railgunCount;		//���ϰ� ī��Ʈ
	int _damageCount;			//�ǰ� ī��Ʈ

	//ĳ���� ����
	int _playerHP, _playerCP;	//ü��, ����
	int _ATK, _railgunATK;		//���ݷ�
	RECT _playerHPgauge, _playerCPgauge, _playerHPFront, _playerCPFront;
	float _hpX, _hpY, _cpX, _cpY, _hpfX, _cpfX;
	
	//ĳ���� ��������
	DIRECTION _direction;
	int _count, _index, _landingCount;

	//ĳ���� ���� ����
	float _angle, _gravity, _speed;

	//ĳ���� �߷� ó��
	bool _isGround;

	//����
	bool _isAttack;
	bool _isRailgun;

	//�ǰ�
	bool _isDamage;

public:
	player();
	~player();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//�������� �浹�Լ�
	void collisionBoss();

	//�ȼ��浹 Ŭ���� ��ũ
	// void setPixelCollAddressLink(pixelCollsion* pixelColl) { _pixelCollsion = pixelColl; }
	//�������� Ŭ���� ��ũ
	void setStageAddressLink(stage* stage) { _stage = stage; }
	//�ʵ彺������ Ŭ���� ��ũ
	//void setFieldStageAddressLink()
	//���� Ŭ���� ��ũ
	void setBossAddressLink(boss* boss) { _boss = boss; }

	//ĳ������ ��Ʈ ������
	RECT getRect() { return _player; }
	//���ϰ��� ��Ʈ ������
	RECT getRailgunRect() { return _railgun; }

	//ĳ���� ��Ʈ�� ���� ������
	int getPlayerRectHeight() { return _player.bottom - _player.top; }

	//ĳ������ ���� ��ǥ ������
	float getPlayerX() { return _x; }
	float getPlayerY() { return _y; }

	//ĳ������ ���� ��ǥ ������
	void setPlayerX(float x) { _x = x; }
	void setPlayerY(float y) { _y = y; }

	//�߷� bool ���� ���� ������
	bool getPlayerGround() { return _isGround; }

	//�߷� bool ���� ���� ������
	void setPlayerGround(bool isGround) { _isGround = isGround; }

	//���� bool ���� ���� ������
	bool getPlayerAttack() { return _isAttack; }
	//���� bool ���� ���� ������
	void setPlayerAttack(bool isAttack) { _isAttack = isAttack; }
	//���ϰ� bool ���� ���� ������
	bool getRailgun() { return _isRailgun; }
	//���ϰ� bool ���� ���� ������
	void setRailgun(bool isRailgun) { _isRailgun = isRailgun; }

	//�ǰ� bool ���� ���� ������
	void setIsDamage(bool isDamage) { _isDamage = isDamage; }

	//�÷��̾��� ü�� ������
	int getPlayerHP() { return _playerHP; }
	//�÷��̾��� ü�� ������
	void setPlayerHP(int playerHP) { _playerHP = playerHP; }
	//�÷��̾��� ���ݷ� ������
	int getATK() { return _ATK; }
	//�÷��̾��� ���ϰ� ���ݷ� ������
	int getRailgunATK() { return _railgunATK; }
};

