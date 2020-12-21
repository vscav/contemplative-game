#pragma once

#ifndef _Trackball_HPP_
#define _Trackball_HPP_

#include <engine/Camera.hpp>

namespace engine
{

    // camera distance to the plane (size of the plane on screen)
    constexpr float cameraDistanceToFollowedObject = 5.0f;
    // camera distance to the plane (size of the plane on screen)
    constexpr float maximumDistance = -3.0f;
    constexpr float minimumDistance = -10.0f;

    /// \class TrackballCamera
    /// \brief Class for creating a trackball camera object, which is an implementation of the abstract base class Camera.
    class TrackballCamera : public Camera
    {
    private:
        float m_distance; /*!< The camera distance. */

        float m_angleX = 0.0f; /*!< The horizontal angle. */
        float m_angleY = 0.0f; /*!< The vertical angle. */

        float m_zoom; /*!< The camera zoom. */

        float m_sensitivity = 0.01f; /*!< The camera sensitivity. */

        float m_speed = 0.7f; /*!< The camera speed. */

        float m_lerpFactor = 0.995f; /*!< The camera rotation lerp factor. */

        float m_angleXSpeed = 0.0f; /*!< The camera horizontal angle speed. */
        float m_angleYSpeed = 0.0f; /*!< The camera vertical angle speed. */

        float m_fov = 70.0f;       /*!< The camera field of view. */
        float m_nearPlane = 0.1f;  /*!< The camera near plane. */
        float m_farPlane = 500.0f; /*!< The camera far plane. */

    public:
        /// \brief Constructor.
        TrackballCamera();
        /// \brief Destructor.
        ~TrackballCamera() override = default;

        /// \brief Zoom in and out (exclusive Trackball Camera feature).
        /// \param delta : The value of the zoom.
        void moveFront(float delta) override;
        /// \brief Moves the camera to the right or to the left according to the t value.
        /// \param t : The value used to move the camera on the right or on the left.
        // void moveLeft(float t) override;
        void moveLeft(float t) override;

        /// \brief Rotates the camera on the horizontal axis.
        /// \param degrees : The value of the rotation in degree.
        void rotateLeft(float degrees) override;
        /// \brief Rotates the camera on the vertical axis.
        /// \param degrees : The value of the rotation in degree.
        void rotateUp(float degrees) override;

        /// \brief Sets the camera sensitivity value.
        /// \param sensitivity : The value representing the speed apply to the camera.
        inline void setSensitivity(const float sensitivity) override { m_sensitivity = sensitivity; };
        /// \brief Sets the camera sensitivity value.
        /// \param sensitivity : The value representing the speed apply to the camera.
        inline float getSensitivity() const override { return m_sensitivity; };

        /// \brief Sets the camera speed value.
        /// \param speed : The value representing the speed apply to the camera.
        inline void setSpeed(const float speed) override { m_speed = speed; };
        /// \brief Gets the camera speed value.
        /// \return The current speed of the camera.
        inline float getSpeed() const override { return m_speed; };

        /// \brief Calculates and get the view matrix of the camera based on its member variables.
        /// \return The view matrix of the camera.
        glm::mat4 getViewMatrix() const override;
        /// \brief Calculates and get the projection matrix of the camera based on its member variables.
        /// \return The projection matrix of the camera.
        glm::mat4 getProjectionMatrix() const override;
        /// \brief Calculates and get the view projection matrix of the camera based on the view and the projection matrices.
        /// \return The view projection matrix of the camera.
        glm::mat4 getVPMatrix() const override;

        // /// \brief Updates the camera zoom.
        void update(float dt);
    };

} // namespace engine

#endif /* _Trackball_HPP_ */