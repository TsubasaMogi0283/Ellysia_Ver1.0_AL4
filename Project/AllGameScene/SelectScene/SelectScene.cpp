#include "SelectScene.h"

#include "GameManager.h"

#include "SampleScene/SampleScene.h"
#include "Input.h"
#include <numbers>

SelectScene::SelectScene() {

}

void SelectScene::Initialize() {

#pragma region 背景
	back_ = std::make_unique<Sprite>();
	uint32_t backTextureHandle = TextureManager::GetInstance()->LoadTexture("Resources/Game/Select/Back/SelectBack.png");


	back_.reset(Sprite::Create(backTextureHandle, { 0.0f,0.0f }));

#pragma endregion

#pragma region ステージのアイコン
	for (int i = 0; i < STAGE_NUMBER_; i++) {
		stageIcon_[i] = std::make_unique<Sprite>();
		
	}
	
	uint32_t stageIconTextureHandle[STAGE_NUMBER_] = { 0u };
	stageIconTextureHandle[0] = TextureManager::GetInstance()->LoadTexture("Resources/Game/Select/Icon/StageIcon1.png");
	stageIconTextureHandle[1] = TextureManager::GetInstance()->LoadTexture("Resources/Game/Select/Icon/StageIcon2.png");


	iconPosition_[0] = {530,200};
	iconPosition_[1] = { iconPosition_[0].x+ ICON_WIDTH_INTERVAL_,200};

	for (int i = 0; i < STAGE_NUMBER_; i++) {
		stageIcon_[i].reset(Sprite::Create(stageIconTextureHandle[i], iconPosition_[i]));
	}


	//Tutorial
	tutorialIcon_ = std::make_unique<Sprite>();
	tutorialPosition_ = { iconPosition_[0].x- ICON_WIDTH_INTERVAL_,200.0f };
	uint32_t tutorialTextureHandle = TextureManager::GetInstance()->LoadTexture("Resources/Game/Select/Icon/StageIconTutorial.png");
	tutorialIcon_.reset(Sprite::Create(tutorialTextureHandle, tutorialPosition_));


	//Return
	returnIcon_ = std::make_unique<Sprite>();
	returnPosition_ = { iconPosition_[1].x+ICON_WIDTH_INTERVAL_,200.0f };
	uint32_t returnTextureHandle = TextureManager::GetInstance()->LoadTexture("Resources/Game/Select/Icon/StageIconReturn.png");
	returnIcon_.reset(Sprite::Create(returnTextureHandle, returnPosition_));

#pragma endregion

#pragma region 矢印
	uint32_t arrowTextureHandle = TextureManager::GetInstance()->LoadTexture("Resources/Game/Select/Arrow/Arrow.png");

	arrowPosition_[0] = { 0.0f,520.0f };
	arrowPosition_[1] = { 1280.0f,715.0f };
	Vector2 arrowScale = { 0.8f,0.8f };
	for (int i = 0; i < ARROW_AMOUNT_; i++) {
		arrow_[i].reset(Sprite::Create(arrowTextureHandle, arrowPosition_[i]));
		arrow_[i]->SetScale(arrowScale);
		
	}
	arrow_[1]->SetRotate(float(std::numbers::pi));
	
#pragma endregion



	//StatePatternで音楽の切り替え


}

void SelectScene::DebugText() {
	ImGui::Begin("Select");

	ImGui::End();


	ImGui::Begin("Arrow");
	ImGui::SliderFloat2("Left", &arrowPosition_[0].x, 0.0f, 1280.0f);
	ImGui::SliderFloat2("Right", &arrowPosition_[1].x, 0.0f, 1280.0f);
	ImGui::End();

}

void SelectScene::Select() {
	//ステージ
	for (int i = 0; i < STAGE_NUMBER_; i++) {
		stageIcon_[i]->SetPosition(iconPosition_[i]);
	}
	tutorialIcon_->SetPosition(tutorialPosition_);
	returnIcon_->SetPosition(returnPosition_);

	//分かりやすく言うとMuseDashの曲選択画面良いなと思ったので再現したい
	//さすがにそのままはダメなので若干アレンジする
	//時間があったら回転で移動させたい

	//右に移動
	//アイコンは左に移動するよ
	if ((Input::GetInstance()->IsTriggerKey(DIK_RIGHT) == true) ||
		(Input::GetInstance()->IsTriggerKey(DIK_D) == true)) {

		//チュートリアル
		tutorialPosition_.x -= ICON_WIDTH_INTERVAL_;
		//タイトルに戻る
		returnPosition_.x -= ICON_WIDTH_INTERVAL_;

		//ステージ
		for (int i = 0; i < STAGE_NUMBER_; i++) {
			iconPosition_[i].x -= ICON_WIDTH_INTERVAL_;
		}

		
	}
	//左に移動
	//アイコンは右に移動するよ
	if ((Input::GetInstance()->IsTriggerKey(DIK_LEFT) == true) ||
		(Input::GetInstance()->IsTriggerKey(DIK_A) == true)) {
		for (int i = 0; i < STAGE_NUMBER_; i++) {
			iconPosition_[i].x += ICON_WIDTH_INTERVAL_;
			
		}
		//チュートリアル
		tutorialPosition_.x += ICON_WIDTH_INTERVAL_;
		//タイトルに戻る
		returnPosition_.x += ICON_WIDTH_INTERVAL_;
	}

	

	//矢印
	for (int i = 0; i < ARROW_AMOUNT_; i++) {
		arrow_[i]->SetPosition(arrowPosition_[i]);
	}


}

//フェードイン
void SelectScene::FadeIn() {

}

//フェードアウト
void SelectScene::FadeOut() {

}

void SelectScene::Update(GameManager* gameManager) {
	//デバッグ用
	DebugText();

	if (isFadeOut_ == false) {
		//選択
		Select();

	}



	



	if (Input::GetInstance()->IsTriggerKey(DIK_SPACE) == true) {
		gameManager->ChangeScene(new SampleScene());
	}

}

void SelectScene::Draw() {
	//背景
	back_->Draw();


	//チュートリアル
	tutorialIcon_->Draw();

	//タイトルに戻る
	returnIcon_->Draw();

	//ステージアイコン
	for (int i= 0; i < STAGE_NUMBER_; i++) {
		stageIcon_[i]->Draw();

	}


	//矢印
	for (int i = 0; i < ARROW_AMOUNT_; i++) {
		arrow_[i]->Draw();
	}


}

SelectScene::~SelectScene() {

}
