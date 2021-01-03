#pragma once

#include <engine/Sphere.hpp>
#include <engine/Shader.hpp>
#include <engine/dependencies/glm.hpp>

#include <GL/glew.h>

#include <vector>
#include <unordered_map>
#include <memory>

namespace engine
{

    /// \struct PointLight
    /// \brief A structure representing a point light and its caracteristics and props.
    struct PointLight
    {
        glm::vec3 position;
        glm::vec3 scale;

        float constant;
        float linear;
        float quadratic;

        glm::vec3 ambientColor;
        glm::vec3 diffuseColor;
    };

    /// \class PointLights
    /// \brief Class used to represent and manage a collection of point lights.
    class PointLights
    {

    private:
        std::vector<PointLight> m_lights; /*!< A collection of point lights */

        std::unique_ptr<Shader> m_shader; /*!< The shader used to render our point lights. */

        std::unique_ptr<Sphere> m_sphere; /*!< The sphere used to represent the geometry of the point light.  */

    public:
        /// \brief Default constructor.
        PointLights();
        /// \brief Default destructor.
        ~PointLights() = default;

        /// \brief Adds a new point light to the collection.
        /// \param position : A 3 floats vector representing the position of the new point light.
        /// \param scale : A 3 floats vector representing the scale of the new point light.
        /// \param constant : A float representing the constant of the new point light.
        /// \param linear : A float representing the linear of the new point light.
        /// \param quadratic : A float the quadratic of the new point light.
        /// \param ambientColor : A 3 floats vector representing the ambient color of the new point light.
        /// \param diffuseColor : A 3 floats vector representing the color of the new point light.
        void addPointLight(const glm::vec3 &position, const glm::vec3 &scale, const float &constant, const float &linear, const float &quadratic, const glm::vec3 &ambientColor, const glm::vec3 &diffuseColor);

        /// \brief Clears the collection of point lights.
        void resetPointLights();

        /// \brief Deletes a specific point light in the collection using its position.
        /// \param position : The position of the point light in the scene.
        void deletePointLight(const glm::vec3 &position);

        /// \brief Returns the collection of point lights.
        /// \return A vector containing all the point ligths.
        inline std::vector<PointLight> getLights() { return m_lights; };

        /// \brief Updates the point lights.
        /// \param dt : The delta time, which describes the time difference between the previous frame that was drawn and the current frame.
        void update(float const dt);

        /// \brief Renders the point lights.
        void render();
    };
} // namespace engine