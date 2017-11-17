#include "PlayerShipGameObject.h"
#include "Game.h"
#include "Message.h"
#include "GlobalDefines.h"
#include "PlayerShipController.h"
#include "AsteroidGameObject.h"
#include "BulletGameObject.h"
#include "GameThreadUnsafeScope.h"

void PlayerShipGameObject::RenderTick(sf::RenderWindow* _RenderWindow) 
{
	mRenderShape.setRotation(mRotation - 90);
	mRenderShape.setScale(1, 2);
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

void PlayerShipGameObject::Tick(sf::Time _DeltaTime)
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

void PlayerShipGameObject::Collide(Collidable* _Collidable)
{
	AsteroidGameObject* AsteroidObject;
	if (_Collidable != nullptr && (AsteroidObject = dynamic_cast<AsteroidGameObject*>(_Collidable)) != nullptr)
	{
		// Queue Message
		if (mGame != nullptr)
		{
			mGame->QueueMessage("GlobalEvents", std::make_unique<Message>(MESSAGE_TYPE_DOUBLE, RESTART_LEVEL));
		}
	}
}

void PlayerShipGameObject::InitializeGameObject()
{
	AttachToMessenger(mGame->GetMessenger("GameEvents"));
	mRenderShape = sf::CircleShape(20, 3);
	mRenderShape.setFillColor(sf::Color(0, 0, 0, 0));
	mRenderShape.setOutlineColor(sf::Color(255, 255, 255, 255));
	mRenderShape.setOutlineThickness(2);
	mRenderShape.setOrigin(20, 20);
	mLayer = LAYER_GAME_SHIP;
	mGame->AddObjectToRenderer(this, mLayer);
	mController = std::make_shared<PlayerShipController>(this, mGame);
	CreateCollider(&mPosition, &mSize, &mRotation);
	mSize = std::pair<double, double>(40, 40);
}

void PlayerShipGameObject::HandleMessage(Message* _Message)
{
	if (_Message->GetMessageType() == MESSAGE_TYPE_FULL)
	{
		if (_Message->GetMessageString().compare("FireBullet") == 0)
		{
			// Rotate ship
			SetRotation(_Message->GetMessageDouble());
			std::pair<double, double> Velocity = _Message->GetMessageDoublePair();
			Velocity.first *= 10.0;
			Velocity.second *= 10.0;
			AddVelocity(Velocity);

			std::shared_ptr<BulletGameObject> Bullet = std::make_shared<BulletGameObject>(mGame, (mParent != nullptr) ? mParent : this);
			Bullet->SetPosition(GetPosition());
			Bullet->SetRotation(GetRotation());
			Bullet->AddVelocity(std::pair<double, double>(GetVelocity().first + (Velocity.first * -10), GetVelocity().second + (Velocity.second * -10)));

			if (mParent != nullptr)
			{
				mParent->AddChild(Bullet);
			}
			else
			{
				AddChild(Bullet);
			}
		}
	}
}