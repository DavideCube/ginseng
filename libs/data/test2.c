#include "hashtable.h"


int main(){

	table_t* hashtable = ht_create(65536);

	ht_put(hashtable, "PI", 3.14);
	ht_put(hashtable, "zero", 0);
	ht_put(hashtable, "Eleven", 11);
	ht_put(hashtable, "PI", 3.14);
	ht_put(hashtable, "a", 1);

	ht_get(hashtable, "a");
	ht_get(hashtable, "PI");
	ht_get(hashtable, "zero");
	ht_get(hashtable, "No");

}