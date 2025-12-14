#pragma once
#include "IShape.h"

/// @brief 円を表すクラス
class Circle : public IShape {
public:

	// コンストラクタ
	Circle(float r);

	// 面積を求める
	virtual void Size() override;

	/// @brief 形状の面積を表示する
	virtual void Draw() override;

private:

	float radius;
	float area;
};

