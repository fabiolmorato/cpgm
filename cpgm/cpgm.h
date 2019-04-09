#ifndef CPGM_H
#define CPGM_H

#include "../pgm/pgm.h"

typedef struct {
    unsigned  dim_x;
    unsigned  dim_y;
    unsigned  max_value;
    unsigned  horizontal_split;
    unsigned  vertical_split;
    unsigned* line_average;
    unsigned* column_average;
} cpgm_t;

cpgm_t* cpgm_create (void);
void    cpgm_compress_pgm (cpgm_t*, pgm_t*);
void    cpgm_split_compress_pgm (cpgm_t*, pgm_t*, unsigned, unsigned);
void    cpgm_write_file (cpgm_t*, char*);
void    cpgm_read_file (cpgm_t*, char*);
pgm_t*  cpgm_uncompress_pgm (cpgm_t*);
void    cpgm_delete (cpgm_t*);

#endif
