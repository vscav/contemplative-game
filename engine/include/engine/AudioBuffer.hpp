#pragma once
#ifndef _AudioBuffer_HPP_
#define _AudioBuffer_HPP_

#include <AL/al.h>

#include <vector>

namespace engine
{
    /// \class AudioBuffer
    /// \brief Class that instanciates an audio buffer and avoid the creation of multiple audio buffers.
    class AudioBuffer
    {
    private:



    public:
        /// \brief Constructor
        AudioBuffer();
        /// \brief Destructor
        ~AudioBuffer();

        ALuint addAudioEffect(const char *filename);
        bool removeAudioEffect(const ALuint &buffer);
        std::vector<ALuint> m_audioEffectBuffers;
    };

} // namespace engine

#endif /* _AudioBuffer_HPP_ */
