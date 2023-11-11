#include "OrtographicCamera.h"

namespace gueepo {

	OrtographicCamera::OrtographicCamera(float width, float height) {
		m_cameraSize.x = width;
		m_cameraSize.y = height;

		m_cameraProjection = math::mat4::CreateOrtographicProjection(-(width / 2.0f), (width / 2.0f), -(height / 2.0f), (height / 2.0f), -1, 1);
		// m_cameraProjection = math::Matrix4::m4Identity;
		m_cameraPosition = math::vec3(0.0f, 0.0f, 0.0f);
		RecalculateViewMatrix();
	}

	void OrtographicCamera::RecalculateViewMatrix() {
		m_cameraTransform = math::mat4::CreateTranslation(m_cameraPosition);
		m_cameraView = math::mat4::CreateInverse(m_cameraTransform);
		// m_cameraView = math::Matrix4::m4Identity;
		m_cameraViewProjection = m_cameraProjection * m_cameraView;
	}

}