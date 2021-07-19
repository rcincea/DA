
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "Matriz.h"
#include "EnterosInf.h"// propios o los de las estructuras de datos de clase

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
using namespace std;

vector<int> calcular_dianas(vector<int> const &v, int C, int &numDardos) {
	int n = v.size();
	vector<EntInf> m(C+1, Infinito);
	m[0] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = v[i - 1]; j <= C; ++j) {
			m[j] = min(m[j], m[j - v[i - 1]] + 1);
		}
	}
	vector<int> sol;
	if (m[0] != Infinito) {
		int i = n, j = C;
		while (j > 0 && i > 0) {
			if (v[i - 1] <= j && m[j] == m[j - v[i - 1]] + 1) {
				sol.push_back(v[i - 1]);
				j -= v[i-1];
				++numDardos;
			}
			else --i;
		}
		if (j != 0) numDardos = -1;
	}

	return sol;
}
// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	// leer los datos de la entrada
	int valorMeta, numSectoreS;
	cin >> valorMeta;
	if (!std::cin)  // fin de la entrada
		return false;
	cin >> numSectoreS;
	vector<int> sectores(numSectoreS);
	int vSector;
	for (int i = 0; i < numSectoreS; ++i){
		cin >> vSector;
		sectores[i] = vSector;
	}
	
	int numMinDardos = 0;
	vector<int> sol;
	sol = calcular_dianas(sectores, valorMeta, numMinDardos);
	if (numMinDardos == -1) cout << "IMPOSIBLE \n";
	else {
		cout << numMinDardos << ": ";
		for (int i = 0; i < sol.size(); ++i) {
			cout << sol[i] << " ";
		}
		cout << "\n";
	}
	// escribir sol

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
