
#pragma once
#ifndef _Random_HPP_
#define _Random_HPP_

#include <random>

namespace engine
{

    /// \class Random
    /// \brief Random generator class.
    class Random
    {
    private:
        static std::mt19937 m_randomEngine;                            /*!< A pseudo-random generator of 32-bit numbers with a state size of 19937 bits. */
        static std::uniform_int_distribution<uint32_t> m_distribution; /*!< A distribution which will produced random unsigned integer values. */

    public:
        /// \brief Initializes the random engine.
        static void init()
        {
            m_randomEngine.seed(std::random_device()());
        }

        /// \brief Provides a random float.
        static float floatDistribution()
        {
            return (float)m_distribution(m_randomEngine) / (float)std::numeric_limits<uint32_t>::max();
        }
    };

} // namespace engine

#endif /* _Random_HPP_ */