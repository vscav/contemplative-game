#pragma once
#ifndef _Entity_HPP_
#define _Entity_HPP_

#include <engine/Model.hpp>
#include <engine/dependencies/glm.hpp>

#include <memory>

namespace engine
{

    /// \brief Structure fo representing the transformations of an entity
    struct Transform
    {
    public:
        const glm::vec3 &m_position = glm::vec3(0);
        const glm::vec3 &m_scale = glm::vec3(1);
        const glm::vec3 &m_rotation = glm::vec3(0);
        Transform(
            const glm::vec3 &position = glm::vec3(0),
            const glm::vec3 &scale = glm::vec3(1),
            const glm::vec3 &rotation = glm::vec3(0))
            : m_position(position), m_scale(scale), m_rotation(rotation){};
    };

    /// \brief Class which represents a general renderable entity.
    class Entity
    {
    protected:
        std::shared_ptr<Model> m_model; /*!< 3D GLTF model of the entity. */

        std::shared_ptr<Shader> m_shader; /*!< The shader to use for the entity. */

        bool m_isStatic = false; /*!< Is the entity static (eg. the entity is unable to move) ? */

        glm::vec3 m_position; /*!< Position of the entity. */
        glm::vec3 m_scale;    /*!< Scale of the entity. */
        glm::vec3 m_rotation; /*!< Rotation of the entity. */

        bool m_hasMatrix = false;    /*!< Does the entity have a matrix ? */
        glm::mat4 m_transformMatrix; /*!< Transformation matrix of the entity in case the entity is static. */

    public:
        /// \brief Parameterized constructor.
        /// \param model : The GLTF model of the entity.
        /// \param shader : The shader to use for the entity.
        /// \param isStatic : Whether the entity is able to move or not.
        /// \param transform : The initial transformation to apply to the entity.
        Entity(
            Model *model,
            Shader *shader,
            const bool isStatic = false,
            const Transform &transform = Transform());

        /// \brief Copy constructor.
        /// \param other : The entity to copy from.
        Entity(const Entity &other);

        ~Entity() = default;

        /// \brief Returns the transform matrix of the entity.
        virtual const glm::mat4 getMatrix();

        // void moveFront(float dt);
        // void moveLeft(float dt);

        // /// \brief Updates the entity.
        // void update(float time);

        /// \brief Renders the entity.
        void render();

        /// \brief Gets the position of the entity.
        inline const glm::vec3 &getPosition() const { return m_position; };
        /// \brief Sets the position of the entity.
        inline void setPosition(glm::vec3 position) { m_position = position; };

        /// \brief Gets the rotation of the entity.
        inline const glm::vec3 &getRotation() const { return m_rotation; };
        /// \brief Gets the rotation of the entity.
        inline void setRotation(glm::vec3 rotation) { m_rotation = rotation; };

        /// \brief Gets the scale of the entity.
        inline const glm::vec3 &getScale() const { return m_scale; };
        /// \brief Gets the scale of the entity.
        inline void setScale(glm::vec3 scale) { m_scale = scale; };

        /// \brief Gets the model of the entity.
        inline const Model *getModel() const { return m_model.get(); };

        /// \brief Returns a boolean to tell whether the entity is able to move or not.
        inline const bool &isStatic() const { return m_isStatic; };
    };

} // namespace engine

#endif
