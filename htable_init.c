/**
 * htable_init.c
 * IJC-DU2, 15.4. 2011
 * Autor: Ondrej Machacek, FIT
 * Prelozeni gcc 4.5.1
 * Inicializace hash_table.
 */


#include "htable.h"
#include <stdlib.h>

/**
 * @see - htable.h
 */
htable_t* htable_init(int size) {
	htable_t* t;
	t = (htable_t*)malloc(sizeof(htable_t));
	if(t == NULL) {
		return NULL;
	}

	t->htable_size = size;
	t->list = (htable_listitem**)malloc(size * sizeof(htable_listitem*));
	int i;
	for(i = 0; i < size; i++) {
		t->list[i] = NULL;
	}

	return t;
}
