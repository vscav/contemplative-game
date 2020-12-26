#include <engine/OpenALManager.hpp>

#include <iostream>

namespace engine
{

    OpenALManager::OpenALManager():m_audioDevice(new audio::AudioDevice())
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
