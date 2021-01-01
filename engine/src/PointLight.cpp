#include <engine/PointLight.hpp>
#include <engine/Renderer.hpp>
#include <engine/utils/common.hpp>

#include <algorithm>

namespace engine
{

    PointLights::PointLights()
        : m_shader(new Shader("application/res/shaders/forward.vert", "application/res/shaders/pointlight.frag")),
          m_sphere(new Sphere(1, 64, 32))
    {
        if (applicationDebug)
            std::cout << "[PointLight] Point light created" << std::endl;
    }

    void PointLights::addPointLight(const glm::vec3 &position, const glm::vec3 &scale, const float &constant, const float &linear, const float &quadratic, const glm::vec3 &ambientColor, const glm::vec3 &diffuseColor)
    {
        m_lights.push_back(PointLight{position, scale, constant, linear, quadratic, ambientColor, diffuseColor});
    }

    void PointLights::resetPointLights()
    {
        m_lights.clear();
    }

    void PointLights::deletePointLight(const glm::vec3 &position)
    {
        m_lights.erase(std::remove_if(m_lights.begin(), m_lights.end(),
                                      [position](const PointLight &pointLight) {
                                          return pointLight.position == position;
                                      }),
                       m_lights.end());
    }

    void PointLights::update(const float dt)
    {
    }

    void PointLights::render()
    {
        m_shader->bind();

        for (GLuint i = 0; i < m_lights.size(); ++i)
        {
            glm::mat4 modelMatrix = glm::mat4(1.0f);
            modelMatrix = glm::translate(modelMatrix, m_lights[i].position);
            modelMatrix = glm::scale(modelMatrix, m_lights[i].scale);

            Renderer::getInstance().sendModelMatrixUniforms(modelMatrix, m_shader.get());

            std::string iStr = std::to_string(i);
            m_shader->setVec3f("pointsLightsAmbiantColor[" + iStr + "]", m_lights[i].ambientColor);
        }

        m_sphere->render();

        m_shader->unbind();
    }

} // namespace engine