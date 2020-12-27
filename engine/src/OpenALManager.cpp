#include <engine/OpenALManager.hpp>

#include <iostream>

namespace engine
{

    OpenALManager::OpenALManager():m_audioDevice(new AudioDevice()),m_audioListener(new AudioListener()),m_audioSource(new AudioSource())
    {
        initialize();
    }

    int OpenALManager::initialize()
    {

        // Return success
        return 0;
    }


    void OpenALManager::update()
    {

    }


    // This destroys the window
    void OpenALManager::destroy()
    {

    }

} // namespace engine
