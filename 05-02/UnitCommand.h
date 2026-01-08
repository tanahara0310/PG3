#pragma once
#include "IStageSceneCommand.h"
#include "Unit.h"
#include "Selector.h"

// ユニット移動コマンド
class UnitMoveCommand : public IStageSceneCommand {
public:
	// コンストラクタ
	UnitMoveCommand(Unit* unit, int x, int y);
	
	// コマンド実行
	void Exec() override;

private:
	Unit* unit_;  // 対象のユニット
	int x_;       // 移動先のX座標
	int y_;       // 移動先のY座標
};

// ユニット移動終了コマンド
class UnitMoveEndCommand : public IStageSceneCommand {
public:
	// コンストラクタ
	UnitMoveEndCommand(Unit* unit, Selector* selector);
	
	// コマンド実行
	void Exec() override;

private:
	Unit* unit_;          // 対象のユニット
	Selector* selector_;  // セレクタ
};
