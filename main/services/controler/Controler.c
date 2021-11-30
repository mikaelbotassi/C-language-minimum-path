//
// Created by mikae on 27/11/2021.
//

#include "Controler.h"

grafo * services(int * tamEntrada){
    grafo * g = NULL;
    int res;
    int origem, destino;
    char criarArquivo;
    printf("\n\n\t\tOLA! NESTE PROGRAMA VOCE TEM OPCOES!\n\t\tVOCE PODE:\n\n");
    printf("1 - LER ARQUIVOS DE ENTRADA(PARA SEGUIR A ORIENTACAO DO TRABALHO DE"
           "'TPA' POR FAVOR SIGA ESTA OPCAO)\n");
    printf("2 - INSERIR MANUALMENTE AS CIDADES E AS DISTANCIAS\n");
    printf("3 - INSERIR MANUALMENTE AS CIDADES E DEIXAR AS DISTANCIAS SEREM ALEATORIAS\n");
    printf("0 - SAIR\n\n");
    printf("DIGITE UMA OPCAO: ");
    scanf("%d", &res);
    switch (res) {
        case 0:
            break;
        case 1:
            printf("DESEJA CRIAR UM NOVO ARQUIVO ALEATORIO?\nDIGITE 's'"
                   "para sim e 'n' PARA NAO: ");
            scanf(" %c", &criarArquivo);
            if(criarArquivo == 's' || criarArquivo == 'S'){
              criaArquivo(); //Cria o arquivo de entrada
            }
            g = readGrafoFromFile(tamEntrada);
            // Para isso eu atribuo 1 para ele como um visitado

            do{
                printf("\nDIGITE A ORIGEM E O DESTINO QUE VOCE DESEJA SABER O CAMINHO MINIMO:\n");

                printf("\n\tORIGEM: ");
                scanf(" %d", &origem);

                printf("\n\tDESTINO: ");
                scanf(" %d", &destino);

                dijkstra(g, origem, destino, *tamEntrada);

                printf("\nDESEJA PROCURAR O CAMINHO MINIMO ENTRE MAIS VERTICES?\n");
                printf("1 - SIM\n");
                printf("0 - NAO\n");
                printf("DIGITE A OPCAO: ");
                scanf(" %d", &res);
            }while(res != 0);

            break;

        case 2:
            printf("DIGITE QUANTAS CIDADES HA NO TOTAL: ");
            scanf("%d", tamEntrada);

            g = newGrafo(*tamEntrada);

            menu(g->cidades, *tamEntrada);

            preenCheMatriz(g->matrizAdj, *tamEntrada, 1);//Atribui valores à matriz;

            do{
                printf("\nDIGITE A ORIGEM E O DESTINO QUE VOCE DESEJA SABER O CAMINHO MINIMO:\n");

                printf("\n\tORIGEM: ");
                scanf(" %d", &origem);

                printf("\n\tDESTINO: ");
                scanf(" %d", &destino);

                dijkstra(g, origem, destino, *tamEntrada);

                printf("\nDESEJA PROCURAR O CAMINHO MINIMO ENTRE MAIS VERTICES?\n");
                printf("1 - SIM\n");
                printf("0 - NAO\n");
                printf("DIGITE A OPCAO: ");
                scanf(" %d", &res);
            }while(res != 0);



            dijkstra(g, origem, destino, *tamEntrada);

            break;

        case 3:
            printf("DIGITE QUANTAS CIDADES HA NO TOTAL: ");

            scanf("%d", tamEntrada);

            g = newGrafo(*tamEntrada);

            menu(g->cidades, *tamEntrada);

            preenCheMatriz(g->matrizAdj, *tamEntrada, 2);//Atribui valores à matriz;

            do{
                printf("\nDIGITE A ORIGEM E O DESTINO QUE VOCE DESEJA SABER O CAMINHO MINIMO:\n");

                printf("\n\tORIGEM: ");
                scanf(" %d", &origem);

                printf("\n\tDESTINO: ");
                scanf(" %d", &destino);

                dijkstra(g, origem, destino, *tamEntrada);

                printf("\nDESEJA PROCURAR O CAMINHO MINIMO ENTRE MAIS VERTICES?\n");
                printf("1 - SIM\n");
                printf("0 - NAO\n");
                printf("DIGITE A OPCAO: ");
                scanf(" %d", &res);
            }while(res != 0);

            break;
    }
    return g;
}
