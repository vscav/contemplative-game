#include <engine/AudioListener.hpp>
#include <engine/utils/common.hpp>
#include <engine/utils/cout_colors.hpp>

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
          std::cerr << COLOR_RED << "[OPENAL] alListenerfv POSITION :  " << error << " with call for " << COLOR_RESET << std::endl;
          return;
      }

      // Velocity ...
      alListenerfv(AL_VELOCITY,m_listenerVel);
      if ((error = alGetError()) != AL_NO_ERROR)
      {
          std::cerr << COLOR_RED << "[OPENAL] alListenerfv VELOCITY :  " << error << " with call for " << COLOR_RESET << std::endl;
          return;
      }
      //
      // // Orientation ...
      alListenerfv(AL_ORIENTATION,m_listenerOri);
      if ((error = alGetError()) != AL_NO_ERROR)
      {
          std::cerr << COLOR_RED << "[OPENAL] alListenerfv ORIENTATION :  " << error << " with call for " << COLOR_RESET << std::endl;
          return;
      }

      if(applicationDebug) std::cout << COLOR_CYAN << "[AudioListener]"<< COLOR_RESET <<" Created listener" << '\n';
    }

    void AudioListener::setPosition(const glm::vec3 newPosition){
      m_listenerPos[0]=newPosition[0];
      m_listenerPos[1]=newPosition[1];
      m_listenerPos[2]=newPosition[2];

      alListenerfv(AL_POSITION,m_listenerPos);
    }

} // namespace engine
