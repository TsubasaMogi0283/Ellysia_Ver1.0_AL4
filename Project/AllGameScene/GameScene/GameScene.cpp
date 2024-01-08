#include "GameScene.h"

#include "GameManager.h"

#include "SampleScene/SampleScene.h"
#include "Input.h"
#include "TextureManager.h"
#include "Camera.h"
#include <VectorCalculation.h>

#include "LoseScene/LoseScene.h"
#include "WinScene/WinScene.h"
#include <cmath>
#include <fstream>

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

	//LoadEnemyPopData();

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


	whiteTransparency_ = 0.0f;

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
	enemy_[6]->Initialize({ -3.0f,0.0f,140.0f });
	enemy_[7]->Initialize({ -4.0f,-4.0f,160.0f });
	enemy_[8]->Initialize({ -1.0f,6.0f,180.0f });
	enemy_[9]->Initialize({ 0.0f,4.0f,200.0f });
	enemy_[10]->Initialize({ 5.0f,-1.0f,220.0f });
	enemy_[11]->Initialize({ 3.0f,-2.0f,240.0f });
	enemy_[12]->Initialize({ -2.0f,0.0f,260.0f });
	enemy_[13]->Initialize({ 0.0f,2.0f,280.0f });
	enemy_[14]->Initialize({ 1.0f,3.0f,300.0f });
	enemy_[15]->Initialize({ 2.0f,2.0f,320.0f });
	enemy_[16]->Initialize({ -4.0f,-1.0f,340.0f });
	enemy_[17]->Initialize({ 1.0f,0.0f,360.0f });
	enemy_[18]->Initialize({ 2.0f,4.0f,380.0f });
	enemy_[19]->Initialize({ 4.0f,2.0f,400.0f });
	


	//BlackOut
	black_ = std::make_unique<Sprite>();
	uint32_t blackTextureHandle = TextureManager::GetInstance()->LoadTexture("Resources/Black.png");
	black_.reset(Sprite::Create(blackTextureHandle, { 0.0f,0.0f }));

	//WhiteOut
	white_ = std::make_unique<Sprite>();
	uint32_t whiteTextureHandle = TextureManager::GetInstance()->LoadTexture("Resources/White.png");
	white_.reset(Sprite::Create(whiteTextureHandle, { 0.0f,0.0f }));

	//Finish
	finish_ = std::make_unique<Sprite>();
	uint32_t finishTextureHandle = TextureManager::GetInstance()->LoadTexture("Resources/Finish/Finish.png");
	finish_.reset(Sprite::Create(finishTextureHandle, { 0.0f,0.0f }));



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
	ImGui::InputInt("winLoadingTime_", &winLoadingTime_);
	ImGui::InputInt("loseLoadingTime_", &loseLodingTime_);

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
	player_->SetTranslate({ 0.0f,-3.0f,0.0f });
	
}

void GameScene::GenerateEnemy(Vector3 position) {
	//生成
	//enemy_ = new Enemy();
	//
	//enemy_->Initialize(position);
	//enemy_->SetPlayer(player_);
	//
	//
	//enemyes_.push_back(enemy_);
}


////敵発生データの読み込み
//void GameScene::LoadEnemyPopData() {
//	////ファイルを開く
//	std::ifstream file;
//
//	file.open("Resources/enemyPop.csv");
//	assert(file.is_open());
//
//	//ファイルの内容を文字列ストリームにコピー
//	//enemyPopCommands_ << file.rdbuf();
//
//	//ファイルを閉じる
//	file.close();
//}
//
////敵発生コマンドの更新
//void GameScene::UpdateEnemyPopCommands() {
//
//
//	//待機処理
//	if (isWait_ == true) {
//		waitingTimer_--;
//		if (waitingTimer_ <= 0) {
//			//待機完了
//			isWait_ = false;
//		}
//	}
//
//
//
//	//1行分の文字列を入れる変数
//	std::string line;
//
//	//コマンド実行ループ
//	while (getline(enemyPopCommands_, line)) {
//		//1行分の文字列をストリームに変呼応して解析しやすくする
//		std::istringstream line_stream(line);
//
//		std::string word;
//		//「,」区切りの先頭文字列を取得
//		getline(line_stream, word, ',');
//
//
//		//"//"から始まる行はコメント
//		if (word.find("//") == 0) {
//			//コメント行を飛ばす
//			continue;
//		}
//
//		//POPコマンド
//		if (word.find("POP") == 0) {
//			//x座標
//			getline(line_stream, word, ',');
//			float x = (float)std::atof(word.c_str());
//
//			//y座標
//			getline(line_stream, word, ',');
//			float y = (float)std::atof(word.c_str());
//
//			//z座標
//			getline(line_stream, word, ',');
//			float z = (float)std::atof(word.c_str());
//
//			//敵を発生させる
//			GenerateEnemy({ x,y,z });
//
//		}
//		else if (word.find("WAIT") == 0) {
//			getline(line_stream, word, ',');
//
//			//待ち時間
//			int32_t waitTime = atoi(word.c_str());
//
//			//待機開始
//			isWait_ = true;
//			//待機タイマー
//			waitingTimer_ = waitTime;
//
//
//
//			//コマンドループを抜ける
//			break;
//
//
//		}
//
//
//	}
//
//
//
//}





