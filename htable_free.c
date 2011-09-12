/**
 * htable_free.c
 * IJC-DU2, 15.4. 2011
 * Autor: Ondrej Machacek, FIT
 * Prelozeni gcc 4.5.1
 * Uvolni pamet.
 */

#include "htable.h"

/**
 * @see - htable.h
 */
void htable_free(htable_t *t) {
	htable_clear(t);
	free(t->list);
	free(t);
}
