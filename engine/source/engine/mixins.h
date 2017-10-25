#pragma once

// Std-Includes
#include <bitset>

// Other Includes

// Internal Includes
#include "_global.h"
#include "vector3f.h"
#include "quaternion4f.h"
#include "entity.h"

ENGINE_NAMESPACE_BEGIN

struct MixinInfo {
    uint8 id;
};

struct Mixin {
    entity_id id;
};

template<typename MIXIN>
MixinInfo get_mixin_info();

template<typename MIXIN>
class MixinContainer {
public:
    vector<MIXIN>&          all_mixins();
    MixinContainer<MIXIN>   snapshot();

private:
    vector<MIXIN> _mixins;
};

//
//typedef uint16 entity_id;
//typedef uint16 trait_id;
//
//template<typename TRAIT>
//struct MixinInfo {
//    trait_id                        id;
//    vector<pair<entity_id,TRAIT>>&  traits;
//};
//
//template<typename TRAIT>
//trait_info<TRAIT> __trait_info();
//
//struct entity {
//
//    entity_id id;
//
//    template<typename TRAIT>
//    static vector<TRAIT>& all_instances_of() {
//        trait_info<TRAIT> info = __trait_info<TRAIT>();
//        return info.traits;
//    }
//
//    template<typename TRAIT>
//    bool has() {
//        trait_info<TRAIT> info = __trait_info<TRAIT>();
//        return _traitBitSet[info.id];
//    }
//
//    template<typename TRAIT>
//    entity& add() {
//        trait_info<TRAIT> info = __trait_info<TRAIT>();
//
//        info.traits.push_back( make_pair( id, TRAIT() ));
//        _traitBitSet[info.id] = true;
//
//        return this;
//    }
//
//    template<typename TRAIT>
//    entity& remove() {
//        auto traits = __trait_info<TRAIT>().traits;
//
//        traits.erase( std::remove_if( traits.begin(), traits.end(), 
//            [&]( pair<entity_id, TRAIT> trait ) { return trait.first = id; } ));
//
//        _traitBitSet[info.id] = false;
//
//        return this;
//    }
//
//    template<typename TRAIT>
//    TRAIT& get() {
//        auto traits = __trait_info<TRAIT>().traits;
//
//        for ( auto& trait : traits ) {
//            if ( trait.first == id )
//                return trait.second;
//        }
//
//        throw std::exception("Entity hasn't trait."); 
//    }
//
//private:
//    std::bitset<MAX_NUM_TRAITS> _traitBitSet;
//};

ENGINE_NAMESPACE_END

