#include <engine/Scene.hpp>

namespace engine
{

    void Scene::update(const float dt)
    {
        if (player() != nullptr)
        {
            player()->update(dt);
        }

        if (!m_entities.empty())
        {
            auto it = m_entities.begin();
            for (it = m_entities.begin(); it != m_entities.end(); ++it)
            {
                if (it->get() != nullptr)
                {
                    it->get()->update(dt);
                }
            }
        }
    }

    void Scene::render()
    {
        if (skybox() != nullptr)
        {
            skybox()->render();
        }

        if (player() != nullptr)
        {
            player()->render();
        }

        if (!m_entities.empty())
        {
            auto it = m_entities.begin();
            for (it = m_entities.begin(); it != m_entities.end(); ++it)
            {
                if (it->get() != nullptr)
                {
                    it->get()->render();
                }
            }
        }
    }

} // namespace engine