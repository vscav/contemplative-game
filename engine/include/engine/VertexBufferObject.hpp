#pragma once
#ifndef _VertexBufferObject_HPP_
#define _VertexBufferObject_HPP_

#include <engine/dependencies/glm.hpp>
#include <engine/Container.hpp>

#include <GL/glew.h>

#include <vector>

namespace engine
{

    /// \class VertexBufferObject
    /// \brief Class used to represent an OpenGL VBO.
    class VertexBufferObject
    {

    private:
        GLuint m_index; /*!< The index of the VBO. */

    public:
        /// \brief Constructor.
        VertexBufferObject();
        /// \brief Destructor.
        ~VertexBufferObject();

        /// \brief Binds the VBO.
        void bind();
        /// \brief Unbinds the VBO.
        void unbind();

        /// \brief Creates and initializes a buffer object's data store.
        /// \param data : Specifies a pointer to data that will be copied into the data store for initialization.
        /// \param drawType : Specifies the expected usage pattern of the data store.
        template <typename T>
        void setData(const Container<T> &data, const GLenum &drawType)
        {
            bind();
            glBufferData(GL_ARRAY_BUFFER, sizeof(T) * data.size(), data.data(), drawType);
            unbind();
        }

        /// \brief Defines an array of generic vertex attribute data.
        /// \param VertexBufferObjectID : Specifies the index of the generic vertex attribute to be modified.
        /// \param size : Specifies the number of components per generic vertex attribute.
        /// \param dataType : Specifies the data type of each component in the array.
        /// \param stride : Specifies the byte offset between consecutive generic vertex attributes.
        /// \param offset : Specifies a offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the target.
        static void setVertexAttrib(const GLuint &VertexBufferObjectID, const GLuint &size, GLenum dataType, const GLuint &stride, const GLuint &offset);

        /// \brief Returns the ID of the VBO instance.
        /// \brief The ID of the VBO instance.
        inline GLuint getId() const { return m_index; }
    };

} // namespace engine

#endif /* _VertexBufferObject_HPP_ */