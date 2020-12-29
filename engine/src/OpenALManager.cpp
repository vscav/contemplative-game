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
      m_audioSource->setBuffer(m_audioBuffer.get()->m_audioEffectBuffers[0]);
        // Return success

        //std::cout << "Testing Calling play sound" << '\n';
        alGetSourcei(m_audioSource->m_source, AL_SOURCE_STATE, &m_isPlaying);
        //std::cout << m_isPlaying << '\n';

        if (m_isPlaying != AL_PLAYING || alGetError() != AL_NO_ERROR)
        {
            m_audioSource->play();
        }
        return 0;
    }


    void OpenALManager::update()
    {

    }

    void OpenALManager::pause(){
      alGetSourcei(m_audioSource->m_source, AL_SOURCE_STATE, &m_isPlaying);
      if(m_isPlaying == AL_PLAYING){
        m_audioSource->pause();
      }
      else{
        m_audioSource->play();
      }
    }


    // This destroys the window
    void OpenALManager::destroy()
    {
      m_audioSource->stop();
      m_isPlaying=AL_STOPPED;
    }

} // namespace engine
