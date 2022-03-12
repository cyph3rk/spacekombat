#include "trace.h"

FILE * iniciaArquivo() {
    FILE *fp;
    if ((fp=fopen("trace.txt","w"))==NULL){
        printf("Erro criar arquivo.\n");
    }
    escreveTrace("Inicio trace\n", fp);
    return fp;
}

void escreveTrace(char *str, FILE *fp){
    fputs(str, fp);
    fputs("\n", fp);
}

void fecharArquivo(FILE *fp){
    escreveTrace("Fim trace\n", fp);
    fclose(fp);
}

