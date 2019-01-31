#include "set.h"

int main(){
	struct set_t* set = _create();

	_insert(set, 12);
	_insert(set, 10);
	_insert(set, 9);

	_print(set);

	_clear(set);

	_print(set);
}