#pragma once
#ifndef _AudioSource_HPP_
#define _AudioSource_HPP_

#include <AL/al.h>

namespace engine
{

    class AudioSource
    {
    private:
        float m_gain = 1.f; /*!< A float that represent the gain (volume) applied to the sound source */
        float m_pitch = 1.f; /*!< A float that represent the pitch applied to the sound source */
        float m_position[3] = {0, 0, 0}; /*!< An array that represent the position of the source */
        float m_velocity[3] = {0, 0, 0}; /*!< An array that represent the velocity of the source */
        bool m_loopAudio = false; /*!< An bolean to know if we loop the audio */
        ALuint m_buffer = 0; /*!< The buffer associated to the source */

    public:
        ALuint m_source; /*!< The source itself */

        /// \brief Constructor.
        AudioSource();

        /// \brief Destructor.
        ~AudioSource();

        void setBuffer(const ALuint buffer_to_play);

        /// \brief Method to make the source start playing the sound
        void play();

        /// \brief Method to pause the source playing the sound
        void pause();

        /// \brief Method to stop the source
        void stop();
    };

} // namespace engine

#endif /* _AudioSource_HPP_ */
