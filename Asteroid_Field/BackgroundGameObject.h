#pragma once
#include "GameObject.h"
#include "Collidable.h"

class BackgroundGameObject : public GameObject
{
public:
	BackgroundGameObject(Game* _Game) : GameObject(_Game) { InitializeGameObject(); }
	void RenderTick(sf::RenderWindow* _RenderWindow) {};
	void InitializeGameObject(void);
};
