#ifndef OUR_DATA_TYPES_H
#define OUR_DATA_TYPES_H

#include <glm/glm.hpp>
#include <bitset>
#include <vector>
#include <glad/gl.h>


namespace famm {
    // Since we may want to store colors in bytes instead of floats for efficiency,
    // we are creating our own 32-bit R8G8B8A8 Color data type with the default GLM precision
    typedef glm::vec<4, glm::uint8, glm::defaultp> Color;

    

    // ECS Types
    typedef  std::uint8_t ComponentType;        //components and entities are defined as unsigned ints (Ids)
    typedef  std::uint32_t Entity;

    
    const Entity MAX_ENTITIES = 5000;           //constants
    const ComponentType MAX_COMPONENTS = 32;

    typedef  std::bitset<MAX_COMPONENTS> Signature;     //the signature on an entity/system is a bit set having the size of all components 
                                                        //(1 in bits corresponding to components that the entity/system has)

    
    

}

#endif //OUR_DATA_TYPES_H
