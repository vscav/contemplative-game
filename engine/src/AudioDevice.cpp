#include <engine/AudioDevice.hpp>

#include <AL/al.h>

#include <iostream>

namespace engine
{


    AudioDevice::AudioDevice()
    {
        // nullptr = get default device
        m_ALCDevice = alcOpenDevice(nullptr);
        if (!m_ALCDevice)
            throw std::runtime_error("[AudioDevice] ERROR: Failed to get audio device");

        // create context
        m_ALCContext = alcCreateContext(m_ALCDevice, nullptr);
        if (!m_ALCContext)
            throw std::runtime_error("[AudioDevice] ERROR: Failed to set audio context");

        // make context current
        if (!alcMakeContextCurrent(m_ALCContext))
            throw std::runtime_error("[AudioDevice] ERROR: Failed to make context current");

        const ALCchar *name = nullptr;
        if (alcIsExtensionPresent(m_ALCDevice, "ALC_ENUMERATE_ALL_EXT"))
            name = alcGetString(m_ALCDevice, ALC_ALL_DEVICES_SPECIFIER);
        if (!name || alcGetError(m_ALCDevice) != AL_NO_ERROR)
            name = alcGetString(m_ALCDevice, ALC_DEVICE_SPECIFIER);
        std::cout << "[AudioDevice] Opened " << name << std::endl;
    }

    AudioDevice::~AudioDevice()
    {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(m_ALCContext);
        alcCloseDevice(m_ALCDevice);
    }

} // namespace audio
