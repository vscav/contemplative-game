
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
        static std::mt19937 m_randomEngine; /*!< */
        static std::uniform_int_distribution<uint32_t> m_distribution; /*!<  */

    public:
        /// \brief
        static void init()
        {
            m_randomEngine.seed(std::random_device()());
        }

        /// \brief
        static float floatDistribution()
        {
            return (float)m_distribution(m_randomEngine) / (float)std::numeric_limits<uint32_t>::max();
        }
    };

} // namespace engine

#endif /* _Random_HPP_ */