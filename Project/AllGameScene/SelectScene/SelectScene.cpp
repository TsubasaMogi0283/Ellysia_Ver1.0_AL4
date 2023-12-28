#include "SelectScene.h"

#include "GameManager.h"

#include "SampleScene/SampleScene.h"
#include "TitleScene/TitleScene.h"
#include "GameScene1.h"

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


	cursorPosition_ = { 530, 200 };


	//Tutorial
	tutorialIcon_ = std::make_unique<Sprite>();
	tutorialPosition_ = { cursorPosition_.x,200.0f };
	uint32_t tutorialTextureHandle = TextureManager::GetInstance()->LoadTexture("Resources/Game/Select/Icon/StageIconTutorial.png");
	tutorialIcon_.reset(Sprite::Create(tutorialTextureHandle, tutorialPosition_));


	//Return
	returnIcon_ = std::make_unique<Sprite>();
	returnPosition_ = { cursorPosition_.x - ICON_WIDTH_INTERVAL_,200.0f };
	uint32_t returnTextureHandle = TextureManager::GetInstance()->LoadTexture("Resources/Game/Select/Icon/StageIconReturn.png");
	returnIcon_.reset(Sprite::Create(returnTextureHandle, returnPosition_)); 



	for (int i = 0; i < STAGE_NUMBER_; i++) {
		stageIcon_[i] = std::make_unique<Sprite>();

	}

	uint32_t stageIconTextureHandle[STAGE_NUMBER_] = { 0u };
	stageIconTextureHandle[0] = TextureManager::GetInstance()->LoadTexture("Resources/Game/Select/Icon/StageIcon1.png");
	stageIconTextureHandle[1] = TextureManager::GetInstance()->LoadTexture("Resources/Game/Select/Icon/StageIcon2.png");

	//ICON_WIDTH_INTERVAL_=500.0f

	iconPosition_[0] = { cursorPosition_.x + 1.0f * ICON_WIDTH_INTERVAL_,200 };
	iconPosition_[1] = { cursorPosition_.x + 2.0f * ICON_WIDTH_INTERVAL_,200 };

	for (int i = 0; i < STAGE_NUMBER_; i++) {
		stageIcon_[i].reset(Sprite::Create(stageIconTextureHandle[i], iconPosition_[i]));
	}

	

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
	ImGui::InputInt("StageNumber", &IconNumber_);
	ImGui::InputInt("ISFADEOUT", &isFadeOut_);
	ImGui::End();


	ImGui::Begin("Arrow");
	ImGui::SliderFloat2("Left", &arrowPosition_[0].x, 0.0f, 1280.0f);
	ImGui::SliderFloat2("Right", &arrowPosition_[1].x, 0.0f, 1280.0f);
	ImGui::End();

}

//フェードイン
void SelectScene::FadeIn() {
	back_->SetTransparency(transparency_);

#pragma endregion

#pragma region ステージのアイコン
	for (int i = 0; i < STAGE_NUMBER_; i++) {
		stageIcon_[i]->SetTransparency(transparency_);

	}



	//Tutorial
	tutorialIcon_->SetTransparency(transparency_);
	//Return
	returnIcon_->SetTransparency(transparency_);
#pragma endregion

#pragma region 矢印
	for (int i = 0; i < ARROW_AMOUNT_; i++) {
		arrow_[i]->SetTransparency(transparency_);

	}
	if (transparency_ > 1.0f) {
		transparency_ = 1.0f;
		isFadeIn_ = false;

	}

}


void SelectScene::Select() {
	

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

	


	
	//ステージ
	for (int i = 0; i < STAGE_NUMBER_; i++) {
		stageIcon_[i]->SetPosition(iconPosition_[i]);
	}
	tutorialIcon_->SetPosition(tutorialPosition_);
	returnIcon_->SetPosition(returnPosition_);

	//矢印
	for (int i = 0; i < ARROW_AMOUNT_; i++) {
		arrow_[i]->SetPosition(arrowPosition_[i]);
	}





	//今指しているステージアイコンに番号をふる
	//タイトルへ
	if (cursorPosition_.x == returnPosition_.x) {
		IconNumber_ = 0;
	}

	//チュートリアル
	if (cursorPosition_.x == tutorialPosition_.x) {
		IconNumber_ = 1;
	}

	//ステージ1
	if (cursorPosition_.x == iconPosition_[0].x) {
		IconNumber_ = 2;
	}
	//ステージ2
	if (cursorPosition_.x == iconPosition_[1].x) {
		IconNumber_ = 3;
	}

	if (Input::GetInstance()->IsTriggerKey(DIK_SPACE) == true) {
		isTrigerSpace_ = true;
		
		for (int i = 0; i < STAGE_AMOUNT_; i++) {
			if (IconNumber_ == i) {
				nextScene_[i] = true;
			}
		}
		

		
	}
	if (isTrigerSpace_ == true) {
		isFadeOut_ = 1;

	}
	

}


//フェードアウト
void SelectScene::FadeOut() {
	back_->SetTransparency(transparency_);

#pragma endregion

#pragma region ステージのアイコン
	for (int i = 0; i < STAGE_NUMBER_; i++) {
		stageIcon_[i]->SetTransparency(transparency_);

	}



	//Tutorial
	tutorialIcon_->SetTransparency(transparency_);
	//Return
	returnIcon_->SetTransparency(transparency_);
#pragma endregion

#pragma region 矢印
	for (int i = 0; i < ARROW_AMOUNT_; i++) {
		arrow_[i]->SetTransparency(transparency_);

	}


}

void SelectScene::Update(GameManager* gameManager) {
	//デバッグ用
	DebugText();

	if (isFadeIn_ == true) {
		transparency_ += TRANSPARENCY_INTERVAL_;
		FadeIn();
	}

	if (isFadeOut_ == 0 && isFadeIn_==false) {
		//選択
		Select();

	}
	if (isFadeOut_ == 1) {
		transparency_ -= TRANSPARENCY_INTERVAL_;
		FadeOut();
	}



	if (transparency_ < 0.0f) {
		transparency_ = 0.0f;

		loadingTime_ += 1;
		if (loadingTime_ > SECOND_ * 2) {
			//タイトル
			if (nextScene_[0] == true && IconNumber_ == 0) {
				gameManager->ChangeScene(new TitleScene());
			}
			//ステージ1
			if (nextScene_[2] == true && IconNumber_ == 2) {
				gameManager->ChangeScene(new GameScene1());
			}



			//ステージ2
			//if (cursorPosition_.x == iconPosition_[1].x) {
			//	IconNumber_ = 3;
			//}
		}
		
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
