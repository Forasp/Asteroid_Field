#pragma once
#include "Controller.h"
#include "GameObject.h"

class PlayerShipController : public Controller
{
public:
	PlayerShipController(GameObject* _Object, Game* _Game = nullptr) : Controller(_Object, _Game)
	{
		InitializeController();
	}

	void ReadMessage(Message* _Message);

	void ControllerTick() {};

	void InitializeController();
};