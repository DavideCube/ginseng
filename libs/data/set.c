#include "set.h"
#include "../core/utils.h"

#define DEBUG


struct set_t* _create(){

	struct set_t* set = memcheck(sizeof(struct set_t));
	set->size = 0;
	set->head = NULL;
	return set;

}


bool _empty(struct set_t* set){
	nullcheck(set);
	return set->size == 0 ? true : false;
}


bool _contains(struct set_t* set, double value){

	nullcheck(set);

	if(_empty(set)){
		debug("This set is empty!\n");
		return false;
	}
	else{
		struct elem_s* curr = set->head;
		while(curr != NULL){
			if(curr->value == value){
				debug("Element found!\n");
				return true;
			}
			curr = curr->next;
		}
	}
	debug("Element not found!\n");
	return false;

}


bool _insert(struct set_t* set, double value){

	if(!nullcheck(set)){

		struct elem_s* new = memcheck(sizeof(struct elem_s));
		new->value = value;

		if(set->head == NULL){
			set->head = new;
			new->next = NULL;
			set->size++;
			debug("Node inserted!\n");
		}
		else{

			if(!_contains(set, value)){
				new->next = set->head;
				set->head = new;
				set->size++;
				debug("Node inserted!\n");
			}

		}


	}

	return true;

}


bool _remove(struct set_t* set, double value){

	nullcheck(set);

	if(_empty(set) || !_contains(set, value)){

		return false;

	}
	//set surely contains the element. Note that two loops are not nested,
	//so this algorithm runs in O(n+n) = O(2n) = O(n) time.
	else{
		struct elem_s* curr = set->head;
		//value to delete is in the head
		if(curr->value == value){
			curr->next = NULL;
			free(curr);
			set->size--;
			return true;
		}
		//value is somewhere else in the set
		else{
			struct elem_s* prev = curr;
			curr = curr->next;
			while(curr != NULL && curr->value != value){
				prev = curr;
				curr = curr->next;
			}
			//curr should not be null. If so, there is a fault in this algorithm or in _contains().
			nullcheck(curr);
			//We reached the element to purge. We also have a reference to the previous one,
			//which will replace the deleted element.
			prev->next = curr->next;
			free(curr);
			set->size--;
			return true;
		}



	}


}


void _clear(struct set_t* set){

	nullcheck(set);

	if(!_empty(set)){

		struct elem_s* curr = set->head;
		struct elem_s* next = NULL;
		if(set->size == 1){
			free(curr);
		}
		else{

			while(curr != NULL){

				next = curr->next;
				curr->next = NULL;
				free(curr);
				curr = next;

			}

			set->size = 0;
			set->head = NULL;

		}

	}	
}



void _print(struct set_t* set){

	nullcheck(set);

	if(_empty(set)){
		printf("{}\n");
		return;
	}
	else{
		struct elem_s* curr = set->head;
		printf("{");
		while(curr != NULL){
			if(curr->next == NULL){
				printf("%.3f", curr->value);
			}
			else{
				printf("%.3f, ", curr->value);
			}
			curr = curr->next;
		}
		printf("}");
	}

}


struct elem_s* _elemdup(struct elem_s* elem){

	struct elem_s* new = memcheck(sizeof(elem));
	new->next = NULL;
	new->value = elem->value;

	return new;

}



struct set_t* _union(struct set_t* set_a, struct set_t* set_b){

	nullcheck(set_a);
	nullcheck(set_b);

	struct set_t* res = _create();

	if(_empty(set_a)){
		res = set_b;
	}
	else if(_empty(set_b)){
		res = set_a;
	}
	else{

		struct elem_s* curr_a = set_a->head;
		while(curr_a != NULL){

			_insert(res, curr_a->value);
			curr_a = curr_a->next;

		}

		struct elem_s* curr_b = set_b->head;
		while(curr_b != NULL){

			_insert(res, curr_b->value);
			curr_b = curr_b->next;

		}
	}

	return res;

}



struct set_t* _intersect(struct set_t* set_a, struct set_t* set_b){

	nullcheck(set_a);
	nullcheck(set_b);

	struct set_t* res = _create();

	if(_empty(set_a)){
		res = set_b;
	}
	else if(_empty(set_b)){
		res = set_a;
	}
	else{

		struct elem_s* curr = set_a->head;
		while(curr != NULL){
			if(_contains(set_b, curr->value)){
				_insert(res, curr->value);
			}
			curr = curr->next;
		}

	}

	return res;

}


struct set_t* _diff(struct set_t* set_a, struct set_t* set_b){

	nullcheck(set_a);
	nullcheck(set_b);

	struct set_t* res = _create();

	if(_empty(set_a)){
		res = set_b;
	}
	else if(_empty(set_b)){
		res = set_a;
	}
	else{

		struct elem_s* curr = set_a->head;
		while(curr != NULL){
			if(!_contains(set_b, curr->value)){
				_insert(res, curr->value);
			}
			curr = curr->next;
		}

	}

	return res;

}



struct set_t* _clone(struct set_t* set){

	nullcheck(set);

	struct set_t* new = _create();

	if(_empty(set)){
		return new;
	}
	else{
		struct elem_s* curr = set->head;
		struct elem_s* last = NULL;
		while(curr != NULL){

			if(_empty(new)){

				new->head = _elemdup(curr);
				new->size++;
				
				curr = curr->next;
				last = new->head;

			}
			else{

				last->next = _elemdup(curr);
				new->size++;

				curr = curr->next;
				last = last->next;

			}

		}
	}

	return new;

}



struct set_t* _from_arr(double* arr, unsigned int length){

	struct set_t* set = _create();

	if(length==0){
		return set;
	}

	for(int i = 0; i < length; i++){

		_insert(set, arr[i]);

	}

	return set;

}




double* _to_arr(struct set_t* set){

	nullcheck(set);

	if(_empty(set)){
		return NULL;
	}
	else{

		unsigned int length = set->size;
		double* arr = memcheck(sizeof(double)*length);

		struct elem_s* curr = set->head;
		unsigned int count = 0;
		while(curr != NULL){

			arr[count] = curr->value;

			curr = curr->next;
			count++;

		}

		return arr;
	}

}



bool _is_subset(struct set_t* a, struct set_t* b){

	nullcheck(a);
	nullcheck(b);

	if(_empty(a)){
		return true;
	}
	else{

		struct elem_s* curr = a->head;

		while(curr != NULL){

			if(!_contains(b, curr->value)){
				return false;
			}

			curr = curr->next;

		}
	}

	return true;

}



bool _equals(struct set_t* a, struct set_t* b){

	nullcheck(a);
	nullcheck(b);

	return (_is_subset(a, b) && _is_subset(b, a));

}






