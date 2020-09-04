#pragma once
#include "gameNode.h"
#include "player.h"
#include "boss.h"
#include "enemyManager.h"
#include "enemy.h"
#include "stage.h"

class playGround : public gameNode
{
private:
	//pixelCollsion* _pixel;
	player* _player;
	enemyManager* _enemyMg;
	boss* _boss;
	//스테이지 관리할 클래스
	stage* _stage;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	

};

