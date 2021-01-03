#pragma once
#ifndef _Entity_HPP_
#define _Entity_HPP_

#include <engine/Model.hpp>
#include <engine/utils/common.hpp>
#include <engine/dependencies/glm.hpp>

#include <memory>

namespace engine
{

    /// \struct Transform
    /// \brief Structure fo representing the transformations of an entity
    struct Transform
    {
    public:
        const glm::vec3 m_position;
        const glm::vec3 m_scale;
        const glm::vec3 m_rotation;
        Transform(
            const glm::vec3 &position = glm::vec3(0.0f),
            const glm::vec3 &scale = glm::vec3(1.0f),
            const glm::vec3 &rotation = glm::vec3(0.0f))
            : m_position(position), m_scale(scale), m_rotation(rotation){};
    };

    /// \class Entity
    /// \brief Class which represents a general renderable entity.
    class Entity
    {
    protected:
        std::unique_ptr<Model> m_model; /*!< 3D GLTF model of the entity. */

        std::unique_ptr<Shader> m_shader; /*!< The shader to use for the entity. */

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
        /// \param isStatic : Whether the entity is able to move.
        /// \param transform : The initial transformation to apply to the entity.
        Entity(
            Model *model,
            Shader *shader,
            const bool isStatic = false,
            const Transform &transform = Transform());

        /// \brief Default destructor.
        ~Entity() = default;

        /// \brief Checks if the entity intersects another entity.
        /// \param  other : The other entity.
        /// \return  A boolean to tell if the entity has intersected another entity.
        bool intersect(Entity &other);

        /// \brief Implements the collision behavior when colliding an other entity.
        /// \param  other : The other entity.
        virtual void doCollisionWith(Entity &other){};

        /// \brief Returns the transform matrix of the entity.
        /// \return The transformation of the entity.
        virtual const glm::mat4 getMatrix();

        /// \brief Updates the entity.
        void update(const float dt);

        /// \brief Renders the entity.
        void render();

        /// \brief Gets the position of the entity.
        /// \return The position of the entity.
        inline const glm::vec3 &getPosition() const { return m_position; };
        /// \brief Sets the position of the entity.
        /// \param position : The new position to apply to the entity.
        inline void setPosition(glm::vec3 position) { m_position = position; };

        /// \brief Gets the rotation of the entity.
        /// \return The rotation of the entity.
        inline const glm::vec3 &getRotation() const { return m_rotation; };
        /// \brief Gets the rotation of the entity.
        /// \param rotation : The new rotation to apply to the entity.
        inline void setRotation(glm::vec3 rotation) { m_rotation = rotation; };

        /// \brief Gets the scale of the entity.
        /// \return The scale of the entity.
        inline const glm::vec3 &getScale() const { return m_scale; };
        /// \brief Gets the scale of the entity.
        /// \param scale : The new scale to apply to the entity.
        inline void setScale(glm::vec3 scale) { m_scale = scale; };

        /// \brief Gets the model of the entity.
        /// \return The model used by the entity.
        inline const Model *getModel() const { return m_model.get(); };

        /// \brief Returns a boolean to tell whether the entity is able to move.
        /// \return A boolean to tell whether the entity is able to move.
        inline const bool &isStatic() const { return m_isStatic; };
    };

} // namespace engine

#endif
