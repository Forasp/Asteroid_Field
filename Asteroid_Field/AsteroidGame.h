#pragma once

#include "Game.h"

class AsteroidGame : public Game
{
public:
	AsteroidGame(sf::RenderWindow* _RenderWindow) : Game(_RenderWindow){mCurrentWorld = GetNewWorld();}
	std::shared_ptr<World> GetNewWorld();
};