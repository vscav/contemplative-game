#pragma once
#ifndef _GLAudioManager_HPP_
#define _GLAudioManager_HPP_



#include <string>
#include <fstream>

namespace engine
{
    /// \class GLAudioManager
    /// \brief Class for managing the creation of the window, input and the
    /// creating of the OpenGL context. This class should be inherited from to create
    /// specific implementations like OPENAL or IrrKlang.
    class GLAudioManager
    {

    public:
        /// \brief Destructor. This is needed so that the class inheriting this will have it's deconstructor called.
        virtual ~GLAudioManager() = default;

        /// \brief Initializes the audio devinc and creates the audio context.
        /// \return An integer acting as a boolean for success/fail information.
        virtual int initialize() = 0;


        /// \brief Updates the audio (should be called every frame).
        virtual void update() = 0;

        /// \brief Destroys the window and the OpenGL context.
        virtual void destroy() = 0;


    };

} // namespace engine

#endif /* _GLAudioManager_HPP_ */
