#pragma once
#ifndef _Collider_HPP_
#define _Collider_HPP_

#include <engine/dependencies/glm.hpp>

#include <iostream>

namespace engine
{

    constexpr glm::vec3 defaultColliderPosition = glm::vec3(0);
    constexpr float defaultColliderRadius = 1.0f;

    /// \class Collider
    /// \brief Class for representing the geometric spheric collision of the models.
    class Collider
    {
    protected:
        glm::vec3 m_position; /*!< The position of the collider. */
        float m_radius;       /*!< The radius of the collider. */

    public:
        /// \brief Parameterized constructor.
        /// \param position : The position of the collider.
        /// \param radius : The radius of the collider.
        Collider(
            const glm::vec3 &position = defaultColliderPosition,
            const float radius = defaultColliderRadius);

        /// \brief Default destructor.
        ~Collider() = default;

        /// \brief Returns a boolean to tell whether or not the current collider object is colliding another collider.
        /// \return A boolean to tell whether or not the current collider object is colliding another collider.
        bool intersect(const Collider other,
                       const glm::mat4 selfTransformMatrix, const float selfScale,
                       const glm::mat4 otherTransformMatrix, const float otherScale) const;
    };

} // namespace engine

#endif /* _Collider_HPP_ */