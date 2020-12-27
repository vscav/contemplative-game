#pragma once
#ifndef _OpenALManager_HPP_
#define _OpenALManager_HPP_

#include <engine/GLAudioManager.hpp>
#include <engine/AudioDevice.hpp>
#include <engine/AudioListener.hpp>
#include <engine/AudioSource.hpp>
//#include <engine/AudioBuffer.hpp>


#include <iostream>
#include <string>
#include <fstream>
#include <memory>

namespace engine
{

    /// \class GLFWManager
    /// \brief Class which is the implementation of the abstract base class GLWindowManager, and which uses the
    /// GLFW cross-platform library to create a window, process input (to communicate with the inputs manager) and create the OpenGL
    /// context.
    class OpenALManager final : public GLAudioManager
    {
    protected:
        std::unique_ptr<AudioDevice> m_audioDevice;
        std::unique_ptr<AudioListener> m_audioListener;
        std::unique_ptr<AudioSource> m_audioSource;
        //std::unique_ptr<AudioBuffer> m_audioBuffer;


    public:
        /// \brief Constructor.
        /// \param title : The window/application title.
        /// \param width : The window width value.
        /// \param height : The window height value.
        /// \param fullScreen : A boolean to determine if the window is in full screen mode.
        explicit OpenALManager();
        /// \brief Destructor.
        inline ~OpenALManager() override { destroy(); };

        /// \brief Initializes the window and creates the OpenGL context.
        /// \return An integer acting as a boolean for success/fail information.
        int initialize() override;

        /// \brief Updates the window (should be called every frame).
        void update() override;

        /// \brief Destroys the window and the OpenGL context.
        void destroy() override;

    };

} // namespace engine

#endif /* _GLFWManager_HPP_ */
