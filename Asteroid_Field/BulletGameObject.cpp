#include "BulletGameObject.h"
#include "GlobalDefines.h"
#include "Game.h"
#include "Message.h"
#include "GlobalDefines.h"
#include "GameThreadUnsafeScope.h"
#include "PlayerShipGameObject.h"

void BulletGameObject::RenderTick(sf::RenderWindow* _RenderWindow) 
{
	mRenderShape.setRotation(mRotation - 90);
	mRenderShape.setPosition(mPosition.first, mPosition.second);
	_RenderWindow->draw(mRenderShape);

	// Render four times over, in each dimension.
	mRenderShape.setPosition(mPosition.first + 1024, mPosition.second);
	_RenderWindow->draw(mRenderShape);
	mRenderShape.setPosition(mPosition.first - 1024, mPosition.second);
	_RenderWindow->draw(mRenderShape);
	mRenderShape.setPosition(mPosition.first, mPosition.second + 768);
	_RenderWindow->draw(mRenderShape);
	mRenderShape.setPosition(mPosition.first, mPosition.second - 768);
	_RenderWindow->draw(mRenderShape);
}

void BulletGameObject::Tick(sf::Time _DeltaTime)
{
	GameObject::Tick(_DeltaTime);
	if (mPosition.first > 1024)
	{
		mPosition.first -= 1024;
	}
	else if (mPosition.first < 0)
	{
		mPosition.first += 1024;
	}
	if (mPosition.second > 768)
	{
		mPosition.second -= 768;
	}
	else if (mPosition.second < 0)
	{
		mPosition.second += 768;
	}
}

void BulletGameObject::Collide(Collidable* _Collidable)
{
	if (_Collidable != nullptr)
	{
		PlayerShipGameObject* PlayerShip;
		if ((PlayerShip = dynamic_cast<PlayerShipGameObject*>(_Collidable)) == nullptr)
		{
			if (mParent != nullptr)
			{
				_Collidable->Collide(nullptr);
				mParent->RemoveChild(this);
			}
		}
	}
	else
	{
		if (mParent != nullptr)
		{
			mParent->RemoveChild(this);
		}
	}
}

void BulletGameObject::InitializeGameObject()
{
	mRenderShape = sf::CircleShape(2, 4);
	mRenderShape.setFillColor(sf::Color(0, 255, 255, 255));
	mRenderShape.setOutlineColor(sf::Color(0, 255, 255, 255));
	mRenderShape.setOutlineThickness(2);
	mRenderShape.setOrigin(2, 2);
	mRenderShape.setScale(1, 3);
	mLayer = LAYER_GAME_SHIP;
	mGame->AddObjectToRenderer(this, mLayer);
	CreateCollider(&mPosition, &mSize, &mRotation);
	mSize = std::pair<double, double>(4, 4);
}


void BulletGameObject::CollisionBroadcast()
{
	mGame->QueueMessage("Collision", std::make_unique<Message>(Message(MESSAGE_TYPE_COLLISION_PTR, dynamic_cast<GameObject*>(this))));
}