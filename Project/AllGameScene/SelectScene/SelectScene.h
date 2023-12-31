#pragma once
#include "AllGameScene/GameManager/IGameScene.h"

#include "Sprite.h"
#include "SpritePosition.h"
#include "Transform.h"
#include "Model.h"

#include <memory>

class GameManager;

class SelectScene : public IGameScene {
public:

	//コンストラクタ
	SelectScene();


	/// 初期化
	void Initialize()override;

	/// 更新
	void Update(GameManager* gameManager)override;

	/// 描画
	void Draw()override;


	/// デストラクタ
	~SelectScene();


private:
	//ImGui用
	void DebugText();

	//選択
	void Select();


	//フェードイン
	void FadeIn();

	//フェードアウト
	void FadeOut();
	

private:
	//Back
	std::unique_ptr<Sprite> back_ = nullptr;


	//Icon
	static const int STAGE_NUMBER_ = 2;
	std::unique_ptr<Sprite> stageIcon_[STAGE_NUMBER_] = { nullptr };
	const float ICON_WIDTH_INTERVAL_ = 500.0f;
	Vector2 iconPosition_[STAGE_NUMBER_] = {};

	int IconNumber_ = 0;

	//Tutorial
	std::unique_ptr<Sprite> tutorialIcon_ = nullptr;
	Vector2 tutorialPosition_ = { 0.0f,0.0f };

	//Return
	std::unique_ptr<Sprite> returnIcon_ = nullptr;
	Vector2 returnPosition_ = { 0.0f,0.0f };


	//科ソール的なやつ
	Vector2 cursorPosition_ = {};


	//Arrow
	static const int ARROW_AMOUNT_ = 2;
	std::unique_ptr<Sprite> arrow_[ARROW_AMOUNT_] = { nullptr };
	Vector2 arrowPosition_[ARROW_AMOUNT_] = {};
	Vector4 arrowColor_[ARROW_AMOUNT_] = {0.0f,0.0f,0.0f,0.0f};


	bool isFadeIn_ = true;
	int isFadeOut_ = 0;
	float transparency_ = 0.0f;
	const float TRANSPARENCY_INTERVAL_ = 0.05f;

	bool isTrigerSpace_ = false;

	static const int STAGE_AMOUNT_ = 4;
	bool nextScene_[STAGE_AMOUNT_] = {};

	const int SECOND_ = 60;
	int loadingTime_ = 0;

};

