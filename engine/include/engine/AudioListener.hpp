#pragma once
#ifndef _AudioListener_HPP_
#define _AudioListener_HPP_

#include <engine/dependencies/glm.hpp>

#include <AL/al.h>
#include <AL/alc.h>
#include <vector>


namespace engine
{

    /// \class AudioDevice
    /// \brief Class that instanciates.
    class AudioListener
    {
    private:
      ALfloat m_listenerPos[3]={0.0, 0.0, 0.0}; /*!< An array that represent the position of the listener. */
      ALfloat m_listenerVel[3]={0.0, 0.0, 0.0}; /*!< An array that represent the velocity of the listener. */
      ALfloat m_listenerOri[6]={0.0,0.0,-1.0, 0.0,1.0,0.0}; /*!< An array that represent the orientation of the listener. */


    public:

        /// \brief Constructor.
        AudioListener();

        /// \brief Destructor.
        ~AudioListener() = default;

        /// \brief Sets the position of the audio listener. 
        void setPosition(const glm::vec3 newPosition);
    };

} // namespace engine

#endif /* _AudioDevice_HPP_ */
