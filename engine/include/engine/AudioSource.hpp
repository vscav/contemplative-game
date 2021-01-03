#pragma once
#ifndef _AudioSource_HPP_
#define _AudioSource_HPP_

#include <engine/dependencies/glm.hpp>

#include <AL/al.h>

namespace engine
{

    /// \class AudioSource
    /// \brief A class that instanciates an audio source, an object emitting sounds.
    class AudioSource
    {
    private:
        float m_gain = 1.f;              /*!< A float that represent the gain (volume) applied to the sound source. */
        float m_pitch = 1.f;             /*!< A float that represent the pitch applied to the sound source. */
        float m_position[3] = {0, 0, 0}; /*!< An array that represent the position of the source. */
        float m_velocity[3] = {0, 0, 0}; /*!< An array that represent the velocity of the source. */
        bool m_loopAudio = false;        /*!< An bolean to know if we loop the audio. */
        ALuint m_buffer = 0;             /*!< The buffer associated to the source. */

    public:
        ALuint m_source; /*!< The source itself */

        /// \brief Constructor.
        AudioSource();

        /// \brief Destructor.
        ~AudioSource();

        /// \brief Sets the buffer to play in the source.
        /// \param bufferToPlay : The buffer to play.
        void setBuffer(const ALuint bufferToPlay);

        /// \brief Makes the source start playing.
        void play();

        /// \brief Pauses the source.
        void pause();

        /// \brief Stops the source.
        void stop();

        /// \brief Sets the new position of the source.
        /// \param newPosition : The new position of the source.
        void setPosition(const glm::vec3 newPosition);

        /// \brief Sets the status in order to play in loop.
        /// \param isLooping : A boolean to tell whether the source is looping.
        void setLooping(ALint isLooping);

        /// \brief Sets the gain of the source.
        /// \param gain : A float representing the value of the gain.
        void setGain(float gain);
    };

} // namespace engine

#endif /* _AudioSource_HPP_ */
