#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"

pgm_t* pgm_create (void)
{
    pgm_t* pgm = malloc(sizeof(pgm_t));
    if (pgm == NULL) return NULL;

    pgm->dim_x = 0;
    pgm->dim_y = 0;
    pgm->pgm = NULL;

    return pgm;
}

void pgm_read_file (pgm_t* pgm, char* file)
{
    if (pgm == NULL || file == NULL) return;

    FILE* fp = fopen(file, "r");
    if (fp == NULL) return;

    fseek(fp, 3, SEEK_SET); // ignoring "P2\n"
    fscanf(fp, "%u %u %u", &(pgm->dim_x), &(pgm->dim_y), &(pgm->max_value));

    pgm->pgm = (unsigned**) malloc(sizeof(unsigned*) * pgm->dim_y);
    if (pgm->pgm == NULL)
    {
        fclose(fp);
        return;
    }

    for (unsigned  i = 0; i < pgm->dim_y; i++)
    {
        pgm->pgm[i] = (unsigned*) malloc(sizeof(unsigned) * pgm->dim_x);
        if (pgm->pgm[i] == NULL)
        {
            for (unsigned j = i + 1; j > 0; j--) free(pgm->pgm[j - 1]);
            free(pgm->pgm);
            pgm->pgm = NULL;
            fclose(fp);
            return;
        }
    }

    for (unsigned i = 0; i < pgm->dim_y; i++)
    {
        for (unsigned j = 0; j < pgm->dim_x; j++)
        {
            fscanf(fp, "%u", &(pgm->pgm[i][j]));
        }
    }

    fclose(fp);
}

void pgm_write_file (pgm_t* pgm, char* file)
{
    if (pgm == NULL || file == NULL || pgm->pgm == NULL) return;

    FILE* fp = fopen(file, "w");
    if (fp == NULL) return;

    fprintf(fp, "P2\n%u %u %u\n", pgm->dim_x, pgm->dim_y, pgm->max_value);

    for (unsigned i = 0; i < pgm->dim_y; i++)
    {
        for (unsigned j = 0; j < pgm->dim_x; j++)
        {
            fprintf(fp, " %u", pgm->pgm[i][j]);
        }

        fprintf(fp, "\n");
    }

    fclose(fp);
}

void pgm_delete (pgm_t* pgm)
{
    if (pgm == NULL) return;

    if (pgm->pgm != NULL)
    {
        for (unsigned i = 0; i < pgm->dim_y; i++) free(pgm->pgm[i]);
        free(pgm->pgm);
    }

    free(pgm);
}
