#pragma once
#ifndef _FilePath_HPP_
#define _FilePath_HPP_

#include <string>

namespace engine
{
    /// \class FilePath
    /// \brief Utility class to create and work easily with file paths.
    class FilePath
    {
    private:
        /// \brief Reformat the path based on the OS.
        void format();

        std::string m_FilePath; /*!< The string file path. */

    public:
#ifdef _WIN32
        static const char PATH_SEPARATOR = '\\';
#else
        static const char PATH_SEPARATOR = '/';
#endif

        /// \brief Constructor.
        FilePath() = default;

        /// \brief Parameterized constructor.
        /// \param filepath : The filepath (const char).
        FilePath(const char *filepath);

        /// \brief Parameterized constructor.
        /// \param filepath : The filepath (string).
        FilePath(const std::string &filepath);

        inline operator std::string() const { return m_FilePath; };

        inline const std::string &str() const { return m_FilePath; };

        /// \brief Returns a pointer to an array that contains the sequence of characters
        /// representing the current value of the string filepath.
        /// \return The path (const char) of the file.
        inline const char *c_str() const { return m_FilePath.c_str(); };

        /// \brief Returns whether the string file path is empty (i.e. whether its length is 0).
        /// \return A boolean that indicates whether the string filepath is empty.
        inline bool empty() const { return m_FilePath.empty(); };

        /// \brief Returns the path of a filepath.
        /// \return The path of the filepath.
        FilePath dirPath() const;

        /// \brief Returns the file of a filepath.
        /// \return The file of the filepath.
        std::string file() const;

        /// \brief Returns the file extension.
        /// \return The file extension.
        std::string ext() const;

        /// \brief Returns whether the file path has a specific extension.
        /// \param ext : The extension with which it must be compared.
        /// \return A boolean that indicates whether the file path has a specific extension.
        bool hasExt(const std::string &ext) const;

        /// \brief Adds an extension to the file.
        /// \param ext : The extension (string) to add to the filepath.
        /// \return The new filepath with its extension.
        inline FilePath addExt(const std::string &ext = "") const { return FilePath(m_FilePath + ext); };

        /// \brief Concatenates two file paths.
        /// \brief other : The filepath to concatenate.
        /// \return The resulting filepath from the concatenation.
        FilePath operator+(const FilePath &other) const;

        /// \brief Compares two filepaths and tells if they are equal.
        /// \param other : The filepath to compare with.
        /// \return A boolean that indicates whether the two filepaths are equal.
        inline bool operator==(const FilePath &other) const { return other.m_FilePath == m_FilePath; };

        /// \brief Compares two filepaths and tells if they are different.
        /// \param other : The filepath to compare with.
        /// \return A boolean that indicates whether the two filepaths are different.
        inline bool operator!=(const FilePath &other) const { return !operator==(other); };

        /// \brief Outputs a filepath.
        /// \param cout : The std::cout object.
        /// \param filepath : The filepath object to output.
        /// \return The output stream.
        inline friend std::ostream &operator<<(std::ostream &cout, const FilePath &filepath) { return (cout << filepath.m_FilePath); };
    };

} // namespace engine

namespace std
{
    template <>
    struct hash<engine::FilePath>
    {
        std::size_t operator()(const engine::FilePath &k) const
        {
            return std::hash<std::string>()(k.str());
        }
    };
} // namespace std

#endif /* _FilePath_HPP_ */
