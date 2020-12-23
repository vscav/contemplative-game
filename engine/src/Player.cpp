// #include <engine/Player.hpp>
#include <engine/GLApplication.hpp>

namespace engine
{
    Player::Player(const Entity &playerEntity)
        : Entity(playerEntity)
    {
    }

    void Player::moveForward(int delta)
    {
        // m_lerpSpeed += m_sensitivity * delta;
        // m_position.z += m_lerpSpeed;
        m_position.z += m_speed * delta;
    }

    void Player::moveLeft(int delta)
    {
        // m_lerpSpeed += m_sensitivity * delta;
        // m_position.x += m_lerpSpeed;
        m_position.x += m_speed * delta;
    }

    void Player::moveUp(int delta)
    {
        // m_lerpSpeed += m_sensitivity * delta;
        // m_position.y += m_lerpSpeed;
        m_position.y += m_speed * delta;
    }

    void Player::update(float dt)
    {
        // m_speed += m_lerpSpeed * dt;
        // m_lerpSpeed *= std::pow(m_lerpFactor, dt);

        // When the player is updated, the camera is updated as well
        GLApplication::getInstance().getCamera()->updatePosition(m_position);
    }

} // namespace engine