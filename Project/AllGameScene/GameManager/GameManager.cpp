#include "GameManager.h"
#include "SampleScene/SampleScene.h"

//コンストラクタ
GameManager::GameManager() {
	
}
	
void GameManager::Initialize() {
	//シーンごとに動作確認したいときはここを変えてね
	currentGamaScene_ = new SampleScene();
	currentGamaScene_->Initialize();

}


void GameManager::Update() {
	currentGamaScene_->Update(this);
}

void GameManager::Draw() {
	currentGamaScene_->Draw();
}



void GameManager::ChangeScene(IGameScene* newGameScene) {
	//一度消してから次のシーンにいく
	delete currentGamaScene_;
	currentGamaScene_ = newGameScene;
	//今は言っているシーンが引数
	currentGamaScene_->Initialize();
}


//デストラクタ
GameManager::~GameManager() {
	delete currentGamaScene_;

}
