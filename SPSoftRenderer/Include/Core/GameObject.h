#pragma once

#include <vector>
#include <memory>

#include <Component/Component.h>
#include <Component/Transform.h>

class GameObject
{
private:
	std::vector<std::unique_ptr<Component>> components;

public:
	GameObject();
	~GameObject();

	Transform* transform = nullptr;

	template<typename T>
	T* AddComponent();
	template<typename T>
	T* GetComponent();


};

#include "GameObject.inl"