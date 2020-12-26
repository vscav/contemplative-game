#include <engine/AudioDevice.hpp>

#include <AL/al.h>

#include <iostream>

namespace audio
{

    AudioDevice *AudioDevice::getInstance()
    {
      std::cout << "Device found" << '\n';
        static AudioDevice *audioDevice = new AudioDevice();
        return audioDevice;
    }

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

    AudioDevice::~AudioDevice() noexcept(false)
    {
        alcMakeContextCurrent(nullptr);
        if (!alcMakeContextCurrent(nullptr))
            throw std::runtime_error("[AudioDevice] ERROR: Failed to set context to nullptr");

        alcDestroyContext(m_ALCContext);
        if (m_ALCContext)
            throw std::runtime_error("[AudioDevice] ERROR: Failed to unset during close");

        alcCloseDevice(m_ALCDevice);
        if (!alcCloseDevice(m_ALCDevice))
            throw std::runtime_error("[AudioDevice] ERROR: Failed to close audio device");
    }

} // namespace audio
