#include "pgm/pgm.h"
#include "cpgm/cpgm.h"

int main (int argc, char** argv)
{
    pgm_t* pgm = pgm_create();
    cpgm_t* cpgm = cpgm_create();
    pgm_read_file(pgm, argv[1]);
    cpgm_compress_pgm(cpgm, pgm);
    cpgm_write_file(cpgm, argv[2]);
    pgm_delete(pgm);
    cpgm_delete(cpgm);
    return 0;
}
