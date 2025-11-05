#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <algorithm>

using namespace std;

// 判定関数 ShowResult
void ShowResult(int roll, int userGuess) {
	// 出目とユーザーの入力を比較
	// 奇数なら roll % 2 == 1、偶数なら roll % 2 == 0
	bool isOdd = (roll % 2 == 1);
	bool userGuessedOdd = (userGuess == 1);
	
	if (isOdd == userGuessedOdd) {
		cout << "出目は" << roll << " でした。「正解」" << endl;
	} else {
		cout << "出目は" << roll << " でした。「不正解」" << endl;
	}
}

// 遅延実行関数 DelayReveal
void DelayReveal(void (*fn)(int, int), unsigned int delayMs, int roll, int userGuess) {
	this_thread::sleep_for(chrono::milliseconds(delayMs));
	
	fn(roll, userGuess);
}

int main() {
	// srand() で乱数初期化
	srand((unsigned)time(NULL));
	
	// 入力（1 or 0）
	int userGuess;
	cout << "丁(偶数)か半(奇数)か予想してください (丁=1, 半=0): ";
	scanf_s("%d", &userGuess);
	
	// rand() で出目を生成
	int roll = rand() % 6 + 1;  // 1~6の乱数を生成
	
	//3秒後に結果表示
	DelayReveal(ShowResult, 3000, roll, userGuess);
	
	return 0;
}