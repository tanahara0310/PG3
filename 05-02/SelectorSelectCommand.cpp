#include "SelectorSelectCommand.h"

// コンストラクタ
SelectorSelectCommand::SelectorSelectCommand(Selector* selector)
	: selector_(selector) {
}

// コマンド実行処理
void SelectorSelectCommand::Exec() {
	// セレクタに包含されたSelectUnit()メソッドを呼び出す
	// このメソッドが全てのユニット選択処理を行う
	selector_->SelectUnit();
}
