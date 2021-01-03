#include <engine/OpenALManager.hpp>
#include <engine/GLApplication.hpp>
#include <engine/dependencies/glm.hpp>

#include <iostream>

namespace engine
{

    OpenALManager::OpenALManager():m_audioDevice(new AudioDevice()),m_audioListener(new AudioListener()),m_audioSource(new AudioSource()), m_audioBuffer(new AudioBuffer()), m_mainSource(new AudioSource()), m_mainSourceBuffer(new AudioBuffer())
    {
        initialize();
    }

    int OpenALManager::initialize()
    {
      alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);

      m_audioBuffer->addAudioEffect("application/res/sounds/hwh.wav");
      m_audioSource->setBuffer(m_audioBuffer.get()->m_audioEffectBuffers[0]);

      m_mainSourceBuffer->addAudioEffect("application/res/sounds/main.wav");
      m_mainSource->setLooping(1);
      m_mainSource->setBuffer(m_mainSourceBuffer.get()->m_audioEffectBuffers[0]);


      //std::cout << "Testing Calling play sound" << '\n';
      alGetSourcei(m_audioSource->m_source, AL_SOURCE_STATE, &m_isPlaying);
      //std::cout << m_isPlaying << '\n';

      if (m_isPlaying != AL_PLAYING || alGetError() != AL_NO_ERROR)
      {
          //m_audioSource->play();
          //m_mainSource->play();
      }
      return 0;
    }


    void OpenALManager::update()
    {
      glm::vec3 cameraPosition = GLApplication::getInstance().getCamera()->getPosition();
      m_audioListener->setPosition(cameraPosition);
      m_mainSource->setPosition(cameraPosition);
    }

    void OpenALManager::pause(){
      alGetSourcei(m_mainSource->m_source, AL_SOURCE_STATE, &m_isPlaying);
      if(m_isPlaying == AL_PLAYING){
        m_audioSource->pause();
        m_mainSource->pause();
      }
      else{
        m_audioSource->play();
        m_mainSource->play();
      }
    }


    // This destroys the window
    void OpenALManager::destroy()
    {
      m_audioSource->stop();
      m_mainSource->stop();
      m_isPlaying=AL_STOPPED;
    }

} // namespace engine
