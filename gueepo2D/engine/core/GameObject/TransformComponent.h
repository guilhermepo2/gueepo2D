#pragma once
#include "Component.h"
#include "core/math/Math.h"

namespace gueepo {
	class TransformComponent : public Component {
	public:
		math::vec2 position;
		float rotation = 0.0f;
		math::vec2 scale;

		TransformComponent() {
			position = math::vec2(0.0f, 0.0f);
			scale = math::vec2(1.0f, 1.0f);
		}

		TransformComponent(const math::vec2& _position, const float& _rotation, const math::vec2& _scale) : position(_position), rotation(_rotation), scale(_scale) {}

		// TODO: rotate(ds)
		// TODO: set scale sign

		void SetPosition(float x, float y) {
			position.x = x;
			position.y = y;
		}

		void SetPosition(math::vec2 pos) { SetPosition(pos.x, pos.y); }

		void Translate(float dx, float dy) {
			position.x += dx;
			position.y += dy;
		}
		
		void Translate(math::vec2 ds) { Translate(ds.x, ds.y); }

		void SetScale(float x, float y) {
			scale.x = x;
			scale.y = y;
		}

		void SetScale(math::vec2 scale) { SetScale(scale.x, scale.y); }

		math::mat4 GetTransformMatrix() {
			return math::mat4::CreateScale(scale)
				* math::mat4::CreateRotation(rotation * math::DEG_TO_RAD)
				* math::mat4::CreateTranslation(position);
		}
	};
}