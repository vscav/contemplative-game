#pragma once
#ifndef _AudioDevice_HPP_
#define _AudioDevice_HPP_

#include <AL/alc.h>

namespace audio
{

    /// \class AudioDevice
    /// \brief Class (singleton) that instanciates an audio device and avoid the creation of multiple devices.
    class AudioDevice
    {
    private:
        /// \brief Constructor.
        AudioDevice();
        /// \brief Destructor.
        ~AudioDevice() noexcept(false);

        ALCdevice *m_ALCDevice;   /*!< A pointer to the default user audio device. */
        ALCcontext *m_ALCContext; /*!< A pointer to the audio context. */

    public:
        /// \brief The function to get the instance of the audio device.
        static AudioDevice *getInstance();
    };

} // namespace audio

#endif /* _AudioDevice_HPP_ */