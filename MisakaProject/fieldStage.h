#pragma once
#include "gameNode.h"
#include "stage.h"

//#define FENCEMAX 8

class enemyManager;

class fieldStage : public stage
{
private:
	enemyManager* _enemyMg;

	bool _isClear;

	//오브젝트
	RECT _portal;	//포탈
	image* _portalImg;
	
	//픽셀충돌 
	void pixelCollision();

	////몬스터 이동 범위 조절할 렉트
	//RECT _fence[FENCEMAX];
	////렉트의 포지션
	//POINT _fencePoint[FENCEMAX] = {
	//	{200, WINSIZEY - 100}, {1000, WINSIZEY - 100}, {1400, WINSIZEY - 100}, {2000, WINSIZEY - 100},
	//	{3000, WINSIZEY - 100}, {4000, WINSIZEY - 100}, {4100, WINSIZEY - 150}, {4500, WINSIZEY - 150}
	//};


public:
	fieldStage();
	~fieldStage();

	//HRESULT init();			
	void release();

	virtual void enter(player* player);
	virtual void exit();
	virtual stage* updateStage();
	virtual void render();

	// void setEnemyMgAddressLink(enemyManager* enemyMg) { _enemyMg = enemyMg; }
};

