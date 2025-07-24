#include <iostream>
#include <vector>
#include <string>
using namespace std;

string generarTramaHammingExtendido(const string& datos) {
    vector<char> trama(16, '0'); 

    int j = 0;
    for (int i = 1; i <= 15; i++) {
        if ((i & (i - 1)) != 0) { 
            trama[i] = datos[j++];
        }
    }

    for (int p = 1; p <= 8; p <<= 1) {
        int parity = 0;
        for (int i = 1; i <= 15; i++) {
            if (i & p) parity ^= (trama[i] - '0');
        }
        trama[p] = parity + '0';
    }

    string resultado;
    for (int i = 1; i <= 15; i++) {
        resultado += trama[i];
    }
    return resultado;
}

bool esBinario(const string& s) {
    for (char c : s)
        if (c != '0' && c != '1') return false;
    return true;
}

int main() {
    string entrada;
    cout << "Ingrese un mensaje de 11 bits (solo 0s y 1s): ";
    cin >> entrada;

    if (entrada.size() != 11 || !esBinario(entrada)) {
        cout << "Error: Ingresa exactamente 11 bits binarios." << endl;
        return 1;
    }

    string trama = generarTramaHammingExtendido(entrada);
    cout << "Trama Hamming generada (15 bits): " << trama << endl;

    return 0;
}
