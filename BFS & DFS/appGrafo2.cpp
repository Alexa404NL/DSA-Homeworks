//
// Created by Alexa Nohemi Lara Carvajal on 12/11/24.
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

        if(m>n-1){
            throw invalid_argument("No puede haber más arcos que nodos");
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

    //complejidad O(V+E) donde v es los nodos y e los arcos
    bool ciclical(int V){
        vector<int> inDegree(V, 0);

        queue<int> q;

        int visited = 0;
        for (int u = 0; u < V; u++) {
            for (int i : adj[u]) {
                inDegree[i]++;
            }
        }

        for (int u = 0; u < V; u++) {
            if (inDegree[u] == 0) {
                q.push(u);
            }
        }

        // BFS
        while (!q.empty()) {
            int i = q.front();
            q.pop();
            visited++;

            for (int v : adj[i]) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }

        return visited != V;
    }

    // O(V + E) donde v es el número de nodos y e el de arcos
    bool bfs(int inicio){
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
            q.pop();

            for (int x : adj[vis]) {
                if (!visited[x]) {
                    visited[x] = true;
                    q.push(x);
                }
            }
        }

        for (bool x : visited){
            if (x==false){
                return false;
            } else return true;
        }
    }

    //O(1) porque solo son ifs
    bool isTree (int n, int m){
        if(n<=0 || m<=0){
            throw invalid_argument("Los números tienen que ser positivos y mayores a 0");
        }

        bool cond1=true, cond2=true;

        if(m!=n-1){
           return false;
        }

        //revisar si es dirigida
        if (!dirigido){
            int n_= adj.size();
            cond2= ciclical(n_);
            cond1= bfs(0);
            return (cond1 && cond2)? true: false;
        }
    }

    //O(V + E) donde v es el número de nodos y e el de arcos
    vector<int> topologicalSort(int V){
        vector<int> inDegree(V, 0);
        queue<int> q;

        int visited = 0;

        for (int u = 0; u < V; u++) {
            for (int v : adj[u]) {
                inDegree[v]++;
            }
        }

        for (int u = 0; u < V; u++) {
            if (inDegree[u] == 0) {
                q.push(u);
            }
        }

        // BFS
        vector<int> result;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            result.push_back(node);

            for (auto it : adj[node]) {
                inDegree[it]--;

                if (inDegree[it] == 0)
                    q.push(it);
            }
        }

        if (result.size() != V) {
            return vector<int>();
        }

        return result;
    }

    //O(V + E) donde v es el número de nodos y e el de arcos
    bool isBipartite(int V) {
        vector<int> color(V, -1);
        queue<int> q;

        for(int i = 0; i < V; i++) {
            if(color[i] == -1) {
                color[i] = 0;
                q.push(i);

                //BFS
                while(!q.empty()) {
                    int u = q.front();
                    q.pop();

                    for(int &v : adj[u]) {
                        if(color[v] == -1) {
                            color[v] = 1 - color[u];
                            q.push(v);
                        }

                        else if(color[v] == color[u]) {
                            return false;
                        }
                    }
                }
            }
        }

        return true;
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
                cout << "Caso 1: DAG simple sin ciclos \n";
                /* No es un árbol, su orden topológico es: [0, 1, 2, 3] y es bipartito porque
                 * es una línea recta con un número par de nodos
                 * */

                Grafo<int> g(4,true);

                g.add_edge(0, 1);
                g.add_edge(1, 2);
                g.add_edge(2, 3);
               cout<< "is a tree? ";
               cout<< (g.isTree(4,3) ? "yes":"no") << endl;
               cout<< "topological sort: ";
               vector<int>tp = g.topologicalSort(4);

               for (int x:tp){
                   cout << x << " ";
               }
               cout << endl;
               cout << "is bipartite? " << (g.isBipartite(4) ? "yes" : "no")<< endl;
               break;
            }
            case 2: {
                cout << "Caso 2: árbol bipartito no dirigido\n";
                /* Es un árbol, su orden topológico es: [] porque no es dirigido y es bipartito */
                Grafo<int> g(5,false);

                g.add_edge(0, 1);
                g.add_edge(0, 2);
                g.add_edge(1, 3);
                g.add_edge(1, 4);
                cout<< "is a tree? ";
                cout<< (g.isTree(5,4) ? "yes":"no") << endl;
                cout<< "topological sort: ";
                vector<int>tp = g.topologicalSort(5);

                if (tp.empty()){
                    cout << "vacio";
                }
                for (int x:tp){
                    cout << x << " ";
                }
                cout << endl;
                cout << "is bipartite? " << (g.isBipartite(4) ? "yes" : "no")<< endl;
                break;
            }
            case 3: {
                cout << "Caso 3: grafo cíclico \n";
                /* No es un árbol, su orden topológico es: [] porque es cíclico el grafo y no es bipartito */
                Grafo<int> g(3,true);

                g.add_edge(0, 1);
                g.add_edge(1, 2);
                g.add_edge(2, 0);

                cout<< "is a tree? ";
                cout<< (g.isTree(3,2) ? "yes":"no") << endl;
                cout<< "topological sort: ";
                vector<int>tp = g.topologicalSort(3);

                if (tp.empty()){
                    cout << "vacio";
                }
                for (int x:tp){
                    cout << x << " ";
                }
                cout << endl;
                cout << "is bipartite? " << (g.isBipartite(3) ? "yes" : "no")<< endl;
                break;
            }
            case 4: {
                cout << "Caso 4: grafo bipartito dirigido\n";
                /* no es un árbol, pero es bipartito y hay varios recorridos topológicos válidos
                 * ejem: [0, 1, 2, 3], [0, 1, 3, 2], etc.
                * */
                Grafo<int> g(4,true);

                g.add_edge(0, 2);
                g.add_edge(0, 3);
                g.add_edge(1, 3);
                g.add_edge(1, 2);
                cout<< "is a tree? ";
                cout<< (g.isTree(4,3) ? "yes":"no") << endl;
                cout<< "topological sort: ";
                vector<int>tp = g.topologicalSort(4);

                for (int x:tp){
                    cout << x << " ";
                }
                cout << endl;
                cout << "is bipartite? " << (g.isBipartite(4) ? "yes" : "no")<< endl;
                break;
            }
            case 5: {
                Grafo<int> g(6, true);
                int n, m;
                cout << "¿Cuántos nodos se quieren?\n";
                cin>>n;
                cout << "¿Cuántos arcos se quieren?\n";
                cin>>m;
                g.loadGraph(n,m);
                g.print();

                cout<< "is a tree? ";
                cout<< (g.isTree(n,m) ? "yes":"no") << endl;
                cout<< "topological sort: ";
                vector<int>tp = g.topologicalSort(n);

                for (int x:tp){
                    cout << x << " ";
                }
                cout << endl;
                cout << "is bipartite? " << (g.isBipartite(n) ? "yes" : "no")<< endl;
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