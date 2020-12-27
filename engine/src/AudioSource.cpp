#include <engine/AudioSource.hpp>

#include <iostream>

namespace engine
{

    AudioSource::AudioSource()
    {
        alGenSources(1, &m_source);
        alSourcef(m_source, AL_PITCH, m_pitch);
        alSourcef(m_source, AL_GAIN, m_gain);
        alSource3f(m_source, AL_POSITION, m_position[0], m_position[1], m_position[2]);
        alSource3f(m_source, AL_VELOCITY, m_velocity[0], m_velocity[1], m_velocity[2]);
        alSourcei(m_source, AL_LOOPING, m_loopAudio);
        alSourcei(m_source, AL_BUFFER, m_buffer);
    }

    AudioSource::~AudioSource()
    {
        std::cout << "[AudioSource] Delete the following audio source: " << m_source << std::endl;
        alDeleteSources(1, &m_source);
    }

    void AudioSource::play(const ALuint buffer_to_play)
    {
        if (buffer_to_play != m_buffer)
        {
            m_buffer = buffer_to_play;
            alSourcei(m_source, AL_BUFFER, (ALint)m_buffer);
        }

        alSourcePlay(m_source);

        ALint state = AL_PLAYING;
        while (state == AL_PLAYING && alGetError() == AL_NO_ERROR)
        {
            alGetSourcei(m_source, AL_SOURCE_STATE, &state);
        }
    }

} // namespace engine