/// <summary>
/// 衝突判定と応答
/// </summary>
void GameScene::CheckAllCollisions() {
	////判定対象AとBの座標
	////資料ではpoAとかやっていたけど分かりずらいから具体的は変数名にする
	//Vector3 playerPos = {};
	//Vector3 enemyPos = {};
	//Vector3 enemyBulletPos = {};
	//Vector3 playerBulletPos = {};

	////自弾リストの取得
	//const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();

	////敵弾リストの取得
	//for (int i = 0; i < amount_; i++) {
	//	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();

	//	//コライダー
	//	std::list<Collider*> colliders;



	//	//衝突マネージャのリストをクリアする
	//	collisionManager_->ClearList();
	//	//コライダーを全て衝突マネージャに登録する
	//	collisionManager_->RegisterList(player_);
	//	for (int i = 0; i < amount_; i++) {
	//		collisionManager_->RegisterList(enemy_);
	//	}

	//	//自弾全てについて
	//	for (PlayerBullet* bullet : playerBullets) {
	//		//colliders.push_back(bullet);
	//		collisionManager_->RegisterList(bullet);
	//	}
	//	//敵弾全てについて
	//	for (EnemyBullet* bullet : enemyBullets) {
	//		//colliders.push_back(bullet);
	//		collisionManager_->RegisterList(bullet);
	//	}

	//	collisionManager_->CheckAllCollision();
	//}

	////衝突マネージャのリストをクリアする
	//collisionManager_->ClearList();



	Vector3 playerPos = {};

	//判定対象AとBの座標
	//自弾
	Vector3 posC={};
	Vector3 posD={};
	//自弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	//敵弾リストの取得
	//const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();

#pragma region プレイヤーと敵の当たり判定
	for (int i = 0; i < amount_; i++) {
		if (enemy_[i]->IsDead() == false) {
			posC = enemy_[i]->GetWorldPosition();



			//自弾の座標
			playerPos = player_->GetWorldPosition();



			//座標CとDの距離を求める
			float distanceCD = Length(Subtract(playerPos, posC));

			if (distanceCD < enemy_[i]->GetRadius() + player_->GetRadius()) {
				//敵キャラの衝突時コールバックを呼び出す
				enemy_[i]->OnCollision();



				//自弾の衝突時コールバックを呼び出す
				player_->OnCollision();

				scene_ = Scene::Lose;


			}

		}

	}
#pragma endregion


#pragma region 自弾と敵キャラの当たり判定
	
			//敵キャラの位置
	
	for (int i = 0; i < amount_; i++) {
		if (enemy_[i]->IsDead() == false) {
			posC = enemy_[i]->GetWorldPosition();



			//自キャラと敵弾全ての当たり判定
			for (PlayerBullet* playerBullet : playerBullets) {
				//自弾の座標
				posD = playerBullet->GetWorldPosition();



				//座標CとDの距離を求める
				float distanceCD = Length(Subtract(posD, posC));

				if (distanceCD < enemy_[i]->GetRadius() + playerBullet->GetRadius()) {
					//敵キャラの衝突時コールバックを呼び出す
					enemy_[i]->OnCollision();



					//自弾の衝突時コールバックを呼び出す
					playerBullet->OnCollision();



				}


			}
		}
	}


#pragma endregion
}



void GameScene::PlaySceneUpdate(){
	player_->SetIsEnableAttack(true);
	player_->SetIsEnableMove(true);

	countDown_->Update();

	//UpdateEnemyPopCommands();
	CheckAllCollisions();
	//for (Enemy* enemy : enemyes_) {
	//	enemy->Update();
	//}
	for (int i = 0; i < amount_; i++) {
		enemy_[i]->Update();

	}


	/*enemyes_.remove_if([](Enemy* enemy) {
		if (enemy->IsDead()) {
			delete enemy;
			return true;
		}
		return false;
	});*/
	

	//勝ち
	if (countDown_->GetTime() < 0) {
		scene_ = Scene::Win;
	}


	//負け
	//if (player_->GetIsDead() == true && countDown_->GetTime() > 0) {
	//	scene_ = Scene::Lose;
	//}

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
		enemy_[i]->SetSpeedOffset(1.0f);
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
		whiteTransparency_ += 0.005f;
		cameraVelocity_ += cameraAccel_;
		
		cameraTranslate_.z += cameraVelocity_;

		if (whiteTransparency_ > 1.0f){
			whiteTransparency_ = 1.0f;
			winLoadingTime_ += 1;
			//finishDisplayTime_ += 1;
		}

	}

	Camera::GetInstance()->SetTranslate(cameraTranslate_);

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
		gameManager->ChangeScene(new LoseScene());
	}
	if (winLoadingTime_ > SECOND_ * 2) {
		gameManager->ChangeScene(new WinScene());
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
	for (int i = 0; i < amount_; i++) {
		enemy_[i]->Draw();
	}

}

void GameScene::LoseSceneDraw(){
	black_->Draw();
	for (int i = 0; i < amount_; i++) {
		enemy_[i]->Draw();
	}
}

void GameScene::WinSceneDraw(){
	white_->Draw();

	if (finishDisplayTime_ > 0 && finishDisplayTime_ <= SECOND_ * 2) {
		finish_->Draw();
	}
	
}



void GameScene::Draw() {
	//共通部分
	skydome_->Draw();
	player_->Draw();
	

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
