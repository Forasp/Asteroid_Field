#include "AsteroidWorld.h"
#include "Game.h"
#include "Message.h"
#include "BackgroundGameObject.h"
#include "AsteroidGameObject.h"
#include "PlayerShipGameObject.h"
#include <memory>

void AsteroidWorld::Initialize()
{
	// Populate world here
	mWorldRoot = std::make_shared<BackgroundGameObject>(mGame);
}