/**
 * htable_iter_next.c
 * IJC-DU2, 15.4. 2011
 * Autor: Ondrej Machacek, FIT
 * Prelozeni gcc 4.5.1
 * Posun iterator na dalsi polozku v htable.
 */


#include "htable.h"

/**
 * @see - htable.h
 */
htable_iterator* htable_iter_next(htable_iterator *i) {

	if (i->ptr->next) {	// pokud je neco v listu, vratto
		i->ptr = i->ptr->next;
	} else {	// najdi dalsi neprazny prvek
		while( ++(i->index) < i->htptr->htable_size) {
			if(i->htptr->list[i->index] != NULL) {
				i->ptr = i->htptr->list[i->index];
				return i;
			}
		}
		i->ptr = NULL;
	}
	return i;
}
