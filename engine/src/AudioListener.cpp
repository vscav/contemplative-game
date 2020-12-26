#include <engine/AudioListener.hpp>

#include <AL/al.h>
#include <AL/alc.h>

#include <iostream>

namespace audio
{

    AudioListener *AudioListener::getInstance()
    {
        static AudioListener *audioListener = new AudioListener();
        return audioListener;
    }

    AudioListener::AudioListener()
    {
      m_listenerPosX=0.0;
      m_listenerPosY=0.0;
      m_listenerPosZ=0.0;

      m_listenerVelX=0.0;
      m_listenerVelY=0.0;
      m_listenerVelZ=0.0;

      // m_listenerVel={0.0,0.0,0.0};
      // m_listenerOri={0.0,0.0,-1.0, 0.0,1.0,0.0};

      ALenum error;

      // Position ...
      alListener3f(AL_POSITION,m_listenerPosX,m_listenerPosY,m_listenerPosZ);
      if ((error = alGetError()) != AL_NO_ERROR)
      {
          std::cerr << "[OPENAL] alListenerfv POSITION :  " << error << " with call for " << std::endl;
          return;
      }

      //
      // Velocity ...
      alListener3f(AL_VELOCITY,m_listenerVelX,m_listenerVelY,m_listenerVelZ);
      if ((error = alGetError()) != AL_NO_ERROR)
      {
          std::cerr << "[OPENAL] alListenerfv VELOCITY :  " << error << " with call for " << std::endl;
          return;
      }
      //
      // // Orientation ...
      // alListenerfv(AL_ORIENTATION,listenerOri);
      // if ((error = alGetError()) != AL_NO_ERROR)
      // {
      //     DisplayALError("alListenerfv ORIENTATION : ", error);
      //     return;
      // }
    }

    AudioListener::~AudioListener() noexcept(false)
    {

    }

} // namespace audio
