/**
 * htable_lookup.c
 * Autor: Ondrej Machacek, FIT
 * Prelozeni gcc 4.5.1
 * Prida novy prvek do htable, nebo inkrementuje pocet vyskytu.
 */

#include "htable.h"
#include <string.h>

unsigned int hash_function(const char *str, unsigned htable_size) {
	unsigned int h = 0;
	unsigned char *p;
	for (p = (unsigned char*) str; *p != '\0'; p++)
		h = 31 * h + *p;
	return h % htable_size;
}

htable_listitem* createNewItem(const char* key) {
	htable_listitem * listitem;
	if ((listitem = (htable_listitem*) malloc(sizeof(htable_listitem))) == NULL) {
		return NULL;
	}
	int len_key = strlen(key) + 1;
	listitem->data = 1;
	if ((listitem->key = (char*) malloc(len_key)) == NULL) {
		free(listitem);
		return NULL;
	}
	listitem->next = NULL;
	strncpy(listitem->key, key, len_key);
	return listitem;
}

/**
 * @see - htable.h
 */
htable_listitem * htable_lookup(htable_t *t, const char *key) {
	/* Find key in htable_t */
	int index = hash_function(key, t->htable_size);
	htable_listitem *listitem;

	if (t->list[index] == NULL) {
		if ((listitem = createNewItem(key)) == NULL)
			return NULL;
		t->list[index] = listitem;
	} else {
		// TODO: is colision? jed na konec seznamu a pridej tam novy prvek
		listitem = t->list[index];
		htable_listitem *l;
		while(listitem) {
			if(strcmp(listitem->key, key) == 0) {
				listitem->data++;
				break;
			}
			l = listitem;
			listitem = listitem->next;
		}
		if(listitem == NULL) {
			if ((listitem = createNewItem(key)) == NULL)
				return NULL;
			l->next = listitem;
			return listitem;
		}
		listitem = t->list[index];
	}
	return listitem;
}
