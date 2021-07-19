
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "DigrafoValorado.h"
#include <algorithm>
#include <deque>
// propios o los de las estructuras de datos de clase


using namespace std;

template <typename Valor>
class Dijkstra {
public:
    Dijkstra(DigrafoValorado<Valor> const& g, int orig) : origen(orig),
        dist(g.V(), INF), ult(g.V()), pq(g.V()), caminos(0) {
        dist[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }
    bool hayCamino(int v) const { return dist[v] != INF; }
    Valor distancia(int v) const { return dist[v]; }
    Camino<Valor> camino(int v) const {
        Camino<Valor> cam;
        // recuperamos el camino retrocediendo
        AristaDirigida<Valor> a;
        for (a = ult[v]; a.desde() != origen; a = ult[a.desde()])
            cam.push_front(a);
        cam.push_front(a);
        return cam;
    }
private:
    const Valor INF = std::numeric_limits<Valor>::max();
    int origen;
    std::vector<Valor> dist;
    std::vector<AristaDirigida<Valor>> ult;
    int caminos;
    IndexPQ<Valor> pq;
    void relajar(AristaDirigida<Valor> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor(); ult[w] = a;
            pq.update(w, dist[w]);
        }
        else if (dist[w] == dist[v] + a.valor()) {

        }
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
    DigrafoValorado g(n);
    int a, b;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        g.ponArista(a - 1, b - 1);
    }

    OrdenTopologico validar(g);

    if (validar.esValid()) {
        vector<int> v = validar.orden();
        for (int i = 0; i < g.V(); ++i) {
            cout << v[i]+1 << " ";
        }
    }
    else {
        cout << "Imposible";
    }
    cout << "\n";
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
