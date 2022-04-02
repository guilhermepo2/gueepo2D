#pragma once
#include "Component.h"
#include "core/math/Math.h"

namespace gueepo {
	class TransformComponent : public Component {
	public:
		math::Vector2 position;
		float rotation = 0.0f;
		math::Vector2 scale;

		TransformComponent() {
			position = math::Vector2(0.0f, 0.0f);
			scale = math::Vector2(1.0f, 1.0f);
		}

		TransformComponent(const math::Vector2& _position, const float& _rotation, const math::Vector2& _scale) : position(_position), rotation(_rotation), scale(_scale) {}

		// TODO: rotate(ds)
		// TODO: translate(ds)
		// TODO: set scale sign

		math::Matrix4 GetTransformMatrix() {
			return math::Matrix4::CreateScale(scale)
				* math::Matrix4::CreateRotation(rotation * math::DEG_TO_RAD)
				* math::Matrix4::CreateTranslation(position);
		}
	};
}