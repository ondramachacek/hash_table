/**
 * htable_clear.c
 * IJC-DU2, 15.4. 2011
 * Autor: Ondrej Machacek, FIT
 * Prelozeni gcc 4.5.1
 * Uvolni pamet.
 */


#include "htable.h"

/**
 * @see - htable.h
 */
void htable_clear(htable_t *table) {
	int i;
	htable_listitem *it, *tmp;
	for (i = 0; i < table->htable_size; i++) {
		it = table->list[i];
		if (it == NULL) continue;
		while (it->next) {
			tmp = it;
			it = it->next;
			free(tmp->key);
			free(tmp);
		}
		free(it->key);
		free(it);
	}
}
