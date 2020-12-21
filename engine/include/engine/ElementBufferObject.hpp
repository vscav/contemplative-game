#pragma once
#ifndef _ElementBufferObject_HPP_
#define _ElementBufferObject_HPP_

#include <engine/Container.hpp>
#include <engine/dependencies/glm.hpp>

#include <vector>
#include <GL/glew.h>

namespace engine
{

    /// \class ElementBufferObject
    /// \brief Class used to represent an OpenGL EBO.
    class ElementBufferObject
    {
    private:
        GLuint m_index; /*!< The index of the EBO. */

    public:
        ///\brief Constructor.
        ElementBufferObject();

        ///\brief Destructor.
        ~ElementBufferObject();

        ///\brief Binds this EBO.
        void bind();

        ///\brief Unbinds the EBO.
        void unbind();

        /// \brief Creates and initializes an element buffer object's data store.
        /// \param indices : Specifies a pointer to indices that will be copied into the indices store for initialization.
        /// \param drawType : Specifies the expected usage pattern of the data store.
        template <typename T>
        void setData(const Container<T> &indices, const GLenum &drawType)
        {
            bind();
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(T) * indices.size(), indices.data(), drawType);
            unbind();
        }

        /// \brief Returns the ID of the EBO.
        /// \return The ID of the EBO.
        inline GLuint getId() const { return m_index; };
    };

} // namespace engine

#endif /* _ElementBufferObject_HPP_ */