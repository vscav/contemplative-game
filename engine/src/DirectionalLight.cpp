#include <engine/DirectionalLight.hpp>
#include <engine/dependencies/glm.hpp>

#include <iostream>

namespace engine
{

    DirectionalLight::DirectionalLight(const glm::vec3 &intensity,
                                       const glm::vec3 &color,
                                       const glm::vec3 &direction,
                                       const bool isStatic)
        : m_intensity(intensity), m_color(color), m_direction(direction), m_isStatic(isStatic)
    {
    }

    void DirectionalLight::update(float const dt)
    {
        if (!m_isStatic)
        {
            m_direction = glm::rotate(m_direction, m_speed * float(dt), glm::vec3(1.0f, 0.0f, -0.6f));
        }
    }

} // namespace engine