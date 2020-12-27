#pragma once
#ifndef _AudioSource_HPP_
#define _AudioSource_HPP_

#include <AL/al.h>

namespace engine
{

    class AudioSource
    {
    private:
        ALuint m_source;
        float m_pitch = 1.f;
        float m_gain = 1.f;
        float m_position[3] = {0, 0, 0};
        float m_velocity[3] = {0, 0, 0};
        bool m_loopAudio = false;
        ALuint m_buffer = 0;

    public:
        AudioSource();
        ~AudioSource();

        void play(const ALuint bufferToPlay);
    };

} // namespace engine

#endif /* _AudioSource_HPP_ */
