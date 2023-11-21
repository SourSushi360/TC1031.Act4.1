/*  Grafo.cpp
    Autor: Jean Paul López Pándura

    Última modificación: 21/11/2023
    Este archivo define las funciones declaradas en Grafo.hpp
    Las clases que define son:
    - Par
    - Vertice
    -Grafo */
#include "Grafo.hpp"

// Par
Par::Par(int destino, double peso) {
    *this->destino = destino;
    *this->peso = peso;
}
Par::~Par() {
    delete this->destino;
    delete this->peso;
}

//Vertice
Vertice::Vertice() {
    this->valor = new int;
    this->estado = new bool;
    this->conjunto = new bool;
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
