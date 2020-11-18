#ifndef OUR_DATA_TYPES_H
#define OUR_DATA_TYPES_H

#include <glm/glm.hpp>
#include <bitset> 

namespace famm {
    // Since we may want to store colors in bytes instead of floats for efficiency,
    // we are creating our own 32-bit R8G8B8A8 Color data type with the default GLM precision
    typedef glm::vec<4, glm::uint8, glm::defaultp> Color;

    // ECS Types
    typedef  std::uint8_t componentType;
    typedef  std::uint32_t Entity;
    typedef  std::bitset<32> Signature;



}

#endif //OUR_DATA_TYPES_H
