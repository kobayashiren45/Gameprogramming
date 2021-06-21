#include "CSceneGame.h"
//
#include "CCamera.h"
//
#include "CUtil.h"
#include "CRes.h"
#include "CModelX.h"
#include "CKey.h"

CMatrix Matrix;
CSceneGame::~CSceneGame() {

}

void CSceneGame::Init() {
	CRes::sModelX.Load(MODEL_FILE);
	
	//�e�L�X�g�t�H���g�̓ǂݍ��݂Ɛݒ�
	mFont.LoadTexture("FontG.tga", 1, 4096 / 64);

}


void CSceneGame::Update() {
	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	//���_�����߂�
	e = CVector(1.0f, 2.0f, 10.0f);
	//�����_�����߂�
	c = CVector();
	//����������߂�
	u = CVector(0.0f, 1.0f, 0.0f);

	//�J�����N���X�̐ݒ�
	Camera.Set(e, c, u);
	Camera.Render();

	if (CKey::Push('K')){
		Matrix = Matrix*CMatrix().RotateX(1);
	}

	if (CKey::Push('I')) {
		Matrix = Matrix * CMatrix().RotateX(-1);
	}


	if (CKey::Push('L')){
		Matrix = Matrix*CMatrix().RotateY(1);
	}

	if (CKey::Push('J')) {
		Matrix = Matrix * CMatrix().RotateY(-1);
	}


	glMultMatrixf(Matrix.mF);
	CRes::sModelX.Render();


	//2D�`��J�n
	CUtil::Start2D(0, 800, 0, 600);

	mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2D�̕`��I��
	CUtil::End2D();

	return;
}

