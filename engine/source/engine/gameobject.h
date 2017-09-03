#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "list.h"
#include "owner_list.h"
#include "idgenerator.h"

#include "transform.h"

#include "logiccomponent.h"
#include "rendercomponent.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class World;
class RenderComponent;

//
// Contracts: 
// - GameObjects are owned by a world.
//
class GameObject
{
public:

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
public:
            explicit GameObject();
			~GameObject();

	void			 set_rendercomponent(owner<RenderComponent> comp);
	RenderComponent* get_rendercomponent();

	void	destroy_at_tick_end();
	bool    shall_be_destroyed_at_tick_end();

    Transform transform;
    Transform lastTransform;

    Transform globalTransform;
    Transform lastGlobalTransform;

protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	uint32					_id;	
	bool					_destroyAtTickEnd;

    owner<LogicComponent>  _logic;     // Owned by this
    owner<RenderComponent> _render;    // Owned by this

	static IdGenerator ID_GENERATOR;

};

ENGINE_NAMESPACE_END
