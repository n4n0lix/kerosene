#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "_meta.h"

#include "idgen.h"
#include "netvar.h"
#include "nethelper.h"

#include "transform.h"
#include "owner.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

extern bool __Entity_Register();

class Entity
{
    META_CLASS

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
public:
    // TODO: Register into a name->class lookup

                    Entity();
    virtual         ~Entity();

    virtual void    on_update();

    virtual void    create_full_snapshot(  vector<byte>&, NetVarType );
    virtual void    create_delta_snapshot( vector<byte>&, Entity&, NetVarType );
    virtual void    update_from_snapshot( map<int32, vector<byte>> );

    // SHARED-VARS
    uint32    uid;
    Transform transform;


    // SELF-VARS

    // LOCAL-VARS
    Transform lastTransform;

protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

};


ENGINE_NAMESPACE_END
