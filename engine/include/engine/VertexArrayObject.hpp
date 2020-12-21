#pragma once
#ifndef _VertexArrayObject_HPP_
#define _VertexArrayObject_HPP_

#include <engine/dependencies/glm.hpp>

#include <GL/glew.h>

namespace engine
{

    /// \class VertexArrayObject
    /// \brief Class used to represent an OpenGL VAO.
    class VertexArrayObject
    {

    private:
        GLuint m_index; /*!< The index of the VAO. */

    public:
        /// \brief Constructor.
        VertexArrayObject();
        /// \brief Destructor.
        ~VertexArrayObject();

        /// \brief Binds the VAO.
        void bind();
        /// \brief Unbinds the VAO.
        void unbind();

        /// \brief Returns the ID of the VAO instance.
        /// \return The ID of the VAO instance.
        inline GLuint getId() const { return m_index; }

        struct VaoRange
        {
            GLsizei begin; /*!< Index of first element in the vertex array Object. */
            GLsizei count; /*!< Number of elements in range. */
        };
    };

} // namespace engine

#endif /* _VertexArrayObject_HPP_ */