#include "StageSceneInputHandler.h"
#include "SelectorMoveCommand.h"
#include "SelectorSelectCommand.h"
#include "UnitCommand.h"
#include <Novice.h>

// コンストラクタ
StageSceneInputHandler::StageSceneInputHandler()
	: selector_(nullptr) {
}

// キー状態の更新処理
void StageSceneInputHandler::UpdateKeyState() {
	// キーの状態は外部から設定される（SetKeys/SetPreKeysで設定）
}

// セレクタの入力処理（WASDキーでの移動）
std::unique_ptr<IStageSceneCommand> StageSceneInputHandler::SelectorHandleInput(Selector* selector) {
	// 現在のセレクタ位置を取得
	int newX = selector->GetMapX();
	int newY = selector->GetMapY();
	bool moved = false;

	// WASDキーでセレクタを移動（押した瞬間のみ反応）
	if (preKeys_[DIK_W] == 0 && keys_[DIK_W] != 0) {
		newY--;  // 上に移動
		moved = true;
	}
	if (preKeys_[DIK_S] == 0 && keys_[DIK_S] != 0) {
		newY++;  // 下に移動
		moved = true;
	}
	if (preKeys_[DIK_A] == 0 && keys_[DIK_A] != 0) {
		newX--;  // 左に移動
		moved = true;
	}
	if (preKeys_[DIK_D] == 0 && keys_[DIK_D] != 0) {
		newX++;  // 右に移動
		moved = true;
	}

	// 画面内に制限（グリッド座標で制限）
	if (newX < 0) newX = 0;
	if (newY < 0) newY = 0;
	if (newX >= 40) newX = 39;
	if (newY >= 22) newY = 21;

	// 移動があった場合、移動コマンドを生成
	if (moved) {
		return std::make_unique<SelectorMoveCommand>(selector, newX, newY);
	}

	// 移動がなければnullptrを返す
	return nullptr;
}

// ユニットの入力処理（WASDキーでの移動）
std::unique_ptr<IStageSceneCommand> StageSceneInputHandler::UnitHandleInput(Unit* unit) {
	// 現在のユニット位置を取得
	int newX = unit->GetMapX();
	int newY = unit->GetMapY();
	bool moved = false;

	// WASDキーでユニットを移動（押した瞬間のみ反応）
	if (preKeys_[DIK_W] == 0 && keys_[DIK_W] != 0) {
		newY--;  // 上に移動
		moved = true;
	}
	if (preKeys_[DIK_S] == 0 && keys_[DIK_S] != 0) {
		newY++;  // 下に移動
		moved = true;
	}
	if (preKeys_[DIK_A] == 0 && keys_[DIK_A] != 0) {
		newX--;  // 左に移動
		moved = true;
	}
	if (preKeys_[DIK_D] == 0 && keys_[DIK_D] != 0) {
		newX++;  // 右に移動
		moved = true;
	}

	// 画面内に制限（グリッド座標で制限）
	if (newX < 0) newX = 0;
	if (newY < 0) newY = 0;
	if (newX >= 40) newX = 39;
	if (newY >= 22) newY = 21;

	// 移動があった場合、移動コマンドを生成
	if (moved) {
		return std::make_unique<UnitMoveCommand>(unit, newX, newY);
	}

	// 移動がなければnullptrを返す
	return nullptr;
}

// ユニット選択の入力チェック
std::unique_ptr<IStageSceneCommand> StageSceneInputHandler::CheckSelectInput(Selector* selector) {
	// スペースキーが押された瞬間にユニット選択コマンドを生成
	if (preKeys_[DIK_SPACE] == 0 && keys_[DIK_SPACE] != 0) {
		return std::make_unique<SelectorSelectCommand>(selector);
	}

	return nullptr;
}

// 移動確定の入力チェック
std::unique_ptr<IStageSceneCommand> StageSceneInputHandler::CheckConfirmInput(Unit* unit, Selector* selector) {
	// スペースキーが押された瞬間に移動終了コマンドを生成
	if (preKeys_[DIK_SPACE] == 0 && keys_[DIK_SPACE] != 0) {
		return std::make_unique<UnitMoveEndCommand>(unit, selector);
	}

	return nullptr;
}

// Undoの入力チェック
bool StageSceneInputHandler::CheckUndoStatus() {
	// Ctrl+Zでアンドゥ
	if (keys_[DIK_LCONTROL] != 0 && preKeys_[DIK_Z] == 0 && keys_[DIK_Z] != 0) {
		return true;
	}

	return false;
}
