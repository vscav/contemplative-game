#pragma once
#ifndef _Player_HPP_
#define _Player_HPP_

#include <engine/Entity.hpp>
#include <engine/Obstacle.hpp>
#include <engine/Collectable.hpp>

namespace engine
{
    class Obstacle;

    constexpr glm::vec3 defaultPlayerPosition = glm::vec3(0.0f, 0.0f, 0.0f);

    constexpr float runSpeed = 0.25f;
    constexpr float turnSpeed = 0.025f;
    constexpr float upSpeed = 0.15f;

    constexpr float minimumPlayerUp = -50.0f;
    constexpr float maximumPlayerUp = 50.0f;

    /// \class Player
    /// \brief Class that represents the player of the application.
    class Player : public Entity
    {
    protected:
        unsigned int m_score; /*!< The current score of the player. */

        float m_currentSpeed = 0.0f;     /*!< The current speed of the player. */
        float m_currentTurnSpeed = 0.0f; /*!< The current turn speed of the player. */
        float m_currentUpspeed = 0.0f;   /*!< The current up and down speed of the player. */

    public:
        /// \brief Parameterized constructor.
        /// \param model : The GLTF model of the player.
        /// \param shader : The shader to use for the player.
        /// \param isStatic : Whether the player is able to move.
        /// \param transform : The initial transformation to apply to the player.
        Player(Model *model,
               Shader *shader,
               const bool isStatic = false,
               const Transform &transform = Transform());
        /// \brief Default destructor.
        ~Player() = default;

        /// \brief Moves the player forward/backward.
        /// \param delta : An int representing the direction.
        void moveForward(int delta);
        /// \brief Turns the player.
        /// \param delta : An int representing the direction.
        void moveLeft(int delta);
        /// \brief Moves the player up and down.
        /// \param delta : An int representing the direction.
        void moveUp(int delta);

        /// \brief Moves the player.
        /// \param dt : The delta time, which describes the time difference between the previous frame that was drawn and the current frame.
        void move(const float dt);

        /// \brief Implements the collision behavior when colliding with an entity.
        /// \param other : An entity.
        void doCollisionWith(Entity &other);

        /// \brief Implements the collision behavior when colliding with an obstacle.
        /// \param other : An obstacle.
        void doCollisionWith(Obstacle &other);

        /// \brief Implements the collision behavior when colliding with a collectable.
        /// \param other : A collectable.
        void doCollisionWith(Collectable &other);

        /// \brief Updates the player.
        /// \param dt : The delta time, which describes the time difference between the previous frame that was drawn and the current frame.
        void update(const float dt);
    };

} // namespace engine

#endif /* _Player_HPP_ */