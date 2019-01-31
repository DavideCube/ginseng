#include "set.h"
#include "utils.h"

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
			debug("Head deleted!\n");
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


void clear(struct set_t* set){
	
}



void _print(struct set_t* set){

	nullcheck(set);

	if(_empty(set)){
		printf("| |\n");
		return;
	}
	else{
		struct elem_s* curr = set->head;
		while(curr != NULL){
			printf(" | %.3f", curr->value);
			curr = curr->next;
		}
	}

}






