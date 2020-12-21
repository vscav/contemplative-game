#pragma once
#ifndef _Camera_HPP_
#define _Camera_HPP_

#include <engine/dependencies/glm.hpp>

namespace engine
{

    /// \class Camera
    /// \brief Class for managing the creation of a camera. This class should be inherited from to create
    /// specific implementations (freefly, trackball, etc.).
    class Camera
    {
    public:
        /// \brief Destructor. This is needed so that the class inheriting this will have its destructor called.
        virtual ~Camera() = default;

        /// \brief Moves the camera forward or backward according to a certain value.
        /// \param t : The value used to move the camera forward or back.
        virtual void moveFront(float t) = 0;
        /// \brief Moves the camera to the right or to the left according to the t value.
        /// \param t : The value used to move the camera on the right or on the left.
        virtual void moveLeft(float t) = 0;

        /// \brief Rotates the camera to the right or to the left according to the degree value.
        /// \param degrees : The value (in degrees) used to move the camera on the right or on the left.
        virtual void rotateLeft(float degrees) = 0;
        /// \brief Rotates the camera to the top or the bottom according to the degree value.
        /// \param degrees : The value (in degrees) used to move the camera to the top or to the bottom.
        virtual void rotateUp(float degrees) = 0;

        /// \brief Sets the camera sensitivity value.
        /// \param sensitivity : The value representing the speed apply to the camera.
        virtual void setSensitivity(const float sensitivity) = 0;
        /// \brief Sets the camera sensitivity value.
        /// \param sensitivity : The value representing the speed apply to the camera.
        virtual float getSensitivity() const = 0;

        /// \brief Sets the camera speed value.
        /// \param speed : The value representing the speed apply to the camera.
        virtual inline void setSpeed(const float speed) = 0;
        /// \brief Gets the camera speed value.
        /// \return The current speed of the camera.
        virtual inline float getSpeed() const = 0;

        /// \brief Calculates and get the view matrix of the camera based on its member variables.
        /// \return The view matrix of the camera.
        virtual glm::mat4 getViewMatrix() const = 0;
        /// \brief Calculates and get the projection matrix of the camera based on its member variables.
        /// \return The projection matrix of the camera.
        virtual glm::mat4 getProjectionMatrix() const = 0;
        /// \brief Calculates and get the view projection matrix of the camera based on the view and the projection matrices.
        /// \return The view projection matrix of the camera.
        virtual glm::mat4 getVPMatrix() const = 0;

        virtual void update(float dt) = 0;

        // /// \brief Gets the current position of the camera.
        // /// \return The position of the camera.
        // virtual glm::vec3 const getPosition() const = 0;
    };

} // namespace engine

#endif /* _Camera_HPP_ */