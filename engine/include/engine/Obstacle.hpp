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
    /// \brief
    class Obstacle : public Entity
    {
    public:
        /// \brief Constructor.
        Obstacle(const Entity &obstacleEntity);
        /// \brief Destructor.
        ~Obstacle() = default;

        /// \brief
        void doCollisionWith(Entity &other);

        /// \brief
        void doCollisionWith(Player &other);

        /// \brief
        void update(const float dt);
    };

} // namespace engine

#endif /* _Obstacle_HPP_ */
