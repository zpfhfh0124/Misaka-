#include "stdafx.h"
#include "stage.h"
//#include "enemyManager.h"

void stage::enter(player* player)
{
	_player = player;
	
	//_isClear = false;
	//_isStageChange = false;

	
	/*_enemyMg = new enemyManager;
	_enemyMg->init();
	_enemyMg->setEnemy();*/
	//setEnemyMgAddressLink(_enemyMg);
}

void stage::enterBoss(boss * boss)
{
	_boss = boss;
}

void stage::exit()
{
	//_enemyMg->release();
}

stage * stage::updateStage()
{
	//if (!_isClear) _enemyMg->update();

	return nullptr;
}

void stage::render()
{
	//_enemyMg->render();
}
