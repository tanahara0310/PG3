#pragma once
#include "IScene.h"

class TitleScene : public IScene {
public:
	TitleScene();
	~TitleScene() override = default;

	void Update(char* keys, char* preKeys) override;
	void Draw() override;
	SceneType GetNextScene() const override;
	bool IsFinished() const override;

private:
	bool isFinished_;
	SceneType nextScene_;
};
