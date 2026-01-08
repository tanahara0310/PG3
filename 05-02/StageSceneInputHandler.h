#pragma once
#include "IStageSceneCommand.h"
#include "Selector.h"
#include "Unit.h"
#include <memory>

// ステージシーンの入力処理を管理するクラス
class StageSceneInputHandler {
private:
	// キー入力の状態
	char keys_[256] = {0};      // 現在のフレームのキー状態
	char preKeys_[256] = {0};   // 前フレームのキー状態
	
	// 管理対象のオブジェクト
	Selector* selector_;  // セレクタへのポインタ

public:
	// コンストラクタ
	StageSceneInputHandler();
	
	// キー状態の更新
	void UpdateKeyState();
	
	// セレクタの入力処理（移動）
	std::unique_ptr<IStageSceneCommand> SelectorHandleInput(Selector* selector);
	
	// ユニットの入力処理（移動）
	std::unique_ptr<IStageSceneCommand> UnitHandleInput(Unit* unit);
	
	// ユニット選択の入力チェック（スペースキー）
	std::unique_ptr<IStageSceneCommand> CheckSelectInput(Selector* selector);
	
	// 移動確定の入力チェック（Enterキー）
	std::unique_ptr<IStageSceneCommand> CheckConfirmInput(Unit* unit, Selector* selector);
	
	// Undoの入力チェック（Ctrl+Z）
	bool CheckUndoStatus();
	
	// Setter各種
	void SetKeys(char* keys) { 
		for (int i = 0; i < 256; i++) {
			keys_[i] = keys[i];
		}
	}
	void SetPreKeys(char* preKeys) { 
		for (int i = 0; i < 256; i++) {
			preKeys_[i] = preKeys[i];
		}
	}
	void SetSelector(Selector* selector) { selector_ = selector; }
};
