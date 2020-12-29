
#pragma once
#ifndef _Random_HPP_
#define _Random_HPP_

#include <random>

namespace engine
{

    class Random
    {
    public:
        static void init()
        {
            m_randomEngine.seed(std::random_device()());
        }

        static float floatDistribution()
        {
            return (float)m_distribution(m_randomEngine) / (float)std::numeric_limits<uint32_t>::max();
        }

    private:
        static std::mt19937 m_randomEngine;
        static std::uniform_int_distribution<uint32_t> m_distribution;
    };

} // namespace engine

#endif /* _Random_HPP_ */