#include <engine/TimeManager.hpp>

namespace engine
{

    double TimeManager::calculateFrameRate(bool writeToConsole = false)
    {
        static double framesPerSecond = 0.0f;
        static double startTime = getTime();
        static double lastTime = getTime();
        static double currentFPS = 0.0f;

        currentTime = getTime();

        deltaTime = currentTime - lastTime;

        lastTime = currentTime;

        ++framesPerSecond;

        if (currentTime - startTime > 1.0f)
        {
            startTime = currentTime;

            if (writeToConsole)
                std::cout << int(framesPerSecond) << " fps" << std::endl;

            currentFPS = framesPerSecond;

            framesPerSecond = 0;
        }

        return currentFPS;
    }

    double TimeManager::getTime()
    {
        // Grab the current system time since 1/1/1970, otherwise know as the Unix Timestamp or Epoch
        auto beginningOfTime = std::chrono::system_clock::now().time_since_epoch();

        // Convert the system time to milliseconds
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(beginningOfTime).count();

        // Return the time in seconds and give us a fractional value
        return ms * 0.001;
    }

    void TimeManager::sleep(int ms)
    {
        // Use the C++ 11 sleep_for() function to pause the current thread
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }

} // namespace engine