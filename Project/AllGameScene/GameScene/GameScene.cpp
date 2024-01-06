#include "GameScene.h"

#include "GameManager.h"

#include "SampleScene/SampleScene.h"
#include "Input.h"
#include "TextureManager.h"
#include "Camera.h"
#include <VectorCalculation.h>


#include <cmath>

GameScene::GameScene() {

}

void GameScene::ExplanationSceneInitialize() {
	explanationTextureHandle_[0] = TextureManager::GetInstance()->LoadTexture("Resources/Explanation/Explanation1/Explanation1.png");
	explanationTextureHandle_[1] = TextureManager::GetInstance()->LoadTexture("Resources/Explanation/Explanation2/Explanation2.png");
	for (int i = 0; i < EXPLANATION_NUMBER_; i++) {
		explamnationSprite[i].reset(Sprite::Create(explanationTextureHandle_[i], {0.0f,0.0f}));
	}

	explanationTextureNumber_ = 1;
	
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
	//敵の速度


	isWait_ = false;

	countDown_ = std::make_unique<CountDown>();
	countDown_->Initialize();


}

void GameScene::Initialize() {
	//共通部分
	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize();

	//プレイヤー
	player_ = new Player();
	player_->Initialize();




	for (int i = 0; i < amount_; i++) {
		enemy_[i] = new Enemy();
		enemy_[i]->SetPlayer(player_);

	}

	enemy_[0]->Initialize({ 3.0f,0.0f,70.0f });
	enemy_[1]->Initialize({ 4.0f,-4.0f,80.0f });
	enemy_[2]->Initialize({ 2.0f,6.0f,60.0f });
	enemy_[3]->Initialize({ 2.0f,4.0f,80.0f });
	enemy_[4]->Initialize({ 4.0f,-5.0f,100.0f });
	enemy_[5]->Initialize({ 1.0f,-2.0f,120.0f });



	//BlackOut
	black_ = std::make_unique<Sprite>();
	uint32_t blackTextureHandle = TextureManager::GetInstance()->LoadTexture("Resources/Black.png");
	black_.reset(Sprite::Create(blackTextureHandle, { 0.0f,0.0f }));

	//WhiteOut
	white_ = std::make_unique<Sprite>();
	uint32_t whiteTextureHandle = TextureManager::GetInstance()->LoadTexture("Resources/White.png");
	black_.reset(Sprite::Create(whiteTextureHandle, { 0.0f,0.0f }));


	//railCamera_ = std::make_unique<RailCamera>();
	//railCamera_->Initialize(player_->GetWorldPosition(), { 0.0f,0.0f,0.0f });
	//player_->SetParent(&railCamera_->GetWorldTransform());
	collisionManager_ = std::make_unique <CollisionManager>();

	cameraTranslate_ = { 0.0f,0.0f,-30.0f };
	cameraRotate_ = { 0.0f,0.0f,0.0f };
	Camera::GetInstance()->SetTranslate(cameraTranslate_);
	Camera::GetInstance()->SetRotate(cameraRotate_);

	//説明
	ExplanationSceneInitialize();
	//カウントダウン
	ReadySceneInitialize();
	//メインのゲーム
	PlaySceneInitialize();
}

void GameScene::DebugText() {
#ifdef _DEBUG
	ImGui::Begin("Game");

	ImGui::End();

#endif
}


#pragma region Update用
void GameScene::ExplanationSceneUpdate(){


	if (Input::GetInstance()->IsTriggerKey(DIK_SPACE) == true) {
		explanationTextureNumber_++;
	}

	if (explanationTextureNumber_ >= 3) {
		scene_ = Scene::Ready;
	}
	
	
}

void GameScene::ReadySceneUpdate(){

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
	
	//プレイヤーが動き出す
	//player_->SetTranslateZ(move_);
	player_->SetIsEnableAttack(true);
	player_->SetIsEnableMove(true);
}


