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
        /// \brief Constructor.
        Obstacle(const Entity &obstacleEntity);
        /// \brief Destructor.
        ~Obstacle() = default;

        /// \brief Implements the collision behavior when colliding with an entity.
        void doCollisionWith(Entity &other);

        /// \brief Implements the collision behavior when colliding with the player.
        void doCollisionWith(Player &other);

        /// \brief Updates the obstacle.
        void update(const float dt);
    };

} // namespace engine

#endif /* _Obstacle_HPP_ */
