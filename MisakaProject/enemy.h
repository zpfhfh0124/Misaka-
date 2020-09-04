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
	image* _enemyImg;			//이미지
	RECT _rc;					//렉트
	float _x, _y;				//중점 위치
	ENEMYDIRECTION _direction;  //디렉션

	int _index;				//프레임 인덱스
	int _count;				//프레임 카운트 용

	//몬스터 이동 방향 조절용
	int _initX, _initY;
	bool _isRight;
	bool _isLeft;

	////몬스터 이동 범위 조절할 렉트
	//RECT _fence[FENCEMAX];
	////렉트의 포지션
	//POINT _fencePoint[FENCEMAX] = {
	//	{200, WINSIZEY - 100}, {1000, WINSIZEY - 100}, {1400, WINSIZEY - 100}, {2000, WINSIZEY - 100},
	//	{3000, WINSIZEY - 100}, {4000, WINSIZEY - 100}, {4100, WINSIZEY - 150}, {4500, WINSIZEY - 150}
	//};

public:
	enemy();
	~enemy();

	HRESULT init(POINT respawnPos);			//초기화용
	void release();
	void update();
	void render();
	void move();			//움직임

	//void enemyDirection(int num) { _direction = (ENEMYDIRECTION)num; }
	
	//렉트 접근자
	inline RECT getRect() { return _rc; }
};


