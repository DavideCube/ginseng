#ifndef _SET_H
#define _SET_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct set_t {

	struct elem_s* head;
	unsigned int size;
};

struct elem_s {

	struct elem_s* next;
	double value;

};


struct set_t* _create();
bool _insert(struct set_t* set, double value);
bool _contains(struct set_t*, double value);
bool _empty(struct set_t* set);
bool _remove(struct set_t* set, double value);
bool _clear(struct set_t* set);

void _print(struct set_t* set);

//TODO
struct set_t* _from_arr(double* arr);
double* _to_arr(struct set_t* set);

struct set_t* _union(struct set_t* set_a, struct set_t* set_b);
struct set_t* _inters(struct set_t* set_a, struct set_t* set_b);
struct set_t* _diff(struct set_t* set_a, struct set_t* set_b);








#endif