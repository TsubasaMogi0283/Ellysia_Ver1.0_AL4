#include "WinScene.h"
#include "Input/Input.h"
#include "TitleScene/TitleScene.h"
#include "AllGameScene/GameManager/GameManager.h"
#include "TextureManager/TextureManager.h"

WinScene::WinScene(){

}

void WinScene::Initialize(){

	//背景
	back_ = std::make_unique<Sprite>();
	uint32_t backTextureHandle = TextureManager::GetInstance()->LoadTexture("Resources/Result/Win/Win.png");
	back_.reset(Sprite::Create(backTextureHandle, {0.0f,0.0f}));
	
	//テキスト
	text_ = std::make_unique<Sprite>();
	uint32_t textTexturehandle = TextureManager::GetInstance()->LoadTexture("Resources/Result/ReturnToTitle.png");
	text_.reset(Sprite::Create(textTexturehandle, { 0.0f,0.0f }));

	//BGM
	//bgm_ = Audio::GetInstance();
	//selectBGMHandle_ = bgm_->LoadWave("Resources/Audio/BGM/Win.wav");
	//bgm_->PlayWave(selectBGMHandle_, true);

	//DecideSE
	//decideSE_ = Audio::GetInstance();
	//decideSEHandle_ = decideSE_->LoadWave("Resources/Audio/Deside/Decide.wav");

}

void WinScene::ShowImGui(){
	ImGui::Begin("Win");
	ImGui::End();
}

void WinScene::Update(GameManager* gamaManager){
	//ShowImGui();

	back_->SetTransparency(spriteTransparency_);

	if (isFadeOut_ == false) {
		//点滅
		flashTime_ += 1;
		if (flashTime_ > 0) {
			if (flashTime_ > 0 && flashTime_ <= 30) {
				text_->SetInvisible(false);
			}
			if (flashTime_ > 30 && flashTime_ <= 60) {
				text_->SetInvisible(true);
			}
			if (flashTime_ > 60) {
				flashTime_ = 0;
			}
		}

		if (Input::GetInstance()->GetJoystickState(joyState)) {

			//Bボタン
			if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
				triggerButtonBTime += 1;

			}

		}

		if (Input::GetInstance()->IsTriggerKey(DIK_SPACE) == true || triggerButtonBTime == 1) {
			isFadeOut_ = true;
			//decideSE_->PlayWave(decideSEHandle_, false);
			//bgm_->StopWave(selectBGMHandle_);
			
		}

	}
	if (isFadeOut_ == true) {

		fastFlashTime_ += 1;
		//高速点滅処理
		const int FLASH_INTERVAL = 2;
		if (fastFlashTime_ > FLASH_INTERVAL * 0) {
			if (fastFlashTime_ > FLASH_INTERVAL * 0 && fastFlashTime_ <= FLASH_INTERVAL * 1) {
				text_->SetInvisible(false);
			}
			if (fastFlashTime_ > FLASH_INTERVAL * 1 && fastFlashTime_ <= FLASH_INTERVAL * 2) {
				text_->SetInvisible(true);
			}
			if (fastFlashTime_ > FLASH_INTERVAL * 2 && fastFlashTime_ <= FLASH_INTERVAL * 3) {
				text_->SetInvisible(false);
			}
			if (fastFlashTime_ > FLASH_INTERVAL * 3 && fastFlashTime_ <= FLASH_INTERVAL * 4) {
				text_->SetInvisible(true);
			}
			if (fastFlashTime_ > FLASH_INTERVAL * 4 && fastFlashTime_ <= FLASH_INTERVAL * 5) {
				text_->SetInvisible(false);
			}
			if (fastFlashTime_ > FLASH_INTERVAL * 5 && fastFlashTime_ <= FLASH_INTERVAL * 6) {
				text_->SetInvisible(true);
			}
			if (fastFlashTime_ > FLASH_INTERVAL * 6 && fastFlashTime_ <= FLASH_INTERVAL * 7) {
				text_->SetInvisible(false);
			}
			if (fastFlashTime_ > FLASH_INTERVAL * 7 && fastFlashTime_ <= FLASH_INTERVAL * 8) {
				text_->SetInvisible(true);
			}
			if (fastFlashTime_ > FLASH_INTERVAL * 8) {
				spriteTransparency_ -= 0.05f;
				if (spriteTransparency_ < 0.0f) {
					spriteTransparency_ = 0.0f;
					
					loadingTime_ += 1;


					if (loadingTime_ > 60 * 2) {
						gamaManager->ChangeScene(new TitleScene());
					}
				}
			}
			
		}
		
	}
}

void WinScene::Draw(){
	back_->Draw();
	text_->Draw();
}

WinScene::~WinScene(){

}


