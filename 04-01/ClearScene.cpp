#include "ClearScene.h"
#include <Novice.h>

ClearScene::ClearScene() : isFinished_(false), nextScene_(SceneType::Clear) {
}

void ClearScene::Update(char* keys, char* preKeys) {
	if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
		isFinished_ = true;
		nextScene_ = SceneType::Title;
	}
}

void ClearScene::Draw() {
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x003300FF, kFillModeSolid);
	Novice::ScreenPrintf(10, 10, "Scene: CLEAR");
	Novice::ScreenPrintf(500, 350, "GAME CLEAR!");
	Novice::ScreenPrintf(450, 400, "Press SPACE to Return to Title");
}

SceneType ClearScene::GetNextScene() const {
	return nextScene_;
}

bool ClearScene::IsFinished() const {
	return isFinished_;
}
