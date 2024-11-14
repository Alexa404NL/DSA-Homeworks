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

 //O(1)
    Grafo(int n, bool d){
        adj = vector<vector<T> >(n, vector<T>(0, 0));
        dirigido = d;
    }

    Grafo(const Grafo<T>& otro) {
        adj = otro.adj;
        dirigido = otro.dirigido;
    }

    Grafo<T> operator=(const Grafo<T>& otro) {
        if (this != &otro) {
            adj = otro.adj;
            dirigido = otro.dirigido;
        }
        return *this;
    }

 //O(1)
    void add_edge(int u, int v) {
        adj[u].push_back(v);
        if (!dirigido) {
            adj[v].push_back(u);
        }
    }

// O(V + E) donde v es el número de nodos y e el de arcos
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

// complejidad O(u) para dirigidos y O(u+v) si es no dirigido
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

  // O(m) donde m es el número de arcos a agregarse
    void loadGraph(int n, int m) {
        if(n<=0 || m<=0){
           throw invalid_argument("Los números tienen que ser positivos y mayores a 0");
        }

        adj.resize(n);

        for (int i = 0; i < m; ++i) {
            int u, v;
            cout << "Ingresa el arco (u v, pensando que comienza indice 0): ";
            cin >> u >> v;

            if(u <0 || v < 0 || u>=n ||v>=n){
                throw invalid_argument("Los números tienen que ser positivos y dentro del rango");
            }
            adj[u].push_back(v);
            if (!dirigido) {
                adj[v].push_back(u);
            }
        }
    }

// complejidad O(V + E) donde v es el número de nodos y e el de arcos
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


// complejidad O(V + E) donde v es el número de nodos y e el de arcos
      void dfsRec(vector<bool> &visitados, int s){
          visitados[s] = true;
          cout << s << " ";

          for (int x : adj[s])
              if (visitados[x] == false)
                  dfsRec(visitados, x);
      }


      void dfs(int s){
          vector<bool> visitados(adj.size(), false);
          if (s<0 || s>adj.size()){
              throw invalid_argument("El nodo de inicio es inválido");
          }
          dfsRec( visitados, s);
      }
};




int main (){

    try {
        int testCase;

        cout << "Selecciona un caso de prueba (1-4): "
                "Para usar la función loadGraph es el caso 5" << endl;

        cin >> testCase;

        switch (testCase) {
            case 1: {
                cout << "Caso 1: grafo no dirigido DFS\n";
                Grafo<int> g(5, false);  // Grafo con 5 nodos, no dirigido
                g.add_edge(0, 1);
                g.add_edge(1, 2);
                g.add_edge(2, 3);
                g.add_edge(3, 4);
                g.print();

                g.delete_edge(3, 4);
                g.print();

                cout << "dfs desde 0\n";
                g.dfs(0);
                cout << endl;
                cout << "dfs desde 1\n";
                g.dfs(1);
                cout << endl;
                cout << "dfs desde 2\n";
                g.dfs(2);
                cout << endl;
                cout << "dfs desde 3\n";
                g.dfs(3);
                cout << endl;
                // Resultado esperado:
                // 0: 1
                // 1: 0 2
                // 2: 1
                // 3: 4
                // 4: 3
                //dfs desde 0 -> 0 1 2 3
                //dfs desde 1 -> 1 0 2 3
                //dfs desde 2 -> 2 1 0 3
                //dfs desde 3 -> 3 2 1 0
                break;
            }
            case 2: {
                cout << "Caso 2: grafo dirigido BFS\n";
                Grafo<int> g(4, true);  // Grafo con 4 nodos, dirigido
                g.add_edge(0, 1);
                g.add_edge(1, 2);
                g.add_edge(2, 3);
                g.print();

                cout << "bfs desde 0\n";
                g.bfs(0);
                cout << endl;
                cout << "bfs desde 1\n";
                g.bfs(1);
                cout << endl;
                cout << "bfs desde 2\n";
                g.bfs(2);
                cout << endl;
                cout << "bfs desde 3\n";
                g.bfs(3);
                cout << endl;

                // Resultado esperado antes de eliminar arista:
                // 0: 1
                // 1: 2
                // 2: 3
                // 3:

                //bfs desde 0 -> 0 1 2 3
                //bfs desde 1 -> 1 2 3
                //bfs desde 2 -> 2 3
                //bfs desde 3 -> 3
                break;
            }
            case 3: {
                cout << "Caso 3: grafo no dirigido BFS \n";
                Grafo<int> g(6, false), f(5,false);  // Grafo con 6 nodos, no dirigido
                g.add_edge(0, 1);
                g.add_edge(0, 2);
                g.add_edge(1, 3);
                g.add_edge(1, 4);
                g.add_edge(2, 4);
                g.add_edge(3, 5);
                g.print();
                f=g;
                g.delete_edge(3, 5);
                g.delete_edge(1, 0);
                g.delete_edge(1, 3);
                cout << "BFS desde el nodo 0 en el grafo editado: ";
                g.bfs(0);
                cout << endl;
                cout << "BFS desde el nodo 0 en el grafo no editado: ";
                f.bfs(0);
                cout << endl;

                // Resultado esperado:
                // 0: 1 2
                // 1: 0 3
                // 2: 0 4
                // 3: 1 5
                // 4: 2
                // 5: 3
                //
                // BFS desde el nodo 0 en no editado:
                // 0 1 2 3 4 5
                break;
            }
            case 4: {
                cout << "Caso 4: grafo dirigido DFS\n";
                Grafo<int> g(5, true);  // Grafo con 5 nodos, dirigido
                g.add_edge(0, 1);
                g.add_edge(0, 2);
                g.add_edge(1, 3);
                g.add_edge(2, 4);
                g.print();
                cout << "DFS desde el nodo 0: ";
                g.dfs(0);

                // Resultado esperado:
                // 0: 1 2
                // 1: 3
                // 2: 4
                // 3:
                // 4:
                //
                // DFS desde el nodo 0:
                // 0 1 3 2 4
                break;
            }
            case 5: {
                Grafo<int> g(6, true);
                int n, m, inico;
                cout << "¿Cuántos nodos se quieren?\n";
                cin>>n;
                cout << "¿Cuántos arcos se quieren?\n";
                cin>>m;
                g.loadGraph(n,m);
                g.print();

                cout << "¿desde donde se incia el recorrido\n";
                cin>>inico;

                cout << "BFS\n";
                g.bfs(inico);
                cout <<endl;
                cout << "DFS\n";
                g.dfs(inico);
                cout <<endl;

                break;
            }

            default:
                cout << "Caso no válido. Selecciona un caso entre 1 y 5.\n";
        }
    } catch (std::invalid_argument& e){
        cerr << e.what() << endl;
        return -1;
    }

    return 0;
}