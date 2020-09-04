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
	//클래스
	// pixelCollsion* _pixelCollsion;
	stage* _stage;
	boss* _boss;

	//이미지
	image* _mikotoIdle;
	image* _mikotoMove;
	image* _mikotoJump;
	image* _mikotoAttack;
	image* _mikotoFallDown;
	image* _mikotoRailgun;
	image* _railgunImg;

	//캐릭터 요소
	RECT _player;			//캐릭터 프레임 렉트
	int _width, _height;	//프레임 가로 세로
	float _x, _y;			//프레임 중점
	//int frameX, frameY;	//getFrameX(), getFrameY()
	RECT _railgun;			//레일건 공격 발사체
	float _rX, _rY, _rW, _rH; //레일건 중점, 가로세로
	int _railgunCount;		//레일건 카운트
	int _damageCount;			//피격 카운트

	//캐릭터 정보
	int _playerHP, _playerCP;	//체력, 마나
	int _ATK, _railgunATK;		//공격력
	RECT _playerHPgauge, _playerCPgauge, _playerHPFront, _playerCPFront;
	float _hpX, _hpY, _cpX, _cpY, _hpfX, _cpfX;
	
	//캐릭터 상태정의
	DIRECTION _direction;
	int _count, _index, _landingCount;

	//캐릭터 점프 관련
	float _angle, _gravity, _speed;

	//캐릭터 중력 처리
	bool _isGround;

	//공격
	bool _isAttack;
	bool _isRailgun;

	//피격
	bool _isDamage;

public:
	player();
	~player();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//보스와의 충돌함수
	void collisionBoss();

	//픽셀충돌 클래스 링크
	// void setPixelCollAddressLink(pixelCollsion* pixelColl) { _pixelCollsion = pixelColl; }
	//스테이지 클래스 링크
	void setStageAddressLink(stage* stage) { _stage = stage; }
	//필드스테이지 클래스 링크
	//void setFieldStageAddressLink()
	//보스 클래스 링크
	void setBossAddressLink(boss* boss) { _boss = boss; }

	//캐릭터의 렉트 접근자
	RECT getRect() { return _player; }
	//레일건의 렉트 접근자
	RECT getRailgunRect() { return _railgun; }

	//캐릭터 렉트의 높이 접근자
	int getPlayerRectHeight() { return _player.bottom - _player.top; }

	//캐릭터의 중점 좌표 접근자
	float getPlayerX() { return _x; }
	float getPlayerY() { return _y; }

	//캐릭터의 중점 좌표 설정자
	void setPlayerX(float x) { _x = x; }
	void setPlayerY(float y) { _y = y; }

	//중력 bool 상태 정의 접근자
	bool getPlayerGround() { return _isGround; }

	//중력 bool 상태 정의 설정자
	void setPlayerGround(bool isGround) { _isGround = isGround; }

	//공격 bool 상태 정의 접근자
	bool getPlayerAttack() { return _isAttack; }
	//공격 bool 상태 정의 설정자
	void setPlayerAttack(bool isAttack) { _isAttack = isAttack; }
	//레일건 bool 상태 정의 접근자
	bool getRailgun() { return _isRailgun; }
	//레일건 bool 상태 정의 설정자
	void setRailgun(bool isRailgun) { _isRailgun = isRailgun; }

	//피격 bool 상태 정의 설정자
	void setIsDamage(bool isDamage) { _isDamage = isDamage; }

	//플레이어의 체력 접근자
	int getPlayerHP() { return _playerHP; }
	//플레이어의 체력 설정자
	void setPlayerHP(int playerHP) { _playerHP = playerHP; }
	//플레이어의 공격력 접근자
	int getATK() { return _ATK; }
	//플레이어의 레일건 공격력 접근자
	int getRailgunATK() { return _railgunATK; }
};

