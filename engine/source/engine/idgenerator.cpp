#include "idgenerator.h"

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Public Static                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Public                         */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

IdGenerator::IdGenerator() : _rng(std::mt19937()), _usedIds(Vector<uint32>()) {

}

uint32 IdGenerator::get() {
	uint32 newId = _rng();

	while ( _usedIds.contains_r(newId) ) {
		newId = _rng();
	}

	_usedIds.add( newId );

	return newId;
}

void IdGenerator::put(uint32 id) {
	_usedIds.add(id);
}

void IdGenerator::remove(uint32 id) {
	_usedIds.remove(id);
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                      Private Static                    */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ENGINE_NAMESPACE_END