#include <engine/Random.hpp>

namespace engine
{

    std::mt19937 Random::m_randomEngine;
    std::uniform_int_distribution<uint32_t> Random::m_distribution;

} // namespace engine