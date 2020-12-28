#pragma once
#ifndef _DirectionalLight_HPP_
#define _DirectionalLight_HPP_

#include <engine/dependencies/glm.hpp>

namespace engine
{

    constexpr float defaultLightCycleSpeed = 0.0001f;

    class DirectionalLight
    {
    private:
        glm::vec3 m_intensity;
        glm::vec3 m_color;
        glm::vec3 m_direction;
        float m_speed = defaultLightCycleSpeed;

    public:
        DirectionalLight(const glm::vec3 &intensity = glm::vec3(1.0f),
                         const glm::vec3 &color = glm::vec3(1.0f),
                         const glm::vec3 &direction = glm::vec3(1.0f));

        ~DirectionalLight() = default;

        /// \brief
        inline glm::vec3 &direction() { return m_direction; };
        /// \brief
        inline const glm::vec3 &direction() const { return m_direction; };

        /// \brief
        inline glm::vec3 &intensity() { return m_intensity; };
        /// \brief
        inline const glm::vec3 &intensity() const { return m_intensity; };

        /// \brief
        inline glm::vec3 &color() { return m_color; };
        /// \brief
        inline const glm::vec3 &color() const { return m_color; };

        /// \brief
        void update(float const dt);
    };

} // namespace engine

#endif /* _DirectionalLight_HPP_ */