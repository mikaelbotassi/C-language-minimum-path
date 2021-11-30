//
// Created by mikae on 22/11/2021.
//
#include "../../lib/cidade/Cidade.h"


#ifndef ARVORE_GERADORA_MINIMA_GRAFO_H
#define ARVORE_GERADORA_MINIMA_GRAFO_H

typedef struct CaminhoMinimo{
    float dist;
    int predecessor;
}caminhoMinimo;

typedef struct Grafo{
    cidade ** cidades;
    int * noRotulado;
    float ** matrizAdj;
    caminhoMinimo ** caminho;
}grafo;

grafo * newGrafo(int tamEntrada);

int * newVetor(int n);

float ** newMatriz(int n);

void preenCheMatriz(float **matriz, int n, int type);

caminhoMinimo ** newCaminho(int n);

void mostraMatriz(float ** f, int n, char nome[]);

void calculaCaminhoMinimoEntreNos(grafo * g, int n, int origem, int destino);

void dijkstra(grafo * g, int origem, int destino, int n);

#endif //ARVORE_GERADORA_MINIMA_GRAFO_H
