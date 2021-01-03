#pragma once
#ifndef _ParticleSystem_HPP_
#define _ParticleSystem_HPP_

#include <engine/Shader.hpp>
#include <engine/Sphere.hpp>
#include <engine/dependencies/glm.hpp>

#include <GL/glew.h>

#include <vector>

namespace engine
{

    /// \struct ParticleProps
    /// \brief The inner props of the entity emit by the particles system.
    struct ParticleProps
    {
        glm::vec3 position, velocity, velocityVariation;
        glm::vec4 colorBegin, colorEnd;

        float sizeBegin, sizeEnd, sizeVariation;
        float lifeTime = 1.0f;
    };

    /// \class ParticleSystem
    /// \brief
    class ParticleSystem
    {
    private:
        /// \struct Particle
        /// \brief A structure representing a particle in the system.
        struct Particle
        {
            glm::vec3 position = glm::vec3(0.0f), velocity;
            glm::vec4 colorBegin, colorEnd;

            float rotation = 0.0f;
            float sizeBegin, sizeEnd;

            float lifeTime = 1.0f;
            float lifeRemaining = 0.0f;

            bool active = false;
        };

        std::vector<Particle> m_particlePool; /*!< The pool (collection) of particles in the system. */

        unsigned int m_poolIndex = 999; /*!< The current index in the particles pool. */

        std::unique_ptr<Shader> m_shader; /*!< The shader to apply to each particle. */

        std::unique_ptr<Sphere> m_sphere; /*!< The sphere representing the geometry of the particle. */

    public:
        /// \brief Parameterized constructor.
        /// \param shader : The shader which will be applied to the particles.
        ParticleSystem(Shader *shader);
        /// \brief Default destructor.
        ~ParticleSystem() = default;

        /// \brief Updates the particles system.
        /// \param dt : The delta time, which describes the time difference between the previous frame that was drawn and the current frame.
        void update(const float dt);

        /// \brief Renders the particle system.
        void render();

        /// \brief Emits a particle of the pool based on the particle props.
        /// \param particleProps : The particle props.
        void emit(const ParticleProps &particleProps);
    };

} // namespace engine

#endif /* _ParticleSystem_HPP_ */