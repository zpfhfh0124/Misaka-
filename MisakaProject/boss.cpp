#include "stdafx.h"
#include "boss.h"
#include "player.h"

boss::boss()
{
}

boss::~boss()
{
}

HRESULT boss::init()
{
	//_x = WINSIZEX / 2;
	//_y = WINSIZEY / 2;

	//���� ĳ�� HP
	_bossHP = 1000;
	_hpX = WINSIZEX / 2;
	_hpY = 120;
	//_hpW = 1000;

	_direction = LEFT_PATTERN_A;
	_accelImage = IMAGEMANAGER->findImage("�׼����ϰ���");
	_blackWaveImg = IMAGEMANAGER->findImage("����");

	_ani = new animation;
	_ani->init(_accelImage->getWidth(), _accelImage->getHeight(),
		_accelImage->getFrameWidth(), _accelImage->getFrameHeight());
	int indexs[3] = {5, 4, 3};
	_ani->setPlayFrame(indexs, 3, false);
	_ani->setFPS(10);
	_ani->start();
	
	_direction = LEFT_IDLE_A;

	_bwCount = 0;

	_isGround = false;
	_isAttack = false;
	_isReflect = false;
	_isDamage = false;

	return S_OK;
}

void boss::release()
{
}

void boss::update()
{
	_ani->frameUpdate(TIMEMANAGER->getElapsedTime());

	if (!_isGround) _y += 5;
	
	/*_patternCount++;
	if (_patternCount % 100 == 0)
	{
		int nextDir = (int)_direction;
		nextDir++;
		if (nextDir > 7) nextDir = 0;
		setDirection(nextDir);
		
		_patternCount = 0;
	}*/
	
	//�ǰ�ó��
	collision();

	//���� ĳ���� AIó��
	//*����ĳ������ �÷��̾�ĳ���� ������ �ִ� ���
	//**�÷��̾���� �Ÿ��� 200 �ʰ�
	if (_player->getRect().right < _bossNPC.left &&
		_bossNPC.left - _player->getRect().right > 200
		&& _direction != LEFT_FALLDOWN_A && _direction != RIGHT_FALLDOWN_A)
	{
		if (_direction != LEFT_MOVE_A)
		{
			_direction = LEFT_MOVE_A;
			_accelImage = IMAGEMANAGER->findImage("�׼��̵�");
			_ani->init(_accelImage->getWidth(), _accelImage->getHeight(),
				_accelImage->getFrameWidth(), _accelImage->getFrameHeight());
			int indexs[6] = { 11, 10, 9, 8, 7, 6 };
			_ani->setPlayFrame(indexs, 6, true);
			_ani->setFPS(1);
			_ani->start();
		}
		_x -= 3;
	}
	//**�÷��̾���� �Ÿ��� 50 �̸�
	if (_player->getRect().right < _bossNPC.left &&
		_bossNPC.left - _player->getRect().right < 50
		&& _direction != LEFT_FALLDOWN_A && _direction != RIGHT_FALLDOWN_A)
	{
		if (_direction != LEFT_PATTERN_A)
		{
			_direction = LEFT_PATTERN_A;
			_accelImage = IMAGEMANAGER->findImage("�׼����ϰ���");
			_ani->init(_accelImage->getWidth(), _accelImage->getHeight(),
				_accelImage->getFrameWidth(), _accelImage->getFrameHeight());
			//int indexs[3] = { 5, 4, 3 };
			_ani->setPlayFrame(5, 3, false, false);
			_ani->setFPS(1);
			_ani->start();
			_isAttack = true;
		}
	}
	//**�÷��̾���� �Ÿ��� 50 ~ 200 ����
	if (_player->getRect().right < _bossNPC.left &&
		_bossNPC.left - _player->getRect().right >= 50 &&
		_bossNPC.left - _player->getRect().right <= 200
		&& _direction != LEFT_FALLDOWN_A && _direction != RIGHT_FALLDOWN_A)
	{
		//���ݹݻ�
		if (_direction != LEFT_REFLECT_A)
		{
			_direction = LEFT_REFLECT_A;
			_accelImage = IMAGEMANAGER->findImage("�׼����ݹݻ�");
			_ani->init(_accelImage->getWidth(), _accelImage->getHeight(),
				_accelImage->getFrameWidth(), _accelImage->getFrameHeight());
			//int indexs[2] = { 3, 2 };
			_ani->setPlayFrame(3, 2, false, true);
			_ani->setFPS(1);
			_ani->start();
			_isReflect = true;
		}
	}

	//*����ĳ������ �÷��̾�ĳ���� ������ �ִ� ���
	//**�÷��̾���� �Ÿ��� 200 �ʰ�
	if (_player->getRect().left > _bossNPC.right &&
		_player->getRect().left - _bossNPC.right > 200
		&& _direction != LEFT_FALLDOWN_A && _direction != RIGHT_FALLDOWN_A)
	{
		if (_direction != RIGHT_MOVE_A)
		{
			_direction = RIGHT_MOVE_A;
			_accelImage = IMAGEMANAGER->findImage("�׼��̵�");
			_ani->init(_accelImage->getWidth(), _accelImage->getHeight(),
				_accelImage->getFrameWidth(), _accelImage->getFrameHeight());
			int indexs[6] = { 0, 1, 2, 3, 4, 5 };
			_ani->setPlayFrame(indexs, 6, true);
			_ani->setFPS(1);
			_ani->start();
		}
		_x += 3;
	}
	//**�÷��̾���� �Ÿ��� 50 �̸�
	if (_player->getRect().left > _bossNPC.right &&
		_player->getRect().left - _bossNPC.right < 50
		&& _direction != LEFT_FALLDOWN_A && _direction != RIGHT_FALLDOWN_A)
	{
		if (_direction != RIGHT_PATTERN_A)
		{
			_direction = RIGHT_PATTERN_A;
			_accelImage = IMAGEMANAGER->findImage("�׼����ϰ���");
			_ani->init(_accelImage->getWidth(), _accelImage->getHeight(),
				_accelImage->getFrameWidth(), _accelImage->getFrameHeight());
			//int indexs[3] = { 0, 1, 2 };
			_ani->setPlayFrame(0, 2, false, false);
			_ani->setFPS(1);
			_ani->start();
			_isAttack = true;
		}
	}
	//**�÷��̾���� �Ÿ��� 50 ~ 200 ����
	if (_player->getRect().left > _bossNPC.right &&
		_player->getRect().left - _bossNPC.right <= 200 &&
		_player->getRect().left - _bossNPC.right >= 50
		&& _direction != LEFT_FALLDOWN_A && _direction != RIGHT_FALLDOWN_A)
	{
		//���ݹݻ�
		if (_direction != RIGHT_REFLECT_A)
		{
			_direction = RIGHT_REFLECT_A;
			_accelImage = IMAGEMANAGER->findImage("�׼����ݹݻ�");
			_ani->init(_accelImage->getWidth(), _accelImage->getHeight(),
				_accelImage->getFrameWidth(), _accelImage->getFrameHeight());
			int indexs[2] = { 0, 1 };
			_ani->setPlayFrame(0, 1, false, true);
			_ani->setFPS(1);
			_ani->start();
			_isReflect = true;
		}
	}
	


	//���ϰ��� ����
	if (_isAttack)
	{
		_ATK = RND->getFromIntTo(12, 24);
		if (_direction == LEFT_PATTERN_A)
		{
			_blackWave = RectMakeCenter(_bossNPC.left - 300,
				(_bossNPC.bottom + _bossNPC.top) / 2, 600, 153);
			_blackWaveImg->setFrameX(0);
			_blackWaveImg->setFrameY(1);
		}
		else if (_direction == RIGHT_PATTERN_A)
		{
			_blackWave = RectMakeCenter(_bossNPC.right + 300,
				(_bossNPC.bottom + _bossNPC.top) / 2, 600, 153);
			_blackWaveImg->setFrameX(0);
			_blackWaveImg->setFrameY(0);
		}
		_bwCount++;
		if (_bwCount > 30) 
		{
			_isAttack = false;
			_player->setIsDamage(false);
		}
	}
	else
	{
		_bwCount = 0;
		_blackWave = RectMakeCenter(0, 0, 0, 0);
	}

	//����
	if (_bossHP <= 0)
	{
		if (_direction == LEFT_IDLE_A || _direction == LEFT_MOVE_A ||
			_direction == LEFT_PATTERN_A || _direction == LEFT_REFLECT_A)
		{
			_direction = LEFT_FALLDOWN_A;
			_accelImage = IMAGEMANAGER->findImage("�׼�����");
			_ani->init(_accelImage->getWidth(), _accelImage->getHeight(),
				_accelImage->getFrameWidth(), _accelImage->getFrameHeight());
			int indexs[1] = { 1 };
			_ani->setPlayFrame(indexs, 1, false);
			_ani->setFPS(1);
			_ani->start();
		}
		if (_direction == RIGHT_IDLE_A || _direction == RIGHT_MOVE_A ||
			_direction == RIGHT_PATTERN_A || _direction == RIGHT_REFLECT_A)
		{
			_direction = RIGHT_FALLDOWN_A;
			_accelImage = IMAGEMANAGER->findImage("�׼�����");
			_ani->init(_accelImage->getWidth(), _accelImage->getHeight(),
				_accelImage->getFrameWidth(), _accelImage->getFrameHeight());
			int indexs[1] = { 0 };
			_ani->setPlayFrame(indexs, 1, false);
			_ani->setFPS(1);
			_ani->start();
		}
	}

	/*switch (_direction)
	{
		case LEFT_IDLE_A:// 0
		{
			_accelImage = IMAGEMANAGER->findImage("�׼��⺻");
			_ani->init(_accelImage->getWidth(), _accelImage->getHeight(),
				_accelImage->getFrameWidth(), _accelImage->getFrameHeight());
			int indexs[4] = { 7, 6, 5, 4 };
			_ani->setPlayFrame(indexs, 4, true);
			_ani->setFPS(1);
			_ani->start();
			
		}
		break;
		case RIGHT_IDLE_A:// 1
		{
			_accelImage = IMAGEMANAGER->findImage("�׼��⺻");
			_ani->init(_accelImage->getWidth(), _accelImage->getHeight(),
				_accelImage->getFrameWidth(), _accelImage->getFrameHeight());
			int indexs[4] = { 0, 1, 2, 3 };
			_ani->setPlayFrame(indexs, 4, true);
			_ani->setFPS(1);
			_ani->start();
		}
		break;
		case LEFT_MOVE_A:// 2
		{
			_accelImage = IMAGEMANAGER->findImage("�׼��̵�");
			_ani->init(_accelImage->getWidth(), _accelImage->getHeight(),
				_accelImage->getFrameWidth(), _accelImage->getFrameHeight());
			int indexs[6] = { 11, 10, 9, 8, 7, 6 };
			_ani->setPlayFrame(indexs, 6, true);
			_ani->setFPS(1);
			_ani->start();
			_x -= 3;
			
		}
			break;
		case RIGHT_MOVE_A:// 3
		{
			_accelImage = IMAGEMANAGER->findImage("�׼��̵�");
			_ani->init(_accelImage->getWidth(), _accelImage->getHeight(),
				_accelImage->getFrameWidth(), _accelImage->getFrameHeight());
			int indexs[6] = { 0, 1, 2, 3, 4, 5 };
			_ani->setPlayFrame(indexs, 6, true);
			_ani->setFPS(1);
			_ani->start();
			_x += 3;
		}
		break;
		case LEFT_PATTERN_A:// 4
		{

			_accelImage = IMAGEMANAGER->findImage("�׼����ϰ���");
			_ani->init(_accelImage->getWidth(), _accelImage->getHeight(),
				_accelImage->getFrameWidth(), _accelImage->getFrameHeight());
			//int indexs[3] = { 5, 4, 3 };
			_ani->setPlayFrame(5, 3, false, false);
			_ani->setFPS(1);
			_ani->start();
			_isAttack = true;
		}
		break;
		case RIGHT_PATTERN_A:// 5
		{
			_accelImage = IMAGEMANAGER->findImage("�׼����ϰ���");
			_ani->init(_accelImage->getWidth(), _accelImage->getHeight(),
				_accelImage->getFrameWidth(), _accelImage->getFrameHeight());
			//int indexs[3] = { 0, 1, 2 };
			_ani->setPlayFrame(0, 2, false, false);
			_ani->setFPS(1);
			_ani->start();
			_isAttack = true;
		}
		break;
		case LEFT_REFLECT_A:// 6
		{
			_accelImage = IMAGEMANAGER->findImage("�׼����ݹݻ�");
			_ani->init(_accelImage->getWidth(), _accelImage->getHeight(),
				_accelImage->getFrameWidth(), _accelImage->getFrameHeight());
			//int indexs[2] = { 3, 2 };
			_ani->setPlayFrame(3, 2, true, true);
			_ani->setFPS(1);
			_ani->start();
			_isReflect = true;
		}
		break;
		case RIGHT_REFLECT_A:// 7
		{
			_accelImage = IMAGEMANAGER->findImage("�׼����ݹݻ�");
			_ani->init(_accelImage->getWidth(), _accelImage->getHeight(),
				_accelImage->getFrameWidth(), _accelImage->getFrameHeight());
			int indexs[2] = { 0, 1 };
			_ani->setPlayFrame(0, 1, false, true);
			_ani->setFPS(1);
			_ani->start();
			_isReflect = true;
		}
		break;
		case LEFT_FALLDOWN_A:// 8
		{
			_accelImage = IMAGEMANAGER->findImage("�׼�����");
			_ani->init(_accelImage->getWidth(), _accelImage->getHeight(),
				_accelImage->getFrameWidth(), _accelImage->getFrameHeight());
			int indexs[1] = { 1 };
			_ani->setPlayFrame(indexs, 1, false);
			_ani->setFPS(1);
			_ani->start();
		}
		break;
		case RIGHT_FALLDOWN_A:// 9
		{
			_accelImage = IMAGEMANAGER->findImage("�׼�����");
			_ani->init(_accelImage->getWidth(), _accelImage->getHeight(),
				_accelImage->getFrameWidth(), _accelImage->getFrameHeight());
			int indexs[1] = { 0 };
			_ani->setPlayFrame(indexs, 1, false);
			_ani->setFPS(1);
			_ani->start();
		}
		break;
		//_ani->frameUpdate(TIMEMANAGER->getElapsedTime());
	}*/
	_ani->frameUpdate(TIMEMANAGER->getElapsedTime());
		
	
}

