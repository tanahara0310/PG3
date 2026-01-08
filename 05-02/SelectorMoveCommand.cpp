#include "SelectorMoveCommand.h"

// コンストラクタ
SelectorMoveCommand::SelectorMoveCommand(Selector* selector, int x, int y)
	: selector_(selector), x_(x), y_(y) {
}

// コマンド実行処理
void SelectorMoveCommand::Exec() {
	// セレクタを指定座標に移動
	selector_->Move(x_, y_);
}
