#include <engine/Obstacle.hpp>

namespace engine
{

    Obstacle::Obstacle(Model *model,
                       Shader *shader,
                       const bool isStatic,
                       const Transform &transform)
        : Entity(model, shader, isStatic, transform)
    {
        if (applicationDebug)
            std::cout << "[Obstacle] Obstacle created" << std::endl;
    }

    void Obstacle::doCollisionWith(Entity &other)
    {
        if (physicsDebug)
            std::cout << "[Obstacle] Obstacle collision with entity" << std::endl;
    };

    void Obstacle::doCollisionWith(Player &other)
    {
        if (physicsDebug)
            std::cout << "[Obstacle] Obstacle collision with player" << std::endl;
    };

    void Obstacle::update(const float dt)
    {
    }

    void Obstacle::render()
    {
        Entity::render();
    }

} // namespace engine