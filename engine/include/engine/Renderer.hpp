#pragma once
#ifndef _Renderer_HPP_
#define _Renderer_HPP_

#include <engine/Camera.hpp>
#include <engine/Shader.hpp>
#include <engine/dependencies/glm.hpp>

#include <vector>
#include <memory>

namespace engine
{

    class Renderer
    {
    private:
        /// \brief Default constructor
        Renderer() = default;
        /// \brief Default destructor
        ~Renderer() = default;

        std::shared_ptr<Camera> m_camera; /*!< A shared pointer to the camera of the application. */

        glm::mat4 m_view;       /*!< The current view matrix. */
        glm::mat4 m_projection; /*!< The current projection matrix. */

    public:
        /// \brief Returns the current renderer instance.
        /// \return The instance of the current renderer.
        static Renderer &getInstance()
        {
            static Renderer instance;
            return instance;
        }

        /// \brief Copy constructor.
        Renderer(const Renderer &) = delete;
        /// \brief Affectation/Copy assignment operator.
        Renderer &operator=(const Renderer &) = delete;

        /// \brief Sends the matrix uniforms to the dedicated shader.
        /// \param modelMatrix : The model matrix used to compute the view matrix.
        /// \param shader : The shader on which the matrix uniforms will be send.
        /// \param removeTranslationView : A boolean to tell whether the translation view need to be removed or not.
        void sendModelMatrixUniforms(const glm::mat4 &modelMatrix, Shader *shader, bool removeTranslationView = false);

        /// \brief Sends the blinn phong model uniforms to the dedicated shader.
        /// \param shader : The shader on which the blinn phong uniforms will be send.
        void sendBlinnPhongUniforms(Shader *shader) const;

        /// \brief Updates the renderer view matrix based on the current camera.
        inline void updateViewMatrix() { m_view = m_camera->getViewMatrix(); };

        /// \brief Updates the renderer projection matrix based on the current camera.
        inline void updateProjectionMatrix() { m_projection = m_camera->getProjectionMatrix(); };

        /// \brief Sets the camera of the renderer.
        /// \param camera : The camera to be set as the renderer camera.
        inline void setCamera(std::shared_ptr<Camera> camera) { m_camera = std::move(camera); };

        /// \brief Returns the view matrix of the renderer (based on the camera).
        /// \return The view matrix.
        inline glm::mat4 getViewMatrix() { return m_camera->getViewMatrix(); };

        /// \brief Returns the projection matrix of the renderer (based on the camera).
        /// \return The projection matrix.
        inline glm::mat4 getProjectionMatrix() { return m_camera->getProjectionMatrix(); };
    };

} // namespace engine

#endif /* _Renderer_HPP_ */