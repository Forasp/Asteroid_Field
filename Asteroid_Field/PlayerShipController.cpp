#include "PlayerShipController.h"
#include "AsteroidGame.h";
#include "Message.h"

void PlayerShipController::InitializeController()
{
	AttachToMessenger(mGame->GetMessenger("MouseEvents"));
}

void PlayerShipController::ReadMessage(Message* _Message)
{
	// If message is a mouse event
	if (_Message->GetMessageType() == MESSAGE_TYPE_MOUSE && _Message->GetMessageString().compare("LeftPressed") == 0)
	{
		std::pair<double, double>* ObjectPosition = &mObject->GetPosition();
		std::pair<double, double>* MousePosition = &_Message->GetMessageDoublePair();
		std::pair<double, double> NormalizedUnitVector;

		// Normalize difference
		double TotalDistance = abs(ObjectPosition->first - MousePosition->first) + abs(ObjectPosition->second - MousePosition->second);
		NormalizedUnitVector.first = (ObjectPosition->first - MousePosition->first) / TotalDistance;
		NormalizedUnitVector.second = (ObjectPosition->second - MousePosition->second) / TotalDistance;

		double Rotation = atan2(NormalizedUnitVector.second, NormalizedUnitVector.first) * 180.0 / 3.141592;

		// Queue Message
		if (mGame != nullptr)
		{
			mGame->QueueMessage("GameEvents", std::make_unique<Message>(MESSAGE_TYPE_FULL, "FireBullet", Rotation, NormalizedUnitVector));
		}
	}
	
	// Spawn a bullet, set its velocity, and update our based on mouse position.

};