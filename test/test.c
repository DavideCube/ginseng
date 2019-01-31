#include "../libs/data/set.h"


int main(){

	struct set_t* set = _create();
	_insert(set, 1);
	_insert(set, 2);
	_print(set);


}