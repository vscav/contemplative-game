#pragma once
#ifndef _EngineException_HPP_
#define _EngineException_HPP_

#include <engine/utils/cout_colors.hpp>

#include <string>
#include <exception>

namespace engine
{
    /// \class EngineException
    /// \brief Class for managing the exception thrown inside the engine core.
    class EngineException : public std::exception
    {
    protected:
        std::string m_message; /*!< The message describing the exception thrown. */
        std::string m_file;    /*!< The file in which the exception was thrown. */
        int m_line;            /*!< The line of the file in which the exception was thrown. */

    public:
        /// \brief Parameterized constructor.
        /// \param message : The message describing the exception thrown.
        /// \param file : The file in which the exception was thrown.
        /// \param line : The line of the file in which the exception was thrown.
        EngineException(const std::string &message, const char *file, const int line);

        /// \brief Default destructor.
        ~EngineException() = default;

        /// \brief Get the string identifying exception.
        const char *what() const noexcept override;
    };

} // namespace engine

#endif /* _EngineException_HPP_ */