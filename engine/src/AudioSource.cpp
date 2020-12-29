#include <engine/AudioSource.hpp>
#include <engine/utils/common.hpp>
#include <engine/utils/cout_colors.hpp>

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
        //alSourcei(m_source, AL_LOOPING, m_loopAudio);
        alSourcei(m_source, AL_BUFFER, m_buffer);
    }

    AudioSource::~AudioSource()
    {
        if(applicationDebug) std::cout << COLOR_CYAN << "[AudioSource]" << COLOR_RESET <<" Delete the following audio source: " << m_source << std::endl;
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

    }

    void AudioSource::stop(){
      alSourceStop(m_source);
      alSourcei(m_source, AL_BUFFER, 0);
    }

} // namespace engine
