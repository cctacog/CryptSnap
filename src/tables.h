#ifndef TABLES
#define TABLES

#include "reference.h"

typedef struct Table
{
    int length;
    int width;    
    char filler[15];    
}Table;

void initialize_table(Table *table, char *filler, int len, int width);

#endif