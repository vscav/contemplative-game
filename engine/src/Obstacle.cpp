#include <engine/Obstacle.hpp>

namespace engine
{

    Obstacle::Obstacle(const Entity &obstacleEntity)
        : Entity(obstacleEntity)
    {
        if (applicationDebug)
            std::cout << "[Obstacle] Obstacle created" << std::endl;
    }

    /// \brief
    void Obstacle::doCollisionWith(Entity &other){
        if (physicsDebug) std::cout << "[Obstacle] Obstacle collision with entity" << std::endl;
    };

    /// \brief
    void Obstacle::doCollisionWith(Player &other){
        if (physicsDebug) std::cout << "[Obstacle] Obstacle collision with player" << std::endl;
    };

    void Obstacle::update(const float dt)
    {
    }

} // namespace engine