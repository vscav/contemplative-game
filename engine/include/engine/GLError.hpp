#pragma once
#ifndef _GLError_HPP_
#define _GLError_HPP_

#include <GL/glew.h>

#include <iostream>
#include <string>

namespace engine
{

    /// \brief An utility function to print a specific OpenGL error to the console.
    /// \param file : The file in which the error occured.
    /// \param line : The line of the file where the error occured.
    void glCheckError(const char *file, unsigned int line);

} // namespace engine

#endif /* _GLError_HPP_ */
