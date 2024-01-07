#pragma once

#include "AllGameScene/GameManager/IGameScene.h"

#include "Sprite.h"
#include "SpritePosition.h"
#include "Transform.h"
#include "Model.h"


#include <memory>

#include "Skydome/Skydome.h"
#include "WorldTransform.h"
//StatePatternを使う時は必ず前方宣言をするように
class Gamemanager;

class TitleScene : public IGameScene {
public:

	//コンストラクタ
	TitleScene();


	/// 初期化
	void Initialize()override;

	/// 更新
	void Update(GameManager* gameManager)override;

	/// 描画
	void Draw()override;


	/// デストラクタ
	~TitleScene();


private:
	void DebugText();




private:

	//天球ポインタ
	Skydome* skydome_ = nullptr;


	std::unique_ptr<Model> playerModel_ = nullptr;
	WorldTransform playerWorldTransform_ = {};

	Vector3 cameraTranslate_ = {};
	Vector3 cameraRotate_ = {};



	float transparency_ = 0.0f;
	int32_t loadingTime_ = 0;
	std::unique_ptr<Sprite> blackSprite_ = nullptr;

	bool isStart_ = false;

	//タイトル
	Sprite* titleLogoSprite_ = nullptr;
	uint32_t titleLogoTexture = 0u;

	//ボタン
	XINPUT_STATE joyState_;
	int triggerButtonTime_ = 0;

};

