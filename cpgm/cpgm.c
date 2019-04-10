#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../pgm/pgm.h"
#include "cpgm.h"

cpgm_t* cpgm_create (void)
{
    cpgm_t* cpgm = malloc(sizeof(cpgm_t));
    if (cpgm == NULL) return NULL;

    cpgm->dim_x = 0;
    cpgm->dim_y = 0;
    cpgm->max_value = 0;

    cpgm->horizontal_split = 0;
    cpgm->vertical_split = 0;

    cpgm->line_average = NULL;
    cpgm->column_average = NULL;

    return cpgm;
}

void cpgm_compress_pgm (cpgm_t* cpgm, pgm_t* pgm)
{
    if (cpgm == NULL || pgm == NULL || pgm->pgm == NULL) return;

    if (cpgm->line_average != NULL) free(cpgm->line_average);
    if (cpgm->column_average != NULL) free(cpgm->column_average);

    cpgm->dim_x = pgm->dim_x;
    cpgm->dim_y = pgm->dim_y;
    cpgm->max_value = pgm->max_value;

    cpgm->line_average = (unsigned*) malloc(sizeof(unsigned) * cpgm->dim_y);
    cpgm->column_average = (unsigned*) malloc(sizeof(unsigned) * cpgm->dim_x);

    for (unsigned i = 0; i < pgm->dim_y; i++)
    {
        unsigned sum = 0;
        for (unsigned j = 0; j < pgm->dim_x; j++) sum += pgm->pgm[i][j];
        cpgm->line_average[i] = sum / cpgm->dim_x;
    }

    for (unsigned j = 0; j < pgm->dim_x; j++)
    {
        unsigned sum = 0;
        for (unsigned i = 0; i < pgm->dim_y; i++) sum += pgm->pgm[i][j];
        cpgm->column_average[j] = sum / cpgm->dim_y;
    }
}

void cpgm_write_file (cpgm_t* cpgm, char* file)
{
    if (cpgm == NULL || file == NULL || cpgm->line_average == NULL || cpgm->column_average == NULL) return;

    FILE* fp = fopen(file, "w");
    if (fp == NULL) return;

    fprintf(fp, "CPGM\n%u %u %u %u %u\n", cpgm->dim_x, cpgm->dim_y, cpgm->max_value, cpgm->horizontal_split, cpgm->vertical_split);

    for (unsigned i = 0; i < cpgm->dim_y; i++) fprintf(fp, " %u", cpgm->line_average[i]);
    fprintf(fp, "\n");
    for (unsigned i = 0; i < cpgm->dim_x; i++) fprintf(fp, " %u", cpgm->column_average[i]);

    fclose(fp);
}

void cpgm_read_file (cpgm_t* cpgm, char* file)
{
    if (cpgm == NULL || file == NULL) return;

    FILE* fp = fopen(file, "r");
    if (fp == NULL) return;

    fseek(fp, 5, SEEK_SET);
    fscanf(fp, "%u %u %u %u %u", &(cpgm->dim_x), &(cpgm->dim_y), &(cpgm->max_value), &(cpgm->horizontal_split), &(cpgm->vertical_split));

    if (cpgm->line_average != NULL)
    {
        free(cpgm->line_average);
        cpgm->line_average = NULL;
    }

    if (cpgm->column_average != NULL)
    {
        free(cpgm->column_average);
        cpgm->column_average = NULL;
    }

    cpgm->line_average = (unsigned*) malloc(sizeof(unsigned) * cpgm->dim_y);
    if (cpgm->line_average == NULL)
    {
        fclose(fp);
        return;
    }

    cpgm->column_average = (unsigned*) malloc(sizeof(unsigned) * cpgm->dim_x);
    if (cpgm->column_average == NULL)
    {
        free(cpgm->line_average);
        cpgm->line_average = NULL;
        fclose(fp);
        return;
    }

    for (unsigned i = 0; i < cpgm->dim_y; i++) fscanf(fp, "%u", &(cpgm->line_average[i]));
    for (unsigned i = 0; i < cpgm->dim_x; i++) fscanf(fp, "%u", &(cpgm->column_average[i]));

    fclose(fp);
}

pgm_t* cpgm_uncompress_pgm (cpgm_t* cpgm)
{
    if (cpgm == NULL || cpgm->line_average == NULL || cpgm->column_average == NULL) return NULL;

    pgm_t* pgm = pgm_create();
    if (pgm == NULL) return NULL;

    pgm->dim_x = cpgm->dim_x;
    pgm->dim_y = cpgm->dim_y;
    pgm->max_value = cpgm->max_value;

    pgm->pgm = (unsigned**) malloc(sizeof(unsigned*) * cpgm->dim_y);
    if (pgm->pgm == NULL)
    {
        pgm_delete(pgm);
        return NULL;
    }

    for (unsigned i = 0; i < cpgm->dim_y; i++)
    {
        pgm->pgm[i] = (unsigned*) malloc(sizeof(unsigned) * cpgm->dim_x);
        if (pgm->pgm[i] == NULL)
        {
            for (unsigned j = i; j > 0; j--) free (pgm->pgm[j - 1]);
            free (pgm->pgm);
            pgm_delete(pgm);
            return NULL;
        }
    }

    for (unsigned i = 0; i < pgm->dim_y; i++)
    {
        for (unsigned j = 0; j < pgm->dim_x; j++)
        {
            float cell = sqrt(cpgm->line_average[i] * cpgm->column_average[j]);
            pgm->pgm[i][j] = (unsigned) cell;
        }
    }

    return pgm;
}

void cpgm_delete (cpgm_t* cpgm)
{
    if (cpgm == NULL) return;

    if (cpgm->line_average != NULL) free(cpgm->line_average);
    if (cpgm->column_average != NULL )free(cpgm->column_average);

    free(cpgm);
}
