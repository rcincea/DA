
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>

// propios o los de las estructuras de datos de clase
using namespace std;
// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(vector<int> const& D, int K) {
	
	int parches = 1;
	int m = D[0]; // distancia desde el ultimo agujero
	for (int i = 1; i < D.size(); ++i) { // estamos en gi
		if (D[i] - m > K) {
			++parches;
			m = D[i];
		}
		
	}
	return parches;
	
}


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

	// leer los datos de la entrada
	int agujeros;
	cin >> agujeros;

	if (!std::cin)  // fin de la entrada
		return false;
	int l, agujero;
	vector<int> manguera;
	
	cin >> l;
	for (int i = 0; i < agujeros; ++i) {
		cin >> agujero;
		manguera.push_back(agujero);
	}
	cout << resolver(manguera, l) << "\n";

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
