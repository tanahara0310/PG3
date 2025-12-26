#include "TitleScene.h"
#include <Novice.h>

TitleScene::TitleScene() : isFinished_(false), nextScene_(SceneType::Title) {
}

void TitleScene::Update(char* keys, char* preKeys) {
	if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
		isFinished_ = true;
		nextScene_ = SceneType::Stage;
	}
}

void TitleScene::Draw() {
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x111111FF, kFillModeSolid);
	Novice::ScreenPrintf(10, 10, "Scene: TITLE");
	Novice::ScreenPrintf(500, 350, "Press SPACE to Start");
}

SceneType TitleScene::GetNextScene() const {
	return nextScene_;
}

bool TitleScene::IsFinished() const {
	return isFinished_;
}
