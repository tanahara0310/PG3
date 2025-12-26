#pragma once
#include "ICommand.h"

class Player;

class MoveRightCommand : public ICommand {
public:
	void Exec(Player& player) override;
};

class MoveLeftCommand : public ICommand {
public:
	void Exec(Player& player) override;
};
