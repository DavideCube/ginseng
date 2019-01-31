#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
* Automatically performs a checked allocation. If the allocation fails, 
* prints an error message and terminates the execution.
* 
*/
void* memcheck(size_t size);


/*
* Debug print stream. Prints the given message, but only if the directive DEBUG
* is defined in the current file.
*/
void debug(const char* msg);


/**
* Checks if the given pointer is null. If so, prints an error message and terminates. 
* Please note that this function should be used only when a null pointer could mean
* error or dangerous uninitialized memory: there are cases in which a NULL pointer
* is an acceptable outcome. In such cases, this function should not be used. 
*/
bool nullcheck(void* p);

#endif