#include <engine/Entity.hpp>
#include <engine/Renderer.hpp>

namespace engine
{

    Entity::Entity(
        Model *model,
        Shader *shader,
        const bool isStatic,
        const Transform &transform)
        : m_model(model), m_shader(shader), m_isStatic(isStatic),
          m_position(transform.m_position), m_scale(transform.m_scale), m_rotation(transform.m_rotation)
    {
    }

    Entity::Entity(const Entity &other)
        : m_model(other.m_model), m_shader(other.m_shader), m_isStatic(other.m_isStatic),
          m_position(other.m_position), m_scale(other.m_scale), m_rotation(other.m_rotation)
    {
    }

    bool Entity::intersect(Entity &other)
    {
        float selfScale = (glm::abs(m_scale.x) + glm::abs(m_scale.y) + glm::abs(m_scale.z)) / 3.0f;
        float otherScale = (glm::abs(other.m_scale.x) + glm::abs(other.m_scale.y) + glm::abs(other.m_scale.z)) / 3.0f;

        return (
            m_model->collider().intersect(
                other.m_model->collider(),
                getMatrix(),
                selfScale,
                other.getMatrix(),
                otherScale));
    }

    const glm::mat4 Entity::getMatrix()
    {
        if (m_isStatic && m_hasMatrix)
        {
            return m_transformMatrix;
        }

        glm::mat4 entityMatrix = glm::mat4(1);

        entityMatrix = glm::translate(entityMatrix, m_position);

        entityMatrix = glm::rotate(entityMatrix, m_rotation[0], -glm::vec3(1.0f, 0.0f, 0.0f));
        entityMatrix = glm::rotate(entityMatrix, m_rotation[1], -glm::vec3(0.0f, 1.0f, 0.0f));
        entityMatrix = glm::rotate(entityMatrix, m_rotation[2], -glm::vec3(0.0f, 0.0f, 1.0f));

        entityMatrix = glm::scale(entityMatrix, m_scale);

        if (m_isStatic)
        {
            m_transformMatrix = entityMatrix;
            m_hasMatrix = true;
        }

        return entityMatrix;
    }

    void Entity::update(const float dt)
    {
    }

    void Entity::render()
    {
        Renderer::getInstance().sendModelMatrixUniforms(getMatrix(), m_shader.get());

        m_model->render(m_shader.get());
    }

} // namespace engine
