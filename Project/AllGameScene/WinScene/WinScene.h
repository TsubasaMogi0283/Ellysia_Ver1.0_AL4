#pragma once
#include "AllGameScene/GameManager/IGameScene.h"
#include "Sprite.h"

#include <Xinput.h>
#include "Audio/Audio.h"
#include <memory>

class GameManager;

class WinScene: public IGameScene{
public:

	WinScene();

	void Initialize() override;
	void Update(GameManager* gamaManager) override;
	void Draw() override;

	~WinScene();

private:
	void ShowImGui();

private:

	//背景
	std::unique_ptr<Sprite> back_ = nullptr;

	//テキスト
	std::unique_ptr<Sprite> text_ = nullptr;

	//フェード
	bool isFadeOut_ = false;
	float_t spriteTransparency_ = 1.0f;

	//点滅
	int32_t flashTime_ = 0;
	int32_t fastFlashTime_ = 0;

	//ローディング時間
	int32_t loadingTime_ = 0;

	//コントローラー
	XINPUT_STATE joyState_{};

	int triggerButtonTime=0;




	//BGM
	Audio* bgm_ = nullptr;
	uint32_t selectBGMHandle_ = 0u;
	//DecideSE
	Audio* decideSE_ = nullptr;
	uint32_t decideSEHandle_ = 0u;
};

