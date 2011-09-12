/**
 * tail2.cc
 * IJC-DU2, 15.4. 2011
 * Autor: Ondrej Machacek, FIT
 * Prelozeni g++ 4.5.1
 * Implemetace utility tail v C++.
 */

#include <cerrno>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <deque>

using namespace std;

enum ECODES
{
        EOK = 0,        /* Vse v poradku */
        EARGS = 1,      /* Spatne argumenty prikazove radky */
        EREAD = 2,      /* Chyba pri cteni souboru */
        EALLOC = 3,     /* Chyba pri alokaci pameti */
        ELINE = 4,      /* Prilis dlouhy radek na vstupu */
        EOPEN = 5,      /* Chyba pri otevirani souboru */
        ENUMBER = 6,    /* Spatne cislo na vstupu */
        EUNKNOWN = 7    /* Neznama chyba. Musi byt definovana jako posledni */
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
	cerr << errors[error_number > EUNKNOWN || error_number < EOK ? EUNKNOWN : error_number];
}

/**
 * Vytiskne vsechny radky od radku @n z proudu @stream.
 * @stream - stream ze ktereho se bude cist
 * @n      - pocet radku ktere se maji vytisknout
 */
void tailFromIndex(istream *in, unsigned int lines = 10) {
	string line;
	unsigned int line_counter = 1;
	unsigned int n = lines; // argv[2]

	while((*in).good()) {
		getline(*in, line);
		if(line_counter++ >= n)
			cout << line << endl;
	}

	if (in != &cin)
		delete in;
}

/**
 * Vytiskne poslednich @n radku z proudu @file.
 * @file - soubor ze ktereho budeme cist, null pro stdin
 * @n    - pocet radku od konce, ktere chceme vytisknout
 */
void tailFromEnd(istream *in, unsigned int lines = 10) {
	string line;
	deque<string> dq;
	deque<string>::iterator it;
	unsigned int counter = 0;

	getline(*in, line);
	while((*in).good()) {
		if(++counter > lines)
			dq.pop_front();
		dq.push_back(line);
		getline(*in, line);
	}

	// Vytiskni zasobnik
	it = dq.begin();
	while(it != dq.end()) {
		cout << *it++ << endl;
	}

	if(in != &cin)
		delete in;
}

int processArguments(int argc, char** argv) {
	istream *stream = &cin;
        char *endptr;
        int plus = 0;
        if (argc == 1 || argc == 2) {
                if(argc == 2)
			if((stream = new ifstream(argv[1], ios::in)) == NULL)
                                return EOPEN;
                tailFromEnd(stream);
        } else if((argc == 3 || argc == 4) && strcmp(argv[1], "-n") == 0 ) {
                        if(argc == 4) {
				if((stream = new ifstream(argv[3], ios::in)) == NULL)
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
                                tailFromIndex(stream, (unsigned) n);
                        else {
				if(n <= 0) {
					if(stream != &cin)
						delete stream;
					return EOK;
				}
                                tailFromEnd(stream, (unsigned) n);
			}
        } else {
                printf("%s\n", HELP);
        }
        return EOK;

}

int main(int argc, char **argv)
{
	int o = processArguments(argc, argv);
	if( o != EOK)
		printError(o);

	return EXIT_SUCCESS;
}
