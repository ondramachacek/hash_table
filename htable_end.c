/**
 * htable_end.c
 * IJC-DU2, 15.4. 2011
 * Autor: Ondrej Machacek, FIT
 * Prelozeni gcc 4.5.1
 * Vrati itarator na posledni prvek v hash_table.
 */


#include "htable.h"

/**
 * @see - htable.h
 */
htable_iterator htable_end(htable_t *t) {
	htable_iterator it;

	it.htptr = t;
	it.index = t->htable_size;
	it.ptr = NULL;

	while ( --(it.index) >= 0 ) {
		if (t->list[it.index] != NULL) {
			it.ptr = t->list[it.index];
			break;
		}
	}

	return it;
}
