#pragma once
#include "AllGameScene/GameManager/IGameScene.h"

#include "Sprite.h"
#include "SpritePosition.h"
#include "Transform.h"
#include "Model.h"

#include <memory>
#include "Skydome/Skydome.h"
#include "Player/Player.h"
#include "RailCamera/RailCamera.h"

class GameManager;

class GameScene : public IGameScene {
public:

	//コンストラクタ
	GameScene();


	/// 初期化
	void Initialize()override;

	/// 更新
	void Update(GameManager* gameManager)override;

	/// 描画
	void Draw()override;


	/// デストラクタ
	~GameScene();


private:
	void DebugText();

#pragma region 初期化
	void ExplanationSceneInitialize();
	void ReadySceneInitialize();
	void PlaySceneInitialize();

#pragma endregion

#pragma region 更新
	void ExplanationSceneUpdate();
	void ReadySceneUpdate();
	void PlaySceneUpdate();

#pragma endregion

#pragma region 描画
	void ExplanationSceneDraw();
	void ReadySceneDraw();
	void PlaySceneDraw();


#pragma endregion

private:
	enum class Scene {
		//説明
		Explanation,

		//カウント
		Ready,

		//メインのゲーム
		Play,

		//勝ち
		Win,

		//負け
		Lose,

	};

	Scene scene_ = Scene();


	//カメラ
	Vector3 cameraTranslate_ = {};
	Vector3 cameraRotate_ = {};


	//共通部分
	const int SECOND_ = 60;

	//天球ポインタ
	std::unique_ptr<Skydome> skydome_ = nullptr;

	//プレイヤー
	std::unique_ptr<Player> player_ = nullptr;
	float move_ = 0.0f;
	const float MOVE_AMOUNT_ = 0.1f;

	//レールカメラ
	std::unique_ptr<RailCamera> railCamera_ = nullptr;

#pragma region 説明
	static const int EXPLANATION_NUMBER_ = 2;
	std::unique_ptr<Sprite> explamnationSprite[EXPLANATION_NUMBER_] = { nullptr };
	uint32_t explanationTextureHandle_[EXPLANATION_NUMBER_] = { 0u };
	int explanationTextureNumber_ = 0;
#pragma endregion


#pragma region カウントダウン
	static const int COUNTDOWN_NUMBER_ = 4;
	std::unique_ptr <Sprite> countDownSprite[COUNTDOWN_NUMBER_] = { nullptr };
	uint32_t countDownTexture[COUNTDOWN_NUMBER_] = { 0u };
	
	
	int32_t displayNumber_ = 3;
	int32_t countDownTime_ = displayNumber_*SECOND_;
#pragma endregion

};

