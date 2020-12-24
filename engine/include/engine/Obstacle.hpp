#pragma once
#ifndef _Obstacle_HPP_
#define _Obstacle_HPP_

#include <engine/Entity.hpp>
#include <engine/Player.hpp>
#include <engine/utils/common.hpp>

namespace engine
{

    class Player;

    /// \brief
    class Obstacle : public Entity
    {
    public:
        /// \brief
        Obstacle(const Entity &obstacleEntity);
        /// \brief
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
