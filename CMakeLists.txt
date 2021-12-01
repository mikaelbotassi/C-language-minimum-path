cmake_minimum_required(VERSION 3.20)
project(ProjetoDijkstra C)

set(CMAKE_C_STANDARD 99)

add_executable(ProjetoDijkstra main/main.c main/lib/grafo/Grafo.c main/lib/cidade/Cidade.c
        main/services/geradorArquivo/GeradorArquivo.c main/services/controleEntradaSaida/ControleArquivo.c
        main/services/controler/Controler.c)
