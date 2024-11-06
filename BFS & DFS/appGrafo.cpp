//
// Created by Alexa Nohemi Lara Carvajal on 05/11/24.
//

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

template <class T> class Grafo {
    vector<vector<T> > adj;
    bool dirigido;

public:
    Grafo(int n, bool d){
        adj = vector<vector<T> >(n, vector<T>(0, 0));
        dirigido = d;
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        if (!dirigido) {
            adj[v].push_back(u);
        }
    }

    void print() {
        for (int i = 0; i < adj.size(); i++) {
            cout << i << ": ";
            for (int j : adj[i]) {
                cout << j << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void delete_edge(int u, int v){
        for (int i = 0; i < adj[u].size(); i++) {
            if (adj[u][i] == v) {
                adj[u].erase(adj[u].begin() + i);
                break;
            }
        }

        if (!dirigido) {
            for (int i = 0; i < adj[v].size(); i++) {
                if (adj[v][i] == u) {
                    adj[v].erase(adj[v].begin() + i);
                    break;
                }
            }
        }
    }

    void loadGraph(int n, int m) {
        if(n <0 || m < 0){
           throw invalid_argument("Los números tienen que ser positivos");
        }

        adj.resize(n);

        for (int i = 0; i < m; ++i) {
            int u, v;
            cout << "Ingresa el arco (u v): ";
            cin >> u >> v;

            adj[u].push_back(v);
            if (!dirigido) {
                adj[v].push_back(u);
            }
        }
    }

  void bfs(int inicio){
        vector<bool> visited(adj.size(), false);

        queue<int> q;

        if (inicio<0 || inicio>adj.size()){
            throw invalid_argument("El nodo de inicio es inválido");
        }

        q.push(inicio);

        visited[inicio] = true;

        int vis;
        while (!q.empty()) {
            
            vis = q.front();
            cout << vis << " ";
            q.pop();

            for (int x : adj[vis]) {
                if (!visited[x]) {
                    visited[x] = true;
                    q.push(x);
                }
            }
        }
    }

      void dfsRec(vector<bool> &visitados, int s){
          visitados[s] = true;
          cout << s << " ";

          for (int i = 0; i < adj[s].size(); i++)
              if (adj[s][i] == 1 && visitados[i] == false)
                  dfsRec(visitados, i);
      }


      void dfs(int s){
          vector<bool> visitados(adj.size(), false);
          dfsRec( visitados, s);
      }
};




int main (){

    try {
        int n = 8;
        // Crear un grafo con 4 vertices
        Grafo<int> g(n, false);
        Grafo<int> f(n, true);


        g.add_edge(0, 3);
        g.add_edge(3, 7);
        g.add_edge(5, 7);
        g.add_edge(7, 6);
        g.add_edge(5, 1);
        g.add_edge(1, 2);
        g.add_edge(6, 4);

        // Visualizar el grafo
        g.print();

        g.delete_edge(2, 1);
        g.delete_edge(6, 4);
        g.print();

      //  f.print();
      //  f.loadGraph(5,6);
      //  f.print();

        cout << endl << "BFS Recorrido desde vertice 0 como origen." << endl;
        g.bfs(0);

        cout << endl << "DFS Recorrido desde vertice 0 como origen." << endl;
        g.dfs(0);

    }

    catch (std::invalid_argument& e){
        cerr << e.what() << endl;
        return -1;
    }

    return 0;
}