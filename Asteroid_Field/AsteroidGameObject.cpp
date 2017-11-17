#include "AsteroidGameObject.h"
#include "GlobalDefines.h"
#include "Game.h"
#include "Message.h"
#include "GlobalDefines.h"
#include "GameThreadUnsafeScope.h"
#include "BulletGameObject.h"

void AsteroidGameObject::RenderTick(sf::RenderWindow* _RenderWindow)
{
	mRenderShape.setRotation(mRotation - 45);
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

void AsteroidGameObject::Tick(sf::Time _DeltaTime)
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

void AsteroidGameObject::Collide(Collidable* _Collidable)
{
	if (_Collidable != nullptr)
	{
		AsteroidGameObject* OtherAsteroid;
		if ((OtherAsteroid = dynamic_cast<AsteroidGameObject*>(_Collidable)) == nullptr)
		{
			if (mParent != nullptr)
			{
				_Collidable->Collide(nullptr);
				mParent->RemoveChild(this);
			}
		}
		else
		{

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

void AsteroidGameObject::InitializeGameObject()
{
	mSize.first = (rand() % 90) + 10;
	mSize.second = mSize.first;
	mRotation = rand() % 360;
	mRenderShape = sf::CircleShape(mSize.first/2, 4);
	mRenderShape.setFillColor(sf::Color(255, 0, 0, 255));
	mRenderShape.setOrigin(mSize.first/2, mSize.first/2);
	mLayer = LAYER_GAME_SHIP;
	mGame->AddObjectToRenderer(this, mLayer);
	CreateCollider(&mPosition, &mSize, &mRotation);
}