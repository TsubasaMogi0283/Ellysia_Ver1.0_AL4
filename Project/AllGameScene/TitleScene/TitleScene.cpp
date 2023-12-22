#include "TitleScene.h"
#include "GameManager.h"

#include "SampleScene/SampleScene.h"
#include "Input.h"
TitleScene::TitleScene(){

}

void TitleScene::Initialize(){

}

void TitleScene::DebugText() {
	ImGui::Begin("Title");

	ImGui::End();
}


void TitleScene::Update(GameManager* gameManager){
	//デバッグ用
	DebugText();

	if (Input::GetInstance()->IsTriggerKey(DIK_SPACE) == true) {
		gameManager->ChangeScene(new SampleScene());
	}

}

void TitleScene::Draw(){

}

TitleScene::~TitleScene(){

}
