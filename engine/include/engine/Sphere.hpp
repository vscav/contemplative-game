#pragma once
#ifndef _Sphere_HPP_
#define _Sphere_HPP_

#include <engine/Camera.hpp>
#include <engine/Shape.hpp>
#include <engine/VertexBufferObject.hpp>
#include <engine/VertexArrayObject.hpp>
#include <engine/Shader.hpp>
#include <engine/Container.hpp>
#include <engine/dependencies/glm.hpp>

#include <cmath>
#include <vector>
#include <iostream>
#include <memory>

namespace engine
{

    /// \class Sphere
    /// \brief Class used to represent a sphere.
    class Sphere
    {
        /// \brief Build the sphere mesh.
        /// \param radius : The radius of the sphere.
        /// \param discLat : The number of segments to discretize the latitude of the sphere.
        /// \param discLong : The number of segments to discretize the longitude of the sphere.
        void build(GLfloat radius, GLsizei discLat, GLsizei discLong);

    private:
        Container<ShapeVertex> m_vertices; /*!< Vertices of the sphere. */
        GLsizei m_nVertexCount;            /*!< Number of vertices. */

        std::shared_ptr<Shader> m_shader; /*!< The shader to use for the sphere. */

        VertexArrayObject m_vao;  /*!< Vertex Array Object of the sphere. */
        VertexBufferObject m_vbo; /*!< Vertex Buffer Object of the sphere. */

        /// \brief Builds the Vertex Array Object of the sphere.
        void buildVAO();

        /// \brief Builds the Vertex Buffer Object of the sphere.
        void buildVBO();

    public:
        /// \brief Builds the Vertex Buffer Object of the sphere.
        /// \param radius : The radius of the sphere.
        /// \param discLat : The number of segments to discretize the latitude of the sphere.
        /// \param discLong : The number of segments to discretize the longitude of the sphere.
        Sphere(GLfloat radius, GLsizei discLat, GLsizei discLong, Shader *shader);
        ~Sphere() = default;

        /// \brief Returns the data (vertices) of the sphere.
        /// \return The data (vertices) of the sphere.
        inline Container<ShapeVertex> getVertices() const { return m_vertices; };

        /// \brief Returns the number of vertices of the sphere.
        /// \return The number of vertices of the sphere.
        inline GLsizei getVertexCount() const { return m_nVertexCount; };

        /// \brief Renders the sphere to the screen/window.
        void render();
    };

} // namespace engine

#endif /* _Sphere_HPP_ */