#pragma once
#ifndef _AudioDevice_HPP_
#define _AudioDevice_HPP_

#include <AL/alc.h>

namespace engine
{

    /// \class AudioDevice
    /// \brief Class that instanciates an audio device
    class AudioDevice
    {
    private:

        ALCdevice *m_ALCDevice;   /*!< A pointer to the default user audio device. */
        ALCcontext *m_ALCContext; /*!< A pointer to the audio context. */

    public:
        /// \brief Constructor.
        AudioDevice();
        /// \brief Destructor.
        ~AudioDevice();
    };

} // namespace audio

#endif /* _AudioDevice_HPP_ */