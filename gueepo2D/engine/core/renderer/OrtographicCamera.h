#pragma once
#include "core/math/vec3.h"
#include "core/math/mat4.h"
#include "Color.h"

namespace gueepo {

	class OrtographicCamera {
	public:
		math::mat4 ViewProjection() {
			return m_cameraProjection * m_cameraView;
		}

		OrtographicCamera(float width, float height);

		const math::vec2 GetSize() const { return m_cameraSize; }
		const math::vec3& GetPosition() const { return m_cameraPosition; }
		void SetPosition(const math::vec3 position) { m_cameraPosition = position; RecalculateViewMatrix(); }

		const Color& GetBackGroundColor() const { return m_cameraBackgroundColor; }
		void SetBackgroundColor(float r, float g, float b, float a) {
			m_cameraBackgroundColor.rgba[0] = r;
			m_cameraBackgroundColor.rgba[1] = g;
			m_cameraBackgroundColor.rgba[2] = b;
			m_cameraBackgroundColor.rgba[3] = a;
		}

		const math::mat4 GetView() const { return m_cameraView; }
		const math::mat4 GetProjectionMatrix() const { return m_cameraProjection; }
		const math::mat4 GetViewProjectionMatrix() const { return m_cameraViewProjection; }
		const math::mat4 GetTransform() const { return m_cameraTransform; }

	private:
		void RecalculateViewMatrix();
	private:
		Color m_cameraBackgroundColor;
		math::vec2 m_cameraSize;
		math::vec3 m_cameraPosition;
		math::mat4 m_cameraTransform;

		math::mat4 m_cameraView;
		math::mat4 m_cameraProjection;
		math::mat4 m_cameraViewProjection;
	};
}