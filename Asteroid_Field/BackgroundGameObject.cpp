#include "BackgroundGameObject.h"
#include "Game.h"
#include "AsteroidGameController.h"
#include "Message.h"
#include "PlayerShipGameObject.h"

void BackgroundGameObject::InitializeGameObject()
{
	int ChildrenPosition = 0;
	// Add World Controller
	mController = std::make_shared<AsteroidGameController>(this, mGame);

	// Add Player Ship
	mChildren.push_back(std::make_shared<PlayerShipGameObject>(mGame));
	mChildren[ChildrenPosition]->SetPosition(std::pair<double, double>(512, 348));
	ChildrenPosition++;

	// Add Asteroids

	// Randomize Asteroid Positions, Sizes, and Velocities
}