#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <climits> 

using namespace std;

// Costos personalizados para cada operación
int costoInsercion(char b) { return 1; }
int costoEliminacion(char a) { return 1; }
int costoSustitucion(char a, char b) { return (a == b) ? 0 : 2; }
int costoTransposicion(char a, char b) { return 1; }

// Función recursiva con memoización para calcular la distancia de edición
int distanciaEdicion(string &s1, string &s2, int m, int n, vector<vector<int>> &dp) {
    // Caso base: Si una de las cadenas está vacía
    if (m == 0) return n * costoInsercion(' ');  // Insertar todos los caracteres de s2
    if (n == 0) return m * costoEliminacion(' '); // Eliminar todos los caracteres de s1

    // Si ya se ha calculado este subproblema, retornamos el valor almacenado
    if (dp[m][n] != -1) return dp[m][n];

    // Si los caracteres actuales coinciden, no hay costo de sustitución
    if (s1[m - 1] == s2[n - 1]) {
        dp[m][n] = distanciaEdicion(s1, s2, m - 1, n - 1, dp);
    } else {
        // Si los caracteres son diferentes, calcular los costos de cada operación
        int costoSust = costoSustitucion(s1[m - 1], s2[n - 1]) + distanciaEdicion(s1, s2, m - 1, n - 1, dp);
        int costoIns = costoInsercion(s2[n - 1]) + distanciaEdicion(s1, s2, m, n - 1, dp);
        int costoElim = costoEliminacion(s1[m - 1]) + distanciaEdicion(s1, s2, m - 1, n, dp);

        // Verificar si es posible realizar una transposición
        int costoTrans = INT_MAX;
        if (m > 1 && n > 1 && s1[m - 1] == s2[n - 2] && s1[m - 2] == s2[n - 1]) {
            costoTrans = costoTransposicion(s1[m - 1], s1[m - 2]) + distanciaEdicion(s1, s2, m - 2, n - 2, dp);
        }

        // Guardar el resultado mínimo en la tabla dp
        dp[m][n] = min({costoSust, costoIns, costoElim, costoTrans});
    }

    return dp[m][n];
}

int main() {
    vector<pair<string, string>> test_cases = {
        {"intention", "execution"},
        {"eabcd", "eacbd"},
        {"", "pan"},
        {"steam", "engine"},
        {"assassin", "asinine"},
        {"agria", "agraria"}
    };

    for (const auto &test_case : test_cases) {
        string s1 = test_case.first;
        string s2 = test_case.second;
        int m = s1.size();
        int n = s2.size();

        // Inicializar la tabla dp con -1 para indicar que no se han calculado los subproblemas
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));

        int costoTotal = distanciaEdicion(s1, s2, m, n, dp);
        cout << "Distancia de edición entre \"" << s1 << "\" y \"" << s2 << "\": " << costoTotal << endl;
    }

    return 0;
}
