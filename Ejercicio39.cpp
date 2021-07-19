
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
#include "EnterosInf.h"
#include "Matriz.h"
// propios o los de las estructuras de datos de clase


using namespace std;

struct tesoro { int tiempo; int valor;};
double mochila_rec(vector<tesoro> const& obj, int i, int j,
    Matriz<double>& mochila) {
    if (mochila[i][j] != -1) // subproblema ya resuelto
    {   
       
        return mochila[i][j];
    }
    if (i == 0 || j == 0) mochila[i][j] = 0;
    else if (obj[i - 1].tiempo + obj[i - 1].tiempo * 2 > j)
        mochila[i][j] = mochila_rec(obj, i - 1, j, mochila);
    else {
        mochila[i][j] = max(mochila_rec(obj, i - 1, j, mochila),
            mochila_rec(obj, i - 1, j - (obj[i - 1].tiempo + obj[i - 1].tiempo * 2), mochila)
            + obj[i - 1].valor);

    }

    return mochila[i][j];
}

double mochila(vector<tesoro> const& objetos, int M, vector<bool>& sol, vector<tesoro> &tesoros) {
    int n = objetos.size();
    Matriz<double> mochila(n + 1, M + 1, -1);
    double valor = mochila_rec(objetos, n, M, mochila);
    // cálculo de los objetos
    int i = n, j = M;
    sol = vector<bool>(n, false);
    while (i > 0 && j > 0) {
        if (mochila[i][j] != mochila[i - 1][j]) {
            tesoro t;
            t.tiempo = objetos[i - 1].tiempo;
            t.valor = objetos[i - 1].valor;
            tesoros.push_back(t);
            sol[i - 1] = true; 
            j = j - objetos[i - 1].tiempo*3;           
        }
        --i;
    }
    return valor;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int t;
    cin >> t;
    if (!cin)
        return false;
    int n;
    cin >> n;
    vector<tesoro> v(n);

    for (int i = 0; i < n; ++i) {
        cin >> v[i].tiempo >> v[i].valor;
    }

    vector<bool> sol;
    vector<tesoro> solucion;
    double val = mochila(v, t, sol, solucion);
    cout << val << "\n";
    cout << solucion.size() << "\n";
    for (int i = solucion.size()-1; i >= 0; --i) {
        cout << solucion[i].tiempo << " " << solucion[i].valor << "\n";
    }
  
    
    cout << "---\n";
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
