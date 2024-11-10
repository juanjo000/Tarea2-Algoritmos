#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

// Costos personalizados para cada operación
int costoInsercion(char b) { return 1; }
int costoEliminacion(char a) { return 1; }
int costoSustitucion(char a, char b) { return (a == b) ? 0 : 2; }
int costoTransposicion(char a, char b) { return 1; }

// Función para calcular la distancia de edición usando programación dinámica
int distanciaEdicionDP(const string &s1, const string &s2) {
    int m = s1.size();
    int n = s2.size();

    // Crear la tabla dp de tamaño (m+1)x(n+1)
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Llenar la primera fila y columna de la tabla dp
    for (int i = 0; i <= m; i++) dp[i][0] = i * costoEliminacion(' ');
    for (int j = 0; j <= n; j++) dp[0][j] = j * costoInsercion(' ');

    // Llenar la tabla dp de manera iterativa
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            // Cálculo del costo de sustitución
            int costoSust = dp[i - 1][j - 1] + costoSustitucion(s1[i - 1], s2[j - 1]);

            // Cálculo del costo de inserción
            int costoIns = dp[i][j - 1] + costoInsercion(s2[j - 1]);

            // Cálculo del costo de eliminación
            int costoElim = dp[i - 1][j] + costoEliminacion(s1[i - 1]);

            // Cálculo del costo de transposición (solo si es aplicable)
            int costoTrans = INT_MAX;
            if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
                costoTrans = dp[i - 2][j - 2] + costoTransposicion(s1[i - 1], s1[i - 2]);
            }

            // Encontrar el costo mínimo entre todas las operaciones
            dp[i][j] = min({costoSust, costoIns, costoElim, costoTrans});
        }
    }

    // El valor de dp[m][n] contiene la distancia de edición mínima
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
        
        int costoTotal = distanciaEdicionDP(s1, s2);
        cout << "Distancia de edición entre \"" << s1 << "\" y \"" << s2 << "\": " << costoTotal << endl;
    }

    return 0;
}
