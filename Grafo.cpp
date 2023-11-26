/*  Grafo.cpp
    Autor: Jean Paul López Pándura

    Última modificación: 21/11/2023
    Este archivo define las funciones declaradas en Grafo.hpp
    Las clases que define son:
    - Par
    - Vertice
    -Grafo */
#include "Grafo.hpp"
#include <iostream>
#include <stack>
#include <queue>

// Par
Par::Par(int destino, double peso) {
    *this->destino = destino;
    *this->peso = peso;
}
Par::~Par() {
    delete this->destino;
    delete this->peso;
}

// Vertice
Vertice::Vertice() {
    this->valor = new int;
    this->estado = new bool(false);
    this->conjunto = new bool(false);
}
Vertice::~Vertice() {
    delete valor;
    delete estado;
    delete conjunto;
}
    // getters
int Vertice::getValor() {
    return *this->valor;
}
bool Vertice::getEstado() {
    return *this->estado;
}
bool Vertice::getConjunto() {
    return this->conjunto;
}
 std::list<Par> Vertice::getArista(){
    return aristas;
}
    // setters
void Vertice::setValor(int valor) {
    *this->valor = valor;
}
void Vertice::setEstado(bool estado) {
    *this->estado = estado;
}
void Vertice::setConjunto(bool conjunto) {
    *this->conjunto = conjunto;
}
    // métodos
void Vertice::agregaArista(int destino, double peso) {
    Par par(destino,peso);
    this->aristas.push_back(par);
}

// Grafo
Grafo::Grafo() {
    this->vertices = nullptr;
    this->numVertices = new int;
    this->numAristas = new int;
    *this->matriz = nullptr;
}
Grafo::~Grafo() {
    delete this->numVertices;
    delete this->numAristas;
    delete[] vertices;
    for (int i = 0; i < *numVertices; ++i) {
        delete[] matriz[i];
    }
    delete[] matriz;
}
    // métodos
        //Carga los vértices del grafo y los almacene en una Lista de Adjacencia de Aristas
        //a partir de la matriz de adyacencias proporcionada.
void Grafo::loadGraph(int numVertices, int numAristas, double **matrizAdjacencia) {   
    *this->numVertices = numVertices;
    *this->numAristas = numAristas;

    this->vertices = new Vertice[numVertices];
    this->matriz = new double*[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        this->vertices[i].setValor(i);
        this->matriz[i] = new double[numVertices];
        for (int j = 0; j < numVertices; ++j) {
            this->matriz[i][j] = matrizAdjacencia[i][j];
            if (matrizAdjacencia[i][j] == 0) {
              this->vertices[i].agregaArista(j, matrizAdjacencia[i][j]);
            }
        }
    }
}
        //Realiza búsqueda en profundidad e imprime 
        //los id de los vértices recorridos separados por comas
void Grafo::dfs(int verticeInicial) {
    for (int i = 0;i < *this->numVertices;i++) {
        this->vertices[i].setEstado(false);
    }

    std::stack<Vertice> pila;
    pila.push(vertices[verticeInicial]);
    Vertice verticeActual;
    // Iterar hasta que la pila esté vacía
    while (!pila.empty()) {
        verticeActual = pila.top();
        pila.pop();
        // Si el vértice no ha sido visitado marcar el vértice como visitado e imprimir su ID
        if (!verticeActual.getEstado()) {
            verticeActual.setEstado(true);
            std::cout << verticeActual.getValor() << ", ";

            // Agregar los vértices adyacentes no visitados a la pila
            for (int i = 0;i < *this->numVertices;i++) {
                if (this->matriz[verticeActual.getValor()][i] == 0
                && !this->matriz[verticeActual.getEstado()][i]) {
                    pila.push(this->vertices[i]);
                }
            }
        }
    }
}
        //Realiza búsqueda en amplitud e imprime
        //los id de los vértices recorridos separados por comas
void Grafo::bfs(int verticeInicial) {
    for (int i = 0;i < *this->numVertices;i++) {
        this->vertices[i].setEstado(false);
    }

    // Utilizar una cola para la búsqueda en amplitud
    std::queue<Vertice> cola;
    cola.push(this->vertices[verticeInicial]);
    Vertice verticeActual;
    // Iterar hasta que la pila esté vacía
    while (!cola.empty()) {
        verticeActual = cola.front();
        cola.pop();
        // Si el vértice no ha sido visitado marcar el vértice como visitado e imprimir su ID
        if (!verticeActual.getEstado()) {
            verticeActual.setEstado(true);
            std::cout << verticeActual.getValor() << ", ";

            // Agregar los vértices adyacentes no visitados a la pila
            for (int i = 0;i < *this->numVertices;i++) {
                if (this->matriz[verticeActual.getValor()][i] == 0
                && !this->matriz[verticeActual.getEstado()][i]) {
                    cola.push(this->vertices[i]);
                }
            }
        }
    }
}
        //Regresa true si el Grafo Dirigido Acíclico (DAG) es un árbol
        //Nota, el grafo proporcionado deberá ser un DAG.
