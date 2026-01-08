#include "Unit.h"
#include "Selector.h"
#include <Novice.h>

// 初期化処理
void Unit::Init(int idxerI) {
	// ユニットIDを設定
	id_ = idxerI;
	
	// 初期位置を原点に設定
	mapX_ = 0;
	mapY_ = 0;
	
	// 選択状態を解除
	isSelected_ = false;
}

// 更新処理
void Unit::Update() {
	// 必要に応じて更新処理を実装
}

// 描画処理
void Unit::Draw() {
	// グリッドサイズに基づいて画面上の描画位置を計算
	int screenX = mapX_ * mapSize_;
	int screenY = mapY_ * mapSize_;
	
	// ユニットの色を選択状態に応じて変更
	// 選択中: 黄色、非選択: 白色
	unsigned int color = isSelected_ ? 0xFFFF00FF : 0xFFFFFFFF;
	
	// ユニットを矩形で描画（塗りつぶし）
	Novice::DrawBox(screenX, screenY, mapSize_, mapSize_, 0.0f, color, kFillModeSolid);
	
	// ユニットの枠線を描画（視認性向上のため）
	Novice::DrawBox(screenX, screenY, mapSize_, mapSize_, 0.0f, 0x000000FF, kFillModeWireFrame);
}

// 移動処理
void Unit::Move(int x, int y) {
	// 新しい座標を設定
	mapX_ = x;
	mapY_ = y;
}
