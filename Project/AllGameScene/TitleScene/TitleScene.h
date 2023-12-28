#pragma once

#include "AllGameScene/GameManager/IGameScene.h"

#include "Sprite.h"
#include "SpritePosition.h"
#include "Transform.h"
#include "Model.h"

#include <memory>

//StatePatternを使う時は必ず前方宣言をするように
class Gamemanager;

class TitleScene : public IGameScene {
public:

	//コンストラクタ
	TitleScene();


	/// 初期化
	void Initialize()override;

	/// 更新
	void Update(GameManager* gameManager)override;

	/// 描画
	void Draw()override;


	/// デストラクタ
	~TitleScene();


private:
	void DebugText();




private:




};
