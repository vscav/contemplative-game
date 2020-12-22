#include <engine/TrackballCamera.hpp>
#include <engine/GLApplication.hpp>
#include <engine/utils/common.hpp>

#include <iostream>

namespace engine
{

    TrackballCamera::TrackballCamera()
        : m_distance(-cameraDistanceToFollowedObject), m_angleX(0.0f), m_angleY(0.0f), m_zoom(-cameraDistanceToFollowedObject)
    {
        if (debug)
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

    void TrackballCamera::moveLeft(const float t)
    {
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

        std::cout << m_position << std::endl;

        // Zoom
        ViewMatrix = glm::translate(ViewMatrix, m_position);

        // Rotation
        ViewMatrix = glm::rotate(ViewMatrix, glm::radians(m_angleX), glm::vec3(1, 0, 0));
        ViewMatrix = glm::rotate(ViewMatrix, glm::radians(m_angleY), glm::vec3(0, 1, 0));

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

    void TrackballCamera::update(float dt)
    {
        m_position = (GLApplication::getInstance().getScene()->player()->getPosition());
        m_position.z += m_distance;

        // Update angles
        m_angleX += m_angleXSpeed * dt;
        m_angleY += m_angleYSpeed * dt;

        m_angleXSpeed *= std::pow(m_lerpFactor, dt);
        m_angleYSpeed *= std::pow(m_lerpFactor, dt);

        // Update distance
        m_distance = glm::mix(m_distance, m_zoom, 1 / 8.0f);
    }

} // namespace engine