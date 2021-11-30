//
// Created by mikae on 22/11/2021.
//

#include "Grafo.h"

#define MAIOR 99999
#define MENOR -99999

void inicializaCaminho(grafo * g, int n, int origem);
float pegaFloat();
void mostraCaminhoMinimo(grafo * g, int n);

grafo * newGrafo(int tamEntrada){
    grafo * g = malloc(sizeof (grafo));
    g->cidades = newVetorCidade(tamEntrada);
    g->noRotulado = newVetor(tamEntrada);
    g->matrizAdj = newMatriz(tamEntrada);
    return g;
}

int * newVetor(int n){
    int * new = malloc(n*sizeof (int));
    for(int i = 0; i < n; i++){
        new[i] = 0;
    }
    return new;
}

float ** newMatriz(int n){
    float ** new = malloc(n * sizeof(float*));
    for (int i = 0; i < n; ++i) {
        new[i] = malloc(n * sizeof (float));
        for(int j = 0; j < n; j++){
            new[i][j] = 0; //Inicia todas as posições com 0
        }
    }
    return new;
}

float pegaFloat(){
    return ((float)rand()/(float)(RAND_MAX) * 10);
}

void preenCheMatriz(float **matriz, int n, int type){
    int caractere = 65;
    for (int i = 0; i < n; ++i) {
        for(int j = 0; j < n; j++){
            if(i == j){
                printf("0.0 ");
                matriz[i][j] = 0;
            }
            else{
                if(matriz[j][i] != 0){ //Como não é um grafo bidirecional não é possível
                //inserir um retorno de um caminho que ja foi inserido
                    printf("%.1f ", 0.0);
                    matriz[i][j] = 0;
                }
                else{
                    if(type == 1){ // Se for 1 insere manualmente as distancias
                        //printf("\nDIGITE A DISTANCIA ENTRE A CIDADE %c E A CIDADE %c: ",caractere + i, caractere + j);
                        printf("\nDIGITE A DISTANCIA ENTRE A CIDADE %d E A CIDADE %d: ", i+1, j+1);
                        scanf("%f", &matriz[i][j]);
                    }
                    else{ //Se for 2 insere automaticamente de maneira aleatória
                        matriz[i][j] = pegaFloat();
                    }
                }
            }
        }
    }
}

void mostraMatriz(float ** f, int n, char nome[]){
    int caractere = 65; // Para pegar a letra que condiz com a coluna
    printf("\n\n\t%s\n\n", nome);
    for(int j = 0; j < n; j++){
        printf("\t  %c ", caractere + j);
    }
    for (int i = 0; i < n; ++i) {
        printf("\n%c ", caractere + i);
        for(int j = 0; j < n; j++){
            printf("\t%.1f ", f[i][j]);
        }
    }
}

caminhoMinimo ** newCaminho(int n){
    caminhoMinimo ** new = (caminhoMinimo **) malloc(n * sizeof (caminhoMinimo *));
    int i;
    for(i = 0; i < n; i++){
        caminhoMinimo * caminho = malloc(sizeof * (caminho));
        caminho->dist = MAIOR;
        caminho->predecessor = 0;
        new[i] = caminho;
    }
    return new;
}

void inicializaCaminho(grafo * g, int n, int origem){
    g->noRotulado = newVetor(n);
    g->noRotulado[origem] = 1; //Defino a posição de origem como rotulada e é de la que irei começar
    g->caminho = newCaminho(n);
    g->caminho[origem]->predecessor = -1; //Defino que não tem predecessor
    g->caminho[origem]->dist = 0; //Defino a distância dele com ele mesmo como 0
}

void dijkstra(grafo * g, int origem, int destino, int n){
    inicializaCaminho(g, n, origem);
    int proxRotulado; //Para armazenar o próximo nó rotulado;
    while(!g->noRotulado[destino]){ // Enquanto eu não rotular o nó destino eu continuo
        int orig;
        for(orig = 0; orig < n; orig++){ //For para percorrer as linhas
            if(g->noRotulado[orig]){ //Se a linha for um nó rotulado então entra
                int dest;
                float menor = MAIOR;
                for(dest = 0; dest < n; dest++){ //For para percorrer as colunas
                    float atual = g->matrizAdj[orig][dest]; //Pego a distância atual
                    if(atual > 0){ //Se tiver caminho entre a linha e a coluna então entra no laço
                        int pAntigo = g->caminho[dest]->predecessor; // Armazeno o antigo predecessor
                        int aux = g->caminho[dest]->predecessor = orig; // variavel auxiliar para percorrer os predecessores
                        printf("Predecessor: %d", g->caminho[dest]->predecessor);
                        /*while (aux != -1) { // Laço que  até que não haja mais nenhum outro nó predecessor.
                            atual += g->caminho[aux]->dist;
                            aux = g->caminho[aux]->predecessor;
                        }*/
                        if(aux != -1){ //soma as distância do nó
                                // predecessor
                            atual += g->caminho[aux]->dist;
                            aux = g->caminho[aux]->predecessor;
                        }

                        float distDestino = g->caminho[dest]->dist; // Guardo a antiga distância do destino
                        if(distDestino > atual){
                            g->caminho[dest]->dist = atual; //Atribuo a distancia entre o predecessor e o destino
                            g->caminho[dest]->predecessor = orig;
                        }
                        else{
                            g->caminho[dest]->predecessor = pAntigo;
                        }
                        if(atual < menor){
                            menor = atual;
                            proxRotulado = dest;
                        }
                    }
                }
                g->noRotulado[proxRotulado] = 1;
            }
        }
    }
    calculaCaminhoMinimoEntreNos(g, n, origem, destino);
}

void mostraCaminhoMinimo(grafo * g, int n){
    int i, j;
    printf("\nCaminho minimo de origem: 5");
    for(i = 0; i < n; i++){
        printf("\nCODIGO %d:\nDISTANCIA: %.2f\nPREDECESSOR: %d\n", i+1, g->caminho[i]->dist, g->caminho[i]->predecessor + 1);
    }
}

void calculaCaminhoMinimoEntreNos(grafo * g, int n, int origem, int destino){
    mostraCaminhoMinimo(g, n);
    int atual = destino; // O valor do caminho é calculado acessado o nó de destino e somando as
    //distâncias até os predecessores até chegar no nó de origem
    float total = 0;
    while(atual != origem){
        total += g->caminho[atual]->dist;
        atual = g->caminho[atual]->predecessor;
    }
    if(!total){
        printf("\nNAO HA CAMINHO!\n");
    }
    else{
        printf("\nO CAMINHO MINIMO E: %.2f\n", total);
    }
}
