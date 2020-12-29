#include <engine/Scene.hpp>
#include <engine/Renderer.hpp>

namespace engine
{

    template <typename T, typename U>
    void Scene::handleCollision(T &firstObject, U &secondObject)
    {
        if (firstObject.intersect(secondObject))
        {
            firstObject.doCollisionWith(secondObject);
            secondObject.doCollisionWith(firstObject);
        }
    }

    void Scene::update(const float dt)
    {
        if (player() != nullptr)
        {
            player()->update(dt);
        }

        updateObstaclesList(m_obstacles, dt);

        directionalLight()->update(dt);

        pointLights()->update(dt);

        m_particle.position = {0.0f, 0.0f, 0.0f};

        m_particleSystem->emit(m_particle);

        particleSystem()->update(dt);
    }

    void Scene::updateObstaclesList(std::list<std::unique_ptr<Entity>> &obstaclesList, const float dt)
    {
        for (typename std::list<std::unique_ptr<Entity>>::iterator it = obstaclesList.begin(); it != obstaclesList.end(); ++it)
        {
            Obstacle &currentEntity(dynamic_cast<Obstacle &>(**it));

            if (glm::abs(currentEntity.getPosition()[0] - m_player->getPosition()[0]) < m_maxCollideDistance)
            {
                currentEntity.update(dt);
                handleCollision(*m_player.get(), currentEntity);
            }
            else if ((*it)->getPosition()[0] > m_player->getPosition()[0])
            {
                break;
            }
        }
    }

    void Scene::render()
    {
        skybox()->render();

        player()->render();

        if (!m_obstacles.empty())
        {
            auto it = m_obstacles.begin();
            for (it = m_obstacles.begin(); it != m_obstacles.end(); ++it)
            {
                if (it->get() != nullptr)
                {
                    it->get()->render();
                }
            }
        }

        pointLights()->render();

        particleSystem()->render();
    }

} // namespace engine