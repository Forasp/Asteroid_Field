#pragma once
#include "Controller.h"

class GameObject;
class Game;
class Message;

class AsteroidGameController : public Controller
{
public:
	AsteroidGameController(GameObject* _Object, Game* _Game = nullptr) : Controller(_Object, _Game)
	{

	}

	void ControllerTick() {};

	void ReadMessage(Message* _Message) {};
};
