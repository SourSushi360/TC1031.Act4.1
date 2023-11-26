#include "Grafo.hpp"
#include <iostream>

int main() {
    // Crear un grafo de ejemplo
    int numVertices = 6;
    int numAristas = 7;

    double** matrizAdjacencia = new double*[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        matrizAdjacencia[i] = new double[numVertices];
        for (int j = 0; j < numVertices; ++j) {
            matrizAdjacencia[i][j] = std::numeric_limits<double>::infinity();
        }
    }

    matrizAdjacencia[0][1] = 1.0;
    matrizAdjacencia[0][2] = 1.0;
    matrizAdjacencia[1][3] = 1.0;
    matrizAdjacencia[2][3] = 1.0;
    matrizAdjacencia[3][4] = 1.0;
    matrizAdjacencia[3][5] = 1.0;
    matrizAdjacencia[4][5] = 1.0;

    // Crear el objeto Grafo
    Grafo miGrafo;
    miGrafo.loadGraph(numVertices, numAristas, matrizAdjacencia);

    // Ejemplo de uso de funciones
    std::cout << "DFS: ";
    miGrafo.dfs(0);
    std::cout << std::endl;

    std::cout << "BFS: ";
    miGrafo.bfs(0);
    std::cout << std::endl;

    std::cout << "Is Tree: " << std::boolalpha << miGrafo.isTree() << std::endl;

    std::cout << "Is Bipartite: " << std::boolalpha << miGrafo.isBipartiteGraph(numVertices, numAristas, matrizAdjacencia) << std::endl;

    std::cout << "Topological Sort: ";
    miGrafo.topologicalSort(numVertices, numAristas, matrizAdjacencia);

    // Liberar memoria
    for (int i = 0; i < numVertices; ++i) {
        delete[] matrizAdjacencia[i];
    }
    delete[] matrizAdjacencia;

    return 0;
}