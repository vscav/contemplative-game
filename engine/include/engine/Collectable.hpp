#pragma once
#ifndef _Collectable_HPP_
#define _Collectable_HPP_

#include <engine/Entity.hpp>
#include <engine/ParticleSystem.hpp>

const float collectableRotationSpeed = 2.f;

namespace engine
{

    class Player;

    /// \class Collectable
    /// \brief Class that represents an obstacle in the application, an interactive entity.
    class Collectable : public Entity
    {
    private:
        bool m_isTaken;  /*!< A boolean to tell whether the collectable has been taken by the player. */
        bool m_isHidden; /*!< A boolean to tell whether the collectable was taken and if it has to be rendered to the screen. */

        std::shared_ptr<ParticleSystem> m_particleSystem; /*!< */
        ParticleProps m_particle;                         /*!< */

    public:
        /// \brief Constructor.
        Collectable(const Entity &collectableEntity);

        /// \brief Destructor.
        virtual ~Collectable()
        {
            if (applicationDebug)
                std::cout << "[Collectable] Delete collectable" << std::endl;
        };

        /// \brief Implements the collision behavior when colliding an entity.
        void doCollisionWith(Entity &other);

        /// \brief Implements the collision behavior when colliding the player.
        /// \param other : The player entity.
        void doCollisionWith(Player &other);

        /// \brief Updates the collectable entity.
        /// \param dt : .
        void update(const float dt);

        /// \brief Renders the obstacle.
        void render();

        /// \brief
        inline const bool isTaken() const { return m_isTaken; }

        /// \brief
        inline const bool isHidden() const { return m_isHidden; }
    };

} // namespace engine

#endif /* _Collectable_HPP_ */
