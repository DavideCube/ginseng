#include "utils.h"

void debug(const char* msg){

	#ifdef DEBUG
		printf("%s\n", msg);
	#endif

}


void* memcheck(size_t size){
	void* mem = malloc(size);
	if(mem == NULL){
		printf("Error: out of memory! Exiting.\n");
		exit(1);
	}

	return mem;
}



bool nullcheck(void* p){

	bool ret = false;
	if(p == NULL){
		printf("Null pointer detected! Exiting.\n");
		exit(1);
	}
	return ret;
}