#pragma once
#ifndef _AudioDevice_HPP_
#define _AudioDevice_HPP_

#include <AL/al.h>
#include <AL/alc.h>
#include <vector>

namespace audio
{

    /// \class AudioDevice
    /// \brief Class (singleton) that instanciates an audio device and avoid the creation of multiple devices.
    class AudioListener
    {
    private:
      /// \brief Constructor.

      /// \brief Destructor.
      ~AudioListener() noexcept(false);

     ALfloat m_listenerPosX;
     ALfloat m_listenerPosY;
     ALfloat m_listenerPosZ;

     ALfloat m_listenerVelX;
     ALfloat m_listenerVelY;
     ALfloat m_listenerVelZ;

    // ALfloat m_listenerOri[];


    public:
        /// \brief The function to get the instance of the audio device.
        static AudioListener *getInstance();

        AudioListener();
    };

} // namespace audio

#endif /* _AudioDevice_HPP_ */

// alec(alListener3f(AL_POSITION, 0.f, 0.f, 0.f));
// 	alec(alListener3f(AL_VELOCITY, 0.f, 0.f, 0.f));
// 	ALfloat forwardAndUpVectors[] = {
// 		/*forward = */ 1.f, 0.f, 0.f,
// 		/* up = */ 0.f, 1.f, 0.f
// 	};
// 	alec(alListenerfv(AL_ORIENTATION, forwardAndUpVectors));
