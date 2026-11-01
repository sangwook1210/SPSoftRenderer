#pragma once

class GameObject;	// 전방 선언

class Component
{
public:
	virtual ~Component() {};

	GameObject* gameObject = nullptr;
};

class TestComponent : public Component
{
public:
	float testValue = 0.0f;
};