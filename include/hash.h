#ifndef _HASH_H
#define _HASH_H
#include "divers.h"
#include "listhash.h"

hashtable_t hashtable_new(int m);

int hashing(cle_t cle, hashtable_t hash);

int hashtable_put(cle_t k, value_t v, hashtable_t t);

int hashtable_put_graph(cle_t k, value_t v, hashtable_t t, graph_t graph);

int hashtable_contains(cle_t k,hashtable_t t);

int hashtable_get_value(cle_t k, value_t* pv, hashtable_t t);

int hashtable_delete_key(cle_t k, hashtable_t t);

int hashtable_delete(hashtable_t hash);

void hashtable_print(hashtable_t hash);

#endif
