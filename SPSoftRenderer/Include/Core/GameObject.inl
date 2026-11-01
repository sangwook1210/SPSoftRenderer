#pragma once

#include <type_traits>

template<typename T>
T* GameObject::AddComponent()
{
	//_todo 하나만 존재해야 하는 Component 목록 분리
	// 게임오브젝트 내에 하나만 존재해야하는 Component일 경우
	if constexpr (std::is_same_v<T, Transform>
		)
	{
		T* result = nullptr;

		// 이미 존재하는지 검사
		for (auto iter = components.begin();
			iter != components.end(); ++iter)
		{
			Component* component = iter->get();

			result = dynamic_cast<T*>(component);

			if (result != nullptr)
				break;
		}

		// 존재할 경우 추가하지 않음 
		if (result != nullptr)
			return nullptr;

		// 존재하지 않을 경우 추가
		auto newComponent = std::make_unique<T>();
		newComponent->gameObject = this;
		result = newComponent.get();
		
		components.push_back(std::move(newComponent));

		return result;

	}

	// 평범한 Component일 경우 추가
	else
	{
		auto newComponent = std::make_unique<T>();
		newComponent->gameObject = this;
		T* result = newComponent.get();
		components.push_back(std::move(newComponent));

		return result;
	}

	return nullptr;
}

template<typename T>
T* GameObject::GetComponent()
{
	for (auto iter = components.begin();
		iter != components.end(); ++iter)
	{
		Component* component = iter->get();

		T* result = dynamic_cast<T*>(component);

		if (result != nullptr)
		{
			return result;
		}
	}

	return nullptr;
}