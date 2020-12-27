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

      ALfloat m_listenerPos[3]={0.0, 0.0, 0.0};
      ALfloat m_listenerVel[3]={0.0, 0.0, 0.0};
      ALfloat m_listenerOri[6]={0.0,0.0,-1.0, 0.0,1.0,0.0};


    public:

        /// \brief Constructor.
        AudioListener();

        /// \brief Destructor.
        ~AudioListener() noexcept(false);
    };

} // namespace engine

#endif /* _AudioDevice_HPP_ */
