#include <engine/OpenALManager.hpp>
#include <engine/GLApplication.hpp>
#include <engine/dependencies/glm.hpp>

#include <iostream>

namespace engine
{

    OpenALManager::OpenALManager():m_audioDevice(new AudioDevice()),m_audioListener(new AudioListener()), m_mainSource(new AudioSource()), m_mainSourceBuffer(new AudioBuffer()), m_boatSource(new AudioSource()), m_boatBuffer(new AudioBuffer())
    {
        initialize();
    }

    int OpenALManager::initialize()
    {
      alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);

      m_mainSourceBuffer->addAudioEffect("application/res/sounds/main.wav");
      m_mainSource->setLooping(1);
      m_mainSource->setBuffer(m_mainSourceBuffer.get()->m_audioEffectBuffers[0]);

      m_boatBuffer->addAudioEffect("application/res/sounds/boat.wav");
      m_boatSource->setLooping(1);
      m_boatSource->setBuffer(m_boatBuffer.get()->m_audioEffectBuffers[0]);


      alGetSourcei(m_mainSource->m_source, AL_SOURCE_STATE, &m_isPlaying);

      if (m_isPlaying != AL_PLAYING || alGetError() != AL_NO_ERROR)
      {
          m_mainSource->play();
          m_boatSource->play();
      }
      return 0;
    }


    void OpenALManager::update()
    {
      glm::vec3 cameraPosition = GLApplication::getInstance().getCamera()->getPosition();
      m_audioListener->setPosition(cameraPosition);
      m_mainSource->setPosition(cameraPosition);
      m_boatSource->setPosition(cameraPosition);
    }

    void OpenALManager::pause(){
      alGetSourcei(m_mainSource->m_source, AL_SOURCE_STATE, &m_isPlaying);
      if(m_isPlaying == AL_PLAYING){
        m_mainSource->pause();
        m_boatSource->pause();
      }
      else{
        m_mainSource->play();
        m_boatSource->play();
      }
    }


    // This destroys the window
    void OpenALManager::destroy()
    {
      m_mainSource->stop();
      m_boatSource->stop();
      m_isPlaying=AL_STOPPED;
    }

} // namespace engine
