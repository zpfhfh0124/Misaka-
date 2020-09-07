#include "stdafx.h"
#include "player.h"
#include "boss.h"
#include "stage.h"
#include "fieldStage.h"

player::player()
{
}

player::~player()
{
}

HRESULT player::init()
{
	//기본 이미지
	_mikotoIdle = IMAGEMANAGER->addFrameImage("미코토기본", "images/캐릭터/MIKOTO/MIKOTO_IDLE.bmp", 400, 320, 4, 2, true, RGB(0, 255, 0));
	_mikotoIdle->setX(100);
	_mikotoIdle->setY(WINSIZEY - 100);
	_mikotoIdle->setFrameX(0);
	_mikotoIdle->setFrameY(0);
	//달리는 이미지
	_mikotoMove = IMAGEMANAGER->addFrameImage("미코토런", "images/캐릭터/MIKOTO/MIKOTO_MOVE.bmp", 500, 320, 5, 2, true, RGB(0, 255, 0));
	_mikotoMove->setX(_mikotoIdle->getX());
	_mikotoMove->setY(_mikotoIdle->getY());
	_mikotoMove->setFrameX(0);
	_mikotoMove->setFrameY(0);
	//점프 이미지
	_mikotoJump = IMAGEMANAGER->addFrameImage("미코토점프", "images/캐릭터/MIKOTO/MIKOTO_JUMP.bmp", 300, 320, 3, 2, true, RGB(0, 255, 0));
	_mikotoJump->setX(_mikotoIdle->getX());
	_mikotoJump->setY(_mikotoIdle->getY());
	_mikotoJump->setFrameX(0);
	_mikotoJump->setFrameY(0);
	//공격 이미지
	_mikotoAttack = IMAGEMANAGER->addFrameImage("미코토공격", "images/캐릭터/MIKOTO/MIKOTO_ATTACK.bmp", 630, 320, 2, 2, true, RGB(0, 255, 0));
	_mikotoAttack->setX(_mikotoIdle->getX());
	_mikotoAttack->setY(_mikotoIdle->getY());
	_mikotoAttack->setFrameX(0);
	_mikotoAttack->setFrameY(0);
	//레일건 스킬 시전 이미지
	_mikotoRailgun = IMAGEMANAGER->addFrameImage("미코토레일건", "images/캐릭터/MIKOTO/MIKOTO_RAILGUN_SKILL.bmp", 900, 500, 3, 2, true, RGB(0, 255, 0));
	_mikotoRailgun->setX(_mikotoIdle->getX());
	_mikotoRailgun->setY(_mikotoIdle->getY());
	_mikotoRailgun->setFrameX(0);
	_mikotoRailgun->setFrameY(0);
	//레일건 이미지
	_railgunImg = IMAGEMANAGER->findImage("레일건");
	//기절 이미지
	_mikotoFallDown = IMAGEMANAGER->addFrameImage("미코토기절", "images/캐릭터/MIKOTO/MIKOTO_FALLDOWN.bmp", 400, 80, 2, 1, true, RGB(0, 255, 0));
	_mikotoFallDown->setX(_mikotoIdle->getX());
	_mikotoFallDown->setY(_mikotoIdle->getY());
	_mikotoFallDown->setFrameX(0);

	//최초 캐릭터 위치(중점 좌표)
	_x = 100;
	_y = WINSIZEY - 200;

	//점프 관련 초기화
	_angle = _gravity = 0;
	_speed = 12.0f;

	_count = _index = 0;
	_landingCount = 0;

	_isGround = false;
	_isAttack = false;
	_isRailgun = false;
	_isRailgun = false;

	//레일건 렉트
	//_rX = _rW = _rH = 0;
	_rY = (_player.bottom + _player.top) / 2;
	// 800 * 80
	//_railgun = RectMakeCenter(0, 0, 800, 80);
	_railgunCount = 0;
	_damageCount = 0;

	//캐릭터 HP, CP관련
	_playerHP = 1000;
	_playerCP = 200;
	_hpX = 200;
	_hpY = 50;
	_cpX = 500;
	_cpY = 50;
	_hpfX = 200;
	_cpfX = 200;

	_playerHPgauge = RectMakeCenter(_hpX, _hpY, 230, 30);
	_playerCPgauge = RectMakeCenter(_cpX, _cpY, 230, 30);
	//
	_playerHPFront = RectMake(_playerHPgauge.left + 26, _playerHPgauge.top, 200, 22);
	_playerCPFront = RectMake(_playerCPgauge.left + 26, _playerCPgauge.top, 200, 22);

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	//캐릭터 조작
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) && _isGround && _direction != LEFT_FALLDOWN && _direction != RIGHT_FALLDOWN) _direction = LEFT_IDLE;
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && _isGround && _direction != LEFT_FALLDOWN && _direction != RIGHT_FALLDOWN) _direction = RIGHT_IDLE;
	//이동 (스테이지에 따른 이동 범위 조절 필요)
	
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _player.left > _stage->getMinX() && _isGround
		&& _direction != LEFT_FALLDOWN && _direction != RIGHT_FALLDOWN)
	{
		_direction = LEFT_MOVE;
		_x -= 7;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _player.right < _stage->getMaxX() && _isGround
		&& _direction != LEFT_FALLDOWN && _direction != RIGHT_FALLDOWN)
	{
		_direction = RIGHT_MOVE;
		_x += 7;
	}
	
	//점프
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _direction != LEFT_FALLDOWN && _direction != RIGHT_FALLDOWN)
	{
		_isGround = false;
		if (_direction == LEFT_IDLE || _direction == LEFT_MOVE)
		{
			_direction = LEFT_JUMP_START;
			_angle = PI * 2 / 3;
		}
		if (_direction == RIGHT_IDLE || _direction == RIGHT_MOVE)
		{
			_direction = RIGHT_JUMP_START;
			_angle = PI / 3;
		}
	}
	//공격
	if (KEYMANAGER->isOnceKeyDown(VK_CONTROL) && !_isAttack && _direction != LEFT_FALLDOWN && _direction != RIGHT_FALLDOWN)
	{
		_isAttack = true;
		_ATK = RND->getFromIntTo(25, 45);
		if (_direction == LEFT_IDLE || _direction == LEFT_MOVE)
		{
			_index = 1;
			_direction = LEFT_ATTACK;
		}
		if (_direction == RIGHT_IDLE || _direction == RIGHT_MOVE)
		{
			_index = 0;
			_direction = RIGHT_ATTACK;
		}
	}
	//레일건
	if (KEYMANAGER->isOnceKeyDown('X') && !_isRailgun && _direction != LEFT_FALLDOWN && _direction != RIGHT_FALLDOWN)
	{
		_playerCP -= 100;
		_cpfX -= 100;
		if ((_direction == LEFT_IDLE || _direction == LEFT_MOVE))
		{
			_index = 2;
			_direction = LEFT_RAILGUN;
			_isRailgun = true;
			_railgunImg->setFrameX(0);
			_railgunImg->setFrameY(1);
			_railgun = RectMakeCenter(_player.left - 410, (_player.bottom + _player.top) / 2, 800, 80);
		}
		if ((_direction == RIGHT_IDLE || _direction == RIGHT_MOVE))
		{
			_index = 0;
			_direction = RIGHT_RAILGUN;
			_isRailgun = true;
			_railgunImg->setFrameX(0);
			_railgunImg->setFrameY(0);
			_railgun = RectMakeCenter(_player.right + 410, (_player.bottom + _player.top) / 2, 800, 80);
		}
		//_railgunCount = 0;
	}
	if (_isRailgun)
	{
		_railgunCount++;
		_railgunATK = RND->getFromIntTo(200, 350);
		if (_railgunCount > 30)
		{
			_isRailgun = false;
			_boss->setIsDamage(false);
		}
	}
	if (!_isRailgun)
	{
		_railgunCount = 0;
		_railgun = RectMakeCenter(0, 0, 0, 0);
		if (_direction == LEFT_RAILGUN) _direction = LEFT_IDLE;
		if (_direction == RIGHT_RAILGUN) _direction = RIGHT_IDLE;
	}

	//기력
	if (_playerCP < 200)
	{
		_playerCP++;
		if(_cpfX < 200)_cpfX++;
	}

	//점프 상태
	if ((_direction == LEFT_JUMP_START || _direction == RIGHT_JUMP_START ||
		_direction == LEFT_JUMP_DESCENT || _direction == RIGHT_JUMP_DESCENT)
		&& !_isGround)
	{
		_x += cosf(_angle) * _speed;
		_y += (-sinf(_angle)) * _speed + _gravity;
		_gravity += 0.2f;
		_player = RectMakeCenter(_x, _y, 100, 160);

		//점프 하강중
		if (_speed <= _gravity)
		{
			if (_direction == LEFT_JUMP_START)
			{
				_direction = LEFT_JUMP_DESCENT;
			}
			if (_direction == RIGHT_JUMP_START)
			{
				_direction = RIGHT_JUMP_DESCENT;
			}
		}
		
		if (_player.right > _stage->getMaxX()) _x = _stage->getMaxX() - 50;
		if (_player.left < _stage->getMinX()) _x = _stage->getMinX() + 50;
		
	}

	//중력처리
	if (_isGround)
	{
		_gravity = 0;
		if (_direction == LEFT_JUMP_DESCENT) _direction = LEFT_JUMP_LANDING;
		if (_direction == RIGHT_JUMP_DESCENT) _direction = RIGHT_JUMP_LANDING;
	}
	else
	{
		_y += 2;
	}

	//충돌처리
	collisionBoss();

	//기절
	if (_playerHP <= 0)
	{
		if (_direction == LEFT_IDLE || _direction == LEFT_MOVE) _direction = LEFT_FALLDOWN;
		if (_direction == RIGHT_IDLE || _direction == RIGHT_MOVE) _direction = RIGHT_FALLDOWN;
	}

	//디렉션
	_count++;
	if (_count % 10 == 0)
	{
		if (!(_direction == LEFT_ATTACK || _direction == RIGHT_ATTACK)) _isAttack = false;
		//기본
		if (_direction == LEFT_IDLE)
		{
			_landingCount = 0;
			if(_index < 0) _index = 3;
			_mikotoIdle->setFrameX(_index);
			_mikotoIdle->setFrameY(1);
			_index--;
		}
		if (_direction == RIGHT_IDLE)
		{
			_landingCount = 0;
			if (_index > 3) _index = 0;
			_mikotoIdle->setFrameX(_index);
			_mikotoIdle->setFrameY(0);
			_index++;
		}
		//이동
		if (_direction == LEFT_MOVE)
		{
			if (_index < 0) _index = 4;
			_mikotoMove->setFrameX(_index);
			_mikotoMove->setFrameY(1);
			_index--;
		}
		if (_direction == RIGHT_MOVE)
		{
			if (_index > 4) _index = 0;
			_mikotoMove->setFrameX(_index);
			_mikotoMove->setFrameY(0);
			_index++;
		}
		//점프
		if (_direction == LEFT_JUMP_START)
		{
			_mikotoJump->setFrameX(2);
			_mikotoJump->setFrameY(1);
		}
		if (_direction == LEFT_JUMP_DESCENT)
		{
			_mikotoJump->setFrameX(1);
			_mikotoJump->setFrameY(1);
		}
		if (_direction == LEFT_JUMP_LANDING)
		{
			_landingCount++;
			_mikotoJump->setFrameX(0);
			_mikotoJump->setFrameY(1);
			if (_landingCount > 2) _direction = LEFT_IDLE;
		}
		if (_direction == RIGHT_JUMP_START)
		{
			_mikotoJump->setFrameX(0);
			_mikotoJump->setFrameY(0);
		}
		if (_direction == RIGHT_JUMP_DESCENT)
		{
			_mikotoJump->setFrameX(1);
			_mikotoJump->setFrameY(0);
		}
		if (_direction == RIGHT_JUMP_LANDING)
		{
			_landingCount++;
			_mikotoJump->setFrameX(2);
			_mikotoJump->setFrameY(0);
			if (_landingCount > 2) _direction = RIGHT_IDLE;
		}
		//공격
		if (_direction == LEFT_ATTACK)
		{
			if (_index < 0)
			{
				_isAttack = false;
				_boss->setIsDamage(false);
				_direction = LEFT_IDLE;
			}
			_mikotoAttack->setFrameX(_index);
			_mikotoAttack->setFrameY(1);
			_index--;
		}
		if (_direction == RIGHT_ATTACK)
		{
			if (_index > 1) 
			{
				_isAttack = false;
				_boss->setIsDamage(false);
				_direction = RIGHT_IDLE;
			}
			_mikotoAttack->setFrameX(_index);
			_mikotoAttack->setFrameY(0);
			_index++;
		}
		//레일건 스킬
		if (_direction == LEFT_RAILGUN)
		{
			if (_index < 0) _index = 0;
			_mikotoRailgun->setFrameX(_index);
			_mikotoRailgun->setFrameY(1);
			_index--;
		}
		if (_direction == RIGHT_RAILGUN)
		{
			if (_index > 2) _index = 2;
			_mikotoRailgun->setFrameX(_index);
			_mikotoRailgun->setFrameY(0);
			_index++;
		}
		//기절
		if (_direction == LEFT_FALLDOWN)
		{
			_mikotoFallDown->setFrameX(0);
		}
		if (_direction == RIGHT_FALLDOWN)
		{
			_mikotoFallDown->setFrameX(1);
		}
		_count = 0;
	}

	
}