/// <summary>
/// 衝突判定と応答
/// </summary>
void GameScene::CheckAllCollisions() {
	//判定対象AとBの座標
	//資料ではpoAとかやっていたけど分かりずらいから具体的は変数名にする
	Vector3 playerPos = {};
	Vector3 enemyPos = {};
	Vector3 enemyBulletPos = {};
	Vector3 playerBulletPos = {};

	//自弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();

	//敵弾リストの取得
	for (int i = 0; i < amount_; i++) {
		const std::list<EnemyBullet*>& enemyBullets = enemy_[i]->GetBullets();

		//コライダー
		std::list<Collider*> colliders;



		//衝突マネージャのリストをクリアする
		collisionManager_->ClearList();
		//コライダーを全て衝突マネージャに登録する
		collisionManager_->RegisterList(player_);
		for (int i = 0; i < amount_; i++) {
			collisionManager_->RegisterList(enemy_[i]);
		}

		//自弾全てについて
		for (PlayerBullet* bullet : playerBullets) {
			//colliders.push_back(bullet);
			collisionManager_->RegisterList(bullet);
		}
		//敵弾全てについて
		for (EnemyBullet* bullet : enemyBullets) {
			//colliders.push_back(bullet);
			collisionManager_->RegisterList(bullet);
		}

		collisionManager_->CheckAllCollision();
	}

	//衝突マネージャのリストをクリアする
	collisionManager_->ClearList();
}



void GameScene::PlaySceneUpdate(){

	countDown_->Update();

	CheckAllCollisions();
	/*for (Enemy* enemy : enemyes_) {
		enemy->Update();
	}*/

	for (int i = 0; i < amount_; i++) {
		enemy_[i]->Update();
	}

	//勝ち
	if (countDown_->GetTime() < 0) {
		scene_ = Scene::Win;
	}


	//負け
	if (player_->GetIsDead() == true) {
		scene_ = Scene::Lose;
	}

}

void GameScene::LoseSceneUpdate() {

#ifdef _DEBUG
	ImGui::Begin("Lose");

	ImGui::End();

#endif


	theta_ += 1.0f;
	cameraTranslate_.x += std::sinf(theta_) * 0.5f;

	

	for (int i = 0; i < amount_; i++) {
		enemy_[i]->Update();
	}
	for (int i = 0; i < amount_; i++) {
		enemy_[i]->SetSpeedOffset(0.5f);
	}
	
	blackTransparency_ += 0.01f;
	black_->SetTransparency(blackTransparency_);
	if (blackTransparency_ > 1.0f) {
		blackTransparency_ = 1.0f;
		loseLodingTime_ += 1;
	}

}

void GameScene::WinSceneUpdate() {
#ifdef _DEBUG
	ImGui::Begin("Win");

	ImGui::End();

#endif
	for (int i = 0; i < amount_; i++) {
		enemy_[i]->SetSpeedOffset(0.0f);
	}

	white_->SetTransparency(whiteTransparency_);

	finishDisplayTime_ += 1;
	if (finishDisplayTime_ > SECOND_ * 2) {
		whiteTransparency_ += 0.05f;

		if (whiteTransparency_ > 1.0f) {
			whiteTransparency_ = 1.0f;



		}



	}

}

#pragma endregion


void GameScene::Update(GameManager* gameManager) {
	//デバッグ用
	DebugText();

	//共通部分
	skydome_->Update();
	player_->Update();
	Camera::GetInstance()->SetTranslate(cameraTranslate_);


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


	case Scene::Lose:
		LoseSceneUpdate();

		break;

	case Scene::Win:
		WinSceneUpdate();
		break;

	}

	if (loseLodingTime_ > SECOND_ * 2) {
		//gameManager->ChangeScene(new LoseScene());
	}

	if (Input::GetInstance()->IsTriggerKey(DIK_1) == true) {
		gameManager->ChangeScene(new SampleScene());
	}

}


void GameScene::ExplanationSceneDraw(){
	if (explanationTextureNumber_ == 1) {
		explamnationSprite[0]->Draw();
	}
	if (explanationTextureNumber_ == 2) {
		explamnationSprite[1]->Draw();
	}
	
}

void GameScene::ReadySceneDraw(){
	for (int i = 0; i < COUNTDOWN_NUMBER_; i++) {
		if (displayNumber_ == i) {
			countDownSprite[i]->Draw();
		}
		
	}
}

void GameScene::PlaySceneDraw(){
	countDown_->Draw();
}

void GameScene::LoseSceneDraw(){
	black_->Draw();

}

void GameScene::WinSceneDraw(){



}



void GameScene::Draw() {
	//共通部分
	skydome_->Draw();
	player_->Draw();
	for (int i = 0; i < amount_; i++) {
		enemy_[i]->Draw();

	}

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


	case Scene::Lose:
		LoseSceneDraw();

		break;

	case Scene::Win:
		WinSceneDraw();
		break;


	}
}

GameScene::~GameScene() {
	delete player_;
	for (int i = 0; i < amount_; i++) {
		delete enemy_[i];
		

	}

}
