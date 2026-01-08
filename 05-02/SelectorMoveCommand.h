#pragma once
#include "IStageSceneCommand.h"
#include "Selector.h"

// セレクタ移動コマンド
class SelectorMoveCommand : public IStageSceneCommand {
public:
	// コンストラクタ
	SelectorMoveCommand(Selector* selector, int x, int y);

	// コマンド実行
	void Exec() override;

private:
	Selector* selector_;  // 対象のセレクタ
	int x_;               // 移動先のX座標
	int y_;               // 移動先のY座標
};

