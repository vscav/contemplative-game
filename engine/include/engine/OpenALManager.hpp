#pragma once
#ifndef _OpenALManager_HPP_
#define _OpenALManager_HPP_

#include <engine/GLAudioManager.hpp>
#include <engine/AudioDevice.hpp>
#include <engine/AudioListener.hpp>
#include <engine/AudioSource.hpp>
#include <engine/AudioBuffer.hpp>
#include <AL/al.h>


#include <iostream>
#include <string>
#include <fstream>
#include <memory>

namespace engine
{

    /// \class GLFWManager
    /// \brief Class which is the implementation of the abstract base class GLAudioManager, and which uses the
    /// OpenAL cross-platform library to create the sound context and manage the sounds entities
    class OpenALManager final : public GLAudioManager
    {
    protected:
        std::unique_ptr<AudioDevice> m_audioDevice; /*!< A pointer to the sound device used to render the audio*/
        std::unique_ptr<AudioListener> m_audioListener; /*!< A pointer to the listener of the sounds in the scene */


        std::unique_ptr<AudioSource> m_audioSource;
        std::unique_ptr<AudioBuffer> m_audioBuffer;
        ALint m_isPlaying=AL_STOPPED;


    public:
        /// \brief Constructor.
        explicit OpenALManager();
        /// \brief Destructor.
        inline ~OpenALManager() override { destroy(); };

        /// \brief Creates and Initializes the OpenAL context.
        /// \return An integer acting as a boolean for success/fail information.
        int initialize() override;

        /// \brief Updates the context (should be called every frame).
        void update() override;

        /// \brief Destroys the OpenAL context.
        void destroy() override;

    };

} // namespace engine

#endif /* _GLFWManager_HPP_ */
