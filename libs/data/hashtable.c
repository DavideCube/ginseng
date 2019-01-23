#include "hashtable.h"
#define DEBUG
#define CONFLICT_CHECK


table_t* ht_create(int size){

	if(size <= 0)
		return NULL;

	table_t* hashtable = malloc(sizeof(table_t));
	if(hashtable == NULL){
		#ifdef DEBUG
			printf("Map allocation failed.\n");
		#endif
		return NULL;
	}

	hashtable->table = malloc(sizeof(entry_t*)*size);
	if(hashtable->table == NULL){
		#ifdef DEBUG
			printf("Bucket allocation failed.\n");
		#endif
		return NULL;
	}

	for(int i = 0; i < size; i++){
		hashtable->table[i] = NULL;
	}

	hashtable->size = size;

	return hashtable;
}


int ht_hash(table_t* hashtable, char* key){

	if(hashtable == NULL)
		return -INT_MAX;

	unsigned long int hashval;
	int i = 0;
	/* Convert our string to an integer */
	while(hashval < ULONG_MAX && i < strlen( key ) ) {
		hashval = hashval << 8;
		hashval += key[i];
		i++;
	}

	#ifdef DEBUG
		unsigned long int result = hashval % hashtable->size;
		printf("Value %s has been hashed to %lu.\n", key, result);
	#endif


	return hashval % hashtable->size;
}



entry_t* ht_pair(char* key, double value){
	entry_t* pair = malloc(sizeof(entry_t));
	if(pair == NULL){
		#ifdef DEBUG
			printf("New pair allocation failed.\n");
		#endif
		return NULL;
	}


	pair->key = strdup(key);
	if(pair->key == NULL){
		#ifdef DEBUG
			printf("New pair allocation failed.\n");
		#endif
		return NULL;
	}


	pair->value = value;
	pair->next = NULL;

	#ifdef DEBUG
		printf("Pair created. Key: %s. Value: %f\n", key, value);
	#endif

	return pair;
}


int ht_put(table_t* hashtable, char* key, double value){

	if(hashtable == NULL)
		return -INT_MAX;

	int bucket = ht_hash(hashtable, key);

	entry_t* next_pair = hashtable->table[bucket];
	entry_t* last_pair = NULL;

	while(next_pair != NULL && next_pair->key != NULL && strcmp(key, next_pair->key) != 0) {
		last_pair = next_pair;
		next_pair = next_pair->next;
	}

	if(next_pair != NULL && next_pair->key != NULL && strcmp(key, next_pair->key) == 0){
		//already present, skip?
		printf("Already present!\n");

		/**
		* Code to replace value if key is already present
		* free(next_pair->value);
		* next_pair->value = strdup(value);
		*/
		return -INT_MAX;
	}
	else{

		entry_t* new_pair = ht_pair(key, value);

		//now decide where to put in the list

		/* We're at the start of the linked list in this bin. */
		if(next_pair == hashtable->table[bucket] ) {
			new_pair->next = next_pair;
			hashtable->table[bucket] = new_pair;
	
		/* We're at the end of the linked list in this bin. */
		}else if(next_pair == NULL){

			last_pair->next = new_pair;
	
		/* We're in the middle of the list. */
		} else  {
			new_pair->next = next_pair;
			last_pair->next = new_pair;
		}


	}

	return OK;
}



double ht_get(table_t* hashtable, char* key){

	if(hashtable == NULL)
		return -DBL_MAX;//could be a good idea to limit type size in ginseng, and set this variable to min value possible

	//find the bucket in which our value will be
	int bucket = ht_hash(hashtable, key);
	entry_t* pair = hashtable->table[bucket];

	//check for the value in the bucketlist
	while(pair != NULL && pair->key != NULL && strcmp(key, pair->key) != 0){
		pair = pair->next;
	}
	if(pair == NULL || pair->key == NULL || strcmp(key, pair->key) != 0){
		#ifdef DEBUG
		printf("No element with key %s found.\n", key);
		#endif
		return -DBL_MAX; //will change with some kind of error code control
	}
	else{
		#ifdef DEBUG
		double result = pair->value;
		printf("Pair found: [%s, %f]\n", key, result);
		#endif
		return pair->value;
	}

}


