#pragma once
#ifndef _ParticleSystem_HPP_
#define _ParticleSystem_HPP_

#include <engine/Shader.hpp>
#include <engine/dependencies/glm.hpp>

#include <GL/glew.h>

#include <vector>

namespace engine
{

    struct ParticleProps
    {
        glm::vec3 position, velocity, velocityVariation;
        glm::vec4 colorBegin, colorEnd;

        float sizeBegin, sizeEnd, sizeVariation;
        float lifeTime = 1.0f;
    };

    class ParticleSystem
    {
    private:
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

        std::vector<Particle> m_particlePool;
        uint32_t m_poolIndex = 999;

        GLuint m_quadVA = 0;
        std::unique_ptr<Shader> m_shader;

    public:
        ParticleSystem(Shader *shader);
        ~ParticleSystem() = default;

        void update(const float ts);
        void render();

        void emit(const ParticleProps &particleProps);
    };

} // namespace engine

#endif /* _ParticleSystem_HPP_ */