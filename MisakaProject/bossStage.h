#pragma once
#include "stage.h"

class bossStage : public stage
{
private:
	void pixelCollision();

public:
	bossStage();
	~bossStage();

	//HRESULT init();
	void release();

	virtual void enter(player* player);
	virtual void enterBoss(boss* boss);
	virtual void exit();

	virtual stage* updateStage();
	virtual void render();
};

