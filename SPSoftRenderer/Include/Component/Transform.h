#pragma once

#include "Component/Component.h"
#include "Math/Vector3.h"

class Transform : Component
{
public:
	Vector3 position;	// 위치
	Vector3 rotation;	// z축 회전
	Vector3 scale;	// 크기


};