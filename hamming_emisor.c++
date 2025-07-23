#include <iostream>
#include <vector>
#include <string>

using namespace std;

string insertarParidad(string mensaje) {
    vector<char> trama(7);

    trama[2] = mensaje[0]; 
    trama[4] = mensaje[1]; 
    trama[5] = mensaje[2]; 
    trama[6] = mensaje[3]; 
    trama[0] = ((trama[2] - '0') ^ (trama[4] - '0') ^ (trama[6] - '0')) + '0'; // P1
    trama[1] = ((trama[2] - '0') ^ (trama[5] - '0') ^ (trama[6] - '0')) + '0'; // P2
    trama[3] = ((trama[4] - '0') ^ (trama[5] - '0') ^ (trama[6] - '0')) + '0'; // P4

    string resultado(trama.begin(), trama.end());
    return resultado;
}

int main() {
    string entrada;
    cout << "Ingrese un mensaje de 4 bits (ej: 1011): ";
    cin >> entrada;

    if (entrada.size() != 4) {
        cout << "Error: El mensaje debe tener exactamente 4 bits." << endl;
        return 1;
    }

    string trama = insertarParidad(entrada);
    cout << "Trama con bits de paridad (Hamming 7,4): " << trama << endl;

    return 0;
}
