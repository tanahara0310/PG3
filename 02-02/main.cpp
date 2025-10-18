#include <iostream>
#include <iomanip>

using namespace std;

// 再帰的貸金体系の時給を計算する関数
int calculateRecursiveWage(int hour) {
	if (hour == 1) {
		return 100;  // 最初の1時間は100円
	}
	// 前の時間の時給 * 2 - 50円
	return calculateRecursiveWage(hour - 1) * 2 - 50;
}

// 再帰的貸金体系の合計賃金を計算する関数
int calculateRecursiveTotalWage(int hours) {
	if (hours == 0) {
		return 0;
	}
	return calculateRecursiveTotalWage(hours - 1) + calculateRecursiveWage(hours);
}

int main() {
	cout << "========================================" << endl;
	cout << "株式会社かまとゥの貸金体系比較" << endl;
	cout << "========================================" << endl << endl;

	const int normalWage = 1226;  // 一般的貸金体系の時給

	cout << "一般的貸金体系: 時給 " << normalWage << "円（固定）" << endl;
	cout << "再帰的貸金体系: 最初は100円、次の1時間から「前の時給 * 2 - 50円」" << endl << endl;

	// 表のヘッダー
	cout << "========================================" << endl;
	cout << "【時間ごとの料金比較表】" << endl;
	cout << "========================================" << endl;
	cout << setw(6) << "時間" << " | "
		<< setw(10) << "一般的貸金" << " | "
		<< setw(10) << "再帰的貸金" << " | "
		<< setw(6) << "差額" << " | "
		<< "状態" << endl;
	cout << "----------------------------------------" << endl;

	int hour = 1;
	bool exceeded = false;
	int normalTotal = 0;
	int recursiveTotal = 0;

	// 再帰的貸金が一般的貸金を上回るまでループ
	while (!exceeded) {
		int recursiveWage = calculateRecursiveWage(hour);
		int diff = recursiveWage - normalWage;

		normalTotal += normalWage;
		recursiveTotal += recursiveWage;

		// 時間、各時給、差額を表示
		cout << setw(4) << hour << "時間目 | "
			<< setw(8) << normalWage << "円 | "
			<< setw(8) << recursiveWage << "円 | ";

		if (diff > 0) {
			cout << setw(5) << "+" << diff << " | ";
			cout << "再帰的が上回る！" << endl;
			exceeded = true;
		} else {
			cout << setw(6) << diff << " | ";
			cout << "一般的が有利" << endl;
		}

		hour++;
	}

	cout << "========================================" << endl << endl;

	// 結果のまとめ
	int breakEvenHour = hour - 1;
	cout << "【結果】" << endl;
	cout << "再帰的貸金が一般的貸金を上回る時点: " << breakEvenHour << "時間目" << endl;
	cout << breakEvenHour << "時間目の時給: " << calculateRecursiveWage(breakEvenHour) << "円" << endl;
	cout << "一般的貸金との差額: +" << (calculateRecursiveWage(breakEvenHour) - normalWage) << "円" << endl;
	cout << endl;



	return 0;
}