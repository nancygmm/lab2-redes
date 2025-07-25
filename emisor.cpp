#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <bitset>
#include <iomanip>
using namespace std;

class CapaAplicacion {
public:
    struct ConfiguracionMensaje {
        string mensaje;
        double porcentajeError;
        string algoritmo;
    };
    
    static ConfiguracionMensaje solicitarMensaje() {
        ConfiguracionMensaje config;
        
        cout << "CAPA DE APLICACIÓN" << endl;
        
        cout << "\nIngrese el mensaje a enviar: ";
        getline(cin, config.mensaje);
        
        cout << "Ingrese el porcentaje de error (0-100): ";
        cin >> config.porcentajeError;
        
        cout << "\nAlgoritmos disponibles:" << endl;
        cout << "1. Hamming" << endl;
        cout << "Seleccione el algoritmo (1): ";
        int opcion;
        cin >> opcion;
        
        switch(opcion) {
            case 1:
                config.algoritmo = "hamming";
                break;
            default:
                config.algoritmo = "hamming";
        }
        
        cout << "\nConfiguración recibida:" << endl;
        cout << "  Mensaje: \"" << config.mensaje << "\"" << endl;
        cout << "  Error: " << config.porcentajeError << "%" << endl;
        cout << "  Algoritmo: " << config.algoritmo << endl;
        
        return config;
    }
};

class CapaPresentacion {
public:
    static string codificarMensaje(const string& mensaje) {
        cout << "\nCAPA DE PRESENTACIÓN" << endl;
        
        string mensajeBinario = "";
        
        for (char c : mensaje) {
            bitset<8> ascii(c);
            string binaryChar = ascii.to_string();
            mensajeBinario += binaryChar;
            
            cout << "  '" << c << "' -> " << (int)c << " -> " << binaryChar << endl;
        }
        
        cout << "\nMensaje codificado (" << mensajeBinario.length() << " bits):" << endl;
        cout << "  " << mensajeBinario << endl;
        
        return mensajeBinario;
    }
};

class CapaEnlace {
private:
    static string generarTramaHammingExtendido(const string& datos) {
        if (datos.length() != 11) {
            throw invalid_argument("Los datos deben tener exactamente 11 bits");
        }
        
        vector<char> trama(17, '0'); 
        
        int j = 0;
        for (int i = 1; i <= 15; i++) {
            if ((i & (i - 1)) != 0) { 
                trama[i] = datos[j++];
            }
        }
        
        for (int p = 1; p <= 8; p <<= 1) {
            int parity = 0;
            for (int i = 1; i <= 15; i++) {
                if (i & p) {
                    parity ^= (trama[i] - '0');
                }
            }
            trama[p] = parity + '0';
        }
        
        int totalParity = 0;
        for (int i = 1; i <= 15; i++) {
            totalParity ^= (trama[i] - '0');
        }
        trama[16] = totalParity + '0';
        
        string resultado;
        for (int i = 1; i <= 16; i++) {
            resultado += trama[i];
        }
        
        return resultado;
    }
    
public:
    static string calcularIntegridad(const string& mensajeBinario, const string& algoritmo) {
        cout << "\nCAPA DE ENLACE" << endl;
        
        string tramaCompleta = "";
        string mensajeOriginal = mensajeBinario;
        
        
        int bloqueNum = 1;
        while (!mensajeOriginal.empty()) {
            string bloque;
            
            if (mensajeOriginal.length() >= 11) {
                bloque = mensajeOriginal.substr(0, 11);
                mensajeOriginal = mensajeOriginal.substr(11);
            } else {
                bloque = mensajeOriginal;
                while (bloque.length() < 11) {
                    bloque += "0";
                }
                mensajeOriginal = "";
            }
            
            cout << "\nBloque " << bloqueNum << ":" << endl;
            cout << "  Datos (11 bits): " << bloque << endl;
            
            string tramaHamming = generarTramaHammingExtendido(bloque);
            tramaCompleta += tramaHamming;
            
            cout << "  Hamming (16 bits): " << tramaHamming << endl;
            cout << "  Posiciones paridad: ";
            for (int i = 0; i < 16; i++) {
                int pos = i + 1;
                if ((pos & (pos - 1)) == 0 || pos == 16) { 
                    cout << pos << "(" << tramaHamming[i] << ") ";
                }
            }
            cout << endl;
            
            bloqueNum++;
        }
        
        cout << "\nTrama completa con integridad (" << tramaCompleta.length() << " bits):" << endl;
        cout << "  " << tramaCompleta << endl;
        cout << "  Overhead: " << (tramaCompleta.length() - mensajeBinario.length()) 
             << " bits adicionales" << endl;
        
        return tramaCompleta;
    }
};

class CapaRuido {
public:
    static string aplicarRuido(const string& trama, double porcentajeError) {
        cout << "\nCAPA DE RUIDO" << endl;
        
        string tramaConRuido = trama;
        double probabilidad = porcentajeError / 100.0;
        
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0.0, 1.0);
        
        int erroresAplicados = 0;
        vector<int> posicionesError;
        
        cout << "\nAplicando ruido bit por bit:" << endl;
        
        for (int i = 0; i < tramaConRuido.length(); i++) {
            if (dis(gen) < probabilidad) {
                tramaConRuido[i] = (tramaConRuido[i] == '0') ? '1' : '0';
                erroresAplicados++;
                posicionesError.push_back(i + 1);
            }
        }
        
        cout << "  Bits totales: " << trama.length() << endl;
        cout << "  Errores aplicados: " << erroresAplicados << endl;
        
        if (!posicionesError.empty()) {
            cout << "  Posiciones afectadas: ";
            for (int pos : posicionesError) {
                cout << pos << " ";
            }
            cout << endl;
        }
        
        cout << "\nTrama original: " << endl;
        cout << "  " << trama << endl;
        cout << "Trama con ruido:" << endl;
        cout << "  " << tramaConRuido << endl;
                
        return tramaConRuido;
    }
};

int main() {
    try {
        cout << "" << endl;
        cout << "EMISOR" << endl;
        cout << "" << endl;
        
        auto config = CapaAplicacion::solicitarMensaje();
        
        string mensajeBinario = CapaPresentacion::codificarMensaje(config.mensaje);
        
        string tramaConIntegridad = CapaEnlace::calcularIntegridad(mensajeBinario, config.algoritmo);
        
        string tramaFinal = CapaRuido::aplicarRuido(tramaConIntegridad, config.porcentajeError);
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}