
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include<algorithm>
#include "Matriz.h" 
#include "EnterosInf.h"

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...

using namespace std;
// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
int maxCamino(const Matriz<int> & tablero, int &indice) {
	vector<int> v1(tablero.numcols(), 0);
	vector<int> v2(tablero.numcols(), 0);
	bool v1aCambiar = true;
	for (int i = 0; i < tablero.numfils(); ++i) {

		for (int j = 0; j < tablero.numcols(); ++j) {
			if (i == 0) v1[j] = tablero[i][j];
		
			else {
				if (v1aCambiar) {
					if (j == 0) v1[j] = max(v2[j], v2[j + 1]) + tablero[i][j];
					else if (j == tablero.numcols() - 1) v1[j] = max(v2[j], v2[j - 1]) + tablero[i][j];
					else v1[j] = max(max(v2[j - 1], v2[j]), v2[j + 1]) + tablero[i][j];
				}

				else {
					if (j == 0) v2[j] = max(v1[j], v1[j + 1]) + tablero[i][j];
					else if (j == tablero.numcols() - 1) v2[j] = max(v1[j], v1[j - 1]) + tablero[i][j];
					else v2[j] = max(max(v1[j - 1], v1[j]), v1[j + 1]) + tablero[i][j];
				}
			}
		}
		if (v1aCambiar) {
			v1aCambiar = false;
		}
		else v1aCambiar = true;
	}
	int max = 0;
	for (int p = 0; p < v1.size(); ++p) {
		if (!v1aCambiar) {
			if (v1[p] > max) {
				max = v1[p];
				indice = p;
			}
		}
		else {
			if (v2[p] > max) {
				max = v2[p];
				indice = p;
			}
		}
	}
	return max;
}

bool resuelveCaso() {

	// leer los datos de la entrada
	int dimensionTablero;
	cin >> dimensionTablero;
	if (!std::cin)  // fin de la entrada
		return false;
	// escribir sol
	int valor;
	Matriz<int> tablero(dimensionTablero, dimensionTablero, 0);
	for (int i = 0; i < dimensionTablero; ++i) {
		for (int j = 0; j < dimensionTablero; ++j) {
			cin >> valor;
			tablero[i][j] = valor;
		}
	}
	int indice = 0;
	cout << maxCamino(tablero, indice) << " ";
	cout<< indice+1 << "\n";

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
