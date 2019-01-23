#include "hashtable.h"


int main(){

	table_t* hashtable = ht_create(65536);

	ht_put(hashtable, "PI", 3.14);
	ht_put(hashtable, "zero", 0);
	ht_put(hashtable, "Eleven", 11);
	ht_put(hashtable, "PI", 3.14);
	ht_put(hashtable, "a1", 1);
	ht_put(hashtable, "PI1", 3.14);
	ht_put(hashtable, "zero1", 0);
	ht_put(hashtable, "Eleven1", 11);
	ht_put(hashtable, "PI1", 3.14);
	ht_put(hashtable, "a2", 1);
	ht_put(hashtable, "PI2", 3.14);
	ht_put(hashtable, "zero2", 0);
	ht_put(hashtable, "Eleven2", 11);
	ht_put(hashtable, "PI2", 3.14);
	ht_put(hashtable, "a2", 1);

	ht_put(hashtable, "PI23", 3.14);
	ht_put(hashtable, "zero23", 0);
	ht_put(hashtable, "Eleven23", 11);
	ht_put(hashtable, "PI24", 3.14);
	ht_put(hashtable, "a124", 1);
	ht_put(hashtable, "PI124", 3.14);
	ht_put(hashtable, "zero124", 0);
	ht_put(hashtable, "Eleven124", 11);
	ht_put(hashtable, "PI165", 3.14);
	ht_put(hashtable, "a277", 1);
	ht_put(hashtable, "PI287", 3.14);
	ht_put(hashtable, "zero21234", 0);
	ht_put(hashtable, "Eleven2209", 11);
	ht_put(hashtable, "PI2=", 3.14);
	ht_put(hashtable, "a296787", 1);

	ht_get(hashtable, "a");
	ht_get(hashtable, "PI");
	ht_get(hashtable, "zero");
	ht_get(hashtable, "No");

}