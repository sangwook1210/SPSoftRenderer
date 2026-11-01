#include "Core/GameObject.h"


GameObject::GameObject()
{
	auto tr = std::make_unique<Transform>();
	transform = tr.get();
	components.push_back(std::move(tr));
}

GameObject::~GameObject()
{

}