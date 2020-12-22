#include <engine/Entity.hpp>

namespace engine
{

    constexpr glm::vec3 defaultPlayerPosition = glm::vec3(0.0f, 0.0f, 10.0f);
    constexpr glm::vec3 defaultPlayerMaximumSpeed = glm::vec3(2.5f, 14.f, 12.f);
    constexpr glm::vec3 defaultPlayerAcceleration = glm::vec3(3.f, 7.f, 7.f);

    constexpr float minimumPlayerUp = 1.0f;
    constexpr float maximumPlayerUp = 10.0f;

    class Player : public Entity
    {
    protected:
        /// \brief
        void updateSpeed(const float dt);
        /// \brief
        void updatePosition(const float dt);

        float m_speed = 0.025; /*!< . */

    public:
        /// \brief Constructor.
        /// \param
        Player(const Entity &playerEntity);
        /// \brief Default destructor.
        ~Player() = default;

        /// \brief
        void moveForward(int delta);
        /// \brief
        void moveLeft(int delta);
        /// \brief
        void moveUp(int delta);

        /// \brief
        void update(const float dt);
    };

} // namespace engine