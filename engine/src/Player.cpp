// #include <engine/Player.hpp>
#include <engine/GLApplication.hpp>

namespace engine
{
    Player::Player(Model *model,
                   Shader *shader,
                   const bool isStatic,
                   const Transform &transform)
        : Entity(model, shader, isStatic, transform),
          m_score(0)
    {
        if (applicationDebug)
            std::cout << "[Player] Player created" << std::endl;
    }

    void Player::moveForward(int delta)
    {
        m_currentSpeed = delta * runSpeed;

        float dx = (float)(m_currentSpeed * glm::cos(m_rotation.y));
        float dz = (float)(m_currentSpeed * glm::sin(m_rotation.y));

        setPosition(glm::vec3(m_position.x + dx, m_position.y, m_position.z + dz));
    }

    void Player::moveLeft(int delta)
    {
        m_currentTurnSpeed = delta * turnSpeed;

        setRotation(glm::vec3(m_rotation.x, m_currentTurnSpeed + m_rotation.y, m_rotation.z));
    }

    void Player::moveUp(int delta)
    {
        m_currentUpspeed = delta * upSpeed;

        if (m_position.y > maximumPlayerUp)
            m_position.y = maximumPlayerUp;
        else if (m_position.y < minimumPlayerUp)
            m_position.y = minimumPlayerUp;

        setPosition(glm::vec3(m_position.x, m_currentUpspeed + m_position.y, m_position.z));
    }

    void Player::doCollisionWith(Entity &other)
    {
        if (physicsDebug)
            std::cout << "[Player] Player collided with an entity" << std::endl;
    };

    void Player::doCollisionWith(Obstacle &other)
    {
        if (physicsDebug)
            std::cout << "[Player] Player collided with an obstacle entity" << std::endl;
    };

    void Player::doCollisionWith(Collectable &other)
    {
        if (physicsDebug)
            std::cout << "[Player] Player collided with a collectable entity" << std::endl;

        if (!other.isTaken())
        {
            m_score += 1;
            GLApplication::getInstance().getUI()->updateScore(m_score);
        }
    };

    void Player::update(float dt)
    {
        GLApplication::getInstance().getCamera()->updatePosition(m_position);

        if (m_score == 10)
        {
            GLApplication::getInstance().setState(stateWin);
        }
    }

} // namespace engine
