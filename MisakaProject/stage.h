#pragma once
#include "gameNode.h"

#include <vector>

class player;
class enemyManager;
class boss;

class stage : public gameNode
{
protected:
	player* _player;
	enemyManager* _enemyMg;
	boss* _boss;

	int _minX = 0;
	int _maxX = 0;
	bool _isClear = false;
	image* _pixelImg;
	
	//스테이지 넘어 갔는지
	//bool _isStageChange;

public:
	virtual void enter(player* player);
	virtual void enterBoss(boss* boss);
	virtual void exit();
	virtual stage* updateStage();
	virtual void render();

	virtual int getMinX() { return _minX; }
	virtual int getMaxX() { return _maxX; }

	bool isClear() { return _isClear;}
	image* getPixelImage() { return _pixelImg; }

	void setEnemyMgAddressLink(enemyManager* enemyMg) { _enemyMg = enemyMg; }
};

