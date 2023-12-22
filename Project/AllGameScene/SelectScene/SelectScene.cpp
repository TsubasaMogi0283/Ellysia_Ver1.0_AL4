#include "SelectScene.h"

#include "GameManager.h"

#include "SampleScene/SampleScene.h"
#include "Input.h"
#include <numbers>

SelectScene::SelectScene() {

}

void SelectScene::Initialize() {
	//ステージのアイコン
	for (int i = 0; i < STAGE_NUMBER_; i++) {
		stageIcon_[i] = std::make_unique<Sprite>();
		
	}
	
	uint32_t stageIconTextureHandle[STAGE_NUMBER_] = { 0u };
	stageIconTextureHandle[0] = TextureManager::GetInstance()->LoadTexture("Resources/Game/Select/StageIcon1.png");
	stageIconTextureHandle[1] = TextureManager::GetInstance()->LoadTexture("Resources/Game/Select/StageIcon2.png");


	iconPosition_[0] = {530,200};
	iconPosition_[1] = {1050,200};

	for (int i = 0; i < STAGE_NUMBER_; i++) {
		stageIcon_[i].reset(Sprite::Create(stageIconTextureHandle[i], iconPosition_[i]));
	}


	uint32_t arrowTextureHandle = TextureManager::GetInstance()->LoadTexture("Resources/Game/Select/Arrow.png");

	arrowPosition_[0] = { 0.0f,220.0f };
	arrowPosition_[1] = { 1280.0f,420.0f };
	Vector2 arrowScale = { 0.8f,0.8f };
	for (int i = 0; i < ARROW_AMOUNT_; i++) {
		arrow_[i].reset(Sprite::Create(arrowTextureHandle, arrowPosition_[i]));
		arrow_[i]->SetScale(arrowScale);
		
	}
	arrow_[1]->SetRotate(float(std::numbers::pi));
	
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
	stageIcon_[0]->SetPosition(iconPosition_[0]);
	stageIcon_[1]->SetPosition(iconPosition_[1]);
	
	//分かりやすく言うとMuseDashの曲選択画面良いなと思ったので再現したい
	//さすがにそのままはダメなので若干アレンジする
	//時間があったら回転で移動させたい

	//右に移動
	//アイコンは左に移動するよ
	if ((Input::GetInstance()->IsTriggerKey(DIK_RIGHT) == true) ||
		(Input::GetInstance()->IsTriggerKey(DIK_D) == true)) {
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
	}



	//矢印
	for (int i = 0; i < ARROW_AMOUNT_; i++) {
		arrow_[i]->SetPosition(arrowPosition_[i]);
		arrow_[i]->SetPosition(arrowPosition_[i]);
	}


}


void SelectScene::Update(GameManager* gameManager) {
	//デバッグ用
	DebugText();

	//選択
	Select();




	if (Input::GetInstance()->IsTriggerKey(DIK_SPACE) == true) {
		gameManager->ChangeScene(new SampleScene());
	}

}

void SelectScene::Draw() {
	for (int i= 0; i < STAGE_NUMBER_; i++) {
		stageIcon_[i]->Draw();

	}
	for (int i = 0; i < ARROW_AMOUNT_; i++) {
		arrow_[i]->Draw();
	}


}

SelectScene::~SelectScene() {

}
