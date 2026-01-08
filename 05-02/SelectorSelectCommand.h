#pragma once
#include "IStageSceneCommand.h"
#include "Selector.h"
#include "Unit.h"

// セレクタによるユニット選択コマンド
class SelectorSelectCommand : public IStageSceneCommand {
public:
	// コンストラクタ
	SelectorSelectCommand(Selector* selector);
	
	// コマンド実行
	void Exec() override;

private:
	Selector* selector_;  // 対象のセレクタ
};
