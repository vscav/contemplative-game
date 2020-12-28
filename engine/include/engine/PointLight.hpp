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

    class PointLights
    {

    private:
        std::vector<PointLight> m_lights;

        std::unique_ptr<Shader> m_shader;

        std::unique_ptr<Sphere> m_sphere;

    public:
        PointLights();
        ~PointLights() = default;

        void addPointLight(const glm::vec3 &position, const glm::vec3 &scale, const float &constant, const float &linear, const float &quadratic, const glm::vec3 &ambientColor, const glm::vec3 &diffuseColor);
        void resetPointLights();
        void deletePointLight(const glm::vec3 &position);

        inline std::vector<PointLight> getLights() { return m_lights; };

        void update(float const dt);

        void render();
    };
} // namespace engine