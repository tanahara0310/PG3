#include "Circle.h"
#include "Rectangle.h"
#include <memory>

int main() {
	// Circleクラスのインスタンスを生成
	std::unique_ptr<IShape> circle = std::make_unique<Circle>(2.0f);
	// Rectangleクラスのインスタンスを生成
	std::unique_ptr<IShape> rectangle = std::make_unique<Rectangle>(3.0f, 4.0f);

	// 面積を計算して表示
	circle->Size();
	circle->Draw();

	rectangle->Size();
	rectangle->Draw();


	return 0;
}