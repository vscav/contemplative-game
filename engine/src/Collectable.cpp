#include <engine/Collectable.hpp>
#include <engine/TimeManager.hpp>
#include <engine/utils/common.hpp>

namespace engine
{

    Collectable::Collectable(Model *model,
                             Shader *shader,
                             const bool isStatic,
                             const Transform &transform)
        : Entity(model, shader, isStatic, transform), m_isTaken(false), m_isHidden(false),
          m_particleSystem(new ParticleSystem(new engine::Shader("application/res/shaders/forward.vert", "application/res/shaders/particle.frag"))),
          m_source(new AudioSource()), m_bufferBuzz(new AudioBuffer()), m_bufferTaken(new AudioBuffer())
    {
        // m_particle.colorBegin = {25 / 255.0f, 25 / 255.0f, 112 / 255.0f, 1.0f};
        // m_particle.colorEnd = {100 / 255.0f, 149 / 255.0f, 237 / 255.0f, 1.0f};
        // m_particle.sizeBegin = 0.5f;
        // m_particle.sizeVariation = 0.3f;
        // m_particle.sizeEnd = 0.0f;
        // m_particle.lifeTime = 10.0f;
        // m_particle.velocity = {0.25f, 0.25f, 0.25f};
        // m_particle.velocityVariation = {3.0f, 1.0f, 1.0f};
        // m_particle.position = {0.0f, 0.0f, 0.0f};
        // m_particle.position = m_position;

        m_bufferBuzz->addAudioEffect("application/res/sounds/buzz.wav");
        m_bufferTaken->addAudioEffect("application/res/sounds/pickgem.wav");

        m_source->setLooping(1);
        m_source->setBuffer(m_bufferBuzz.get()->m_audioEffectBuffers[0]);
        m_source->setPosition(m_position);

        alGetSourcei(m_source->m_source, AL_SOURCE_STATE, &m_isPlaying);
        if (m_isPlaying != AL_PLAYING || alGetError() != AL_NO_ERROR)
        {
          m_source->play();
        }
    }

    void Collectable::doCollisionWith(Entity &other)
    {
        if (physicsDebug)
            std::cout << "[Collectable] Collectable collided with an entity" << std::endl;
    }

    void Collectable::doCollisionWith(Player &other)
    {
        if (physicsDebug)
            std::cout << "[Collectable] Collectable collided with the player entity" << std::endl;

        m_isTaken = true;


        m_source->stop();
        m_source->setLooping(0);
        m_source->setBuffer(m_bufferTaken.get()->m_audioEffectBuffers[0]);
        m_source->play();
    }

    void Collectable::update(const float dt)
    {
        m_position.y += 0.5f * dt * glm::sin(TimeManager::getInstance().getTime() * 0.5f * M_PI);
        m_rotation.y += 0.75f * dt;

        // m_particleSystem->emit(m_particle);
        // m_particleSystem->update(dt);

        if (m_isTaken && !m_isHidden)
        {
            m_scale = glm::mix(m_scale, glm::vec3(0.2f), 0.1f);

            if (m_scale.x <= 0.25f)
            {
                m_isHidden = true;
            }
        }

        m_source->setPosition(m_position);
    }

    void Collectable::render()
    {
        Entity::render();

        m_particleSystem->render();

    }

} // namespace engine
