#include <iostream>
#include <string>
using namespace std;

string generarTramaHamming(string datos) {
    char d1 = datos[0];
    char d2 = datos[1];
    char d3 = datos[2];
    char d4 = datos[3];

    char p1 = ((d1 - '0') ^ (d2 - '0') ^ (d4 - '0')) + '0';
    char p2 = ((d1 - '0') ^ (d3 - '0') ^ (d4 - '0')) + '0';
    char p4 = ((d2 - '0') ^ (d3 - '0') ^ (d4 - '0')) + '0';

    string trama = "";
    trama += p1;  
    trama += p2;  
    trama += d1;  
    trama += p4;   
    trama += d2;   
    trama += d3;   
    trama += d4;   

    return trama;
}

bool esBinario(string s) {
    for (char c : s)
        if (c != '0' && c != '1') return false;
    return true;
}

int main() {
    string entrada;
    cout << "Ingrese un mensaje de 4 bits (ej: 1011): ";
    cin >> entrada;

    if (entrada.length() != 4 || !esBinario(entrada)) {
        cout << "Error: Ingresa exactamente 4 bits binarios (0 o 1)." << endl;
        return 1;
    }

    string trama = generarTramaHamming(entrada);
    cout << "Trama generada (Hamming 7,4): " << trama << endl;

    return 0;
}
