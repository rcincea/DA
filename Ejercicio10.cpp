
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "PriorityQueue.h" 
#include "Grafo.h"
#include <deque>
// propios o los de las estructuras de datos de clase


using namespace std;

class CaminosDFS {
private:
    vector<bool> visit; // visit[v] = ¿hay camino de s a v?
    vector<int> ant; // ant[v] = último vértice antes de llegar a v
    bool libre = true;
    int s; // vértice origen
    void dfs(Grafo const& G, int v, int &verticesVisitados) {
        visit[v] = true;
        for (int w : G.ady(v)) {
            if (visit[w] && ant[v] != w) {
                libre = false;
            }
            else if (!visit[w]) {
                verticesVisitados++;
                ant[w] = v;
                dfs(G, w, verticesVisitados);
               
            }
        }
    }

public:
    CaminosDFS(Grafo const& G) : visit(G.V(), false),
        ant(G.V()) {
        int visitados = 1;
        dfs(G, 0, visitados);
        if (visitados < G.V()) libre = false;
    }

    bool esLibre() {
        return libre;
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int n, m;
    cin >> n;
    if (!cin)
        return false;
    cin >> m;
    Grafo g(n);
    int a, b;
    int v;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        if (i == 0) v = a;
        g.ponArista(a, b);
    }

    CaminosDFS camino(g);
    if (camino.esLibre()) {
        cout << "SI\n";
    }
    else cout << "NO\n";
    return true;
   
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
