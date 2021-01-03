#pragma once
#ifndef _AudioBuffer_HPP_
#define _AudioBuffer_HPP_

#include <AL/al.h>

#include <vector>

namespace engine
{
    /// \class AudioBuffer
    /// \brief Class that instanciates an audio buffer.
    class AudioBuffer
    {
    public:
        /// \brief Constructor.
        AudioBuffer();
        /// \brief Destructor.
        ~AudioBuffer();

        std::vector<ALuint> m_audioEffectBuffers; /*!< The audio buffer */

        /// \brief Method that load a sound file and put it into a buffer.
        /// \param filename : the path of the sound file.
        /// \return The buffer created.
        ALuint addAudioEffect(const char *filename);

        /// \brief Method that unload a buffer.
        /// \param buffer : the buffer to unload.
        /// \return A boolean for the success (or not) of the operation.
        bool removeAudioEffect(const ALuint &buffer);
    };

} // namespace engine

#endif /* _AudioBuffer_HPP_ */