void player::render()
{
	//캐릭터 각 상태 프레임별 크기
	//IDLE, MOVE, JUMP : 100 * 160 -> _x = 50, _y = 80
	//ATTACK : 315 * 160 -> _x = 157, _y = 80
	//FALLDOWN : 200 * 80 -> _x = 100, _y = 40

	//캐릭터 HP/CP 게이지
	_playerHPgauge = RectMakeCenter(CAMERA->getLeft() + _hpX, _hpY, 230, 30);
	_playerCPgauge = RectMakeCenter(CAMERA->getLeft() + _cpX, _cpY, 230, 30);
	Rectangle(getMemDC(), _playerHPgauge);
	Rectangle(getMemDC(), _playerCPgauge);

	IMAGEMANAGER->findImage("플레이어HP게이지바탕")->render(getMemDC(), _playerHPgauge.left, _playerHPgauge.top);
	IMAGEMANAGER->findImage("플레이어CP게이지바탕")->render(getMemDC(), _playerCPgauge.left, _playerCPgauge.top);

	HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);

	FillRect(getMemDC(), &_playerHPFront, brush);
	//Rectangle(getMemDC(), _playerHPFront);

	SelectObject(getMemDC(), oldBrush);
	DeleteObject(brush);

	brush = CreateSolidBrush(RGB(0, 250, 255));
	oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);

	FillRect(getMemDC(), &_playerCPFront, brush);
	//Rectangle(getMemDC(), _playerCPFront);

	SelectObject(getMemDC(), oldBrush);
	DeleteObject(brush);

	//_playerHPFront = RectMake(CAMERA->getLeft() + 200, _playerHPgauge.top + 4, _hpfX, 22);
	//_playerCPFront = RectMake(CAMERA->getLeft() + 500, _playerCPgauge.top + 4, _cpfX, 22);
	_playerHPFront = RectMake(_playerHPgauge.left + 26, _playerHPgauge.top + 4, _hpfX, 22);
	_playerCPFront = RectMake(_playerCPgauge.left + 26, _playerCPgauge.top + 4, _cpfX, 22);
	//_playerHPFront = RectMakeCenter(CAMERA->getLeft() + _hpfX, 50, 200, 23);
	//_playerCPFront = RectMakeCenter(CAMERA->getLeft() + _cpfX, 50, 200, 23);
	//Rectangle(getMemDC(), _playerHPFront);

	//렉트 조정용 정수형 변수
	int controlX = 100;
	int	controlY = 160;

	//캐릭터 렉트 렌더
	//Rectangle(getMemDC(), _player);
	
	_player = RectMakeCenter(_x, _y, controlX, controlY);
	//기본
	if (_direction == LEFT_IDLE || _direction == RIGHT_IDLE)
	{
		_mikotoIdle->frameRender(getMemDC(), _player.left, _player.top, _mikotoIdle->getFrameX(), _mikotoIdle->getFrameY());
	}
	//이동
	if (_direction == LEFT_MOVE || _direction == RIGHT_MOVE)
	{
		_mikotoMove->frameRender(getMemDC(), _player.left, _player.top, _mikotoMove->getFrameX(), _mikotoMove->getFrameY());
	}
	//점프
	if (_direction == LEFT_JUMP_START || _direction == RIGHT_JUMP_START || 
		_direction == LEFT_JUMP_DESCENT || _direction == RIGHT_JUMP_DESCENT ||
		_direction == LEFT_JUMP_LANDING || _direction == RIGHT_JUMP_LANDING)
	{
		_mikotoJump->frameRender(getMemDC(), _player.left, _player.top, _mikotoJump->getFrameX(), _mikotoJump->getFrameY());
	}
	//공격
	if (_direction == LEFT_ATTACK || _direction == RIGHT_ATTACK)
	{
		controlX = 315;
		controlY = 160;
		_mikotoAttack->frameRender(getMemDC(), _player.left - 107, _player.top, _mikotoAttack->getFrameX(), _mikotoAttack->getFrameY());
		//Rectangle(getMemDC(), _player); //공격 렉트
	}
	//레일건 스킬
	if (_direction == LEFT_RAILGUN || _direction == RIGHT_RAILGUN)
	{
		controlX = 300;
		controlY = 250;
		_mikotoRailgun->frameRender(getMemDC(), _player.left - 100, _player.top-45, _mikotoRailgun->getFrameX(), _mikotoRailgun->getFrameY());
		//Rectangle(getMemDC(), _railgun); //레일건 공격 렉트
	}
	//기절
	if (_direction == LEFT_FALLDOWN || _direction == RIGHT_FALLDOWN)
	{
		controlX = 200;
		controlY = 80;
		_mikotoFallDown->frameRender(getMemDC(), _player.left, _player.top + 80, _mikotoFallDown->getFrameX(), _mikotoFallDown->getFrameY());
	}
	
	//IMAGEMANAGER->findImage("레일건")->render(getMemDC(), _railgun.left, _railgun.top);

	_player = RectMakeCenter(_x, _y, controlX, controlY);
	//디버깅용
	/*char str[128];
	sprintf_s(str, "플레이어X : %f / 플레이어Y : %f", _x, _y);
	TextOut(getMemDC(), CAMERA->getLeft()+100, 100, str, strlen(str));

	sprintf_s(str, "isGround : %d", (int)_isGround);
	TextOut(getMemDC(), CAMERA->getLeft() + 100, 120, str, strlen(str));

	sprintf_s(str, "isAttack : %d", (int)_isAttack);
	TextOut(getMemDC(), CAMERA->getLeft() + 100, 140, str, strlen(str));

	sprintf_s(str, "isRailgun : %d", (int)_isRailgun);
	TextOut(getMemDC(), CAMERA->getLeft() + 100, 160, str, strlen(str));

	sprintf_s(str, "isDamage : %d", (int)_isDamage);
	TextOut(getMemDC(), CAMERA->getLeft() + 100, 180, str, strlen(str));

	sprintf_s(str, "플레이어 체력 : %d / 플레이어 기력 : %d", _playerHP, _playerCP);
	TextOut(getMemDC(), CAMERA->getLeft() + 200, 140, str, strlen(str));

	sprintf_s(str, "플레이어 공격력 : %d / 플레이어 스킬공격력 : %d", _ATK, _railgunATK);
	TextOut(getMemDC(), CAMERA->getLeft() + 200, 160, str, strlen(str));*/

	//레일건
	//Rectangle(getMemDC(), _railgun);
	if(_isRailgun) _railgunImg->frameRender(getMemDC(), _railgun.left, _railgun.top, _railgunImg->getFrameX(), _railgunImg->getFrameY());

}

