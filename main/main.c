#include "services/controler/Controler.h"

int main() {

    setvbuf(stdout, NULL, _IONBF, 0); //Uma função para nao dar problema no debugger, não é referente
    //ao trabalho

    int tamEntrada;

//================Estruturas==============================
    grafo * g = services(&tamEntrada);
//========================================================
    if(g != NULL){
        mostraMatriz(g->matrizAdj, tamEntrada, "MATRIZ ADJACENTE");
        //writeGrafoOnFile(g, tamEntrada);
    }

    return 0;
}
