#pragma once
#include <gueepo2d.h>

const float SCALE = 16.0f;

class Transform {
public:
	gueepo::math::Vector2 position;
	float rotation;
	gueepo::math::Vector2 scale;

	Transform() {
		position = gueepo::math::Vector2(0.0f, 0.0f);
		rotation = 0.0f;
		scale = gueepo::math::Vector2(1.0f, 1.0f);
	}

	gueepo::math::Matrix4 GetTransformMatrix() {
		return gueepo::math::Matrix4::CreateScale(scale)
			* gueepo::math::Matrix4::CreateRotation(rotation * gueepo::math::DEG_TO_RAD)
			* gueepo::math::Matrix4::CreateTranslation(position);
	}
};

class GameObject {
public:
	void Render(gueepo::Shader* shader, gueepo::VertexArray* va) {
		m_tex->Bind();
		gueepo::math::Matrix4 textureScale = gueepo::math::Matrix4::CreateScale(gueepo::math::Vector2(SCALE, SCALE));
		gueepo::math::Matrix4 transform = textureScale * (m_Transform.GetTransformMatrix());
		shader->SetMat4("u_Transform", transform);
		gueepo::Renderer::Submit(va, shader);
	}

	void SetPosition(gueepo::math::Vector2 position) {
		m_Transform.position = position;
	}

	void SetTexture(gueepo::Texture* t) {
		m_tex = t;
	}

	void Translate(float dx, float dy) {
		m_Transform.position.x += dx;
		m_Transform.position.y += dy;
	}

	void Translate(gueepo::math::Vector2 delta) {
		Translate(delta.x, delta.y);
	}

private:
	Transform m_Transform;
	gueepo::Texture* m_tex;
};