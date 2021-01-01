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

    void Scene::updateObstaclesList(std::list<std::unique_ptr<Entity>> &obstaclesList, const float dt)
    {
        if (player() != nullptr)
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
    }

    void Scene::updateCollectablesList(std::list<std::unique_ptr<Entity>> &collectablesList, const float dt)
    {
        std::list<std::unique_ptr<Entity>>::iterator it = collectablesList.begin();

        while (it != collectablesList.end())
        {
            Collectable &currentCollectableEntity(dynamic_cast<Collectable &>(**it));

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
            renderEntitiesList(m_obstacles);
        }

        if (!m_collectables.empty())
        {
            renderEntitiesList(m_collectables);
        }

        if (pointLights() != nullptr)
        {
            pointLights()->render();
        }
    }

    void Scene::renderEntitiesList(const std::list<std::unique_ptr<Entity>> &entitiesList)
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