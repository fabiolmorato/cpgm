compress: compress.c pgm/pgm.h pgm/pgm.c cpgm/cpgm.h cpgm/cpgm.c
	gcc -o compress compress.c pgm/pgm.c cpgm/cpgm.c -std=c11 -Wall -pedantic -lm -g

uncompress: uncompress.c pgm/pgm.h pgm/pgm.c cpgm/cpgm.h cpgm/cpgm.c
	gcc -o uncompress uncompress.c pgm/pgm.c cpgm/cpgm.c -std=c11 -Wall -pedantic -lm -g