void boss::render()
{
	int controlX = 100;
	int controlY = 180;

	/*if (_direction == LEFT_IDLE_A || _direction == RIGHT_IDLE_A)
	{
		_accelImage = IMAGEMANAGER->findImage("�׼��⺻");
	}
	if (_direction == LEFT_MOVE_A || _direction == RIGHT_MOVE_A)
	{
		_accelImage = IMAGEMANAGER->findImage("�׼��̵�");
	}*/
	if (_direction == LEFT_PATTERN_A || _direction == RIGHT_PATTERN_A)
	{
		//_accelImage = IMAGEMANAGER->findImage("�׼����ϰ���");
		controlX = 245;
		controlY = 240;
	}
	if (_direction == LEFT_REFLECT_A || _direction == RIGHT_REFLECT_A)
	{
		//_accelImage = IMAGEMANAGER->findImage("�׼����ݹݻ�");
		controlX = 120;
		controlY = 180;
	}
	if (_direction == LEFT_FALLDOWN_A || _direction == RIGHT_FALLDOWN_A)
	{
		_accelImage = IMAGEMANAGER->findImage("�׼�����");
		controlX = 200;
		controlY = 80;
	}

	_bossNPC = RectMakeCenter(_x, _y, controlX, controlY);
	_accelImage->aniRender(getMemDC(), _bossNPC.left, _bossNPC.top, _ani);

	//���� ü�� HP ������
	_bossHPgauge = RectMakeCenter(_hpX, _hpY, 1080, 70);
	Rectangle(getMemDC(), _bossHPgauge);
	IMAGEMANAGER->findImage("��������������")->render(getMemDC(), _bossHPgauge.left, _bossHPgauge.top);

	HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);

	FillRect(getMemDC(), &_bossHPFront, brush);

	SelectObject(getMemDC(), oldBrush);
	DeleteObject(brush);

	_bossHPFront = RectMake(_bossHPgauge.left + 64, _bossHPgauge.top + 10, _bossHP, 50);
	//_bossHPFront = RectMakeCenter(_bossHPgauge.left + 564, _hpY, _hpW, 50);

	//��ȭ���� �߻�ü
	//Rectangle(getMemDC(), _blackWave);
	if (_isAttack) _blackWaveImg->frameRender(getMemDC(), _blackWave.left, _blackWave.top, _blackWaveImg->getFrameX(), _blackWaveImg->getFrameY());

	//�����
	/*char str[128];
	sprintf_s(str, "����ī��Ʈ : %d", _patternCount);
	TextOut(getMemDC(), 200, 140, str, strlen(str));

	sprintf_s(str, "���� ü�� : %d", _bossHP);
	TextOut(getMemDC(), 600, 140, str, strlen(str));

	sprintf_s(str, "���� ���ݷ� : %d", _ATK);
	TextOut(getMemDC(), 600, 160, str, strlen(str));*/
}

void boss::collision()
{
	//�÷��̾��� �Ϲ� ����
	if (_player->getPlayerAttack() && !_isReflect && !_isDamage)
	{
		RECT temp;
		if (IntersectRect(&temp, &_bossNPC, &_player->getRect()))
		{
			_bossHP -= _player->getATK();
			//_hpW -= _player->getATK();
			if (_bossHP < 0)
			{
				_bossHP = 0;
			}
			_isDamage = true;
			//_player->setPlayerAttack(false);
		}
	}
	//�÷��̾��� ��ų ����
	if (_player->getRailgun() && !_isReflect && !_isDamage)
	{
		RECT temp;
		if (IntersectRect(&temp, &_bossNPC, &_player->getRailgunRect()))
		{
			_bossHP -= _player->getRailgunATK();
			//_hpW -= _player->getATK();
			if (_bossHP < 0)
			{
				_bossHP = 0;
			}
			_isDamage = true;
			//_player->setRailgun(false);
		}
	}
}
