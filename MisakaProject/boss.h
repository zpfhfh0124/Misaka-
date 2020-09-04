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
	//이미지 
	image* _accelImage;
	image* _blackWaveImg;
	player* _player;

	/*image* _accelIdle = IMAGEMANAGER->findImage("액셀기본");
	image* _accelMove = IMAGEMANAGER->findImage("액셀이동");
	image* _accelPattern = IMAGEMANAGER->findImage("액셀패턴공격");
	image* _accelReflect = IMAGEMANAGER->findImage("액셀공격반사");
	image* _accelFalldown = IMAGEMANAGER->findImage("액셀기절");*/

	animation* _ani;
	DIRECTION_A _direction;

	//캐릭터 요소
	RECT _bossNPC;
	float _x, _y;
	RECT _blackWave;	//공격 발사체
	float _bY;			//발사체의 Y축 중점
	int _bwCount;

	//캐릭터 정보
	int _bossHP;
	int _ATK;
	RECT _bossHPgauge, _bossHPFront;
	float _hpX, _hpY, _hpW;

	//중력처리
	bool _isGround;
	//공격
	bool _isAttack;
	//반사
	bool _isReflect;
	//피격
	bool _isDamage;

	//패턴처리
	int _patternCount;



public:
	boss();
	~boss();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//피격 처리
	void collision();

	//플레이어 클래스 링크
	void setPlayerAddressLink(player* player) { _player = player; }

	//보스캐릭의 렉트 접근자
	RECT getRect() { return _bossNPC; }
	//보스캐릭 공격 발사체 렉트 접근자
	RECT getBlackWaveRect() { return _blackWave; }

	//보스캐릭의 렉트 높이 접근자
	int getRectHeight() { return _bossNPC.bottom - _bossNPC.top; }

	//보스 캐릭 중점 좌표 접근자
	float getBossX() { return _x; }
	float getBossY() { return _y; }

	//보스 캐릭 중점 좌표 설정자
	void setBossX(float x) { _x = x; }
	void setBossY(float y) { _y = y; }

	//중력 bool 상태 정의 접근자
	bool getIsGround() { return _isGround; }

	//중력 bool 상태 정의 설정자
	void setIsGround(bool isGround) { _isGround = isGround; }

	//공격 bool 상태 정의 접근자
	bool getIsAttack() { return _isAttack; }
	//공격 bool 상태 정의 설정자
	void setIsAttack(bool isAttack) { _isAttack = isAttack; }

	//반사 bool 상태 정의 접근자
	bool getIsReflect() { return _isReflect; }
	//반사 bool 상태 정의 설정자
	void setIsReflect(bool isReflect) { _isReflect = isReflect; }

	//피격 bool 상태 정의 설정자
	void setIsDamage(bool isDamage) { _isDamage = isDamage; }

	//공격력 접근자
	int getATK() { return _ATK; }

	//상태정의 열거체 설정자
	void setDirection(int direction) { _direction = (DIRECTION_A)direction; }
};

