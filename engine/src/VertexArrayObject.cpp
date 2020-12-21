#include <engine/VertexArrayObject.hpp>
#include <engine/utils/common.hpp>

#include <iostream>

namespace engine
{

    VertexArrayObject::VertexArrayObject()
    {
        glGenVertexArrays(1, &m_index);
    }

    VertexArrayObject::~VertexArrayObject()
    {
        if(debug) std::cout << "[VAO] Delete VAO with index " << m_index << std::endl;
        glDeleteVertexArrays(1, &m_index);
    }

    void VertexArrayObject::bind()
    {
        glBindVertexArray(m_index);
    }

    void VertexArrayObject::unbind()
    {
        glBindVertexArray(0);
    }

} // namespace engine