void player::collisionBoss()
{
	//보스 공격 피격
	if (_boss->getIsAttack() && !_isDamage)
	{
		RECT temp;
		if (IntersectRect(&temp, &_player, &_boss->getBlackWaveRect()))
		{
			_playerHP -= _boss->getATK();
			_hpfX -= _boss->getATK();
			if (_hpfX <= 0)
			{
				_playerHP = 0;
				_hpfX = 0;
			}
			_isDamage = true;
			//_boss->setIsAttack(false);
		}
	}
	//공격 반사
	if (_boss->getIsReflect() && !_isDamage)
	{
		//일반 공격
		RECT temp;
		if (_isAttack && IntersectRect(&temp, &_player, &_boss->getRect()))
		{
			_playerHP -= _ATK / 2;
			_hpfX -= _ATK / 2;
			if (_hpfX <= 0)
			{
				_playerHP = 0;
				_hpfX = 0;
			}
			_isDamage = true;
			_boss->setIsReflect(false);
		}
		//레일건
		if (_isRailgun && IntersectRect(&temp, &_railgun, &_boss->getRect()))
		{
			_playerHP -= _railgunATK / 2;
			_hpfX -= _railgunATK / 2;
			if (_hpfX <= 0)
			{
				_playerHP = 0;
				_hpfX = 0;
			}
			_isDamage = true;
			_boss->setIsReflect(false);
		}
	}

	//피격 면제 타임 흐름
	if (_isDamage)
	{
		_damageCount++;
		if (_damageCount > 50)
		{
			_isDamage = false;
			_damageCount = 0;
		}
	}
}

