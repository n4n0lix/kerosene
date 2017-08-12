#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "vector.h"
#include "uptrvector.h"

#include "world.h"
#include "transform.h"

#include "ilogiccomponent.h"
#include "irendercomponent.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class World;

//
// Contracts: 
// - GameObjects are owned by a world.
//
class GameObject
{
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
public:
            explicit GameObject();
			~GameObject();

	class Handle {
	public:
		Handle(GameObject* gameObject);
		~Handle();

		GameObject* get();
		void		invalidate();

	private:
		GameObject*	gameObject;
		bool		valid;

	};

	u_ptr<Handle> get_handle();

	void		  destroy();
	bool          shall_be_destroyed();

    Transform transform;
    Transform lastTransform;

    Transform globalTransform;
    Transform lastGlobalTransform;

	vector<Handle*> activeHandles;

protected:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                       Protected                        */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	uint64					_id;	
	bool					_destroy;

    u_ptr<ILogicComponent>  _logic;     // Owned by this
    u_ptr<IRenderComponent> _render;    // Owned by this

	static atomic<uint64>	UID_COUNTER;

};

ENGINE_NAMESPACE_END
