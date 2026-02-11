#include <iostream>
#include <string>

using namespace std;

class Enemy {
public:
	// メンバ関数ポインタの型定義
	using StateFunction = void (Enemy::*)();

	Enemy() : currentState(&Enemy::Approach), stateName("接近") {
	}

	// 状態更新
	void Update() {
		if (currentState != nullptr) {
			(this->*currentState)(); // メンバ関数ポインタを使用して現在の状態を実行
		}
	}

	// 現在の状態名を取得
	string GetStateName() const {
		return stateName;
	}

private:
	// 状態：接近
	void Approach() {
		cout << "【接近】敵が近づいてきます..." << endl;
		// 次の状態へ遷移
		currentState = &Enemy::Shoot;
		stateName = "射撃";
	}

	// 状態：射撃
	void Shoot() {
		cout << "【射撃】敵が攻撃してきます！" << endl;
		// 次の状態へ遷移
		currentState = &Enemy::Retreat;
		stateName = "離脱";
	}

	// 状態：離脱
	void Retreat() {
		cout << "【離脱】敵が離れていきます..." << endl;
		// 最初の状態へ戻る
		currentState = &Enemy::Approach;
		stateName = "接近";
	}

	StateFunction currentState;  // 現在の状態を保持するメンバ関数ポインタ
	string stateName;    // 状態名
};

int main()
{
	Enemy enemy;

	cout << "\n=== 敵の状態遷移 ===" << endl;
	cout << "接近 → 射撃 → 離脱 のサイクルを繰り返します\n" << endl;

	// 状態遷移を複数回実行
	for (int i = 0; i < 9; ++i) {
		std::cout << "ターン " << (i + 1) << ": ";
		enemy.Update();
		cout << endl;
	}

	cout << "=== 終了 ===" << endl;

	return 0;
}