#ifndef PGM_H
#define PGM_H

typedef struct {
    unsigned   dim_x;
    unsigned   dim_y;
    unsigned   max_value;
    unsigned** pgm;
} pgm_t;

pgm_t* pgm_create (void);
void   pgm_read_file (pgm_t*, char*);
void   pgm_write_file (pgm_t*, char*);
void   pgm_delete (pgm_t*);

#endif
