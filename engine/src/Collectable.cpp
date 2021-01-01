#include <engine/Collectable.hpp>
#include <engine/utils/common.hpp>

namespace engine
{

    Collectable::Collectable(const Entity &collectableEntity)
        : Entity(collectableEntity), m_isTaken(false), m_isHidden(false){};

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
    }

    void Collectable::update(const float dt)
    {
        if (m_isTaken && !m_isHidden)
        {
            m_scale = glm::mix(m_scale, glm::vec3(0.2f), 0.2f);

            if (m_scale.x <= 0.25f)
            {
                m_isHidden = true;
            }
        }
    }

} // namespace engine
