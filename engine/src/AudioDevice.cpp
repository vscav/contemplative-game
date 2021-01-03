#include <engine/AudioDevice.hpp>
#include <engine/utils/common.hpp>
#include <engine/utils/cout_colors.hpp>
#include <engine/EngineException.hpp>

#include <AL/al.h>

#include <iostream>

namespace engine
{


    AudioDevice::AudioDevice()
    {
        // nullptr = get default device
        m_ALCDevice = alcOpenDevice(nullptr);
        if (!m_ALCDevice)
            throw EngineException("[AudioDevice] ERROR: Failed to get audio device", __FILE__, __LINE__);

        // create context
        m_ALCContext = alcCreateContext(m_ALCDevice, nullptr);
        if (!m_ALCContext)
            throw EngineException("[AudioDevice] ERROR: Failed to set audio context", __FILE__, __LINE__);

        // make context current
        if (!alcMakeContextCurrent(m_ALCContext))
            throw EngineException("[AudioDevice] ERROR: Failed to make context current", __FILE__, __LINE__);

        const ALCchar *name = nullptr;
        if (alcIsExtensionPresent(m_ALCDevice, "ALC_ENUMERATE_ALL_EXT"))
            name = alcGetString(m_ALCDevice, ALC_ALL_DEVICES_SPECIFIER);
        if (!name || alcGetError(m_ALCDevice) != AL_NO_ERROR)
            name = alcGetString(m_ALCDevice, ALC_DEVICE_SPECIFIER);
        if(applicationDebug) std::cout << COLOR_CYAN << "[AudioDevice]" << COLOR_RESET << " Opened " << name << std::endl;
    }

    AudioDevice::~AudioDevice()
    {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(m_ALCContext);
        alcCloseDevice(m_ALCDevice);
    }

} // namespace audio
