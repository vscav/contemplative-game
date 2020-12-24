#pragma once
#ifndef _Player_HPP_
#define _Player_HPP_

#include <engine/Entity.hpp>
#include <engine/Obstacle.hpp>

namespace engine
{
    class Obstacle;

    constexpr glm::vec3 defaultPlayerPosition = glm::vec3(0.0f, 0.0f, 10.0f);
    constexpr float defaultPlayerSpeed = 0.25f;

    constexpr float minimumPlayerUp = 1.0f;
    constexpr float maximumPlayerUp = 10.0f;

    class Player : public Entity
    {
    protected:
        float m_speed = defaultPlayerSpeed; /*!< The player current movement speed. */

        // float m_lerpFactor = 0.9f;
        // float m_lerpSpeed = 0.0f;
        // float m_sensitivity = 0.1f;

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

        /// \brief
        void doCollisionWith(Entity &other);

        /// \brief
        void doCollisionWith(Obstacle &other);

        /// \brief
        void update(const float dt);
    };

} // namespace engine

#endif /* _Player_HPP_ */