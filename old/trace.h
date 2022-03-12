#ifndef TRACE_H_INCLUDED
#define TRACE_H_INCLUDED

#include <stdio.h>
#include <time.h>


FILE * iniciaArquivo();
void escreveTrace(char *str, FILE *fp);
void fecharArquivo(FILE *fp);
char dataHora();
#endif // TRACE_H_INCLUDED
