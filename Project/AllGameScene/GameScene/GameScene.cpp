#include "GameScene.h"

#include "GameManager.h"

#include "SampleScene/SampleScene.h"
#include "Input.h"
#include "TextureManager.h"
GameScene::GameScene() {

}

void GameScene::ExplanationSceneInitialize() {
	explanationTextureHandle_[0] = TextureManager::GetInstance()->LoadTexture("Resources/Explanation/Explanation1/Explanation1.png");
	explanationTextureHandle_[1] = TextureManager::GetInstance()->LoadTexture("Resources/Explanation/Explanation2/Explanation2.png");
	for (int i = 0; i < EXPLANATION_NUMBER_; i++) {
		explamnationSprite[i].reset(Sprite::Create(explanationTextureHandle_[i], {0.0f,0.0f}));
	}
	
}
void GameScene::ReadySceneInitialize() {
	//カウントダウン
	countDownTexture[3] = TextureManager::LoadTexture("Resources/Ready/CountDown/CountDown3.png");
	countDownTexture[2] = TextureManager::LoadTexture("Resources/Ready/CountDown/CountDown2.png");
	countDownTexture[1] = TextureManager::LoadTexture("Resources/Ready/CountDown/CountDown1.png");
	countDownTexture[0] = TextureManager::LoadTexture("Resources/Ready/CountDown/CountDownStart.png");

	for (int i = 0; i < COUNTDOWN_NUMBER_; i++) {
		countDownSprite[i].reset(Sprite::Create(countDownTexture[i], { 0.0f, 0.0f }));
	}
}
void GameScene::PlaySceneInitialize() {

}

void GameScene::Initialize() {
	//共通部分
	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize();

	//説明
	ExplanationSceneInitialize();
	//カウントダウン
	ReadySceneInitialize();
	//メインのゲーム
	PlaySceneInitialize();
}

void GameScene::DebugText() {
	ImGui::Begin("Game");

	ImGui::End();
}


#pragma region Update用
void GameScene::ExplanationSceneUpdate(){
	ImGui::Begin("GExplanation");

	ImGui::End();


	explanationTextureNumber_ = 1;
	scene_ = Scene::Ready;
}

void GameScene::ReadySceneUpdate(){
	ImGui::Begin("Ready");

	ImGui::End();

	countDownTime_ -= 1;
	
	if (countDownTime_ < SECOND_*3 && countDownTime_ >= SECOND_ * 2) {
		displayNumber_ = 3;
	}
	if (countDownTime_ < SECOND_ * 2 && countDownTime_ >= SECOND_ * 1) {
		displayNumber_ = 2;
	}
	if (countDownTime_ < SECOND_ * 1 && countDownTime_ >= SECOND_ * 0) {
		displayNumber_ = 1;
	}
	if (countDownTime_ < SECOND_ * 0 && countDownTime_ >= SECOND_ * -1) {
		displayNumber_ = 0;
	}
	if (countDownTime_ < SECOND_ * -1) {
		scene_ = Scene::Play;
	}
	

	
}

void GameScene::PlaySceneUpdate(){
	ImGui::Begin("Play");

	ImGui::End();
}

#pragma endregion


void GameScene::Update(GameManager* gameManager) {
	//デバッグ用
	DebugText();

	//共通部分
	skydome_->Update();


	switch (scene_) {
	case Scene::Explanation:
	default:
		ExplanationSceneUpdate();

		break;

		//
	case Scene::Ready:
		ReadySceneUpdate();
		break;

		//
	case Scene::Play:
		PlaySceneUpdate();
		break;
	}
	if (Input::GetInstance()->IsTriggerKey(DIK_SPACE) == true) {
		gameManager->ChangeScene(new SampleScene());
	}

}


void GameScene::ExplanationSceneDraw(){

	for (int i = 0; i < EXPLANATION_NUMBER_; i++) {
		explamnationSprite[i].reset(Sprite::Create(explanationTextureHandle_[i], { 0.0f,0.0f }));
	}
	
}

void GameScene::ReadySceneDraw(){
	for (int i = 0; i < COUNTDOWN_NUMBER_; i++) {
		if (displayNumber_ == i) {
			countDownSprite[i]->Draw();
		}
		
	}
}

void GameScene::PlaySceneDraw()
{
}
void GameScene::Draw() {
	//共通部分
	skydome_->Draw();

	switch (scene_) {
	case Scene::Explanation:
	default:
		ExplanationSceneDraw();

		break;

		//
	case Scene::Ready:
		ReadySceneDraw();
		break;

		//
	case Scene::Play:
		PlaySceneDraw();
		break;
	}
}

GameScene::~GameScene() {

}
