#pragma once
#ifndef _Collider_HPP_
#define _Collider_HPP_

#include <engine/dependencies/glm.hpp>

#include <iostream>

namespace engine
{

    constexpr glm::vec3 defaultColliderPosition = glm::vec3(0);
    constexpr float defaultColliderRadius = 1.0f;

    class Collider
    {
    protected:
        glm::vec3 m_position;
        float m_radius;

    public:
        /// \brief Parameterized constructor.
        Collider(
            const glm::vec3 &position = defaultColliderPosition,
            const float radius = defaultColliderRadius);

        /// \brief Default destructor.
        ~Collider() = default;

        bool intersect(const Collider other,
                       const glm::mat4 selfTransformMatrix, const float selfScale,
                       const glm::mat4 otherTransformMatrix, const float otherScale) const;
    };

} // namespace engine

#endif /* _Collider_HPP_ */