#include <engine/Renderer.hpp>
#include <engine/GLApplication.hpp>

namespace engine
{

    void Renderer::sendModelMatrixUniforms(const glm::mat4 &modelMatrix, Shader *shader, bool removeTranslationView)
    {
        // Update the view matrix by using the application camera
        updateViewMatrix();
        // Update the projection matrix by using the application camera
        updateProjectionMatrix();

        // If there is a need to remove the translation view (example: skybox object)
        if (removeTranslationView)
            m_view = glm::mat4(glm::mat3(m_view));

        shader->bind();

        glm::mat4 MVP = m_projection * m_view * modelMatrix;
        glm::mat4 MV = m_view * modelMatrix;
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MV));

        if (!removeTranslationView)
        {
            shader->setMat4("uModelViewMatrix", MV);
            shader->setMat4("uNormalMatrix", NormalMatrix);
        }
        shader->setMat4("uModelViewProjMatrix", MVP);

        shader->unbind();
    }

    void Renderer::sendBlinnPhongUniforms(Shader *shader) const
    {
        shader->bind();

        glm::mat4 modelLight = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0, 1, 0));
        glm::vec4 LightDirection = m_view * modelLight * glm::vec4(1, 1, 1, 0);

        shader->setVec3f("uLightDir_vs", LightDirection.x, LightDirection.y, LightDirection.z);
        shader->setVec3f("uLightIntensity", 1.0, 1.0, 1.0);
        shader->setVec3f("uKd", 1.0, 1.0, 1.0);
        shader->setVec3f("uKs", 1.0, 1.0, 1.0);
        shader->setFloat("uShininess", 16.0);

        shader->unbind();
    }

    void Renderer::sendDirectionalLightUniforms(Shader *shader) const
    {
        shader->bind();

        const auto lightDirectionInViewSpace = glm::normalize(glm::vec3(m_view * glm::vec4(m_scene->directionalLight()->direction(), 0.0f)));
        const auto lightIntensity = m_scene->directionalLight()->intensity();
        const auto lightColor = m_scene->directionalLight()->color();

        shader->setVec3f("uLightDirection",
                         lightDirectionInViewSpace[0],
                         lightDirectionInViewSpace[1],
                         lightDirectionInViewSpace[2]);

        shader->setVec3f("uLightIntensity",
                         lightIntensity[0],
                         lightIntensity[1],
                         lightIntensity[2]);

        shader->setVec3f("uLightColor",
                         lightColor[0],
                         lightColor[1],
                         lightColor[2]);

        shader->unbind();
    }

} // namespace engine