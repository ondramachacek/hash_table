/**
 * wordcount.c
 * IJC-DU2, 15.4. 2011
 * Autor: Ondrej Machacek, FIT
 * Prelozeni gcc 4.5.1
 * Funkce pro testovani implementace htable,
 */


#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "io.h"
#include "htable.h"

#define HTABLE_SIZE 8192

int main() {
	FILE *f = stdin;
	// f = fopen("/home/Ondra/ahoj1.txt", "r"); // smazat
	char string[MAX_LEN];
	int len;

	htable_t* table = htable_init(HTABLE_SIZE);
	htable_listitem *item;

	while ( (len = fgetword(string, MAX_LEN, f)) != 0 ) {
		if((item = htable_lookup(table, string)) == NULL) {
			fprintf(stderr, "Chyba pri alokaci pameti.\n");
			return EXIT_FAILURE;
		}
	}

	// fclose(f);	//smazat

	htable_iterator b = htable_begin(table);
	htable_iterator *bg = &b;
	htable_iterator end = htable_end(table);

	while( !htable_iter_eq(bg, &end) ) {
		if(htable_iter_deref(bg) == NULL)
			break;
		printf("%s\t%d\n", bg->ptr->key, bg->ptr->data);
		bg = htable_iter_next(bg);
	}
	if(end.ptr != NULL)
		printf("%s\t%d\n", end.ptr->key, end.ptr->data);
	// Uklid haldu
	htable_free(table);

	return EXIT_SUCCESS;
}
