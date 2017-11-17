#pragma once
#include "World.h"

class Game;

class AsteroidWorld : public World
{
public:
	AsteroidWorld(Game* _Game) : World(_Game) { Initialize(); };
	void Initialize();
};