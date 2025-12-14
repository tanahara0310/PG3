#pragma once
#include "Vehicle.h"

/// @brief 車を表す派生クラス
class Car : public Vehicle {
public:
	/// @brief 車を移動させる
	void Move() override;
};

