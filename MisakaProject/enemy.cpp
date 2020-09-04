#include "stdafx.h"
#include "enemy.h"


enemy::enemy()
{
}


enemy::~enemy()
{
}

HRESULT enemy::init(POINT respawnPos)
{
	_initX = _x = respawnPos.x;
	_initY = _y = respawnPos.y;
	_enemyImg = IMAGEMANAGER->findImage("¶óÃ÷");
	_rc = RectMakeCenter(_x, _y, _enemyImg->getWidth(), _enemyImg->getHeight());
	
	_direction = LEFT;
	_index = 0;
	_count = 0;

	_isRight = _isLeft = false;

	/*for (int i = 0; i < FENCEMAX; i++)
	{
		_fence[i] = RectMakeCenter(_fencePoint[i].x, _fencePoint[i].y, 50, 50);
	}*/
	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	

	//µð·º¼Ç
	_count++;
	if (_count ==  10)
	{
		if (_direction == LEFT)
		{
			_index++;
			if (_index > 6) _index = 0;
		}
		if (_direction == RIGHT)
		{
			_index--;
			if (_index < 0) _index = 6;
		}
		_count = 0;
	}
}

void enemy::render()
{
	_enemyImg->frameRender(getMemDC(), _rc.left, _rc.top, _index, (_direction == LEFT)?0:1);

	/*for (int i = 0; i < FENCEMAX; i++)
	{
		Rectangle(getMemDC(), _fence[i]);
	}*/
	_rc = RectMakeCenter(_x, _y, _enemyImg->getWidth(), _enemyImg->getHeight());
}

void enemy::move()
{
	if (!_isLeft && !_isRight) _x -= 1;

	if (_x < _initX - 100)
	{
		_isLeft = false;
		_isRight = true;
	}
	else if (_x > _initX + 100)
	{
		_isLeft = true;
		_isRight = false;
	}

	if (_isLeft && !_isRight)
	{
		_direction = LEFT;
		_x -= 1;
	}
	else if (!_isLeft && _isRight)
	{
		_direction = RIGHT;
		_x += 1;
	}
}




