
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include<string>
#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase


using namespace std;

class Camiones {
public:
	Camiones(GrafoValorado<int> const &G,int inicio, int fin, int umbral) :visit(G.V(), false) {
		dfs(G, inicio, umbral);
		if (visit[fin] == true) posible = true;
		else posible = false;
	}
	bool esPosible() {
		return posible;
	}
private:
	vector<bool> visit;
	bool posible;
	void dfs(GrafoValorado<int> const &G, int v, int umbral) {
		visit[v] = true;
		for (auto a : G.ady(v)) {
			if (a.valor() >= umbral) {
				int w = a.otro(v);
				if (!visit[w])
					dfs(G, w, umbral);
			}
		}
	}
};



bool resuelveCaso() {
	int n, m;
	cin >> n >> m; // número de intersecciones y numero calles
	if (!cin) return false;

	GrafoValorado<int> grafo(n);
	int u, v, valor;
	for (int i = 0; i < m; ++i) {
		cin >> u >> v >> valor;
		grafo.ponArista({ u-1,v-1,valor });
	}

	int k;
	cin >> k;
	int v1, v2, anchura;
	for (int j = 0; j < k; ++j) {
		cin >> v1 >> v2 >> anchura;
		Camiones c(grafo, v1-1, v2-1, anchura);
		if (c.esPosible()) cout << "SI\n";
		else cout << "NO\n";
	}
	
	
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
