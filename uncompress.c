#include "pgm/pgm.h"
#include "cpgm/cpgm.h"

int main (int argc, char** argv)
{
    cpgm_t* cpgm = cpgm_create();
    cpgm_read_file(cpgm, argv[1]);
    pgm_t* pgm = cpgm_uncompress_pgm(cpgm);
    pgm_write_file(pgm, argv[2]);
    pgm_delete(pgm);
    cpgm_delete(cpgm);
    return 0;
}
