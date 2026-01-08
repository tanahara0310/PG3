#include "UnitCommand.h"

// ===== UnitMoveCommand =====

// コンストラクタ
UnitMoveCommand::UnitMoveCommand(Unit* unit, int x, int y)
	: unit_(unit), x_(x), y_(y) {
}

// コマンド実行処理
void UnitMoveCommand::Exec() {
	// ユニットを指定座標に移動
	unit_->Move(x_, y_);
}

// ===== UnitMoveEndCommand =====

// コンストラクタ
UnitMoveEndCommand::UnitMoveEndCommand(Unit* unit, Selector* selector)
	: unit_(unit), selector_(selector) {
}

// コマンド実行処理
void UnitMoveEndCommand::Exec() {
	// ユニットの選択状態を解除
	unit_->SetIsSelected(false);
	
	// セレクタをユニットの位置に移動（重複描画を防ぐ）
	selector_->Move(unit_->GetMapX(), unit_->GetMapY());
	
	// セレクタの選択ユニットをクリア
	selector_->SetSelectedUnit(nullptr);
	
	// セレクタモードに戻す
	selector_->SetSelectMode(SELECTOR);
}
