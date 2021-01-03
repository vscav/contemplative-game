#pragma once
#ifndef _Collectable_HPP_
#define _Collectable_HPP_

#include <engine/Entity.hpp>
#include <engine/ParticleSystem.hpp>
#include <engine/AudioSource.hpp>
#include <engine/AudioBuffer.hpp>
#include <engine/utils/common.hpp>

#include <AL/al.h>

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

        std::unique_ptr<AudioSource> m_source;
        std::unique_ptr<AudioBuffer> m_bufferBuzz;
        std::unique_ptr<AudioBuffer> m_bufferTaken;

        ALint m_isPlaying;

    public:
        /// \brief Constructor.
        Collectable(Model *model,
                    Shader *shader,
                    const bool isStatic = false,
                    const Transform &transform = Transform());

        /// \brief Destructor.
        virtual ~Collectable()
        {
            if (applicationDebug)
                std::cout << "[Collectable] Delete collectable" << std::endl;

        };

        /// \brief Implements the collision behavior when colliding an entity.
        /// \param other : An entity.
        void doCollisionWith(Entity &other);

        /// \brief Implements the collision behavior when colliding the player.
        /// \param other : The player entity.
        void doCollisionWith(Player &other);

        /// \brief Updates the collectable entity.
        /// \param dt : The delta time, which describes the time difference between the previous frame that was drawn and the current frame.
        void update(const float dt);

        /// \brief Renders the obstacle entity.
        void render();

        /// \brief Returns a boolean to tell whether the collectable entity was taken by the player.
        /// \return A boolean to tell whether the collectable entity was taken by the player.
        inline const bool isTaken() const { return m_isTaken; }

        /// \brief Returns a boolean to tell whether the collectable entity is hidden.
        /// \return A boolean to tell whether the collectable entity is hidden.
        inline const bool isHidden() const { return m_isHidden; }
    };

} // namespace engine

#endif /* _Collectable_HPP_ */
