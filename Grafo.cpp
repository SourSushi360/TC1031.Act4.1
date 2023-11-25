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
        this->matriz[i] = new double[numVertices];
        for (int j = 0; j < numVertices; ++j) {
            this->matriz[i][j] = matrizAdjacencia[i][j];
        }
    }
}
        //Realiza búsqueda en profundidad e imprime 
        //los id de los vértices recorridos separados por comas
void Grafo::dfs(int verticeInicial) {
}
        //Realiza búsqueda en amplitud e imprime
        //los id de los vértices recorridos separados por comas
void Grafo::bfs(int verticeInicial) {
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
