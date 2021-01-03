#pragma once
#ifndef _Obstacle_HPP_
#define _Obstacle_HPP_

#include <engine/Entity.hpp>
#include <engine/Player.hpp>
#include <engine/utils/common.hpp>

namespace engine
{

    class Player;

    /// \class Obstacle
    /// \brief Class that represents an obstacle in the application.
    class Obstacle : public Entity
    {
    public:
        /// \brief Parameterized constructor.
        /// \param model : The GLTF model of the obstacle.
        /// \param shader : The shader to use for the obstacle.
        /// \param isStatic : Whether the obstacle is able to move.
        /// \param transform : The initial transformation to apply to the obstacle.
        Obstacle(Model *model,
                 Shader *shader,
                 const bool isStatic = false,
                 const Transform &transform = Transform());
        /// \brief Destructor.
        ~Obstacle() = default;

        /// \brief Implements the collision behavior when colliding with an entity.
        /// \param other : An entity.
        void doCollisionWith(Entity &other);

        /// \brief Implements the collision behavior when colliding with the player.
        /// \param other : The player entity.
        void doCollisionWith(Player &other);

        /// \brief Updates the obstacle.
        /// \param dt : The delta time, which describes the time difference between the previous frame that was drawn and the current frame.
        void update(const float dt);

        /// \brief Renders the obstacle.
        void render();
    };

} // namespace engine

#endif /* _Obstacle_HPP_ */
