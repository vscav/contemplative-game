#include <engine/Collider.hpp>
#include <engine/utils/common.hpp>

#include <iostream>

namespace engine
{

    Collider::Collider(const glm::vec3 &position, const float radius)
        : m_position(position), m_radius(radius)
    {
        if (applicationDebug)
        {
            std::cout << "[Collider] Model collider created" << std::endl;
        }
    }

    bool Collider::intersect(const Collider other,
                             const glm::mat4 selfTransformMatrix, const float selfScale,
                             const glm::mat4 otherTransformMatrix, const float otherScale) const
    {
        glm::vec3 selfWorldPosition(selfTransformMatrix * glm::vec4(m_position, 1.f));
        glm::vec3 otherWorldPosition(otherTransformMatrix * glm::vec4(other.m_position, 1.f));

        float squaredDistances = glm::distance(selfWorldPosition, otherWorldPosition) * glm::distance(selfWorldPosition, otherWorldPosition);
        float squaredRadiuses = m_radius * m_radius * selfScale * selfScale + other.m_radius * other.m_radius * otherScale * otherScale;

        if (squaredDistances < squaredRadiuses)
        {
            return true;
        }

        return false;
    }

} // namespace engine