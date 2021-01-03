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

    constexpr float runSpeed = 0.1f;    /*!< */
    constexpr float turnSpeed = 0.025f; /*!< */
    constexpr float upSpeed = 0.025f;   /*!< */

    constexpr float minimumPlayerUp = -10.0f; /*!< */
    constexpr float maximumPlayerUp = 10.0f;  /*!< */

    class Player : public Entity
    {
    protected:
        unsigned int m_score; /*!< */

        float m_currentSpeed = 0.0f;     /*!< */
        float m_currentTurnSpeed = 0.0f; /*!< */
        float m_currentUpspeed = 0.0f;   /*!< */

    public:
        /// \brief
        /// \param model : The GLTF model of the obstacle.
        /// \param shader : The shader to use for the obstacle.
        /// \param isStatic : Whether the obstacle is able to move.
        /// \param transform : The initial transformation to apply to the obstacle.
        Player(Model *model,
               Shader *shader,
               const bool isStatic = false,
               const Transform &transform = Transform());
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