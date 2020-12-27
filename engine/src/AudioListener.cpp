#include <engine/AudioListener.hpp>

#include <AL/al.h>
#include <AL/alc.h>

#include <iostream>

namespace engine
{

    AudioListener::AudioListener()
    {

      ALenum error;

      // Position ...
      alListenerfv(AL_POSITION,m_listenerPos);
      if ((error = alGetError()) != AL_NO_ERROR)
      {
          std::cerr << "[OPENAL] alListenerfv POSITION :  " << error << " with call for " << std::endl;
          return;
      }

      // Velocity ...
      alListenerfv(AL_VELOCITY,m_listenerVel);
      if ((error = alGetError()) != AL_NO_ERROR)
      {
          std::cerr << "[OPENAL] alListenerfv VELOCITY :  " << error << " with call for " << std::endl;
          return;
      }
      //
      // // Orientation ...
      alListenerfv(AL_ORIENTATION,m_listenerOri);
      if ((error = alGetError()) != AL_NO_ERROR)
      {
          std::cerr << "[OPENAL] alListenerfv ORIENTATION :  " << error << " with call for " << std::endl;
          return;
      }

      std::cout << "[Audio Listener] Created listener" << '\n';
    }

    AudioListener::~AudioListener() noexcept(false)
    {

    }

} // namespace engine
