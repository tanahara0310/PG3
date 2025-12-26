#include <Novice.h>
#include <memory>
#include "IScene.h"
#include "TitleScene.h"
#include "StageScene.h"
#include "ClearScene.h"

const char kWindowTitle[] = "学籍番号";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// シーン管理
	SceneType currentSceneType = SceneType::Title;
	std::unique_ptr<IScene> currentScene = std::make_unique<TitleScene>();

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		currentScene->Update(keys, preKeys);

		// シーン遷移チェック
		if (currentScene->IsFinished()) {
			SceneType nextSceneType = currentScene->GetNextScene();

			switch (nextSceneType) {
			case SceneType::Title:
				currentScene = std::make_unique<TitleScene>();
				break;
			case SceneType::Stage:
				currentScene = std::make_unique<StageScene>();
				break;
			case SceneType::Clear:
				currentScene = std::make_unique<ClearScene>();
				break;
			}

			currentSceneType = nextSceneType;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		currentScene->Draw();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
