#pragma once
#include "core/Common.h"

namespace gueepo {
	class Entity;
	struct InputState;
	
	class Component {
	public:
		Entity* Owner = nullptr;
		Component() {}
		virtual ~Component() {}
		virtual void Initialize() {}
		virtual void BeginPlay() {}
		virtual bool ProcessInput(const InputState& CurrentInputState) { unreferenced(CurrentInputState); return false; }
		virtual void Update(float DeltaTime) { unreferenced(DeltaTime); }
		virtual void Render() {}
		virtual void Destroy() {};
	};
}