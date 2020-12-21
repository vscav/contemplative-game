#include <engine/EngineException.hpp>

#include <iostream>

namespace engine
{

    EngineException::EngineException(const std::string &message, const char *file, const int line)
        : m_message(message), m_file(file), m_line(line)
    {
    }

    const char *EngineException::what() const noexcept
    {
        std::cerr << COLOR_RED << "EngineException: " << COLOR_RESET;
        std::cerr << "[" << m_file << ":" << std::to_string(m_line) << "]" << std::endl;

        return m_message.c_str();
    }

} // namespace engine