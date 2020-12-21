#pragma once
#ifndef _TimeManager_HPP
#define _TimeManager_HPP

#include <iostream>
#include <chrono>
#include <thread>

namespace engine
{

    /// \class TimeManager
    /// \brief Class (Singleton) used to manage the time of our main application.
    class TimeManager
    {
    private:
        /// \brief Default constructor.
        TimeManager() = default;
        /// \brief Default destructor.
        ~TimeManager() = default;

    public:
        /// \brief Gets the instance of the manager, or initializes and returns the instance.
        static TimeManager &getInstance()
        {
            static TimeManager instance;
            return instance;
        }

        /// \brief Copy constructor.
        TimeManager(TimeManager const &) = delete;
        /// \brief Affectation operator.
        TimeManager &operator=(TimeManager const &) = delete;

        /// \brief Calculates our current scene's frames per second and displays it in the console.
        /// \param writeToConsole : A boolean to indicate whether or not we display the value in the console.
        /// \return The current scene's frames per second.
        double calculateFrameRate(bool writeToConsole);

        /// \brief Returns the current time in seconds.
        /// \return The current time in seconds.
        double getTime();

        /// \brief Pauses the current thread for an amount of time in milliseconds.
        /// \param milliseconds : The duration of sleep in milliseconds.
        void sleep(int milliseconds);

        double deltaTime = 0; /*!< The time slice that stores the total time in seconds that has elapsed since the last frame. */

        double currentTime = 0; /*!< The current time of the manager instance. */
    };

} // namespace engine

#endif /* _TimeManager_HPP */