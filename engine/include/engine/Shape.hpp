#pragma once
#ifndef _Shape_HPP_
#define _Shape_HPP_

#include <engine/dependencies/glm.hpp>

#include <GL/glew.h>

namespace engine
{

    /// \struct ShapeVertex
    /// \brief Structure used to represent a type of vertex.
    struct ShapeVertex
    {
        glm::vec3 position;  /*!< Position of the vertex. */
        glm::vec3 normal;    /*!< Normal of the vertex. */
        glm::vec2 texCoords; /*!< Texture coordinates of the vertex. */
    };

} // namespace engine

#endif /* _Shape_HPP_ */