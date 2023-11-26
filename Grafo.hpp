/**************************************************************************
 * Encabezado de Grafo
 * Autor: Gerardo Rodríguez Hernández
 * Fecha: 09/11/2023
 * Descripcion:
 * El objetivo de esta actividad es crear las funcionalidades de un Grafo
 **************************************************************************/
#ifndef GRAFO_h
#define GRAFO_h
#include <list>
#include <vector>
#include <limits>

class MatrizAdyacencia{
    private:
    double **matriz;
    int *numVertices;

    //Constructor
    MatrizAdyacencia(int numVertices){
        this->numVertices = new int(numVertices);
        for(int i = 0; i < numVertices; i++){
            matriz[i] = new double[numVertices];
            for(int j = 0; j < numVertices; j++ ){
                if(i == j){
                    matriz[i][j] = 0;
                }
                else{
                    matriz[i][j] = std::numeric_limits<double>::infinity(); 
                }
            }
        }
    }

    //Destructor
    ~MatrizAdyacencia(){
        for(int i = 0; i < *this->numVertices; i++){
            delete (matriz[i]);
        }
    }

    //Define el valor del peso de una arista
    void setPeso(int origen, int destino, double peso){
        if(origen < *this->numVertices && destino < *this->numVertices){
            this->matriz[origen][destino] = peso;
        }
    }

    //Regresa el peso de una arista
    double getPeso(int origen, int destino){
        return this->matriz[origen][destino];
    }

    //Regresa el número de vértices de grafo
    int getNumVertices(){
        return *this->numVertices;
    }

    //Regresa la matris de adyacencias
    double** getMatriz(){
        return this->matriz;
    }
};

class Par{
    public:
        int *destino;
        double *peso;

        //Constructor
        Par(int destino, double peso);
        
        //Destructor
        ~Par();
};

class Vertice{
    private:
        int  *valor;
        bool *estado;  //Se utiliza para los recorridos, True si el nodo ya fue procesado o False si aún no
        bool *conjunto; //Para probar si el grafo es bipartita
         //Lista ligada de pares que contiene la lista de aristas donde el vértice es el origen
        std::list<Par> aristas; 

    public:
        //Constructor
        Vertice();

        //Destructor
        ~Vertice();

        //Regresa el valor del vértice
        int getValor();

        //Modifica el valor del vértice
        void setValor(int);
        
        //Agrega arista a la lista de pares del vértice
        void agregaArista(int destino, double peso);

        void setEstado(bool);

        bool getEstado(); 

        void setConjunto(bool);

        bool getConjunto();

         std::list<Par> getArista();

};

class Grafo{
    private:
        //Arreglo de Vértices que contiene la estructura del grafo 
        Vertice *vertices;
        int *numVertices;
        int *numAristas;
        //Matriz de adyacencias
        double **matriz;

    public:

        //Constructor
        Grafo();

        //Destructor
        ~Grafo();

        //Carga los vértices del grafo y los almacene en una Lista de Adjacencia de Aristas
        //a partir de la matriz de adyacencias proporcionada.
        void loadGraph(int numVertices, int numAristas, double **matrizAdjacencia);
        
        //Realiza búsqueda en profundidad e imprime 
        //los id de los vértices recorridos separados por comas 
        void dfs(int verticeInicial);

        //Realiza búsqueda en amplitud e imprime
        //los id de los vértices recorridos separados por comas
        void bfs(int verticeInicial);
    
        //Regresa true si el Grafo Dirigido Acíclico (DAG) es un árbol
        //Nota, el grafo proporcionado deberá ser un DAG.
        bool isTree();

        //Regresa true si el DAG proporcionado es un grafo Bipartita
        bool isBipartiteGraph(int numVertices, int numAristas, double **matrizAdjacencia);

        //Imprime la lista de vértices del (DAG) ordenados topológicamente separados por comas
        void topologicalSort(int numVertices, int numAristas, double **matrizAdjacencia);
};

#endif