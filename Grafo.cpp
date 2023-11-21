/*  Grafo.cpp
    Autor: Jean Paul López Pándura

    Última modificación: 21/11/2023
    Este archivo define las funciones declaradas en Grafo.hpp*/
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
