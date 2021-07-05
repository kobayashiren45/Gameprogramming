#include "CMaterial.h"
//memset�̃C���N���[�h
#include <string.h>
#include "glut.h"

//�f�t�H���g�R���X�g���N�^
CMaterial::CMaterial()
:mVertexNum(0)
, mpTextureFilename(nullptr)
{
	//���O��0�Ŗ���
	memset(mName, 0, sizeof(mName));
	//0�Ŗ��߂�
	memset(mDiffuse, 0, sizeof(mDiffuse));
}

CMaterial::CMaterial(CModelX*model)
:mpTextureFilename(nullptr)
{
	model->GetIntToken();
	if (strcmp(model->mToken, "{") != 0){
		strcpy(mName, model->mToken);
		model->GetToken();
	}
	mDiffuse[0] = model->GetFloatToken();
	mDiffuse[1] = model->GetFloatToken();
	mDiffuse[2] = model->GetFloatToken();
	mDiffuse[3] = model->GetFloatToken();

	mPower = model->GetFloatToken();

	mSpecular[0] = model->GetFloatToken();
	mSpecular[1] = model->GetFloatToken();
	mSpecular[2] = model->GetFloatToken();

	mEmissive[0] = model->GetFloatToken();
	mEmissive[1] = model->GetFloatToken();
	mEmissive[2] = model->GetFloatToken();

	model->GetToken();

	if (strcmp(model->mToken, "TextureFilename") == 0){
		model->GetToken();
		model->GetToken();
		mpTextureFilename = new char[strlen(model->mToken) + 1];
		strcpy(mpTextureFilename, model->mToken);
		model->GetToken();
		model->GetToken();
	}

#ifdef _DEBUG
	printf("%s��n", mName);
	printf("Diffuse:%f %f %f %f��n", mDiffuse[0], mDiffuse[1], mDiffuse[2], mDiffuse[3]);
	printf("Power:%f��n", mPower);
	printf("Specular:%f %f %f��n", mSpecular[0], mSpecular[1], mSpecular[2]);
	printf("Emissive:%f %f %f��n", mEmissive[0], mEmissive[1], mEmissive[2]);
#endif

}

//�}�e���A����L���ɂ���
void CMaterial::Enabled() {
	//�g�U���̐ݒ�
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse);
	//�e�N�X�`���L��
	if (mTexture.mId)
	{
		//�e�N�X�`�����g�p�\�ɂ���
		glEnable(GL_TEXTURE_2D);
		//�e�N�X�`�����o�C���h����
		glBindTexture(GL_TEXTURE_2D, mTexture.mId);
		//�A���t�@�u�����h��L���ɂ���
		glEnable(GL_BLEND);
		//�u�����h���@���w��
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
}

//�e�N�X�`����ǂݍ���
void CMaterial::LoadTexture(char *file)
{
	mTexture.Load(file);
}
//�}�e���A���𖳌��ɂ���
void CMaterial::Disabled()
{
	//�e�N�X�`���L��
	if (mTexture.mId)
	{
		//�A���t�@�u�����h�𖳌�
		glDisable(GL_BLEND);
		//�e�N�X�`���̃o�C���h������
		glBindTexture(GL_TEXTURE_2D, 0);
		//�e�N�X�`���𖳌��ɂ���
		glDisable(GL_TEXTURE_2D);
	}
}
