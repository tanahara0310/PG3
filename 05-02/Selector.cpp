#include "Selector.h"
#include <Novice.h>

// コンストラクタ
Selector::Selector() 
	: mapX_(0), mapY_(0), mapSize_(32), selectMode_(SELECTOR), 
	  units_(nullptr), unitCount_(0), selectedUnit_(nullptr) {
}

// 初期化処理
void Selector::Init() {
	// 座標を原点に設定
	mapX_ = 0;
	mapY_ = 0;
	
	// セレクタモードに設定
	selectMode_ = SELECTOR;
	
	// ユニット関連をリセット
	units_ = nullptr;
	unitCount_ = 0;
	selectedUnit_ = nullptr;
}

// 更新処理
void Selector::Update() {
	// 必要に応じて更新処理を実装
}

// 描画処理
void Selector::Draw() {
	// グリッドサイズに基づいて画面上の描画位置を計算
	int screenX = mapX_ * mapSize_;
	int screenY = mapY_ * mapSize_;
	
	// セレクタの色をモードによって変更
	// SELECTOR: 赤色、UNIT: 緑色
	unsigned int color = (selectMode_ == UNIT) ? 0x00FF00FF : 0xFF0000FF;
	
	// セレクタの枠を描画
	Novice::DrawBox(screenX, screenY, mapSize_, mapSize_, 0.0f, color, kFillModeWireFrame);
	
	// セレクタの内側を半透明で塗りつぶし（視認性向上のため）
	unsigned int fillColor = (selectMode_ == UNIT) ? 0x00FF0044 : 0xFF000044;
	Novice::DrawBox(screenX + 2, screenY + 2, mapSize_ - 4, mapSize_ - 4, 0.0f, fillColor, kFillModeSolid);
}

// セレクタの移動処理
void Selector::Move(int x, int y) {
	// 新しい座標を設定
	mapX_ = x;
	mapY_ = y;
}

// ユニット選択処理
void Selector::SelectUnit() {
	// ユニット配列が設定されていない場合は処理しない
	if (units_ == nullptr || unitCount_ <= 0) {
		return;
	}
	
	// 現在のセレクタ位置を取得
	int selectorX = mapX_;
	int selectorY = mapY_;
	
	// 全ユニットをチェックして、セレクタと同じ位置にいるユニットを探す
	for (int i = 0; i < unitCount_; i++) {
		// ユニットの位置とセレクタの位置が一致するか確認
		if (units_[i].GetMapX() == selectorX && units_[i].GetMapY() == selectorY) {
			// ユニットが見つかった場合
			
			// ユニットを選択状態にする
			units_[i].SetIsSelected(true);
			
			// 選択中のユニットとして保存
			selectedUnit_ = &units_[i];
			
			// モードをユニット選択モードに変更
			selectMode_ = UNIT;
			
			return;
		}
	}
	
	// ユニットが見つからなかった場合、選択解除
	if (selectedUnit_ != nullptr) {
		// 既に選択中のユニットがあれば、選択状態を解除
		selectedUnit_->SetIsSelected(false);
	}
	
	// 選択中ユニットをクリア
	selectedUnit_ = nullptr;
	
	// モードをセレクタモードに戻す
	selectMode_ = SELECTOR;
}
