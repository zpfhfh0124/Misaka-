#include "stdafx.h"
#include "playGround.h"
#include "fieldStage.h"
#include "bossStage.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ �Լ�
HRESULT playGround::init()
{
	gameNode::init(true);


	// * �̹��� �߰�
	// ** ���
	IMAGEMANAGER->addImage("����", "images/���/Academy_City_(Aerial_View)_����_1200x800.bmp", 1200, 800, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("�ٰ�", "images/���/���� �ٰ�2.bmp", 5000, 800, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���������", "images/���/battleAccel.bmp", 1200, 800, true, RGB(255, 0, 255));
	// ** ����
	IMAGEMANAGER->addImage("�ʵ�����ó��", "images/��ֹ� ������Ʈ/map_ground.bmp", 5000, 800, true, RGB(0, 255, 255));
	IMAGEMANAGER->addImage("����������ó��", "images/��ֹ� ������Ʈ/battleAccel_ground.bmp", 1200, 800, true, RGB(0, 255, 255));
	IMAGEMANAGER->addImage("��Ż", "images/��ֹ� ������Ʈ/��Ż.bmp", 130, 200, true, RGB(255, 0, 255));
	
	// ** ����
	// *** �Ϲݸ���
	IMAGEMANAGER->addFrameImage("����", "images/����/����_resize.bmp", 980, 200, 7, 2, true, RGB(0, 255, 0));
	// *** ����ĳ��
	IMAGEMANAGER->addFrameImage("�׼��⺻", "images/ĳ����/ACCEL/ACCEL_IDLE.bmp", 400, 360, 4, 2, true, RGB(0, 255, 0));
	IMAGEMANAGER->addFrameImage("�׼��̵�", "images/ĳ����/ACCEL/ACCEL_MOVE.bmp", 1200, 300, 6, 2, true, RGB(0, 255, 0));
	IMAGEMANAGER->addFrameImage("�׼����ϰ���", "images/ĳ����/ACCEL/ACCEL_PATTERN.bmp", 735, 480, 3, 2, true, RGB(0, 255, 0));
	IMAGEMANAGER->addFrameImage("�׼����ݹݻ�", "images/ĳ����/ACCEL/ACCEL_REFLECT.bmp", 240, 360, 2, 2, true, RGB(0, 255, 0));
	IMAGEMANAGER->addFrameImage("�׼�����", "images/ĳ����/ACCEL/ACCEL_FALLDOWN.bmp", 400, 80, 2, 1, true, RGB(0, 255, 0));
	IMAGEMANAGER->addFrameImage("����", "images/ĳ����/ACCEL/ACCEL_VECTOR_re.bmp", 600, 306, 1, 2, true, RGB(0, 255, 0));
	// *** �÷��̾� ĳ��
	IMAGEMANAGER->addFrameImage("���ϰ�", "images/ĳ����/MIKOTO/MIKOTO_RAILGUN_re.bmp", 800, 160, 1, 2, true, RGB(0, 255, 0));

	// **** UI
	//ü��, ���� ������
	IMAGEMANAGER->addImage("��������������", "images/UI/����������_����_re.bmp", 1080, 70, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("�÷��̾�HP����������", "images/UI/HP������_����.bmp", 230, 30, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("�÷��̾�CP����������", "images/UI/CP������_����.bmp", 230, 30, false, RGB(0, 0, 0));


	//���� �߰�
	SOUNDMANAGER->addSound("�ʵ�BGM", "sounds/nightmare.mp3", true, true);
	SOUNDMANAGER->addSound("����BGM", "sounds/Accelerator.mp3", true, true);


	//Ŭ���� �����Ҵ�
	_player = new player;
	_player->init();

	_boss = new boss;
	//_boss->init();

	/*_pixel = new pixelCollsion;
	_pixel->init();*/

	//_enemyMg = new enemyManager;
	//_enemyMg->init();
	//_enemyMg->setEnemy();

	_stage = new fieldStage;	// �� ó�� �������� ����
	_stage->enter(_player);		//�÷��̾� Ŭ������ �����Ͽ� �ʱ�ȭ
	_player->setStageAddressLink(_stage);
	_player->setBossAddressLink(_boss);
	_boss->setPlayerAddressLink(_player);
	// _enemyMg->setPlayerMemoryAddress(_player);
	// _stage->setEnemyMgAddressLink(_enemyMg);

	// CAMERA->setPosition(_player->getPlayerX(), _player->getPlayerY());
	
	return S_OK;
}

//�޸� ����
void playGround::release()
{
	
}

//����
void playGround::update()
{
	gameNode::update();

	_player->update();
	// _pixel->update();
	// _enemyMg->update();

	//newStage�� ������ ���ٸ� ���� ��������
	//newStage�� ���ο� �����Ͱ��� ������
	//���� �������� ���� �� �� �������� ȣ��
	stage* newStage = _stage->updateStage(); 
	if (newStage != nullptr)
	{
		//_stage->exit();		// �����Ҵ�� ������� ���� �ؾ� �� ��
		delete _stage;
		_stage = newStage; // ���ο� ���������� ����
		_stage->enter(_player); // ���ο� ������������ �ʱ�ȭ �Ұ�
		_stage->enterBoss(_boss);
		_player->setStageAddressLink(_stage);
		// _pixel->setStageAddressLink(_stage);
	}

	
}

//�׸��� ����
void playGround::render()
{	
	//ī�޶� ������ �̵� �߰�
	PatBlt(getMemDC(), 0, 0, getMemDCWidth(), getMemDCHeight(), WHITENESS);
	PatBlt(CAMERA->getMemDC(), 0, 0, getMemDCWidth(), getMemDCHeight(), WHITENESS);
	
	//=================================================

	_stage->render();
	// _pixel->render();
	_player->render();
	// _enemyMg->render();
	
	//=============================================
	_backBuffer->render(CAMERA->getMemDC(), 0, 0,
		CAMERA->getLeft(), CAMERA->getTop(),
		CAMERA->getWidth(), CAMERA->getHeight());
	CAMERA->render(getHDC());
}
