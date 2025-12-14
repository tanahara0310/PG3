#include <iostream>

/// @brief 2つの値の最小値を返すテンプレートクラス
/// @tparam T データ型
template<typename T>
class Min {
public:
	/// @brief 2つの値の最小値を返す
	T min(T a, T b) {
		return (a < b) ? a : b;
	}
};

int main() {

	// Min クラスのインスタンスを作成
	Min<int> minInt;
	Min<float> minFloat;
	Min<double> minDouble;

	std::cout << "Min<int>(10, 20) = " << minInt.min(10, 20) << std::endl;
	std::cout << "Min<int>(30, 15) = " << minInt.min(30, 15) << std::endl;

	std::cout << "Min<float>(3.14f, 2.71f) = " << minFloat.min(3.14f, 2.71f) << std::endl;
	std::cout << "Min<float>(1.5f, 2.5f) = " << minFloat.min(1.5f, 2.5f) << std::endl;

	std::cout << "Min<double>(5.678, 5.123) = " << minDouble.min(5.678, 5.123) << std::endl;
	std::cout << "Min<double>(9.999, 10.001) = " << minDouble.min(9.999, 10.001) << std::endl;

	return 0;
}
