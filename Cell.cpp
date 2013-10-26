#include "Cell.h"
#include <assert.h>

bool CCell::setType(unsigned int type){
	assert(0 == type || 1 == type && "Invalid cell type");
	if(0 != type && 1 != type) return false;
	_type = type;
	return true;
}
