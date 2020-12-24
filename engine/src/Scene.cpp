#include <engine/Scene.hpp>

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

        // if (!m_entities.empty())
        // {
        //     auto it = m_entities.begin();
        //     for (it = m_entities.begin(); it != m_entities.end(); ++it)
        //     {
        //         if (it->get() != nullptr)
        //         {
        //             it->get()->update(dt);
        //         }
        //     }
        // }

        // updateEntitiesList(m_entities, dt);
        updateObstaclesList(m_obstacles, dt);
    }

    // void Scene::updateEntitiesList(std::list<std::unique_ptr<Entity>> &entitiesList, const float dt)
    // {
    //     Entity &player(dynamic_cast<Entity &>(*m_player));
    //     for (typename std::list<std::unique_ptr<Entity>>::iterator it = entitiesList.begin(); it != entitiesList.end(); ++it)
    //     {
    //         Entity &currentEntity(dynamic_cast<Entity &>(**it));

    //         if (glm::abs(currentEntity.getPosition()[0] - m_player->getPosition()[0]) < m_maxCollideDistance)
    //         {
    //             currentEntity.update(dt);
    //             handleCollision(player, currentEntity);
    //         }
    //         else if ((*it)->getPosition()[0] > m_player->getPosition()[0])
    //         {
    //             break;
    //         }
    //     }
    // }

    // void Scene::updateObstaclesList(std::list<std::unique_ptr<Obstacle>> &obstaclesList, const float dt)
    // {
    //     // Entity &player(dynamic_cast<Entity &>(*m_player));
    //     for (typename std::list<std::unique_ptr<Obstacle>>::iterator it = obstaclesList.begin(); it != obstaclesList.end(); ++it)
    //     {
    //         Entity &currentEntity(dynamic_cast<Entity &>(**it));

    //         if (glm::abs(currentEntity.getPosition()[0] - m_player->getPosition()[0]) < m_maxCollideDistance)
    //         {
    //             currentEntity.update(dt);
    //             handleCollision(m_player, currentEntity);
    //         }
    //         else if ((*it)->getPosition()[0] > m_player->getPosition()[0])
    //         {
    //             break;
    //         }
    //     }
    // }

    void Scene::updateObstaclesList(std::list<std::unique_ptr<Entity>> &obstaclesList, const float dt)
    {
        // Player &player(dynamic_cast<Player &>(*m_player));
        for (typename std::list<std::unique_ptr<Entity>>::iterator it = obstaclesList.begin(); it != obstaclesList.end(); ++it)
        {
            Obstacle &currentEntity(dynamic_cast<Obstacle &>(**it));

            currentEntity.update(dt);
            handleCollision(*m_player.get(), currentEntity);

            // if (glm::abs(currentEntity.getPosition()[0] - m_player->getPosition()[0]) < m_maxCollideDistance)
            // {
            //     currentEntity.update(dt);
            //     handleCollision(*m_player.get(), currentEntity);
            // }
            // else if ((*it)->getPosition()[0] > m_player->getPosition()[0])
            // {
            //     break;
            // }
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
    }

} // namespace engine