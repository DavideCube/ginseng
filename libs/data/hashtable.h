#ifndef HASHTABLE_H
#define HASHTABLE_H

#define _XOPEN_SOURCE 500 /* Enable certain library functions (strdup) on linux.  See feature_test_macros(7) */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <float.h>

#define OK 0
#define NO_MEM -1
#define FULL -2
#define DUPLICATED -3


struct ht_entry {
	char* key;
	double value;
	struct ht_entry *next;
};
typedef struct ht_entry entry_t;


struct ht_table {
	int size;
	struct ht_entry** table;	
};
typedef struct ht_table table_t;


table_t* ht_create(int size);
int ht_hash(table_t* table, char *key);
entry_t* ht_pair(char* key, double value);
int ht_put(table_t* hashtable, char* key, double value);
double ht_get(table_t* hashtable, char *key);

int ht_has(table_t* hashtable, char* key);
//int ht_delete(table_t* hashtable, char* key);
//size_t get_size(table_t* hashtable);


#endif