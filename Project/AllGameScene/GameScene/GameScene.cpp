#include "GameScene.h"

#include "GameManager.h"

#include "SampleScene/SampleScene.h"
#include "Input.h"
GameScene::GameScene() {

}

void GameScene::Initialize() {

}

void GameScene::DebugText() {
	ImGui::Begin("Select");

	ImGui::End();
}


void GameScene::Update(GameManager* gameManager) {
	//デバッグ用
	DebugText();

	if (Input::GetInstance()->IsTriggerKey(DIK_SPACE) == true) {
		gameManager->ChangeScene(new SampleScene());
	}

}

void GameScene::Draw() {

}

GameScene::~GameScene() {

}
