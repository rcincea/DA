
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>


#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase
using namespace std;
struct registro {
	int momento; // cuando le toca
	int id; // idnetificador (para desempatar)
	int periodo; // tiempo entre consultas
};

bool operator<(registro const &a, registro const &b) {
	return b.momento > a.momento || (a.momento == b.momento && b.id > a.id);
}


bool resuelveCaso() {
	int n;
	cin >> n;

	if (n == 0) return false;
	
	PriorityQueue<registro> cola;

	//leer registros
	for (int i = 0; i < n; ++i) {
		int id_us, periodo;
		cin >> id_us >> periodo;
		cola.push({ periodo,id_us, periodo });
	}
	int envios;
	cin >> envios;

	while (envios--) {
		auto e = cola.top(); // se consulta el mas prioritario de la cola
		cola.pop(); // se saca despues de consultarlo
		cout << e.id << "\n";
		e.momento += e.periodo; // se le suma al momento el periodo para tener el proximo momento en el que lo consultaremos pasado este determinado periodo
		cola.push(e); // coste O(log N) respecto al numero de elementos de la cola
	}

	cout << "---\n";
	return true;

	// escribir solución
	return true;
}
/*
 ___    _____  _______  _____
(  _`\ (  _  )(_____  )(  _  )
| ( (_)| ( ) |     /'/'| (_) |
| |___ | | | |   /'/'  |  _  |
| (_, )| (_) | /'/'___ | | | |
(____/'(_____)(_______)(_) (_)
*/

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
