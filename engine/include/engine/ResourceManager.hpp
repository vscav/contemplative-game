#pragma once
#ifndef _ResourceManager_HPP_
#define _ResourceManager_HPP_

#include <engine/Texture.hpp>
#include <engine/Container.hpp>
#include <engine/FilePath.hpp>

#include <GL/glew.h>

#include <unordered_map>
#include <vector>
#include <memory>

namespace engine
{
    /// \class ResourceManager
    /// \brief Class used to manage the resources of the application.
    class ResourceManager
    {
    private:
        /// \brief Default constructor.
        ResourceManager() = default;
        /// \brief Default destructor.
        ~ResourceManager() = default;

    public:
        /// \brief Returns the current resource manager instance.
        /// \return The instance of the current resource manager.
        static ResourceManager &getInstance()
        {
            static ResourceManager instance;
            return instance;
        }

        /// \brief Copy constructor.
        ResourceManager(ResourceManager const &) = delete;
        /// \brief Affectation operator.
        ResourceManager &operator=(ResourceManager const &) = delete;

        /// \brief Loads an image and generates an OpenGL texture.
        /// \param path : The path to the texture image.
        GLuint loadTexture(const std::string &path);

        /// \brief Loads images and generates a cube map texture.
        /// \param faces : The container which holds the path to each texture image of the cube map.
        GLuint loadCubeMapTexture(Container<std::string> &faces);
    };

} // namespace engine

#endif /* _ResourceManager_HPP_ */