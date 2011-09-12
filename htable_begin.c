/**
 * htable_begin.c
 * IJC-DU2, 15.4. 2011
 * Autor: Ondrej Machacek, FIT
 * Prelozeni gcc 4.5.1
 * Vrati iterator na prvni polozku v hash_table.
 */

#include "htable.h"

/**
 * @see - htable.h
 */
htable_iterator htable_begin(htable_t *t) {
	htable_iterator it;

	it.htptr = t;
	it.index = -1;
	it.ptr = NULL;

	while ( ++(it.index) < t->htable_size) {
		if(t->list[it.index] != NULL) {
			it.ptr = t->list[it.index];
			break;
		}
	}

	return it;
}
