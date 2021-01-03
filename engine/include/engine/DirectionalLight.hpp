#pragma once
#ifndef _DirectionalLight_HPP_
#define _DirectionalLight_HPP_

#include <engine/dependencies/glm.hpp>

namespace engine
{

    constexpr float defaultLightCycleSpeed = 0.0001f; /*!< The default speed of the directional light cycle (if activated). */

    class DirectionalLight
    {
    private:
        glm::vec3 m_intensity;                  /*!< The intensity of the directional light. */
        glm::vec3 m_color;                      /*!< The color of the directional light. */
        glm::vec3 m_direction;                  /*!< The direction of the directional light. */
        bool m_isStatic;                        /*!< A boolean to tell whether the directional light is animated. */
        float m_speed = defaultLightCycleSpeed; /*!< The speed of the directional light (if animated). */

    public:
        /// \brief Parameterized constructor.
        /// \param intensity : The intensity of the directional light.
        /// \param color : The color of the directional light.
        /// \param direction : The direction of the directional light.
        /// \param isStatic : A boolean to tell whether the directional light is animated.
        DirectionalLight(const glm::vec3 &intensity = glm::vec3(1.0f),
                         const glm::vec3 &color = glm::vec3(1.0f),
                         const glm::vec3 &direction = glm::vec3(1.0f),
                         const bool isStatic = true);

        /// \brief Default destructor.
        ~DirectionalLight() = default;

        /// \brief Gets the direction of the directional light.
        /// \return The direction of the directional light.
        inline glm::vec3 &direction() { return m_direction; };
        /// \brief Gets the direction of the directional light as a const reference.
        /// \return The direction of the directional light as a const reference.
        inline const glm::vec3 &direction() const { return m_direction; };

        /// \brief Gets the intensity of the directional light.
        /// \return The intensity of the directional light.
        inline glm::vec3 &intensity() { return m_intensity; };
        /// \brief Gets the intensity of the directional light as a const reference.
        /// \return The intensity of the directional light as a const reference.
        inline const glm::vec3 &intensity() const { return m_intensity; };

        /// \brief Gets the color of the directional light.
        /// \return The color of the directional light.
        inline glm::vec3 &color() { return m_color; };
        /// \brief Gets the color of the directional light as a const reference.
        /// \return The color of the directional light as a const reference.
        inline const glm::vec3 &color() const { return m_color; };

        /// \brief Updates the directional light.
        /// \param dt : The delta time, which describes the time difference between the previous frame that was drawn and the current frame.
        void update(float const dt);
    };

} // namespace engine

#endif /* _DirectionalLight_HPP_ */