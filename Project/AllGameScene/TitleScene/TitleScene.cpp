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

	uint32_t blackTextureHandle = TextureManager::GetInstance()->LoadTexture("Resources/Black.png");
	blackSprite_.reset(Sprite::Create(blackTextureHandle, { 0.0f,0.0f }));

	playerWorldTransform_.Initialize();
	playerWorldTransform_.scale_ = { 1.0f,1.0f,1.0f };
	playerWorldTransform_.rotate_ = { 0.0f,0.0f,0.0f };
	playerWorldTransform_.translate_ = { 0.0f,0.0f,0.0f };


	//生成
	skydome_ = new Skydome();

	//フォルダの名前を指定してね
	//読み込むファイルと同じフォルダ名にしないと✕
	/////skydomeModel_ = Model::CreateFromOBJ("CelestialSphere", true);

	//テクスチャ読み込み
	//skydomeTextureHandle_ = TextureManager::Load("CelestialSphere/SpaceSphere.png");

	//天球の初期化
	skydome_->Initialize();

	//タイトル
	titleLogoTexture = TextureManager::LoadTexture("Resources/Title/Logo/TitleLogo.png");
	// スプライトの生成
	titleLogoSprite_ = Sprite::Create(titleLogoTexture, { 0.0f, 0.0f });

	cameraTranslate_ = {0.0f,0.0f,-20.0f};
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

	skydome_->Update();
	playerWorldTransform_.Update();


	blackSprite_->SetTransparency(transparency_);
	

	if (Input::GetInstance()->IsTriggerKey(DIK_SPACE) == true) {
		isStart_ = true;
		//gameManager->ChangeScene(new GameScene());
	}

	if (isStart_ == true) {
		const float TRANSPARENCY_INTERVAL = 0.05f;
		transparency_ += TRANSPARENCY_INTERVAL;

		if (transparency_ > 1.0f) {
			loadingTime_ += 1;
			if (loadingTime_ > 60 * 2) {
				gameManager->ChangeScene(new GameScene());
			}
			
		}
	}

}

void TitleScene::Draw(){
	playerModel_->Draw(playerWorldTransform_);
	skydome_->Draw();


	//スプライト
	titleLogoSprite_->Draw();

	blackSprite_->Draw();
}

TitleScene::~TitleScene(){
	delete skydome_;
	delete titleLogoSprite_;
}
