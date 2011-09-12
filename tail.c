/**
 * tail.c
 * IJC-DU2, 15.4. 2011
 * Autor: Ondrej Machacek, FIT
 * Prelozeni gcc 4.5.1
 * Ze zadaneho vstupniho proudu vytiskne poslednich 10 radku nebo tolik kolik je predano argumentem.
 */

#include <limits.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 1026	/* Maximalni delka radku = 1024 + 1('\n') + 1('\0') */
#define DEFAULT 10	/* Defaultni tiskni 10 poslednich radku */
#define EOL '\n'	/* Znak konce radku */
#define READ_ONLY "r"	/* Soubor se otevre pouze pro cteni */

enum ECODES
{
        EOK = 0,        /* Vse v poradku */
        EARGS = 1,      /* Spatne argumenty prikazove radky */
        EREAD = 2,      /* Chyba pri cteni souboru */
        EALLOC = 3,     /* Chyba pri alokaci pameti */
        ELINE = 4,      /* Prilis dlouhy radek na vstupu */
        EOPEN = 5,      /* Chyba pri otevirani souboru */
        ENUMBER = 6,    /* Spatne cislo na vstupu */
        EUNKNOWN = 7,   /* Neznama chyba. Musi byt definovana jako posledni */
};

/* Texty chyb */
const char *errors[] =
{
        "OK",
        "Chybne argumenty prikazove radky.",
        "Chyba pri cteni z proudu.",
        "Chyba pri alokovani pameti.",
        "Prilis dlouhy radek na vstupu.",
        "Chyba pri otevirani souboru.",
        "Spatny pocet radku.",
        "Neznama chyba. Program se ukonci.", /* Musi byt posledni */
};

/* Napoveda */
const char *HELP =
"pouziti: tail [VOLBY] [SOUBOR]\n"
"Tiskne poslednich 10 radku souboru.\n"
"Volby:\n"
"\t-n\tvytiskne poslednich n radku souboru\n"
"\t+n\tvytiskne vsechny radky od n-teho radku vcetne\n";

/**
 * Vytiskne chybove hlaseni na stderr.
 * @error_number - cislo indentifikujici chybu
 */
void printError(int error_number)
{
	fprintf(stderr, "%s\n", errors[error_number > EUNKNOWN || error_number < EOK ? EUNKNOWN : error_number]);
}

/**
 * Alokace pameti pro n poslednich radku
 */
char** alloc(unsigned int n) {
	int i, j;
	char **buffer;
	if((buffer = (char **) malloc(n * sizeof(unsigned int))) == NULL )
                return NULL;
        for(i = 0; i < n; i++) {
                if((buffer[i] = (char*)malloc(MAX_LINE)) == NULL ) {
                        for (j = i-1; j > 0; j--)
                                free(buffer[j]);
			free(buffer);
                        return NULL;
                }
        }
	return buffer;
}

/**
 * Vytiskne poslednich @n radku z proudu @file.
 * @file - soubor ze ktereho budeme cist, null pro stdin
 * @n    - pocet radku od konce, ktere chceme vytisknout
 */
int tailFromEnd(FILE *stream, unsigned int n)
{
	char **buffer;
 	int point = 0;
	int over = 0;
	
	if(n <= 0) {
		if(stream != NULL && stream != stdin)
                	fclose(stream);
		return EOK;
	}	

	// Alokace pameti
	if((buffer = alloc(n)) == NULL)
		return EALLOC;

	// Nacti do buffer poslednich n radku
	while(fgets(buffer[point], MAX_LINE, stream) != NULL) {
		if(++point == n) {
			point = 0;
			over = 1;
		}
	}

	int i;
	// Vytiskni vsecnhy radky
	if (over)
		for(i = point; i < n; i++)
			fputs(buffer[i], stdout);
	for(i = 0; i < point; i++)
		fputs(buffer[i], stdout);

	// Uzavri stream pokud neni stdin
	if(stream != NULL && stream != stdin)
		fclose(stream);

	// Uvolneni pameti
	for (i = 0; i < n; i++)
		free(buffer[i]);
	free(buffer);

	return EOK;
}

/**
 * Vytiskne vsechny radky od radku @n z proudu @stream.
 * @stream - stream ze ktereho se bude cist
 * @n 	   - pocet radku ktere se maji vytisknout
 */
int tailFromIndex(FILE* stream, unsigned int n)
{
	unsigned int line_counter = 1;
	char *buffer;
	
	// alokace pameti
        buffer = (char *) malloc(MAX_LINE);
        if(buffer == NULL) {
                return EALLOC;
        }

	// Vypis vsechn radku od radku n
	while( fgets(buffer, MAX_LINE, stream) != NULL ) {
		if(buffer[strlen(buffer) - 1] != EOL)
			return ELINE;
		if(line_counter++ >= n)
			fputs(buffer, stdout);
	}
	
	// Uzavreni streamu	
	if(stream != stdin)
		fclose(stream);

	free(buffer);

	return EOK;
}

/**
 * Zpracuje argumenty prikazove radky.
 * @argc - pocet argumentu prikazove radky
 * @argv - pole argumentu prikazove radky
 */
int processArguments(int argc, char **argv)
{
        FILE *f = stdin;
	char *endptr;
	int plus = 0;
        if (argc == 1 || argc == 2) {
                if(argc == 2)
                        if((f = fopen(argv[1], "r")) == NULL)
                                return EOPEN;
                tailFromEnd(f, DEFAULT);
        } else if((argc == 3 || argc == 4) && strcmp(argv[1], "-n") == 0 ) {
                	if(argc == 4) {
                        	if((f = fopen(argv[3], "r")) == NULL)
                                	return EOPEN;
			}
			if(argv[2][0] == '+') {
                                argv[2] = &argv[2][1];
				plus = 1;
			}
 	        	int n = strtol(argv[2], &endptr, 10);
			if(errno == ERANGE || endptr == argv[2])
				return ENUMBER;
                        if( plus )
                                tailFromIndex(f, (unsigned) n);
                        else {
                                tailFromEnd(f, (unsigned) n);
			} 
        } else {
                printf("%s\n", HELP);
        }
        return EOK;
}
       

/* ==--==--==--== */
int main (int argc, char **argv)
{
	int o = processArguments(argc, argv);
	if (o != EOK )	
		printError(o);
	return EXIT_SUCCESS;
}
