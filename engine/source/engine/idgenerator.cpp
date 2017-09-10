#include "idgenerator.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Public Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

IDGen::IDGen() : _rng(std::mt19937()), _usedIds(list<uint32>()) {

}

uint32 IDGen::new_id() {
	uint32 newId = _rng();

    std::sort(_usedIds.begin(), _usedIds.end());
	while ( std::binary_search(_usedIds.begin(), _usedIds.end(), newId) ) {
		newId = _rng();
	}

	_usedIds.add( newId );
    
	return newId;
}

void IDGen::put(uint32 id) {
	_usedIds.add(id);
}

void IDGen::release_id(uint32 id) {
	_usedIds.remove(id);
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Private Static                    */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END