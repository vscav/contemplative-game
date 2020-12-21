#include <engine/FilePath.hpp>

namespace engine
{
    FilePath::FilePath(const char *filepath) : m_FilePath(filepath)
    {
        format();
    }

    FilePath::FilePath(const std::string &filepath) : m_FilePath(filepath)
    {
        format();
    }

    void FilePath::format()
    {
        for (size_t i = 0; i < m_FilePath.size(); ++i)
        {
            if (m_FilePath[i] == '\\' || m_FilePath[i] == '/')
            {
                m_FilePath[i] = PATH_SEPARATOR;
            }
        }
        while (!m_FilePath.empty() && m_FilePath.back() == PATH_SEPARATOR)
        {
            m_FilePath.pop_back();
        }
    }

    FilePath FilePath::dirPath() const
    {
        size_t pos = m_FilePath.find_last_of(PATH_SEPARATOR);
        if (pos == std::string::npos)
        {
            return FilePath();
        }
        return m_FilePath.substr(0, pos);
    }

    std::string FilePath::file() const
    {
        size_t pos = m_FilePath.find_last_of(PATH_SEPARATOR);
        if (pos == std::string::npos)
        {
            return m_FilePath;
        }
        return m_FilePath.substr(pos + 1);
    }

    std::string FilePath::ext() const
    {
        size_t pos = m_FilePath.find_last_of('.');
        if (pos == std::string::npos || pos == 0)
        {
            return "";
        }
        return m_FilePath.substr(pos + 1);
    }

    bool FilePath::hasExt(const std::string &ext) const
    {
        int offset = (int)m_FilePath.size() - (int)ext.size();
        return offset >= 0 && m_FilePath.substr(offset, ext.size()) == ext;
    }

    FilePath FilePath::operator+(const FilePath &other) const
    {
        if (m_FilePath.empty())
        {
            return other;
        }
        else
        {
            if (other.empty())
            {
                return m_FilePath;
            }
            FilePath copy(*this);
            if (other.m_FilePath.front() != PATH_SEPARATOR)
            {
                copy.m_FilePath += PATH_SEPARATOR;
            }
            copy.m_FilePath += other.m_FilePath;
            return copy;
        }
    }
} // namespace engine