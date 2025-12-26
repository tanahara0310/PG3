#pragma once
#include "Command.h"

class ICommand;

class InputHandler {
public:
	ICommand* HandleInput();
	
	void AssignMoveLeftCommand2PressKeyA();
	void AssignMoveRightCommand2PressKeyD();

private:
	ICommand* pressKeyD_ = nullptr;
	ICommand* pressKeyA_ = nullptr;
};
