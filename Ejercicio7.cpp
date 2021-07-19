
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "PriorityQueue.h" 
#include "Grafo.h"
// propios o los de las estructuras de datos de clase


using namespace std;

class CaminosDFS {
private:
    vector<bool> visit; // visit[v] = ¿hay camino de s a v?
    vector<int> nVisitas;
    vector<int> ant; // ant[v] = último vértice antes de llegar a v
    bool libre = true;
    int s; // vértice origen
    void dfs(Grafo const& G, int v) {
        visit[v] = true;
        for (int w : G.ady(v)) {
            nVisitas[w]++;
            if (nVisitas[w] > 1 && visit[w]) libre = false;
            if (!visit[w]) {
                ant[w] = v;
                dfs(G, w);
            }
        }
    }

public:
    CaminosDFS(Grafo const& G, int s) : visit(G.V(), false), nVisitas(G.V(), 0),
        ant(G.V()), s(s) {
        dfs(G, s);
    }
    // ¿hay camino del origen a v?
    bool hayCamino(int v) const {
        return visit[v];
    }
    int numCaminos(int v) const {
        return nVisitas[v];
    }
    using Camino = std::deque<int>; // para representar caminos
    // devuelve un camino desde el origen a v (debe existir)
    Camino camino() const {
        Camino cam;
        if (!hayCamino(v))
            throw std::domain_error("No existe camino");
        // recuperamos el camino retrocediendo
        for (int x = v; x != s; x = ant[x])
            cam.push_front(x);
        cam.push_front(s);
        return cam;
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
    Grafo g(n,m);
    g.ponArista();
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
