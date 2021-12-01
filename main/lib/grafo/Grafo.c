//
// Created by mikae on 22/11/2021.
//

#include "Grafo.h"

#define INFINITO 99999999
#define MESSAGE_PATH "\n\t> Calculando o caminho minimo...\n"

//------------------ FUNÇÕES PRIVADAS --------------------------------
void inicializaCaminho(grafo * g, int n, int origem);
float pegaFloat();
void mostraCaminhoMinimo(grafo * g, int origem, int n);
int temCaminho(float * vetorAdj, int * rotulados, int n);
void zeraCaminho(caminhoMinimo * cm, int n);
void atribuiValorVetor(int * vetor, int n, int valor);
//--------------------------------------------------------------------

grafo * newGrafo(int tamEntrada){
    grafo * g = malloc(sizeof (grafo));
    g->cidades = newVetorCidade(tamEntrada);
    g->caminho = newCaminho(tamEntrada);
    g->rotulados = newVetor(tamEntrada);
    g->matrizAdj = newMatriz(tamEntrada);
    return g;
}

int * newVetor(int n){
    int * new = (int *) malloc(n * sizeof (int));
    atribuiValorVetor(new, n, 0);
    return new;
}

void atribuiValorVetor(int * vetor, int n, int valor){
    int i;
    for(i = 0; i < n; i++){
        vetor[i] = valor;
    }
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
            printf("\t%.2f ", f[i][j]);
        }
    }
}

caminhoMinimo * newCaminho(int n){
    caminhoMinimo * new = (caminhoMinimo *) malloc(n * sizeof (caminhoMinimo));
    int i;
    zeraCaminho(new, n);
    return new;
}

void zeraCaminho(caminhoMinimo * cm, int n){
    int i;
    for(i = 0; i < n; i++){
        cm[i].dist = INFINITO;
        cm[i].predecessor = -1;
    }
}

void inicializaCaminho(grafo * g, int n, int origem){
    zeraCaminho(g->caminho, n);
    atribuiValorVetor(g->rotulados, n, 0);
    g->caminho[origem].predecessor = INFINITO; //Defino o primeiro nó
    g->caminho[origem].dist = 0; //Defino a distância dele com ele mesmo como 0
    g->rotulados[origem] = 1; //Se for 1 é no rotulado atual;
}

int temCaminho(float * vetorAdj, int * rotulados, int n){ // Função que verifica se uma linha tem caminho para o qual seguir
    //Ou seja, se a linha pode ir para algum outro vértice do grafo ainda não rotulado
    int i;
    for (i = 0; i < n; ++i) {
        if(vetorAdj[i] != 0 && !(rotulados[i])){
            return 1;
        }
    }
    return 0;
}

void dijkstra(grafo * g, int origem, int destino, int n){
    printf(MESSAGE_PATH);
    inicializaCaminho(g, n, origem);
    int proxRotulo;
    while(!(g->rotulados[destino])){ // Enquanto eu não rotular o nó destino eu continuo
        int orig;
        for(orig = 0; orig < n; orig++){ //For para percorrer as linhas
            if(g->rotulados[orig]){ //Se a linha for um nó rotulado então entra

                if(temCaminho(g->matrizAdj[orig], g->rotulados,n)){
                    int dest;
                    float menor = INFINITO;
                    for(dest = 0; dest < n; dest++){ //For para percorrer as colunas
                        float atual = g->matrizAdj[orig][dest]; //Pego a distância atual
                        if(atual > 0){ //Se tiver caminho entre a linha e a coluna então entra no laço
                            if(g->caminho[orig].dist != INFINITO){
                                atual += g->caminho[orig].dist;
                            }
                            if(atual < g->caminho[dest].dist){
                                g->caminho[dest].dist = atual; //Atribuo a distancia entre o predecessor e o destino
                                g->caminho[dest].predecessor = orig;
                            }

                            if(atual < menor && g->rotulados[dest] == 0){
                                proxRotulo = dest;
                                menor = atual;
                            }
                        }
                    }
                }
                else{
                    g->rotulados[orig] = -1; //Se nao tiver como ir desse ponto para outro, apenas rotula ele e sai
                    return;
                }
            }
        }
        g->rotulados[proxRotulo] = 1; //Proximo nó a ser rotulado
        g->rotulados[orig] = -1; //Já foi rotulado
    }
}

void mostraCaminhoMinimo(grafo * g, int origem, int n){
    int i;
    printf("\n\nCAMINHO MINIMO DA ORIGEM %d\n", origem);
    for(i = 0; i < n; i++){
        printf("\nCODIGO %d:[DIST: %.2f, PRED: %d]", i, g->caminho[i].dist, g->caminho[i].predecessor);
    }
}

void calculaCaminhoMinimoEntreNos(grafo * g, int n, int origem, int destino){
    mostraCaminhoMinimo(g, origem, n);
    int atual = destino;// O valor do caminho é calculado acessado o nó de destino e somando as
    //distâncias dos predecessores até chegar no nó de origem
    //int * emOrdem = newVetor(n, 0);//variável para imprimir o caminho em ordem
    int emOrdem[n];
    int j, cont = 0;
    float total = g->caminho[destino].dist;
    if(total == INFINITO){
        printf("\nNAO HA CAMINHO!\n");
    }
    else{
        while(atual != -1 && atual != INFINITO && cont < n){
            emOrdem[cont] = atual;
            atual = g->caminho[atual].predecessor;
            cont++;
        }
        printf("\nCAMINHO = {");
        cont--;
        for(j = cont; j >= 0; j--){
            int vertice = emOrdem[j];
               printf(" %d ", vertice);
        }
        printf("}\n");
        printf("\nO CAMINHO MINIMO E: %.2f\n", total);
    }
}
