#include <engine/OpenALManager.hpp>

#include <iostream>

namespace engine
{

    OpenALManager::OpenALManager():m_audioDevice(new AudioDevice()),m_audioListener(new AudioListener()),m_audioSource(new AudioSource()), m_audioBuffer(new AudioBuffer())
    {
        initialize();
    }

    int OpenALManager::initialize()
    {
      m_audioBuffer->addAudioEffect("application/res/sounds/hwh.wav");
        // Return success
        return 0;
    }


    void OpenALManager::update()
    {
      //std::cout << "Testing Calling play sound" << '\n';
      alGetSourcei(m_audioSource->m_source, AL_SOURCE_STATE, &m_isPlaying);
      //std::cout << m_isPlaying << '\n';

      if (m_isPlaying != AL_PLAYING || alGetError() != AL_NO_ERROR)
      {
          std::cout << "Callign play function" << '\n';
          m_audioSource->play(m_audioBuffer.get()->m_audioEffectBuffers[0]);
      }

    }


    // This destroys the window
    void OpenALManager::destroy()
    {
      m_audioSource->stop();
      m_isPlaying=AL_STOPPED;
    }

} // namespace engine
