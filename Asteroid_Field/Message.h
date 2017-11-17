#pragma once
#include <string>

#define MESSAGE_TYPE_INVALID	-1
#define MESSAGE_TYPE_STRING		1
#define MESSAGE_TYPE_DOUBLE		2
#define MESSAGE_TYPE_INPUT		3
#define MESSAGE_TYPE_QUIT		4
#define MESSAGE_TYPE_MOUSE		5
#define MESSAGE_TYPE_FULL		6
#define MESSAGE_TYPE_EVENT		7
#define MESSAGE_TYPE_COLLISION_PTR		8

#define COLLISION_WITH_SELF 1
#define RESTART_LEVEL 2
#define TICK_EVENT 3

class Message
{
public:
	Message(int _MessageType, std::string _MessageString, double _MessageDouble, std::pair<double, double> _DoublePair, bool _Consumable = false);
	Message(int _MessageType, std::string _MessageString, double _MessageDouble, bool _Consumable = false);
	Message(int _MessageType, std::string _MessageString, std::pair<double, double> _DoublePair, bool _Consumable = false);
	Message(int _MessageType, std::string _MessageString, bool _Consumable = false);
	Message(int _MessageType, std::pair<double, double> _DoublePair, bool _Consumable = false);
	Message(int _MessageType, double _MessageDouble, bool _Consumable = false);
	Message(int _MessageType, void* _VoidPtr, bool _Consumable = false) : mMessageType(_MessageType), mMessageVoidPtr(_VoidPtr), mConsumable(_Consumable) { mConsumed = false; };
	~Message() {}

	void Consume();
	void SetConsumable(bool _Consumable);
	int GetMessageType();
	std::string GetMessageString();
	double GetMessageDouble();
	std::pair<double, double> GetMessageDoublePair();
	void* GetMessageVoidPtr() { return mMessageVoidPtr; }

protected:
	bool mConsumed;
	bool mConsumable;

	int mMessageType;

	std::string mMessageString;

	double mMessageDouble;

	std::pair<double, double> mMessageDoublePair;

	void* mMessageVoidPtr;
};