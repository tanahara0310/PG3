#pragma once
#include "Vehicle.h"

/// @brief 自転車を表す派生クラス
class Bicycle : public Vehicle {
public:
	/// @brief 自転車を移動させる
	void Move() override;
};

