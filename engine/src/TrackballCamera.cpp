#include <engine/TrackballCamera.hpp>
#include <engine/GLApplication.hpp>
#include <engine/utils/common.hpp>

#include <iostream>

namespace engine
{

    TrackballCamera::TrackballCamera()
        : m_distance(-cameraDistanceToFollowedObject), m_angleX(0.0f), m_angleY(0.0f), m_zoom(-cameraDistanceToFollowedObject)
    {
        if (applicationDebug)
            std::cout << "[Camera] Trackball camera created" << std::endl;
    }

    void TrackballCamera::moveFront(const float delta)
    {
        m_zoom += m_speed * delta;

        if (m_zoom > maximumDistance)
            m_zoom = maximumDistance;
        else if (m_zoom < minimumDistance)
            m_zoom = minimumDistance;
    }

    void TrackballCamera::rotateLeft(const float degrees)
    {
        m_angleYSpeed += m_sensitivity * degrees;

        // To avoid free movement
        // m_angleY = glm::clamp(m_angleY, -90.0f, 90.0f);
    }

    void TrackballCamera::rotateUp(const float degrees)
    {
        m_angleXSpeed += m_sensitivity * degrees;

        // To avoid free movement
        // m_angleX = glm::clamp(m_angleX, 0.0f, 90.0f);
    }

    glm::mat4 TrackballCamera::getViewMatrix() const
    {
        glm::mat4 ViewMatrix = glm::mat4(1);

        // Translate to be away from the center of rotation
        ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0, 0, m_distance));

        // Rotation
        ViewMatrix = glm::rotate(ViewMatrix, glm::radians(m_angleX), glm::vec3(1, 0, 0));
        ViewMatrix = glm::rotate(ViewMatrix, glm::radians(m_angleY), glm::vec3(0, 1, 0));

        // Translate from its position
        ViewMatrix = glm::translate(ViewMatrix, -m_position);

        return ViewMatrix;
    }

    glm::mat4 TrackballCamera::getProjectionMatrix() const
    {
        auto width = (float)GLApplication::getInstance().getWindowManager()->getWidth();
        auto height = (float)GLApplication::getInstance().getWindowManager()->getHeight();

        return glm::perspective(glm::radians(m_fov), width / height, m_nearPlane, m_farPlane);
    }

    glm::mat4 TrackballCamera::getVPMatrix() const
    {
        return getProjectionMatrix() * getViewMatrix();
    }

    void TrackballCamera::updatePosition(const glm::vec3 position) {
        m_position = position;
    }

    glm::vec3 TrackballCamera::getPosition() const 
    {
      return m_position;
    }

    void TrackballCamera::update(float dt)
    {
        // Update angles
        m_angleX += m_angleXSpeed * dt * 100;
        m_angleY += m_angleYSpeed * dt * 100;

        // Update angles speed
        m_angleXSpeed *= std::pow(m_lerpFactor, dt * 100);
        m_angleYSpeed *= std::pow(m_lerpFactor, dt * 100);

        // Update distance based on zoom
        m_distance = glm::mix(m_distance, m_zoom, 1 / 8.0f);
    }

} // namespace engine
