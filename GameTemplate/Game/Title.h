#pragma once
//#include "sound/SoundSource.h"

//タイトル。
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
	SoundSource* titleBGM;                          //タイトルBGM
	SoundSource* titleSE;                           //タイトルの効果音
	ModelRender m_modelRender;                     //モデルレンダー
};

