// #include <engine/Player.hpp>
#include <engine/GLApplication.hpp>

namespace engine
{
    Player::Player(const Entity &playerEntity)
        : Entity(playerEntity)
    {
        if (applicationDebug)
            std::cout << "[Player] Player created" << std::endl;
    }

    void Player::moveForward(int delta)
    {
        m_currentSpeed = delta * runSpeed;

        float dx = (float)(m_currentSpeed * glm::sin(m_rotation.y));
        float dz = (float)(m_currentSpeed * glm::cos(m_rotation.y));

        setPosition(glm::vec3(m_position.x + dx, 0.0, m_position.z + dz));
    }

    void Player::moveLeft(int delta)
    {
        m_currentTurnSpeed = delta * turnSpeed;

        setRotation(glm::vec3(m_rotation.x, m_currentTurnSpeed + m_rotation.y, m_rotation.z));
    }

    void Player::moveUp(int delta)
    {
    }

    /// \brief
    void Player::doCollisionWith(Entity &other)
    {
        if (physicsDebug)
            std::cout << "[Player] Player collided with an entity" << std::endl;
    };

    /// \brief
    void Player::doCollisionWith(Obstacle &other)
    {
        if (physicsDebug)
            std::cout << "[Player] Player collided with an obstacle" << std::endl;
    };

    void Player::update(float dt)
    {
        // // Update angles
        // m_angleX += m_angleXSpeed * dt;
        // m_angleY += m_angleYSpeed * dt;

        // // Update angles speed
        // m_angleXSpeed *= std::pow(m_lerpFactor, dt);
        // m_angleYSpeed *= std::pow(m_lerpFactor, dt);

        GLApplication::getInstance().getCamera()->updatePosition(m_position);
    }

} // namespace engine