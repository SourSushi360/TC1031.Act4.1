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
            if (matrizAdjacencia[i][j] != std::numeric_limits<double>::infinity()) {
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
                if (this->matriz[verticeActual.getValor()][i] != std::numeric_limits<double>::infinity()
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
                if (this->matriz[verticeActual.getValor()][i] != std::numeric_limits<double>::infinity()
                && !this->matriz[verticeActual.getEstado()][i]) {
                    cola.push(this->vertices[i]);
                }
            }
        }
    }
}
        //Regresa true si el Grafo Dirigido Acíclico (DAG) es un árbol
        //Nota, el grafo proporcionado deberá ser un DAG.
bool Grafo::isTree() {
    
}
        //Regresa true si el DAG proporcionado es un grafo Bipartita
bool Grafo::isBipartiteGraph(int numVertices, int numAristas, double **matrizAdjacencia) {
}
        //Imprime la lista de vértices del (DAG) ordenados topológicamente separados por comas
void Grafo::topologicalSort(int numVertices, int numAristas, double **matrizAdjacencia) {
}
