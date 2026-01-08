#pragma once
#include "IScene.h"
#include "../Selector.h"
#include "../Unit.h"
#include "../StageSceneInputHandler.h"
#include "../IStageSceneCommand.h"
#include <memory>
#include <list>

// ステージシーン
class StageScene : public IScene {
public:
	StageScene();
	~StageScene() override = default;

	void Update(char* keys, char* preKeys) override;
	void Draw() override;
	SceneType GetNextScene() const override;
	bool IsFinished() const override;

private:
	// グリッド描画
	void DrawGrid();
	
	// Undo処理
	void Undo();
	
	// シーン状態
	bool isFinished_;
	SceneType nextScene_;
	
	// グリッド設定
	static const int kGridSize = 32;
	int gridColor_;
	
	// ゲームオブジェクト
	Selector selector_;              // セレクタ（ユニットを包含）
	static const int kMaxUnits = 10;
	Unit units_[kMaxUnits];          // 全ユニットの配列
	int unitCount_;                  // 現在のユニット数
	
	// 入力処理
	StageSceneInputHandler inputHandler_;
	
	// コマンド履歴（Undo用）
	std::list<std::unique_ptr<IStageSceneCommand>> commandHistory_;
	
	// 各ユニットの位置履歴（Undo用）
	struct PositionState {
		int unitId;  // ユニットID
		int x;       // X座標
		int y;       // Y座標
	};
	std::list<PositionState> positionHistory_;
};
