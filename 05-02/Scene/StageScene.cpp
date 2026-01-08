#include "StageScene.h"
#include <Novice.h>

// コンストラクタ
StageScene::StageScene()
	: isFinished_(false), nextScene_(SceneType::Stage), gridColor_(0x888888FF), unitCount_(0) {
	
	// ユニットの初期化
	units_[0].Init(0);
	units_[0].SetMapX(10);
	units_[0].SetMapY(10);
	unitCount_ = 1;
	
	units_[1].Init(1);
	units_[1].SetMapX(15);
	units_[1].SetMapY(8);
	unitCount_ = 2;
	
	units_[2].Init(2);
	units_[2].SetMapX(3);
	units_[2].SetMapY(15);
	unitCount_ = 3;
	
	// セレクタの初期化
	selector_.Init();
	selector_.SetMapX(5);
	selector_.SetMapY(5);
	
	// セレクタにユニット配列を設定（セレクタがユニットを包含）
	selector_.SetUnits(units_, unitCount_);
	
	// InputHandlerの初期化
	inputHandler_.SetSelector(&selector_);
}

// 更新処理
void StageScene::Update(char* keys, char* preKeys) {
	// キー入力の状態を更新
	inputHandler_.SetKeys(keys);
	inputHandler_.SetPreKeys(preKeys);
	inputHandler_.UpdateKeyState();
	
	std::unique_ptr<IStageSceneCommand> command = nullptr;
	
	// セレクタのモードに応じてコマンドを取得
	if (selector_.GetSelectMode() == SELECTOR) {
		// ===== セレクタモード =====
		
		// スペースキーでユニット選択をチェック
		command = inputHandler_.CheckSelectInput(&selector_);
		
		if (!command) {
			// ユニット選択がなければ、セレクタの移動コマンドを取得
			command = inputHandler_.SelectorHandleInput(&selector_);
		}
	} 
	else if (selector_.GetSelectMode() == UNIT) {
		// ===== ユニットモード =====
		
		// Undoチェック（Ctrl+Z）- ユニット選択中のみ有効
		if (inputHandler_.CheckUndoStatus()) {
			Undo();
			return;
		}
		
		// 選択中のユニットを取得
		Unit* selectedUnit = selector_.GetSelectedUnitAddress();
		
		// スペースキーで移動確定をチェック
		command = inputHandler_.CheckConfirmInput(selectedUnit, &selector_);
		
		// 移動確定が押された場合、位置履歴とコマンド履歴をクリア
		if (command) {
			// 移動確定後は履歴をクリア（確定したので戻せなくする）
			positionHistory_.clear();
			commandHistory_.clear();
		} else {
			// 移動確定がなければ、ユニットの移動コマンドを取得
			
			// 移動前の位置を保存（Undo用）
			int oldX = selectedUnit->GetMapX();
			int oldY = selectedUnit->GetMapY();
			
			// ユニットの移動コマンドを取得
			command = inputHandler_.UnitHandleInput(selectedUnit);
			
			// 移動が実行される場合、位置履歴に追加
			if (command) {
				PositionState state;
				state.unitId = selectedUnit->GetId();
				state.x = oldX;
				state.y = oldY;
				positionHistory_.push_back(state);
			}
		}
	}
	
	// コマンドがあれば実行
	if (command) {
		// コマンドを実行
		command->Exec();
		
		// コマンドを履歴に追加（Undo用に保持）
		commandHistory_.push_back(std::move(command));
	}
	
	// セレクタの更新
	selector_.Update();
	
	// 全ユニットの更新
	for (int i = 0; i < unitCount_; i++) {
		units_[i].Update();
	}
}

// Undo処理（ユニット選択中のみ有効）
void StageScene::Undo() {
	// ユニットモードでない場合は何もしない
	if (selector_.GetSelectMode() != UNIT) {
		return;
	}
	
	// 位置履歴が空の場合は何もしない
	if (positionHistory_.empty()) {
		return;
	}
	
	// 選択中のユニットを取得
	Unit* selectedUnit = selector_.GetSelectedUnitAddress();
	if (selectedUnit == nullptr) {
		return;
	}
	
	// 最後の位置状態を取得
	PositionState lastState = positionHistory_.back();
	
	// 選択中のユニットの履歴のみUndoできる
	if (lastState.unitId != selectedUnit->GetId()) {
		return;
	}
	
	// 履歴から削除
	positionHistory_.pop_back();
	
	// ユニットを元の位置に戻す
	selectedUnit->Move(lastState.x, lastState.y);
	
	// コマンド履歴からも削除
	if (!commandHistory_.empty()) {
		commandHistory_.pop_back();
	}
}

// 描画処理
void StageScene::Draw() {
	// 背景色を描画
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x4466AAFF, kFillModeSolid);
	
	// グリッドを描画
	DrawGrid();
	
	// 全ユニットを描画
	for (int i = 0; i < unitCount_; i++) {
		units_[i].Draw();
	}
	
	// セレクタを描画
	selector_.Draw();
	
	// デバッグ情報を表示
	Novice::ScreenPrintf(10, 10, "Scene: STAGE");
	Novice::ScreenPrintf(10, 30, "Selector: (%d, %d)", selector_.GetMapX(), selector_.GetMapY());
	Novice::ScreenPrintf(10, 50, "Units: %d", unitCount_);
	Novice::ScreenPrintf(10, 70, "Mode: %s", selector_.GetSelectMode() == SELECTOR ? "SELECTOR" : "UNIT");
	Novice::ScreenPrintf(10, 90, "Commands: %d", static_cast<int>(commandHistory_.size()));
	Novice::ScreenPrintf(10, 110, "Undo History: %d", static_cast<int>(positionHistory_.size()));
	
	// モードに応じた操作説明を表示
	if (selector_.GetSelectMode() == SELECTOR) {
		Novice::ScreenPrintf(10, 130, "SPACE: Select Unit, WASD: Move Selector");
	} else {
		Novice::ScreenPrintf(10, 130, "SPACE: Confirm Move, WASD: Move Unit, Ctrl+Z: Undo");
	}
}

// グリッド描画処理
void StageScene::DrawGrid() {
	// 縦線を描画（左から右へ）
	for (int x = 0; x <= 1280; x += kGridSize) {
		Novice::DrawLine(x, 0, x, 720, gridColor_);
	}
	
	// 横線を描画（上から下へ）
	for (int y = 0; y <= 720; y += kGridSize) {
		Novice::DrawLine(0, y, 1280, y, gridColor_);
	}
}

// 次のシーン取得
SceneType StageScene::GetNextScene() const {
	return nextScene_;
}

// シーン終了判定
bool StageScene::IsFinished() const {
	return isFinished_;
}
