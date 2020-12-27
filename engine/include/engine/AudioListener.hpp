#pragma once
#ifndef _AudioListener_HPP_
#define _AudioListener_HPP_

#include <AL/al.h>
#include <AL/alc.h>
#include <vector>

namespace engine
{

    /// \class AudioDevice
    /// \brief Class that instanciates an audio device and avoid the creation of multiple devices.
    class AudioListener
    {
    private:


     ALfloat m_listenerPosX;
     ALfloat m_listenerPosY;
     ALfloat m_listenerPosZ;

     ALfloat m_listenerVelX;
     ALfloat m_listenerVelY;
     ALfloat m_listenerVelZ;

    // ALfloat m_listenerOri[];


    public:

        /// \brief Constructor.
        AudioListener();

        /// \brief Destructor.
        ~AudioListener() noexcept(false);
    };

} // namespace engine

#endif /* _AudioDevice_HPP_ */
