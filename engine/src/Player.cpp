#include <engine/Player.hpp>

namespace engine
{
    Player::Player(const Entity &playerEntity)
        : Entity(playerEntity)
    {
    }

    void Player::update(const float dt)
    {
        // updateSpeed(dt);
        // updatePosition(dt);
    }

    void Player::updateSpeed(const float dt)
    {
    }

    void Player::updatePosition(const float dt)
    {
    }

    void Player::moveForward(int delta)
    {
        m_position.z +=  delta * m_speed;
    }

    void Player::moveLeft(int delta)
    {
        m_position.x +=  delta * m_speed;
    }

    void Player::moveUp(int delta)
    {
        m_position.y +=  delta * m_speed;
    }

} // namespace engine