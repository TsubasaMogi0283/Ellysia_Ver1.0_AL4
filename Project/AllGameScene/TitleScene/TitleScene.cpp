#include "TitleScene.h"
#include "GameManager.h"

#include "SampleScene/SampleScene.h"
#include "GameScene/GameScene.h"
#include "Input.h"
#include <numbers>
TitleScene::TitleScene(){

}

void TitleScene::Initialize() {
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

	cameraTranslate_ = { 0.0f,0.0f,-30.0f };
	//cameraTranslate_ = { 0.0f,0.0f,0.0f };
	cameraRotate_ = {0.0f,0.0f,0.0f};
	Camera::GetInstance()->SetTranslate(cameraTranslate_);
	Camera::GetInstance()->SetRotate(cameraRotate_);

	//BGM
	bgm_ = Audio::GetInstance();
	bgmHandle_ = bgm_->LoadWave("Resources/Audio/Title/Music/Title.wav");
	bgm_->PlayWave(bgmHandle_, true);

	//DecideSE
	decideSE_ = Audio::GetInstance();
	seHandle_ = decideSE_->LoadWave("Resources/Audio/Title/Music/StartSE.wav");

	isFadeIn_ = true;


	int count = 3;

	//0.5秒ごとに発生
	float frequency = 0.5f;
	//発生頻度用の時刻。0.0で初期化
	float frequencyTime = 0.0f;

	//model_ = std::make_unique<Particle3D>();
	//model_->Create("Resources/05_02", "plane.obj");
	




	particleTextureHandle_ = TextureManager::GetInstance()->LoadTexture("Resources/CG3/circle.png");

	//model_->SetCount(count);
	//model_->SetFrequency(frequency);
	//model_->SetFrequencyTime(frequencyTime);

	
}

void TitleScene::DebugText() {
#ifdef _DEBUG
	ImGui::Begin("Title");
	ImGui::SliderFloat("initialCamerTranslate_", &initialCamerTranslate_, -20.0f, 20.0);
	ImGui::End();
#endif
}


void TitleScene::Update(GameManager* gameManager){
	//デバッグ用
	DebugText();
	skydome_->Update();
	playerWorldTransform_.Update();

	blackSprite_->SetTransparency(transparency_);

	const float RADIUS = 30.0f;

	/*theta_ = 0.001f;
	cameraTranslate_.z = RADIUS*std::sinf(theta_)+ initialCamerTranslate_;
	cameraTranslate_.x = RADIUS*std::cosf(theta_);
	const float INITIAL_CAMERA_ROTATE = float(std::numbers::pi) / 2.0f;
	cameraRotate_.y = -theta_;*/
	
	Camera::GetInstance()->SetTranslate(cameraTranslate_);
	Camera::GetInstance()->SetRotate(cameraRotate_);

	const float TRANSPARENCY_INTERVAL = 0.05f;

	if (isFadeIn_ == true) {
		transparency_ -= TRANSPARENCY_INTERVAL;

		if (transparency_ < 0.0f) {
			isFadeIn_ = false;
		}
	}
	//model_->Update();
	
	
	if (isFadeIn_ == false&& isStart_ == false) {
		if (Input::GetInstance()->GetJoystickState(joyState_)) {
			if (joyState_.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
				triggerButtonTime_ += 1;
			}
		}
		if ((joyState_.Gamepad.wButtons & XINPUT_GAMEPAD_B) == 0) {
			triggerButtonTime_ = 0;
		}





		//スペースかBボタンでスタート
		if ((Input::GetInstance()->IsTriggerKey(DIK_SPACE) == true) || triggerButtonTime_ == 1) {

			decideSE_->PlayWave(seHandle_, false);
			bgm_->StopWave(bgmHandle_);
			isStart_ = true;
		}
	}
	

	if (isStart_ == true) {
		
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

	//model_->Draw(particleTextureHandle_);
	//スプライト
	titleLogoSprite_->Draw();

	blackSprite_->Draw();
}

TitleScene::~TitleScene(){
	delete skydome_;
	delete titleLogoSprite_;
}
