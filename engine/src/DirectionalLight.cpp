#include <engine/DirectionalLight.hpp>

namespace engine
{

    DirectionalLight::DirectionalLight(const glm::vec3 &intensity,
                                       const glm::vec3 &color,
                                       const glm::vec3 &direction)
        : m_intensity(intensity), m_color(color), m_direction(direction)
    {
    }

} // namespace engine