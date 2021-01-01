#pragma once
#ifndef _Collectable_HPP_
#define _Collectable_HPP_

#include <engine/Entity.hpp>

const float collectableRotationSpeed = 2.f;

namespace engine
{

    class Player;

    /// \brief Represents a Collectable Gameobject
    class Collectable : public Entity
    {
    private:
        bool m_isTaken;
        bool m_isHidden;

    public:
        /// \brief
        Collectable(const Entity &collectableEntity);

        /// \brief
        virtual ~Collectable(){};

        /// \brief
        void doCollisionWith(Entity &other);

        /// \brief
        void doCollisionWith(Player &other);

        /// \brief
        void update(const float dt);

        /// \brief
        inline const bool isTaken() const { return m_isTaken; }

        /// \brief
        inline const bool isHidden() const { return m_isHidden; }
    };

} // namespace engine

#endif /* _Collectable_HPP_ */
