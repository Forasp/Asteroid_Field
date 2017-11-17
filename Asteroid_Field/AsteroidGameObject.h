#pragma once
#include "GameObject.h"
#include "Collidable.h"
#include "SFML/Graphics/CircleShape.hpp"

class AsteroidGameObject : public GameObject, public Collidable
{
public:
	AsteroidGameObject(Game* _Game, GameObject* _Parent = nullptr) : GameObject(_Game, _Parent) { InitializeGameObject(); }
	void RenderTick(sf::RenderWindow* _RenderWindow);
	void Tick(sf::Time _DeltaTime);
	void Collide(Collidable* _Collidable);
	void InitializeGameObject();
	void ReadMessage(Message* _Message) { GameObject::ReadMessage(_Message); Collidable::ReadMessage(_Message); }
protected:
	sf::CircleShape mRenderShape;
};
