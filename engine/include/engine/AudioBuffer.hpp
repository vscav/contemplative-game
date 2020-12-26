#pragma once
#ifndef _AudioBuffer_HPP_
#define _AudioBuffer_HPP_

#include <AL/al.h>

#include <vector>

namespace audio
{
    /// \class AudioBuffer
    /// \brief Class (singleton) that instanciates an audio buffer and avoid the creation of multiple audio buffers.
    class AudioBuffer
    {
    private:
        /// \brief Constructor
        AudioBuffer();
        /// \brief Destructor
        ~AudioBuffer();

        std::vector<ALuint> m_audioEffectBuffers;

    public:
        static AudioBuffer *getInstance();

        ALuint addAudioEffect(const char *filename);
        bool removeAudioEffect(const ALuint &buffer);
    };

} // namespace audio

#endif /* _AudioBuffer_HPP_ */