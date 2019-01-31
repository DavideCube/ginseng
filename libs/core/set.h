#ifndef _SET_H
#define _SET_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
* Set data structure. 
* Elements are stored into an unordered linked list, 
* along with a size attribute.
*/
struct set_t {

	struct elem_s* head;
	unsigned int size;
};

/*
* Linked list data structure. Holds doubles.
*/
struct elem_s {

	struct elem_s* next;
	double value;

};

/*
* Returns a pointer to an initialized set.
*/
struct set_t* _create();

/*
* Inserts an element into a set. If the element is already
* present, it is not inserted and false is returned
* (true otherwise).
*/
bool _insert(struct set_t* set, double value);

/*
* Checks if a set contains an element.
*/
bool _contains(struct set_t*, double value);

/*
* Checks if the set is empty.
*/
bool _empty(struct set_t* set);

/*
* Removes an element if present. Returns true if
* the element was there and has been now removed,
* false otherwise.
*/
bool _remove(struct set_t* set, double value);

/*
* Clears a set, removing all of its elements.
*/
void _clear(struct set_t* set);

/*
* Prints the set.
*/
void _print(struct set_t* set);

//TODO
struct set_t* _from_arr(double* arr);
double* _to_arr(struct set_t* set);

struct set_t* _union(struct set_t* set_a, struct set_t* set_b);
struct set_t* _inters(struct set_t* set_a, struct set_t* set_b);
struct set_t* _diff(struct set_t* set_a, struct set_t* set_b);

#endif