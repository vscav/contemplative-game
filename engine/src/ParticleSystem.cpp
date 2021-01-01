#include <engine/ParticleSystem.hpp>
#include <engine/Random.hpp>
#include <engine/Renderer.hpp>

namespace engine
{

    ParticleSystem::ParticleSystem(Shader *shader)
        : m_shader(shader)
    {
        m_particlePool.resize(1000);

        float vertices[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f};

        glCreateVertexArrays(1, &m_quadVA);
        glBindVertexArray(m_quadVA);

        GLuint quadVB, quadIB;
        glCreateBuffers(1, &quadVB);
        glBindBuffer(GL_ARRAY_BUFFER, quadVB);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

        uint32_t indices[] = {
            0, 1, 2, 2, 3, 0};

        glCreateBuffers(1, &quadIB);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIB);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    }

    void ParticleSystem::update(const float dt)
    {
        for (auto &particle : m_particlePool)
        {
            if (!particle.active)
                continue;

            if (particle.lifeRemaining <= 0.0f)
            {
                particle.active = false;
                continue;
            }

            particle.lifeRemaining -= dt;
            particle.position += particle.velocity * dt;
            particle.rotation += 0.01f * dt;
        }
    }

    void ParticleSystem::render()
    {
        m_shader->bind();

        for (auto &particle : m_particlePool)
        {
            if (!particle.active)
                continue;

            float life = particle.lifeRemaining / particle.lifeTime;
            glm::vec4 color = glm::lerp(particle.colorEnd, particle.colorBegin, life);

            float size = glm::lerp(particle.sizeEnd, particle.sizeBegin, life);

            glm::mat4 transform = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f)) * glm::translate(glm::mat4(1.0f), {particle.position.x, particle.position.y, particle.position.z}) * glm::rotate(glm::mat4(1.0f), particle.rotation, {0.0f, 0.0f, 1.0f}) * glm::scale(glm::mat4(1.0f), {size, size, 1.0f});

            Renderer::getInstance().sendModelMatrixUniforms(transform, m_shader.get());
            glUniform4fv(m_shader->getUniform("uColor"), 1, glm::value_ptr(color));

            glBindVertexArray(m_quadVA);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        }

        m_shader->unbind();
    }

    void ParticleSystem::emit(const ParticleProps &particleProps)
    {
        Particle &particle = m_particlePool[m_poolIndex];

        particle.active = true;

        particle.position = particleProps.position;
        particle.rotation = Random::floatDistribution() * 2.0f * glm::pi<float>();

        particle.velocity = particleProps.velocity;

        particle.velocity.x += particleProps.velocityVariation.x * (Random::floatDistribution() - 0.5f);
        particle.velocity.y += particleProps.velocityVariation.y * (Random::floatDistribution() - 0.5f);
        particle.velocity.z += particleProps.velocityVariation.z * (Random::floatDistribution() - 0.5f);

        particle.colorBegin = particleProps.colorBegin;
        particle.colorEnd = particleProps.colorEnd;

        particle.lifeTime = particleProps.lifeTime;
        particle.lifeRemaining = particleProps.lifeTime;
        particle.sizeBegin = particleProps.sizeBegin + particleProps.sizeVariation * (Random::floatDistribution() - 0.5f);
        particle.sizeEnd = particleProps.sizeEnd;

        m_poolIndex = --m_poolIndex % m_particlePool.size();
    }

} // namespace engine