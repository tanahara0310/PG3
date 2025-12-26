#pragma once

enum class SceneType {
	Title,
	Stage,
	Clear
};

class IScene {
public:
	virtual ~IScene() = default;
	virtual void Update(char* keys, char* preKeys) = 0;
	virtual void Draw() = 0;
	virtual SceneType GetNextScene() const = 0;
	virtual bool IsFinished() const = 0;
};
