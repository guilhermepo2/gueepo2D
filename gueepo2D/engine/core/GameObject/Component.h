#pragma once
#include "core/Common.h"

namespace gueepo {
	class Entity;
	struct InputState;
	class SpriteBatcher;
	
	class Component {
	public:
		Entity* Owner = nullptr;
		Component() {}
		virtual ~Component() { Owner = nullptr; }
		virtual void Initialize() {}
		virtual void BeginPlay() {}
		virtual bool ProcessInput(const InputState& CurrentInputState) { unreferenced(CurrentInputState); return false; }
		virtual void Update(float DeltaTime) { unreferenced(DeltaTime); }
		virtual void Render(SpriteBatcher* batch) {}
		virtual void Destroy() {};
	};
}