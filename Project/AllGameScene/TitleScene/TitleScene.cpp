#include "TitleScene.h"
#include "GameManager.h"

#include "SampleScene/SampleScene.h"
#include "GameScene/GameScene.h"
#include "Input.h"
TitleScene::TitleScene(){

}

void TitleScene::Initialize(){
	playerModel_ = std::unique_ptr<Model>();
	playerModel_.reset(Model::Create("Resources/Sample/Player", "playre.obj"));


	playerWorldTransform_.Initialize();
	playerWorldTransform_.scale_ = { 1.0f,1.0f,1.0f };
	playerWorldTransform_.rotate_ = { 0.0f,0.0f,0.0f };
	playerWorldTransform_.translate_ = { 0.0f,0.0f,0.0f };

	cameraTranslate_ = {0.0f,0.0f,0.0f};
	cameraRotate_ = {0.0f,0.0f,0.0f};
	Camera::GetInstance()->SetTranslate(cameraTranslate_);
	Camera::GetInstance()->SetRotate(cameraRotate_);

}

void TitleScene::DebugText() {
	ImGui::Begin("Title");

	ImGui::End();
}


void TitleScene::Update(GameManager* gameManager){
	//デバッグ用
	DebugText();


	playerWorldTransform_.Update();

	if (Input::GetInstance()->IsTriggerKey(DIK_SPACE) == true) {
		gameManager->ChangeScene(new GameScene());
	}


}

void TitleScene::Draw(){
	playerModel_->Draw(playerWorldTransform_);
}

TitleScene::~TitleScene(){

}
