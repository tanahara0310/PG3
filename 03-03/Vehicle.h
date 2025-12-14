#pragma once

/// @brief 乗り物を表す基底クラス
class Vehicle {
public:
	/// @brief 乗り物を移動させる純粋仮想関数
	virtual void Move() = 0;

	/// @brief 仮想デストラクタ
	virtual ~Vehicle() {}
};