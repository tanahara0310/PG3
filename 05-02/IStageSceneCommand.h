#pragma once

// ステージシーンコマンドのインターフェース
// Commandパターンの基底クラス
class IStageSceneCommand {
public:
	// デストラクタ
	virtual ~IStageSceneCommand() = default;

	// コマンド実行（純粋仮想関数）
	virtual void Exec() = 0;
};
