#pragma once
#include "IScene.h"

class ClearScene : public IScene {
public:
	ClearScene();
	~ClearScene() override = default;

	void Update(char* keys, char* preKeys) override;
	void Draw() override;
	SceneType GetNextScene() const override;
	bool IsFinished() const override;

private:
	bool isFinished_;
	SceneType nextScene_;
};
