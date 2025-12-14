#pragma once

/// @brief 形状を表すインターフェース
class IShape {
public:

	// 面積を求める
	virtual void Size() = 0;

	/// @brief 形状の面積を表示する
	virtual void Draw() = 0;

	/// @brief 仮想デストラクタ
	virtual ~IShape() {}

};