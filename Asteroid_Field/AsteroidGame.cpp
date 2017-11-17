#include "AsteroidGame.h"
#include "AsteroidWorld.h"
#include "Message.h"

std::shared_ptr<World> AsteroidGame::GetNewWorld()
{
	return std::make_shared<AsteroidWorld>(this);
}