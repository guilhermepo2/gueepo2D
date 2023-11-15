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

    void OrtographicCamera::TranslateCameraInPixels(int x, int y) {
        // here's how the camera works...the camera maps the screen size in between -1 and 1 (so, 2)
        // so if the camera is, let's say, 1.0 moved to the x it moved 320 pixels (if the screen is 640 pixels) to the x
        // if the width is 640, I have to move 0.1 for every 32 pixels on the position...
        // if position.x == 32, then cameraX = 0.1 - what's the math here?
        // 32 / 320 -> so position.x / halfWidth

        float halfWidth = m_cameraSize.x / 2.0f;
        float halfHeight = m_cameraSize.y / 2.0f;
        float cameraX = x / halfWidth;
        float cameraY = y / halfHeight;
        gueepo::math::vec3 CameraPosition = GetPosition();
        CameraPosition.x += cameraX;
        CameraPosition.y += cameraY;
        SetPosition(CameraPosition);
    }

    gueepo::math::vec2 OrtographicCamera::MouseToWorldPosition(gueepo::math::vec2 MousePosition) {
        gueepo::math::vec2 worldPosition(MousePosition.x, MousePosition.y);
        worldPosition.x -= (m_cameraSize.x / 2);
        worldPosition.y -= (m_cameraSize.y / 2);
        worldPosition.y = -worldPosition.y; // inverting because world is bottom up, mouse is originally top down

        // We have to account for having moved the camera
        gueepo::math::vec3 cameraPosition = GetPosition();
        int xInPixels = static_cast<int>((m_cameraSize.x * cameraPosition.x) / 2);
        int yInPixels = static_cast<int>((m_cameraSize.y * cameraPosition.y) / 2);
        worldPosition.x += xInPixels;
        worldPosition.y += yInPixels;

        return worldPosition;
    }

}