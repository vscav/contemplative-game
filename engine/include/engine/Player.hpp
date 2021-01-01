#pragma once
#ifndef _Player_HPP_
#define _Player_HPP_

#include <engine/Entity.hpp>
#include <engine/Obstacle.hpp>
#include <engine/Collectable.hpp>

namespace engine
{
    class Obstacle;

    constexpr glm::vec3 defaultPlayerPosition = glm::vec3(0.0f, 0.0f, 0.0f); /*!< */

    constexpr float runSpeed = 0.25f; /*!< */
    constexpr float turnSpeed = 0.05f; /*!< */
    constexpr float upSpeed = 0.15f; /*!< */

    constexpr float minimumPlayerUp = 1.0f; /*!< */
    constexpr float maximumPlayerUp = 10.0f; /*!< */

    class Player : public Entity
    {
    protected:
        unsigned int m_score; /*!< */

        float m_currentSpeed = 0.0f; /*!< */
        float m_currentTurnSpeed = 0.0f; /*!< */
        float m_currentUpspeed = 0.0f; /*!< */

    public:
        /// \brief
        Player(const Entity &playerEntity);
        /// \brief
        ~Player() = default;

        /// \brief
        void moveForward(int delta);
        /// \brief
        void moveLeft(int delta);
        /// \brief
        void moveUp(int delta);

        void move(const float dt);

        /// \brief
        void doCollisionWith(Entity &other);

        /// \brief
        void doCollisionWith(Obstacle &other);

        /// \brief
        void doCollisionWith(Collectable &other);

        /// \brief
        void update(const float dt);
    };

} // namespace engine

#endif /* _Player_HPP_ */