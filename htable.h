/**
 * htbale.h
 * IJC-DU2, 15.4. 2011
 * Autor: Ondrej Machacek, FIT
 * Prelozeni gcc 4.5.1
 * Rozhrani pro praci s hash_table.
 */


#define MAX_LEN 256	/* Maximalni delka slova  255 + '\0' */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

enum ECODES {
	EOK,
	EALLOC,
	EUNKNOWN,
};

/**
 *
 */
typedef struct st_htable_listitem {
	char *key;
	unsigned int data;
	struct st_htable_listitem* next;
} htable_listitem;

/**
 *
 */
typedef struct st_htable {
	int htable_size;// Most of the time, this required size is either a power of two, or a prime number.
	htable_listitem** list;
} htable_t;

/**
 *
 */
typedef struct st_htable_iterator {
	htable_t *htptr;
	int index;
	htable_listitem *ptr;
} htable_iterator;

/**
 * pro vytvoření a inicializaci tabulky
 */
htable_t* htable_init(int size);

/**
 *
 */
htable_listitem * htable_lookup(htable_t *t, const char *key);

/**
 * zrušení všech položek v tabulce
 */
void htable_clear(htable_t *t);

/**
 * zrušení tabulky (volá clear)
 */
void htable_free(htable_t *t);

/**
 * získání iterátoru na první položku
 */
htable_iterator htable_begin(htable_t *t);

/**
 * získání iterátoru za poslední položku (NULL)
 */
htable_iterator htable_end(htable_t *t);

/**
 *  posun iterátoru na další prvek (++i)
 */
htable_iterator* htable_iter_next(htable_iterator *t);

/**
 *  porovnání iterátorů na shodu
 */
static inline bool htable_iter_eq(htable_iterator* i1, htable_iterator* i2) {
	return (i1->ptr && i1->ptr->next == NULL && i1->ptr == i2->ptr && i1->index == i2->index && i1->htptr == i2->htptr);
}

/**
 * získání ukazatele na záznam v tabulce
 */
static inline htable_listitem* htable_iter_deref(htable_iterator* i) {
	return i->ptr;
}
