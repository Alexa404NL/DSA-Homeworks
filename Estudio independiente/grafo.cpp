//
// Created by Alexa Nohemi Lara Carvajal on 04/11/24.
//
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

template <class T> class Graph {
    // Matriz de adyacencia.
    vector<vector<T> > adj_matrix;
    bool dirigido;

public:
    Graph(int n, bool d){
        adj_matrix = vector<vector<T> >(n, vector<T>(n, 0));
        dirigido = d;
    }

    void add_edge(int u, int v){
        adj_matrix[u][v] = 1;
        if (!dirigido) {
            adj_matrix[v][u] = 1;
        }
    }

    void add_edge_ponderado(int u, int v, int val){
        adj_matrix[u][v] = val;
        if (!dirigido) {
            adj_matrix[v][u] = val;
        }
    }

    void delete_edge(int u, int v){
        adj_matrix[u][v] = 0;
        if (!dirigido) {
            adj_matrix[v][u] = 0;
        }
    }

    // Función para visualizar la matriz de adyacencia del grafo.
    void print(){
        // Obtener el número de vértices.
        cout << "Matriz de adyacencia del grafo: " << endl;
        int n = adj_matrix.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << adj_matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Función para implementar recorrido en anchura (BFS)
    void bfs(int inicio){
        // utilizamos un arreglo para saber si el nodo o vértice  ha sido
        // visitado o no.
        // Se inicializa en false (no visitado)
        vector<bool> visited(adj_matrix.size(), false);

        // cola implementada con un vector.
        vector<int> q;
        q.push_back(inicio);

        // Se marca el nodo origen como visitado
        visited[inicio] = true;

        int vis; // variable auxiliar que almacena el valor en el frente de la cola.
        while (!q.empty()) { // si la cola no está vacía
            vis = q[0]; // extraigo valor en el frente (indice 0 de la cola)

            // Procesamiento.. en este caso se visualiza la info.
            cout << vis << " "; //
            q.erase(q.begin()); // borro elemento extraido

            // Para todos los vértices adyacentes del vertice siendo procesado
            for (int i = 0; i < adj_matrix[vis].size(); i++) { // cantidad de elementos de una fila de la matriz.
                if (adj_matrix[vis][i] == 1 && (!visited[i])) { // si hay arco y no se visitó el destino

                    // lo inserto en la cola.
                    q.push_back(i);

                    // Lo marco como visitado
                    visited[i] = true;
                }
            }
        }
    }

// Función recursiva para recorrido en profundidad
    void dfsRec(vector<bool> &visitados, int s){

        visitados[s] = true;

        // Procesar el vértice actual.
        cout << s << " ";

        // se visitan de forma recursiva todos los
        // vertices adyacentes que no
        // han sido visitados
        for (int i = 0; i < adj_matrix[s].size(); i++)
            if (adj_matrix[s][i] == 1 && visitados[i] == false)
                dfsRec(visitados, i);
    }

// Función DFS que inicializa el arreglo de visitados y llama a la
// función recursiva que recorre el Grafo.
    void dfs(int s){
        vector<bool> visitados(adj_matrix.size(), false);
        dfsRec( visitados, s);
    }

// Función que realiza el ordenamiento topologico basada en DFS
    void topologicalSortRec(int v, vector<bool>& visitados, stack<int>& pila){
        // Marcar el nodo como visitado
        visitados[v] = true;

        // Llamada recursiva a los nodos adyacentes
        for (int i = 0; i < adj_matrix[v].size(); i++) {
            if (adj_matrix[v][i] == 1 && visitados[i]== false )
                topologicalSortRec(i, visitados, pila);
        }

        // Insertar en la pila el nodo actual.
        pila.push(v);
    }

// Funcion que realiza el ordenamiento topológico
    void topologicalSort(int V){
        stack<int> pila; // Pila para almacenar
        vector<bool> visitados(adj_matrix.size(), false);

        // Llamar a la función recursiva que construye la pila
        // el ordenamiento recorre todos los vértices, uno x uno.

        for (int i = 0; i < adj_matrix[V].size(); i++) {
            if (visitados[i]== false)
                topologicalSortRec(i, visitados, pila);
        }

        // Procesar la pila. En este caso se visualiza
        while (!pila.empty()) {
            cout << pila.top() << " ";
            pila.pop();
        }
    }


};


int main(){
    // Número de vértices
    int n = 5;
    // Crear un grafo con 4 vertices
    Graph<int> g(n,true);

    // AAdicionando los arcos a los vértices (ejemplo)

    g.add_edge(1, 3);
    g.add_edge(2, 3);
    g.add_edge(4, 2);

    g.add_edge(3, 2);

    // Visualizar el grafo
    g.print();

    g.delete_edge(2, 3);
    g.delete_edge(1, 3);
    g.print();
    cout << endl << "Recorrido desde vertice 0 como origen." << endl;
    g.bfs(0);
    cout << endl << "Recorrido desde vertice 1 como origen." << endl;
    g.bfs(1);
    cout << endl << "Recorrido DFS desde vertice 0 como origen." << endl;
    g.dfs(0);
    cout << endl << "Recorrido DFS desde vertice 1 como origen." << endl;
    g.dfs(1);
    cout << endl << "ordenamiento topologico desde vertice 0 como origen." << endl;
    g.topologicalSort(0);
    cout << endl << "ordenamiento topologico desde vertice 1 como origen." << endl;
    g.topologicalSort(1);
    return 0;
}