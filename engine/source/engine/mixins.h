#pragma once

// Std-Includes
#include <bitset>

// Other Includes

// Internal Includes
#include "_global.h"
#include "vector3f.h"
#include "quaternion4f.h"
#include "entity.h"
#include "compact_map.h"

#define MAX_NUM_MIXINS 128

#define GLOBAL public
#define PLAYER public
#define LOCAL public

namespace ENGINE_NAMESPACE::mixin {

    struct Mixin {
        entity_id id;
    };

    template<typename MIXIN>
    struct MixinInfo {
        uint32 id;
    };

    template<typename MIXIN>
    const MixinInfo<MIXIN>& get_mixin_info();

    extern std::vector<compact_map_t*> MIXINS;

    template<typename MIXIN>
    void register_type() {
        MixinInfo<MIXIN> info = get_mixin_info<MIXIN>();

        size_t requiredSize = info.id + 1; // We also need a slot for id==0

        if ( requiredSize >= MIXINS.size() ) {
            MIXINS.resize( requiredSize + 16, nullptr );
        }

        if ( MIXINS[info.id] == nullptr ) {
            MIXINS[info.id] = new compact_map<entity_id, MIXIN>();
        }
    }

    template<typename MIXIN>
    void unregister_type() {
        MixinInfo<MIXIN> info = get_mixin_info<MIXIN>();
        delete MIXINS[info.id];
    }

    template<typename MIXIN>
    MIXIN& add( Entity& pEntity ) {
        return add<MIXIN>( pEntity.id );
    }

    template<typename MIXIN>
    MIXIN& add( entity_id pEntityId ) {
        MixinInfo<MIXIN> info = get_mixin_info<MIXIN>();

        MIXIN mixn = MIXIN();
        mixn.id = pEntityId;

        auto* map = (compact_map<entity_id, MIXIN>*) MIXINS[info.id];
        map->put( pEntityId, std::move( mixn ) );

        return map->access( pEntityId );
    }

    template<typename MIXIN>
    void remove( Entity& pEntity ) {
        remove<MIXIN>( pEntity.id );
    }

    template<typename MIXIN>
    void remove( entity_id pEntityId ) {
        MixinInfo<MIXIN> info = get_mixin_info<MIXIN>();

        auto* map = (compact_map<entity_id, MIXIN>*) MIXINS[info.id];

        map->remove( pEntityId );
    }

    template<typename MIXIN>
    bool has( Entity& pEntity ) {
        return has<MIXIN>( pEntity.id );
    }

    template<typename MIXIN>
    bool has( entity_id pEntityId ) {
        MixinInfo<MIXIN> info = get_mixin_info<MIXIN>();

        auto* map = (compact_map<entity_id, MIXIN>*) MIXINS[info.id];

        return map->contains( pEntityId );
    }

    template<typename MIXIN>
    MIXIN& access( Entity& pEntity ) {
        return access<MIXIN>( pEntity.id );
    }

    template<typename MIXIN>
    MIXIN& access( entity_id pEntityId ) {
        MixinInfo<MIXIN> info = get_mixin_info<MIXIN>();

        auto* map = (compact_map<entity_id, MIXIN>*) MIXINS[info.id];

        return map->access( pEntityId );
    }

    template<typename MIXIN>
    std::vector<MIXIN>& get_all() {
        MixinInfo<MIXIN> info = get_mixin_info<MIXIN>();

        auto* map = (compact_map<entity_id, MIXIN>*) MIXINS[info.id];

        return map->values();
    }


#define DEFINE_MIXIN(type) \
extern const mixin::MixinInfo<##type##> MIXIN_INFO_##type##; \
\
template<> \
const mixin::MixinInfo<##type##>& mixin::get_mixin_info();

#define REGISTER_MIXIN(id, type) \
const mixin::MixinInfo<##type##> MIXIN_INFO_##type = { id }; \
\
template<> \
const mixin::MixinInfo<##type##>& mixin::get_mixin_info() { \
    return MIXIN_INFO_##type##; }\

}