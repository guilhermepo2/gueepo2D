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
		// TODO: translate(ds)
		// TODO: set scale sign

		math::mat4 GetTransformMatrix() {
			return math::mat4::CreateScale(scale)
				* math::mat4::CreateRotation(rotation * math::DEG_TO_RAD)
				* math::mat4::CreateTranslation(position);
		}
	};
}