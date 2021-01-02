#include <engine/Scene.hpp>
#include <engine/Renderer.hpp>

namespace engine
{

    template <typename T, typename U>
    void Scene::handleCollision(T &firstEntity, U &secondEntity)
    {
        if (firstEntity.intersect(secondEntity))
        {
            firstEntity.doCollisionWith(secondEntity);
            secondEntity.doCollisionWith(firstEntity);
        }
    }

    void Scene::update(const float dt)
    {
        if (player() != nullptr)
        {
            player()->update(dt);
        }

        if (directionalLight() != nullptr)
        {
            directionalLight()->update(dt);
        }

        if (pointLights() != nullptr)
        {
            pointLights()->update(dt);
        }

        if (!m_obstacles.empty())
        {
            updateObstaclesList(m_obstacles, dt);
        }

        if (!m_collectables.empty())
        {
            updateCollectablesList(m_collectables, dt);
        }
    }

    void Scene::updateObstaclesList(std::list<std::unique_ptr<Obstacle>> &obstaclesList, const float dt)
    {
        if (player() != nullptr)
        {
            for (typename std::list<std::unique_ptr<Obstacle>>::iterator it = obstaclesList.begin(); it != obstaclesList.end(); ++it)
            {
                Obstacle &currentEntity(**it);

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
    }

    void Scene::updateCollectablesList(std::list<std::unique_ptr<Collectable>> &collectablesList, const float dt)
    {
        std::list<std::unique_ptr<Collectable>>::iterator it = collectablesList.begin();

        while (it != collectablesList.end())
        {
            Collectable &currentCollectableEntity(**it);

            if (glm::abs(currentCollectableEntity.getPosition()[0] - m_player->getPosition()[0]) < m_maxCollideDistance)
            {
                currentCollectableEntity.update(dt);
                handleCollision(*m_player.get(), currentCollectableEntity);
            }
            else if (currentCollectableEntity.getPosition()[0] > m_player->getPosition()[0])
            {
                break;
            }

            if (currentCollectableEntity.isHidden())
            {
                collectablesList.erase(it++);
            }
            else
            {
                ++it;
            }
        }
    }

    void Scene::render()
    {
        skybox()->render();

        player()->render();

        if (!m_obstacles.empty())
        {
            renderEntitiesList<Obstacle>(m_obstacles);
        }

        if (!m_collectables.empty())
        {
            renderEntitiesList<Collectable>(m_collectables);
        }

        if (pointLights() != nullptr)
        {
            pointLights()->render();
        }
    }

    template <typename T>
    void Scene::renderEntitiesList(const std::list<std::unique_ptr<T>> &entitiesList)
    {
        if (!entitiesList.empty())
        {
            auto it = entitiesList.begin();
            for (it = entitiesList.begin(); it != entitiesList.end(); ++it)
            {
                if (it->get() != nullptr)
                {
                    it->get()->render();
                }
            }
        }
    }

} // namespace engine