#pragma once
#ifndef _CubeMap_HPP_
#define _CubeMap_HPP_

#include <engine/Camera.hpp>
#include <engine/Shape.hpp>
#include <engine/VertexArrayObject.hpp>
#include <engine/VertexBufferObject.hpp>
#include <engine/Shader.hpp>
#include <engine/Container.hpp>
#include <engine/Iterator.hpp>
#include <engine/dependencies/glm.hpp>

#include <GL/glew.h>

#include <iostream>
#include <string>
#include <memory>

namespace engine
{

    /// \class CubeMap
    /// \brief Class for creating a cube map, a textured cube
    /// that contains 6 individual 2D textures that each form one side of a cube.
    class CubeMap
    {
    private:
        Container<GLfloat> m_vertices; /*!< Vertices of the cube map. */

        Container<std::string> m_faces; /*!< A vector containing all the path to each images used to create the cube map texture. */

        GLuint m_cubeMapTexture; /*!< The texture to apply to the cube map. */

        std::shared_ptr<Shader> m_shader; /*!< The shader to use for the cube map. */

        VertexArrayObject m_vao;  /*!< Vertex Array Object of the cube map. */
        VertexBufferObject m_vbo; /*!< Vertex Buffer Object of the cube map. */

        /// \brief Builds the Vertex Array Object of the cube map.
        void buildVAO();

        /// \brief Builds the Vertex Buffer Object of the cube map.
        void buildVBO();

    public:
        /// \brief Constructor.
        // explicit CubeMap(const char *cubeFront, const char *cubeLeft, const char *cubeBack,
        //         const char *cubeBottom, const char *cubeRight, const char *cubeTop, Shader *shader);
        explicit CubeMap(const char *cubeFront, const char *cubeLeft, const char *cubeBack,
                 const char *cubeBottom, const char *cubeRight, const char *cubeTop, Shader *shader);
        /// \brief Destructor.
        ~CubeMap() = default;

        /// \brief Renders the sphere to the screen/window.
        void render();

        /// \brief Returns the data (vertices) of the cube map.
        /// \return The container holding the vertices of the cube map.
        inline Container<GLfloat> getVertices() const { return m_vertices; };
    };

} // namespace engine

#endif /* _CubeMap_HPP_ */