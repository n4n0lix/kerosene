#include "idgen.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Public Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

IDGen::IDGen() : _rng(std::mt19937()), _usedIds(vector<uint32>()) {

}

uint32 IDGen::new_id() {
	uint32 newId = _rng();

    std::sort(_usedIds.begin(), _usedIds.end());
	while ( std::binary_search(_usedIds.begin(), _usedIds.end(), newId) ) {
		newId = _rng();
	}

	_usedIds.push_back( newId );
    
	return newId;
}

void IDGen::put(uint32 id) {
	_usedIds.push_back(id);
}

void IDGen::release_id(uint32 id) {
    _usedIds.erase( std::remove( _usedIds.begin(), _usedIds.end(), id ));
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Private Static                    */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END