#pragma once
#include "core/math/Vector3.h"
#include "core/math/Matrix4.h"
#include "Color.h"

namespace gueepo {

	class OrtographicCamera {
	public:
		math::Matrix4 ViewProjection() {
			return m_cameraProjection * m_cameraView;
		}

		OrtographicCamera(float width, float height);

		const math::Vector3& GetPosition() const { return m_cameraPosition; }
		void SetPosition(const math::Vector3 position) { m_cameraPosition = position; RecalculateViewMatrix(); }

		const Color& GetBackGroundColor() const { return m_cameraBackgroundColor; }
		void SetBackgroundColor(float r, float g, float b, float a) {
			m_cameraBackgroundColor.rgba[0] = r;
			m_cameraBackgroundColor.rgba[1] = g;
			m_cameraBackgroundColor.rgba[2] = b;
			m_cameraBackgroundColor.rgba[3] = a;
		}

		const math::Matrix4 GetView() const { return m_cameraView; }
		const math::Matrix4 GetProjectionMatrix() const { return m_cameraProjection; }
		const math::Matrix4 GetViewProjectionMatrix() const { return m_cameraViewProjection; }
		const math::Matrix4 GetTransform() const { return m_cameraTransform; }

	private:
		void RecalculateViewMatrix();
	private:
		Color m_cameraBackgroundColor;
		math::Vector3 m_cameraPosition;
		math::Matrix4 m_cameraTransform;

		math::Matrix4 m_cameraView;
		math::Matrix4 m_cameraProjection;
		math::Matrix4 m_cameraViewProjection;
	};
}