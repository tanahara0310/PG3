#pragma once
#include "IShape.h"

/// @brief 四角形を表すクラス
class Rectangle : public IShape {
public:

	// コンストラクタ
	Rectangle(float w, float h);
	// 面積を求める
	virtual void Size() override;
	/// @brief 形状の面積を表示する
	virtual void Draw() override;

private:

	float width;
	float height;
	float area;
};

