#ifndef OUR_DATA_TYPES_H
#define OUR_DATA_TYPES_H

#include <glm/glm.hpp>
#include <bitset>

namespace famm {
    // Since we may want to store colors in bytes instead of floats for efficiency,
    // we are creating our own 32-bit R8G8B8A8 Color data type with the default GLM precision
    typedef glm::vec<4, glm::uint8, glm::defaultp> Color;

    // ECS Types
    typedef  std::uint8_t ComponentType;        //components and entities are defined as unsigned ints (Ids)
    typedef  std::uint32_t Entity;
    typedef  std::bitset<MAX_COMPONENTS> Signature;     //the signature on an entity is a bit set having the size of all components (1 in bits corresponding to components that the entity has)

    //constants
    const Entity MAX_ENTITIES = 5000;
    const ComponentType MAX_COMPONENTS = 32;

}

#endif //OUR_DATA_TYPES_H
