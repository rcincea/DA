
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
class MaximaCompConexa {
public:
    MaximaCompConexa(Grafo const& g) : visit(g.V(), false), maxim(0), tamGrupo(g.V(), 0), grupoDeUsuario(g.V(),0) {
        for (int v = 0; v < g.V(); ++v) {
          // se recorre una nueva componente conexa
            if (!visit[v]) {
                int tam = dfs(g, v);
                tamGrupo[nGrupo] = tam;
                ++nGrupo;
            }
 
        }
    }
    // tamaño máximo de una componente conexa
    int maximo() const {
        return maxim;
    }
    vector<int> tamanyoGrupo() {
        return tamGrupo;
    }
    vector<int> grupoDeUser() {
        return grupoDeUsuario;
    }
private:
    vector<bool> visit; // visit[v] = se ha visitado el vértice v?
    vector<int> tamGrupo;
    vector<int> grupoDeUsuario;
    int nGrupo = 0;
    int maxim; // tamaño de la componente mayor

    
    int dfs(Grafo const& g, int v) {
        visit[v] = true;
        int tam = 1;
        grupoDeUsuario[v] = nGrupo;
        for (int w : g.ady(v)) {
            if (!visit[w]) {
                grupoDeUsuario[w] = nGrupo;
                tam += dfs(g, w);
            }
             
        }
        return tam;
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
    vector<int> elems(n);
    int a;
    for (int i = 0; i < m; ++i) {
        cin >> a;
        for (int j = 0; j < a; ++j) {
            cin >> elems[j];  
        }
        for (int j = 1; j< a; ++j) {
            g.ponArista(elems[0]-1, elems[j]-1);
        }
    }

    MaximaCompConexa camino(g);

    vector<int> vec = camino.tamanyoGrupo();
    vector<int> vec2 = camino.grupoDeUser();
    for (int i = 0; i < vec2.size(); ++i) {
        cout << vec[vec2[i]] << " ";
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
