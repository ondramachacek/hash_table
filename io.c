/**
 * io.c
 * IJC-DU2, 15.4. 2011
 * Autor: Ondrej Machacek, FIT
 * Prelozeni gcc 4.5.1
 * Funkce pro cteni vstupu.
 */


#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Cte jedno slovo ze souboru f do zadaneho pole znaku a vrati delku slova
 * (z delsich slov vrati prvnich max-1 znaku, a zbytek preskoci).
 * Funkce vraci nulu, pokud je konec souboru.
 */
int fgetword(char *s, int max, FILE *f) {
	int c, index = 0;
	int counter = max - 1;
	static bool err = false;

	while (isspace(c = fgetc(f)));	// preskot whitespace
	ungetc(c, f);	// vrat do streamu posledni nacteny znak(neni whitespace)
	while ((!isspace(c = fgetc(f)) && (--counter)) && c != EOF) {	// nacti radek nebo MAX_LINE znaku
		s[index++] = c;
	}
	s[index] = '\0';
	if (!counter) { // jeste osetrit jestli neni posledni znak EOF
		while (!isspace(c = fgetc(f)) && c != EOF ); // zbav se znaku za znakem s indexem 254
		if(c != EOF)
			ungetc(c, f);
		if(!err) {
			fprintf(stderr, "Prilis dlouhe slovo na radku.\n");
			err=true;
		}
	}

	if (c == EOF) { // Osetreni moznosti kdy neni EOF za whitespace
		if (index > 0)
			ungetc(c, f);
		else
			return 0;
	}

	return max - 1 - (counter ? counter : 1);
}
