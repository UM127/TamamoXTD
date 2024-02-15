#pragma once
//#include "sound/SoundSource.h"

//�^�C�g���B
class Game;

class Title : public IGameObject
{
public:
	Title();
	~Title();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	Game* game;
	SpriteRender spriteRender;
	SpriteRender spriteRender2;
	SoundSource* titleBGM;                          //�^�C�g��BGM
	SoundSource* titleSE;                           //�^�C�g���̌��ʉ�
	ModelRender m_modelRender;                     //���f�������_�[
};

