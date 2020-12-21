#pragma once

#include <engine/dependencies/glm.hpp>
#include <engine/FilePath.hpp>

#include <vector>
#include <memory>
#include <unordered_map>

namespace engine
{
    /// \class Texture
    /// \brief Class used to represent a texture object.
    class Texture
    {
    private:
        unsigned int m_width = 0u;            /*!< The width of the image. */
        unsigned int m_height = 0u;           /*!< The height of the image. */
        std::unique_ptr<glm::vec4[]> m_pixels; /*!< A unique pointer of the array containing the pixels of the image. */

    public:
        /// \brief Constructor.
        explicit Texture(unsigned int width, unsigned int height);

        /// \brief Gets the width of the image.
        /// \return The width of the image.
        inline unsigned int getWidth() const { return m_width; };

        /// \brief Gets the height of the image.
        /// \return The height of the image.
        inline unsigned int getHeight() const { return m_height; };

        /// \brief Gets the pixels of the image.
        /// \return A pointer to the pixels data of the image.
        inline const glm::vec4 *getPixels() const { return m_pixels.get(); };

        /// \brief Gets the pixels of the image.
        /// \return A pointer to the pixels data of the image.
        inline glm::vec4 *getPixels() { return m_pixels.get(); };
    };

    /// \brief Loads an image.
    /// \param filepath : The filepath (FilePath object) to the image.
    /// \return A unique pointer to the loaded image.
    std::unique_ptr<Texture> loadImage(const FilePath &filepath);

    /// \class TextureManager
    /// \brief Class for managing all the images used as texture.
    class TextureManager
    {
    private:
        static std::unordered_map<FilePath, std::unique_ptr<Texture>> m_textureMap; /*!< A map to store already loaded images. */

    public:
        /// \brief Loads the texture from a filepath object.
        /// \param filepath : The filepath (FilePath object) to the image.
        /// \return A pointer to the texture created.
        static const Texture *loadImage(const FilePath &filepath);
    };

} // namespace engine
