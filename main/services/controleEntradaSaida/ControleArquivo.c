#include "ControleArquivo.h"

// =-=-=-=-= CONSTANTES =-=-=-=-=

#define ERRO_ABRIR_ARQUIVO "\n\tERRO: Erro na abertura do arquivo!\n"

#define MENSSAGE_LENDO_ARQUIVO "\n\tAVISO: Lendo arquivo, por favor aguarde...\n"
#define MESSAGE_CIDADES "\n\t> Armazenando Cidades...\n"
#define MESSAGE_DISTANCIAS "\n\t> Armazenando Distancias...\n"
#define DIRETORIO_ARQUIVO_ENTRADA "../entradas/entrada.txt"
#define LINE_MAX_LENGTH 255
#define DELIMITER ";"

// =-=-=-=-= METODOS PRIVADOS | DECLARAÇÃO =-=-=-=-=

cidade *readNextCity(FILE *fp);
void readDist(FILE * fp, int registros, float * vetorAdj);

// =-=-=-=-= METODOS PRIVADOS | IMPLEMENTAÇÃO =-=-=-=-=

void readDist(FILE * fp, int registros, float * vetorAdj){
    float f;
    char * line = malloc((registros * 7)*sizeof (char));
    char * ptr;
    int cont = 0;

    fscanf(fp, " %[^\n]*c", line);
    ptr = strtok(line, DELIMITER);
    while(ptr != NULL){
        vetorAdj[cont] = (float) atof(ptr);
        ptr = strtok(NULL, DELIMITER);
        cont++;
    }
    free(line);
}

cidade * readNextCity(FILE *fp) {
    cidade * c = newCidade();
    char *line = (char *) malloc((LINE_MAX_LENGTH + 1) * sizeof(char));
    char *ptr;

    fscanf(fp, " %[^\n]%*c", line);
    strtok(line, DELIMITER);

    ptr = strtok(NULL, DELIMITER);
    strcpy(c->nome, ptr);

    free(line);

    return c;
}
// =-=-=-=-= METODOS PUBLICOS =-=-=-=-=

grafo * readGrafoFromFile(int * tamEntrada)
{
    FILE *fp = fopen(DIRETORIO_ARQUIVO_ENTRADA, "r");
    int contador = 0;
    int registros;

    if (!fp)
    {
        printf(ERRO_ABRIR_ARQUIVO);
        return NULL;
    }

    printf(MENSSAGE_LENDO_ARQUIVO);
    fscanf(fp, "%d", &registros);
    grafo * fork = newGrafo(registros);
    printf(MESSAGE_CIDADES);
    while (!feof(fp) && contador < registros)
    {
        cidade * c = readNextCity(fp);
        insereCidade(fork->cidades, c, registros);
        contador++;
    }
    contador = 0;
    printf(MESSAGE_DISTANCIAS);
    while (!feof(fp) && contador < registros)
    {
        readDist(fp, registros, fork->matrizAdj[contador]);
        contador++;
    }

    fclose(fp);
    *tamEntrada = registros;
    return fork;
}