bool esCicloEnDFS(Vertice *vertices,int vertice, bool visitado[], bool pilaRecursion[]) {
    visitado[vertice] = true;
    pilaRecursion[vertice] = true;

    for (auto const& par : vertices[vertice].getArista()) {
        int destino = *par.destino;
        if (!visitado[destino]) {
            if (esCicloEnDFS(vertices,destino, visitado, pilaRecursion)) {
                return true;
            }
        } else if (pilaRecursion[destino]) {
            return true;
        }
    }

    pilaRecursion[vertice] = false;
    return false;
}
bool Grafo::isTree() {
    // Marcar todos los vértices como no visitados
    bool *visitado = new bool[*this->numVertices];
    for (int i = 0; i < *this->numVertices; i++) {
        visitado[i] = false;
    }

    // Marcar todos los vértices en la pila de recurrencia como no visitados
    bool *pilaRecursion = new bool[*this->numVertices];
    for (int i = 0; i < *this->numVertices; i++) {
        pilaRecursion[i] = false;
    }

    // Verificar si hay un ciclo en cualquier punto del grafo
    for (int i = 0; i < *this->numVertices; i++) {
        if (!visitado[i] && esCicloEnDFS(this->vertices,i, visitado, pilaRecursion)) {
            delete[] visitado;
            delete[] pilaRecursion;
            return false;  // Hay un ciclo, no es un árbol
        }
    }

    // Verificar si todos los vértices están conectados
    for (int i = 0; i < *this->numVertices; i++) {
        if (!visitado[i]) {
            delete[] visitado;
            delete[] pilaRecursion;
            return false;  // No es un árbol, no todos los vértices están conectados
        }
    }

    delete[] visitado;
    delete[] pilaRecursion;
    return true;  // Es un árbol
}


        //Regresa true si el DAG proporcionado es un grafo Bipartita
bool Grafo::isBipartiteGraph(int numVertices, int numAristas, double **matrizAdjacencia) {
    // Crear un array para almacenar el color de cada vértice (0 y 1 representan dos colores diferentes)
    int *colores = new int[numVertices];
    for (int i = 0; i < numVertices; i++) {
        colores[i] = -1;  // Inicializar todos los colores como no asignados
    }

    // Utilizar una cola para el recorrido BFS
    std::queue<int> cola;

    // Verificar la bipartición para cada componente conexa del grafo
    for (int i = 0; i < numVertices; i++) {
        if (colores[i] == -1) {
            // Si el vértice no está coloreado, asignar un color e iniciar BFS
            colores[i] = 0;
            cola.push(i);

            while (!cola.empty()) {
                int verticeActual = cola.front();
                cola.pop();

                for (int j = 0; j < numVertices; j++) {
                    if (matrizAdjacencia[verticeActual][j] != 0) {
                        // Si hay una arista entre los vértices y el vértice adyacente no está coloreado
                        if (colores[j] == -1) {
                            // Asignar un color diferente al vértice adyacente y encolarlo
                            colores[j] = 1 - colores[verticeActual];
                            cola.push(j);
                        } else if (colores[j] == colores[verticeActual]) {
                            // Si el vértice adyacente tiene el mismo color, el grafo no es bipartito
                            delete[] colores;
                            return false;
                        }
                    }
                }
            }
        }
    }

    // Si se recorrieron todos los vértices y no se encontraron conflictos de colores, el grafo es bipartito
    delete[] colores;
    return true;
}
        //Imprime la lista de vértices del (DAG) ordenados topológicamente separados por comas
// Función auxiliar para DFS utilizada en la ordenación topológica
void topologicalSortDFS(Vertice *vertices,int vertice, bool visitado[], std::stack<int>& pila) {
    visitado[vertice] = true;

    for (auto const& par : vertices[vertice].getArista()) {
        int destino = *par.destino;
        if (!visitado[destino]) {
            topologicalSortDFS(vertices,destino, visitado, pila);
        }
    }

    // Después de procesar todos los vértices adyacentes, agregar el vértice actual a la pila
    pila.push(vertice);
}
void Grafo::topologicalSort(int numVertices, int numAristas, double **matrizAdjacencia) {
    // Crear un array para almacenar el estado de cada vértice (false si no ha sido visitado, true si ha sido visitado)
    bool *visitado = new bool[numVertices];
    for (int i = 0; i < numVertices; i++) {
        visitado[i] = false;
    }

    // Utilizar una pila para almacenar los vértices ordenados topológicamente
    std::stack<int> pila;

    // Realizar el recorrido DFS y almacenar los vértices en la pila
    for (int i = 0; i < numVertices; i++) {
        if (!visitado[i]) {
            topologicalSortDFS(this->vertices,i, visitado, pila);
        }
    }

    // Imprimir la lista de vértices ordenados topológicamente separados por comas
    while (!pila.empty()) {
        std::cout << pila.top();
        pila.pop();
        if (!pila.empty()) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;

    // Liberar memoria
    delete[] visitado;
}

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
